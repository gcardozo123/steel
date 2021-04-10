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
        Steel::Color background_color; //rgba

	public:
        GameInfo() = default;
	    GameInfo(
            int window_width,
            int window_height,
            Steel::Color background_color,
            double desired_fps = 60.0,
            double time_scale = 1.0,
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

        void SetBackgroundColor(Steel::Color& color) { background_color = color; }
        Steel::Color GetBackgroundColor() { return background_color; }

	};
}