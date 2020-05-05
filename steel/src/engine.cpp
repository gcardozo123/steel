#include "engine.hpp"
#include "log.hpp"

#include <iostream>

namespace Steel
{
	Engine::Engine()
		: 
		is_running(false), 
		game_info(CreateSharedPtr<GameInfo>()),
		renderer(CreateSharedPtr<Renderer>())
	{
		if (!Log::GetCoreLogger())
			Log::Init();
	}

	void Engine::Start(std::string window_title, int window_width, int window_height, bool is_window_resizable)
	{
		renderer->Initialize(window_title, window_width, window_height, is_window_resizable);
		is_running = true;
		RunMainLoop();
	}

	void Engine::Stop()
	{
		is_running = false;
	}

	void Engine::ProcessInput()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) 
		{
			case SDL_QUIT: 
			{
				Stop();
				break;
			}
			case SDL_KEYDOWN: 
			{
				if (event.key.keysym.sym == SDLK_ESCAPE) 
				{
					Stop();
				}
			}
			default: 
			{
				break;
			}
		}
	}
	
	void Engine::RunMainLoop()
	{
		double update_rate = renderer->GetDesiredFps();
		double update_multiplicity = renderer->GetTimeScale();
		bool unlock_framerate = false;

		//compute how many ticks one update should be
		double fixed_deltatime = 1.0 / update_rate;
		int64_t desired_frametime = SDL_GetPerformanceFrequency() / update_rate;

		//these are to snap deltaTime to vsync values if it's close enough
		int64_t vsync_maxerror = SDL_GetPerformanceFrequency() * .0002;
		int64_t time_60hz = SDL_GetPerformanceFrequency() / 60; //since this is about snapping to common vsync values
		int64_t snap_frequencies[] = { 
			time_60hz,        //60fps
			time_60hz * 2,      //30fps
			time_60hz * 3,      //20fps
			time_60hz * 4,      //15fps
			(time_60hz + 1) / 2,  //120fps //120hz, 240hz, or higher need to round up, so that adding 120hz twice guaranteed is at least the same as adding time_60hz once
			// (time_60hz+2)/3,  //180fps //that's where the +1 and +2 come from in those equations
			// (time_60hz+3)/4,  //240fps //I do not want to snap to anything higher than 120 in my engine, but I left the math in here anyway
		};

		//this is for delta time averaging
		//I know you can and should use a ring buffer for this, but I didn't want to include dependencies in this sample code
		const int time_history_count = 4;
		int64_t time_averager[time_history_count] = { desired_frametime, desired_frametime, desired_frametime, desired_frametime };

		//these are stored in my Application class and are not local variables in production code
		bool resync = true;
		int64_t prev_frame_time = SDL_GetPerformanceCounter();
		int64_t frame_accumulator = 0;

		while (is_running)
		{	
			//frame timer
			int64_t current_frame_time = SDL_GetPerformanceCounter();
			int64_t delta_time = current_frame_time - prev_frame_time;
			prev_frame_time = current_frame_time;
			//STEEL_INFO("update: {0}", 1.0 / desired_frametime * 1000 * 10000);

			//handle unexpected timer anomalies (overflow, extra slow frames, etc)
			//ignore extra-slow frames (this is 8/60 (7.5fps))
			if (delta_time > desired_frametime * 8) 
			{ 
				delta_time = desired_frametime;
			}
			// If delta time is less than 0, that means that the system timer wrapped around (overflow)
			if (delta_time < 0) 
			{
				delta_time = 0;
			}

			//vsync time snapping
			for (int64_t snap : snap_frequencies) 
			{
				if (std::abs(delta_time - snap) < vsync_maxerror) 
				{
					delta_time = snap;
					break;
				}
			}

			//delta time averaging
			for (int i = 0; i < time_history_count - 1; i++) 
			{
				time_averager[i] = time_averager[i + 1];
			}
			time_averager[time_history_count - 1] = delta_time;
			delta_time = 0;
			for (int i = 0; i < time_history_count; i++) 
			{
				delta_time += time_averager[i];
			}
			delta_time /= time_history_count;

			//add to the accumulator
			frame_accumulator += delta_time;

			//spiral of death protection
			//If your game cannot *update* at 60hz, you end up in a spiral of doom where your 
			//game can never catch up to where it should be, and so it will do more and more 
			//updates every time until it eventually just freezes. Let's cap the accumulator to 
			//a maximum (8/60 (7.5fps)) and it should prevent that issue.This will not be a fun 
			//experience for whoever is trying to play the game, but at least it won’t freeze.
			if (frame_accumulator > desired_frametime * 8) 
			{
				resync = true;
			}

			//timer resync if requested
			//In my engine I have a manual callback I can use to “resync” my timer code(set the 
			//accumulator to 0 and delta time to 1 / 60 the next time through the loop), which 
			//I do after loading a level or swapping scenes.You need this because you typically 
			//don’t want the game to start each level by immediately trying to make up the time it spent loading.
			if (resync) 
			{
				frame_accumulator = 0;
				delta_time = desired_frametime;
				resync = false;
			}

			// process system events
			//ProcessEvents();
			ProcessInput();

			if (unlock_framerate) 
			{   //UNLOCKED FRAMERATE, INTERPOLATION ENABLED
				int64_t consumed_delta_time = delta_time;

				while (frame_accumulator >= desired_frametime) 
				{
					//game.fixed_update(fixed_deltatime);
					if (consumed_delta_time > desired_frametime) 
					{   //cap variable update's dt to not be larger than fixed update, and interleave it (so game state can always get animation frames it needs)
						//game.variable_update(fixed_deltatime);
						consumed_delta_time -= desired_frametime;
					}
					frame_accumulator -= desired_frametime;
				}
				//game.variable_update((double)consumed_deltaTime / SDL_GetPerformanceFrequency());
				//game.render((double)frame_accumulator / desired_frametime);
				//display(); //swap buffers
			}
			else
			{   //LOCKED FRAMERATE, NO INTERPOLATION
				while (frame_accumulator >= desired_frametime * update_multiplicity) 
				{
					for (int i = 0; i < update_multiplicity; i++) 
					{
						//SDL_Delay(fixed_deltatime / 2); //TODO: remove this (it's just a placeholder while I don't have actual update methods)
						//game.fixed_update(fixed_deltatime);
						//game.variable_update(fixed_deltatime);
						frame_accumulator -= desired_frametime;
					}
				}
				renderer.get()->Render();
				//game.render(1.0);
				//display(); //swap buffers
			}
		}
	}
}
