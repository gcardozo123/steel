#include "color.hpp"
#include "game_info.hpp"

namespace Steel
{
    GameInfo::GameInfo(
        int window_width,
        int window_height,
        Steel::Color background_color,
        double desired_fps,
        int update_multiplicity,
        bool is_window_resizable,
        std::string window_title
    ) 
        :
        desired_fps(desired_fps),
        update_multiplicity( update_multiplicity ),
        window_width(window_width),
        window_height(window_height),
        is_window_resizable(is_window_resizable),
        window_title(window_title),
        background_color(background_color)
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
    void GameInfo::SetUpdateMultiplicity( int value )
    {
        this->update_multiplicity = value;
    }
    int GameInfo::GetUpdateMultiplicity() const
    {
        return this->update_multiplicity;
    }

}