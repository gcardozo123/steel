#pragma once

#include <memory>

#include<SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


namespace Steel 
{
    static void SdlDeleteResource(SDL_Window   *r) { SDL_DestroyWindow(r); }
    static void SdlDeleteResource(SDL_Renderer *r) { SDL_DestroyRenderer(r); }
    static void SdlDeleteResource(SDL_Texture  *r) { SDL_DestroyTexture(r); }
    static void SdlDeleteResource(SDL_Surface  *r) { SDL_FreeSurface(r); }

    template <typename T>
    struct SdlResourceDeleter
    {
        void operator()(T *t) const
        {
            SdlDeleteResource(t);
        }
    };

    template <typename T>
    std::shared_ptr<T> SdlMakeSharedPtr(T *t)
    {
        return std::shared_ptr<T>(t, [](T *t) { SdlDeleteResource(t); });
    }

    template<typename T>
    using SdlUniquePtr = std::unique_ptr<T, SdlResourceDeleter<T>>;

    template <typename T>
    SdlUniquePtr<T> SdlMakeUniquePtr(T *t)
    {
        return SdlUniquePtr<T>(t);
    }

}