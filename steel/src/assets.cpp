#include "assets.hpp"
#include "asserts.hpp"

namespace Steel
{

Assets::Assets()
    :
    renderer(nullptr),
    fonts()
{
}

void Assets::SetRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

TextureComponent Assets::LoadTexture(const std::string& filename)
{
    if (!renderer)
    {
        STEEL_CORE_ASSERT(false, "Missing renderer for Assets to work with");
        return {};
    }
    SDL_Surface *surface = IMG_Load(filename.c_str());
    TextureComponent res{SDL_CreateTextureFromSurface(renderer, surface), surface->w, surface->h};
    SDL_FreeSurface(surface);
    return res;
}

TextureComponent Assets::GetText(const std::string& font_filename, int size, const std::string& text, const Color& color)
{
    if (!renderer)
    {
        STEEL_CORE_ASSERT(false, "Missing renderer for Assets to work with");
        return {};
    }
    TTF_Font* font = GetFont( font_filename, size );
    if (!font)
    {
        STEEL_CORE_ASSERT(false, "Failed to load font");
        return {};
    }
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color.ToSdl() );
    TextureComponent res{SDL_CreateTextureFromSurface(renderer, surface), surface->w, surface->h};
    SDL_FreeSurface(surface);
    return res;
}

TTF_Font* Assets::GetFont(const std::string& filename, const int size)
{
    std::string font_key = filename + std::to_string( size );
    auto it = fonts.find(font_key);
    if( it != fonts.end() )
    {
        return it->second.get();
    }
    fonts[font_key] = SdlMakeUniquePtr( TTF_OpenFont(filename.c_str(), size) );
    TTF_Font* font = fonts[font_key].get();
    return font;
}

}