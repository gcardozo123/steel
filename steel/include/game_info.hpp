#pragma once

#include <string>
#include <utility>

namespace Steel
{
    enum class RenderingMode
    {
        PixelPerfect,
        Default,
    };

    struct GameInfo
	{
        double desired_fps;
        int update_multiplicity;
        int window_width;
        int window_height;
        bool is_window_resizable;
        std::string window_title;
        Color bg_color{};
        RenderingMode rendering_mode;


	    explicit GameInfo(
            RenderingMode rendering_mode = RenderingMode::PixelPerfect,
            int window_width = 1280,
            int window_height = 720,
            Color bg_color = Color(199, 199, 199, 255),
            double desired_fps = 60.0,
            int update_multiplicity = 1,
            bool is_window_resizable = false,
            std::string window_title = "Steel"
        ) :
        rendering_mode(rendering_mode),
        window_width(window_width),
        window_height(window_height),
        bg_color(std::move(bg_color)),
        desired_fps(desired_fps),
        update_multiplicity(update_multiplicity),
        is_window_resizable(is_window_resizable),
        window_title(std::move(window_title))
        {}
	};
}