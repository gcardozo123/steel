#pragma once

#include <memory>

#include<SDL.h>
#include <SDL_image.h>

namespace Steel 
{	
    static void SdlDeleteResource(SDL_Window   *r) { SDL_DestroyWindow(r); }
    static void SdlDeleteResource(SDL_Renderer *r) { SDL_DestroyRenderer(r); }
    static void SdlDeleteResource(SDL_Texture  *r) { SDL_DestroyTexture(r); }
    static void SdlDeleteResource(SDL_Surface  *r) { SDL_FreeSurface(r); }

    template <typename T>
    std::shared_ptr<T> SdlSharedPtr(T *t)
    {
        return std::shared_ptr<T>(t, [](T *t) { SdlDeleteResource(t); });
    }
    
    template <typename T>
    std::unique_ptr<T> SdlUniquePtr(T *t)
    {
        return std::unique_ptr<T>(t, [](T *t) { SdlDeleteResource(t); });
    }

    struct SteelSdlWindowDestroyer
    {
        void operator()(SDL_Window* w) const
        {
            SDL_DestroyWindow(w);
        }
    };


}