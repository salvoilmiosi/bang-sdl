#ifndef __LOADING_H__
#define __LOADING_H__

#include "scene_base.h"

class loading_scene : public scene_base {
public:
    loading_scene(client_manager *parent, const std::string &text);

    void refresh_layout() override;

    void tick(duration_type time_elapsed) override;
    void render(sdl::renderer &renderer) override;

private:
    widgets::stattext m_loading_text;
    widgets::button m_cancel_btn;

    sdl::rect m_loading_rect;
    float m_loading_rotation = 0.f;
};

#endif