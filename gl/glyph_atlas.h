#ifndef GLYPH_ATLAS_H
#define GLYPH_ATLAS_H
#include "ui_common.h"
#include <map>
#include <GLES2/gl2.h>
#include "texture.h"

namespace gl {

class GlyphAtlas {

    static std::map< ui::uint, ui::shared_ptr<GlyphAtlas> > s_PreloadedBySize;

private:

    GlyphAtlas(const GlyphAtlas &) { }

    GlyphAtlas& operator=(const GlyphAtlas &) { }

public:

    GlyphAtlas(const std::string &font, ui::uint size);

    ~GlyphAtlas();

    ui::glyph_info& info(ui::uint ch) {
        std::map< ui::uint, std::pair< ui::glyph_info, ui::vec2< float > > >::iterator glyphInfo = m_GlyphInfo.find(ch);
        if(glyphInfo != m_GlyphInfo.end()) {
            return glyphInfo->second.first;
        } else {
            static ui::glyph_info defaultInfo(ui::point(), 0, 0, 0, 0);
            return defaultInfo;
        }
    }

    ui::vec2<float>& location(ui::uint ch) {
        std::map< ui::uint, std::pair< ui::glyph_info, ui::vec2< float > > >::iterator glyphInfo = m_GlyphInfo.find(ch);
        if(glyphInfo != m_GlyphInfo.end()) {
            return glyphInfo->second.second;
        } else {
            static ui::vec2<float> defaultLocation = {0,0};
            return defaultLocation;
        }
    }

    GLuint textureId() {
        return m_TextureId;
    }

    bool loaded() const {
        return m_TextureId != 0;
    }

    float width() const { return m_Width; }

    float height() const { return m_Height; }

    static ui::shared_ptr< GlyphAtlas > forSize(ui::uint sz);

private:
    std::map< ui::uint, std::pair< ui::glyph_info, ui::vec2< float > > > m_GlyphInfo;
    float m_Width;
    float m_Height;
    GLuint m_TextureId;

};

}

#endif // GLYPH_ATLAS_H
