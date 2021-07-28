#pragma once

#include <string>

namespace Steel
{
	class GameInfo
	{
	private:
        double desired_fps;
        int update_multiplicity;
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
            int update_multiplicity = 1,
            bool is_window_resizable = false,
            std::string window_title = "Steel"
        );
        
        void SetDesiredFps(double value);
        double GetDesiredFps();

        /* Sets how many times per game loop iteration the logic should be updated.
         * 1 = 1 logic update per iteration, 2 = logic updates per iteration, so on.
         * In other words, if the game is running at 30fps with `update_multiplicity = 2`
         * the logic will still run as if the game was running at 60 fps.
        */
        void SetUpdateMultiplicity( int value );
        int GetUpdateMultiplicity() const;

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