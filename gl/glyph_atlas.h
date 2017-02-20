#ifndef GLYPH_ATLAS_H
#define GLYPH_ATLAS_H
#include "ui_common.h"
#include <map>
#include <GLES2/gl2.h>
#include "texture.h"

namespace gl {

class GlyphAtlas {

    static std::map< ui::uint, ui::shared_ptr<GlyphAtlas> > s_preloadedBySize;

private:

    GlyphAtlas(const GlyphAtlas &);

    GlyphAtlas& operator=(const GlyphAtlas &);

public:

    GlyphAtlas(const std::string &font, ui::uint size);

    ~GlyphAtlas();

    ui::glyph_info& info(ui::uint ch) {
        std::map< ui::uint, std::pair< ui::glyph_info, ui::vec2< float > > >::iterator glyphInfo = m_glyphInfo.find(ch);
        if(glyphInfo != m_glyphInfo.end()) {
            return glyphInfo->second.first;
        } else {
            static ui::glyph_info defaultInfo(ui::point(), 0, 0, 0, 0);
            return defaultInfo;
        }
    }

    ui::vec2<float>& location(ui::uint ch) {
        std::map< ui::uint, std::pair< ui::glyph_info, ui::vec2< float > > >::iterator glyphInfo = m_glyphInfo.find(ch);
        if(glyphInfo != m_glyphInfo.end()) {
            return glyphInfo->second.second;
        } else {
            static ui::vec2<float> defaultLocation = {0,0};
            return defaultLocation;
        }
    }

    GLuint textureId() {
        return m_textureId;
    }

    bool loaded() const {
        return m_textureId != 0;
    }

    float width() const { return m_width; }

    float height() const { return m_height; }

    static ui::shared_ptr< GlyphAtlas > forSize(ui::uint sz);

private:
    std::map< ui::uint, std::pair< ui::glyph_info, ui::vec2< float > > > m_glyphInfo;
    GLuint m_width;
    GLuint m_height;
    GLuint m_textureId;

};

}

#endif // GLYPH_ATLAS_H
