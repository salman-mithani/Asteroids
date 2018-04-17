#include "Asteroid.h"
#include <FL/fl_draw.H>

Asteroid::Asteroid(GameWindow* game, Vec2 pos, Vec2 velocity) : SpaceObject(game, pos, velocity, 45.0) {
    
}

void Asteroid::draw() {
    fl_color(FL_WHITE);
    fl_push_matrix();
    fl_translate(pos.x, pos.y);
//    fl_rotate(45.0);
    fl_begin_loop();
    
//    fl_vertex(0.0, 0.0);
//    fl_vertex(25.0, 7.0);
//    fl_vertex(33.0, -30.0);
//    fl_vertex(75.0, -12.0);
//    fl_vertex(78.0, 10.0);
//    fl_vertex(55.0, 35.0);
//    fl_vertex(40.0, 20.0);
//    fl_vertex(25.0, 25.0);
//    fl_vertex(10.0, 10.0);
    
    fl_vertex(0.0, 0.0);
    fl_vertex(0.0, -40.0);
    fl_vertex(30.0, -25.0);
    fl_vertex(40.0, 0.0);
    fl_vertex(25.0, 25.0);
    fl_vertex(25.0, 30.0);
    fl_vertex(0.0, 40.0);
    fl_vertex(-35.0, 30.0);
    fl_vertex(-40.0, 0.0);
    fl_vertex(-35.0, -25.0);
    fl_vertex(-25.0, -20.0);
    fl_vertex(-17.0, -35.0);
    
    fl_end_loop();
    fl_pop_matrix();
}
