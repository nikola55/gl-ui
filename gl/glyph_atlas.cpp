#include "glyph_atlas.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <ft2build.h>
#include <cassert>

#include FT_FREETYPE_H

using std::runtime_error;
using std::map;
using std::string;
using std::pair;

using gl::GlyphAtlas;
using gl::Texture;

using ui::glyph_info;
using ui::point;
using ui::uint;
using ui::vec2;
using ui::shared_ptr;

class FT_Lib {
public:
    FT_Lib() : m_Lib(0), m_OK(true) {
        if(FT_Init_FreeType(&m_Lib)!=0) {
            m_OK = false;
            m_Lib = 0;
        }
    }

    ~FT_Lib() {
        FT_Done_FreeType(m_Lib);
    }

    FT_Library lib() {
        return m_Lib;
    }

    bool ok() const {
        return m_OK;
    }

private:

    FT_Library m_Lib;
    bool m_OK;

};

static FT_Lib gs_FTLib;

#define MAX_GLYPH_ATLAS_WIDTH  2048
#define MAX_GLYPH_ATLAS_HEIGHT 2048

GlyphAtlas::GlyphAtlas(const std::string &font, uint size) : m_textureId(0) {

    if(!gs_FTLib.ok()) {
        throw runtime_error("cannot initialize freetype");
    }
    FT_Face face;
    if(FT_New_Face(gs_FTLib.lib(), font.c_str(), 0, &face) != 0) {
        throw runtime_error("cannot load "+font);
    }

    FT_Set_Pixel_Sizes(face, 0, size);
    FT_GlyphSlot g = face->glyph;

    m_width = 0;
    m_height = 0;
    GLuint roww = 0;
    GLuint rowh = 0;
    // ASCII and Cyrilic Basic for now
    for(uint i = 32 ; i < 1280 ; i++) {
        if(i==128) {
            i = 1024;
        }
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)!=0) {
            FT_Done_Face(face);
            std::stringstream ss;
            ss << i;
            throw runtime_error("cannot load char " + ss.str());
            continue;
        }
        FT_Bitmap &bitmap = g->bitmap;
        if(roww + bitmap.width+1 > MAX_GLYPH_ATLAS_WIDTH) {
            m_width = std::max(roww, m_width);
            m_height += rowh;
            roww = 0;
            rowh = 0;
        }
        roww += bitmap.width+1;
        rowh = std::max(rowh, GLuint(g->bitmap.rows));
    }

    m_width = std::max(roww, m_width);
    m_height += rowh + 1;

    glGenTextures(1, &m_textureId);
    if(glGetError() != GL_NO_ERROR) {
        FT_Done_Face(face);
        m_textureId = 0;
        throw runtime_error("cannot generate texture");
    }
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, GLuint(m_width), GLuint(m_height), 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
    GLenum err = glGetError();
    if(err != GL_NO_ERROR) {
        glDeleteTextures(1, &m_textureId);
        FT_Done_Face(face);
        m_textureId = 0;
        throw runtime_error("cannot create texture");
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLuint oy = 0, ox = 0;
    roww = 0;
    rowh = 0;
    for(uint i = 32 ; i < 1280 ; i++) {
        if(i==128) {
            i = 1024;
        }
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)!=0) {
            glDeleteTextures(1, &m_textureId);
            FT_Done_Face(face);
            m_textureId = 0;
            std::stringstream ss;
            ss << i;
            throw runtime_error("cannot load char " + ss.str());
        }

        FT_Bitmap &bitmap = g->bitmap;

        glyph_info gy = {
            { (uint)g->advance.x>>6, (uint)g->advance.y>>6 },
            (uint)bitmap.width, (uint)bitmap.rows,
            (uint)g->bitmap_left, (uint)g->bitmap_top
        };

        if(ox + bitmap.width + 1 > MAX_GLYPH_ATLAS_WIDTH) {
            oy += rowh;
            rowh = 0;
            ox = 0;
        }
        vec2<float> loc = {
            float(ox) / m_width, float(oy) / m_height
        };

        glTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, gy.width, gy.height, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap.buffer);

        typedef pair< uint, pair< glyph_info, vec2< float > > > pair_type;
        m_glyphInfo.insert(pair_type(i, pair< glyph_info, vec2<float> >(gy,loc)));

        rowh = std::max(rowh, GLuint(bitmap.rows));
        ox += bitmap.width + 1;

    }

    FT_Done_Face(face);
}

#define FONT_LOCATION "/home/nikola/Qt_Creator_Projects/UI/res/FreeSans.ttf"

map<uint, shared_ptr<GlyphAtlas> > GlyphAtlas::s_preloadedBySize;

shared_ptr< GlyphAtlas > GlyphAtlas::forSize(uint sz) {
    map<uint, shared_ptr<GlyphAtlas> >::iterator iter = s_preloadedBySize.find(sz);
    if(iter == s_preloadedBySize.end()) {
        // unhardcode
        shared_ptr<GlyphAtlas> atlas = new GlyphAtlas(FONT_LOCATION, sz);
        pair<uint, shared_ptr<GlyphAtlas> > insert(sz, atlas);
        pair<map<uint, shared_ptr<GlyphAtlas> >::iterator,bool> res = s_preloadedBySize.insert(insert);
        iter = res.first;
    }
    return iter->second;
}

GlyphAtlas::~GlyphAtlas() {
    if(loaded()) {
        glDeleteTextures(1, &m_textureId);
    }
}
