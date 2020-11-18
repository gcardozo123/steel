#pragma once

#include <string>

namespace Steel
{
	class GameInfo
	{
	private:
        double desired_fps;
        double time_scale;
        int window_width;
        int window_height;
        bool is_window_resizable;
        std::string window_title;
        //Vec4 background_color; //rgba

	public:

        GameInfo(double desired_fps = 60,
            double time_scale = 1.0,
            int window_width = 1280,
            int window_height = 720,
            bool is_window_resizable = false,
            std::string window_title = "Steel"
        );
        
        void SetDesiredFps(double value);
        double GetDesiredFps();

        /* Controls the game's playback speed, useful for slow motion fx
        */
        void SetTimeScale(double value);
        double GetTimeScale();

        void SetWindowWidth(int value);
        int GetWindowWidth();
        
        void SetWindowHeight(int value);
        int GetWindowHeight();
        
        void SetWindowResizable(bool value);
        bool IsWindowResizable();

        void SetWindowTitle(std::string value);
        std::string GetWindowTitle();

	};
}