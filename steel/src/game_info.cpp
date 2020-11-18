#include "./game_info.hpp"

namespace Steel
{
    GameInfo::GameInfo(
        double desired_fps, 
        double time_scale, 
        int window_width, 
        int window_height, 
        bool is_window_resizable, 
        std::string window_title
    ) 
        :
        desired_fps(desired_fps),
        time_scale(time_scale),
        window_width(window_width),
        window_height(window_height),
        is_window_resizable(is_window_resizable),
        window_title(window_title)
    {}
    void GameInfo::SetDesiredFps(double value)
    {
        this->desired_fps = value;
    }
    double GameInfo::GetDesiredFps()
    {
        return this->desired_fps;
    }
    void GameInfo::SetWindowWidth(int value)
    {
        this->window_width = value;
    }
    int GameInfo::GetWindowWidth()
    {
        return this->window_width;
    }
    void GameInfo::SetWindowHeight(int value)
    {
        this->window_height = value;
    }
    int GameInfo::GetWindowHeight()
    {
        return this->window_height;
    }
    void GameInfo::SetWindowResizable(bool value)
    {
        this->is_window_resizable = value;
    }
    bool GameInfo::IsWindowResizable()
    {
        return this->is_window_resizable;
    }
    void GameInfo::SetWindowTitle(std::string value)
    {
        this->window_title = value;
    }
    std::string GameInfo::GetWindowTitle()
    {
        return this->window_title;
    }
    void GameInfo::SetTimeScale(double value)
    {
        this->time_scale = value;
    }
    double GameInfo::GetTimeScale()
    {
        return this->time_scale;
    }

}