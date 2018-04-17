#include "SpaceObject.h"


SpaceObject::SpaceObject(GameWindow* game, Vec2 pos, Vec2 velocity, double radius) :
    Fl_Widget(1, 1, 0, 0), pos(pos), velocity(velocity), collision_radius(radius), game(game) {
    
}

Vec2 SpaceObject::getPos() const {
    return pos;
}

void SpaceObject::updatePos() {
    pos += velocity;
    //add wrap around feature
    if(pos.x<0 || pos.x>800 || pos.y<0 || pos.y>600) {
        pos %= Vec2(800, 600);
    }
}

bool SpaceObject::checkCollision(SpaceObject* obj) {
    if(Vec2::dist(this->pos, obj->pos) <= (this->collision_radius + obj->collision_radius) )
       return true;
    else
       return false;
}
