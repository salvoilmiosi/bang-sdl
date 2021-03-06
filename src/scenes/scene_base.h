#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "game/messages.h"

#include "sdl_wrap.h"

#include "../widgets/button.h"
#include "../widgets/textbox.h"

class client_manager;

class scene_base {
public:
    scene_base(client_manager *parent) : parent(parent) {}
    virtual ~scene_base() {}
    
    virtual void refresh_layout() = 0;

    virtual void tick(duration_type time_elapsed) {}
    
    virtual void render(sdl::renderer &renderer) = 0;
    
    virtual void handle_event(const sdl::event &event) {}

protected:
    client_manager *parent;
};

#endif