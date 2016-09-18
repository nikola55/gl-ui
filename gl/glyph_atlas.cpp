#include "glyph_atlas.h"
#include <algorithm>
#include <stdexcept>
#include <ft2build.h>
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

static FT_Library ftLib;

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

GlyphAtlas::GlyphAtlas(const std::string &font, uint size) : m_TextureId(0) {

    if(!gs_FTLib.ok()) {
        throw runtime_error("cannot initialize freetype");
    }
    FT_Face face;
    if(FT_New_Face(gs_FTLib.lib(), font.c_str(), 0, &face) != 0) {
        throw runtime_error("cannot load "+font);
    }

    FT_Set_Pixel_Sizes(face, 0, size);
    FT_GlyphSlot g = face->glyph;

    m_Width = 0;
    m_Height = 0;
    for(uint i = 32 ; i < 128 ; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)!=0) {
            FT_Done_Face(face);
            char m[2] = { char(i), 0 };
            throw runtime_error("cannot load char " + string(m));
        }
        FT_Bitmap &bitmap = g->bitmap;
        m_Width += bitmap.width+1;
        m_Height = std::max(m_Height, float(g->bitmap.rows));
    }

    glGenTextures(1, &m_TextureId);
    if(glGetError() != GL_NO_ERROR) {
        FT_Done_Face(face);
        m_TextureId = 0;
        throw runtime_error("cannot generate texture");
    }
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, GLuint(m_Width), GLuint(m_Height), 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
    GLenum err = glGetError();
    if(err != GL_NO_ERROR) {
        glDeleteTextures(1, &m_TextureId);
        FT_Done_Face(face);
        m_TextureId = 0;
        throw runtime_error("cannot create texture");
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    float ox = 0;
    float oy = 0;

    for(uint i = 32 ; i < 128 ; i++) {

        if (FT_Load_Char(face, i, FT_LOAD_RENDER)!=0) {
            glDeleteTextures(1, &m_TextureId);
            FT_Done_Face(face);
            m_TextureId = 0;
            char m[2] = { char(i), 0 };
            throw runtime_error("cannot load char " + string(m));
        }

        FT_Bitmap &bitmap = g->bitmap;

        glyph_info gy = {
            { g->advance.x>>6, g->advance.y>>6 },
            bitmap.width, bitmap.rows,
            g->bitmap_left, g->bitmap_top
        };
        vec2<float> loc = {
            ox / m_Width, 0
        };

        glTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, gy.width, gy.height, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap.buffer);

        typedef pair< uint, pair< glyph_info, vec2< float > > > pair_type;
        m_GlyphInfo.insert(pair_type(i, pair< glyph_info, vec2<float> >(gy,loc)));

        ox+= bitmap.width+1;

    }

    FT_Done_Face(face);
}

map<uint, shared_ptr<GlyphAtlas> > GlyphAtlas::s_PreloadedBySize;

shared_ptr< GlyphAtlas > GlyphAtlas::forSize(uint sz) {
    map<uint, shared_ptr<GlyphAtlas> >::iterator iter = s_PreloadedBySize.find(sz);
    if(iter == s_PreloadedBySize.end()) {
        // unhardcode
        shared_ptr<GlyphAtlas> atlas = new GlyphAtlas("/home/nikola/Qt_Creator_Projects/UI/res/SourceCodePro-Regular.ttf", sz);
        pair<uint, shared_ptr<GlyphAtlas> > insert(sz, atlas);
        pair<map<uint, shared_ptr<GlyphAtlas> >::iterator,bool> res = s_PreloadedBySize.insert(insert);
        iter = res.first;
    }
    return iter->second;
}

GlyphAtlas::~GlyphAtlas() {
    if(loaded()) {
        glDeleteTextures(1, &m_TextureId);
    }
}