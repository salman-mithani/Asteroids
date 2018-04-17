#include "Bullet.h"
#include "GameWindow.h"
#include <FL/fl_draw.H>

Bullet::Bullet(GameWindow* game, Vec2 pos, Vec2 velocity) : SpaceObject(game, pos, velocity, 0.0) {
    
}

void Bullet::updatePos() {
    pos += velocity;
}

bool Bullet::checkOutOfBounds() {
    if(pos.x<0 || pos.x>800 || pos.y<0 || pos.y>600) {
        return true;
    }
    return false;
}

void Bullet::draw() {
    fl_color(FL_WHITE);
    fl_rectf(pos.x,pos.y,4,4);
}
