
#include <string>

#include <catch2/catch.hpp>
#include <SDL.h>
#include <SDL_image.h>

#include "steel.hpp"

using namespace Steel;

TEST_CASE("test_game", "[test_game]") 
{
	Game *game = new Steel::Game();
	game->Init("Steel", 1280, 720, true);
    auto texture = game->assets->LoadTexture(std::string("game_assets/ghost1.png"));
    auto actor = game->actors->CreateActor();
    actor->GetComponent<TextureComponent>().lock()->SetTextureAsset(texture);
    game->Run();
    game->Quit();
    delete game;
    
	// smoke test: make sure calling `Start` again won't break anything
    //game->Start("Steel", 1366, 768, true);
	// simulate that "esc" was pressed to close the window:
	/*SDL_Event sdlevent;
	sdlevent.type = SDL_KEYDOWN;
	sdlevent.key.keysym.sym = SDLK_ESCAPE;
	SDL_PushEvent(&sdlevent);*/
}

//TEST_CASE("test_load_texture_example", "[test_game]")
//{
//    int SHAPE_SIZE = 50;
//    SDL_Window* Main_Window;
//    SDL_Renderer* Main_Renderer;
//    SDL_Surface* Loading_Surf;
//    SDL_Texture* Background_Tx;
//    SDL_Texture* BlueShapes;
//
//    /* Rectangles for drawing which will specify source (inside the texture)
//    and target (on the screen) for rendering our textures. */
//    SDL_Rect SrcR;
//    SDL_Rect DestR;
//
//    SrcR.x = 0;
//    SrcR.y = 0;
//    SrcR.w = SHAPE_SIZE;
//    SrcR.h = SHAPE_SIZE;
//
//    DestR.x = 640 / 2 - SHAPE_SIZE / 2;
//    DestR.y = 580 / 2 - SHAPE_SIZE / 2;
//    DestR.w = SHAPE_SIZE;
//    DestR.h = SHAPE_SIZE;
//
//
//    /* Before we can render anything, we need a window and a renderer */
//    Main_Window = SDL_CreateWindow("SDL_RenderCopy Example",
//        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 580, 0);
//    Main_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);
//
//    /* The loading of the background texture. Since SDL_LoadBMP() returns
//    a surface, we convert it to a texture afterwards for fast accelerated
//    blitting. */
//    Loading_Surf = SDL_LoadBMP("game_assets/dog.bmp");
//    REQUIRE(Loading_Surf != NULL);
//    Background_Tx = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
//    SDL_FreeSurface(Loading_Surf); /* we got the texture now -> free surface */
//
//    /* Load an additional texture */
//    Loading_Surf = SDL_LoadBMP("game_assets/dog.bmp");
//    REQUIRE(Loading_Surf != NULL);
//    BlueShapes = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
//    SDL_FreeSurface(Loading_Surf);
//
//    /* now onto the fun part.
//    This will render a rotating selection of the blue shapes
//    in the middle of the screen */
//    int i;
//    int n;
//    for (i = 0; i < 2; ++i) {
//        for (n = 0; n < 4; ++n) {
//            SrcR.x = SHAPE_SIZE * (n % 2);
//            if (n > 1) {
//                SrcR.y = SHAPE_SIZE;
//            }
//            else {
//                SrcR.y = 0;
//            }
//
//            /* render background, whereas NULL for source and destination
//            rectangles just means "use the default" */
//            SDL_RenderCopy(Main_Renderer, Background_Tx, NULL, NULL);
//
//            /* render the current animation step of our shape */
//            SDL_RenderCopy(Main_Renderer, BlueShapes, &SrcR, &DestR);
//            SDL_RenderPresent(Main_Renderer);
//            SDL_Delay(500);
//        }
//    }
//
//
//    /* The renderer works pretty much like a big canvas:
//    when you RenderCopy() you are adding paint, each time adding it
//    on top.
//    You can change how it blends with the stuff that
//    the new data goes over.
//    When your 'picture' is complete, you show it
//    by using SDL_RenderPresent(). */
//
//    /* SDL 1.2 hint: If you're stuck on the whole renderer idea coming
//    from 1.2 surfaces and blitting, think of the renderer as your
//    main surface, and SDL_RenderCopy() as the blit function to that main
//    surface, with SDL_RenderPresent() as the old SDL_Flip() function.*/
//
//    SDL_DestroyTexture(BlueShapes);
//    SDL_DestroyTexture(Background_Tx);
//    SDL_DestroyRenderer(Main_Renderer);
//    SDL_DestroyWindow(Main_Window);
//    SDL_Quit();
//}


