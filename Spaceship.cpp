#include "Spaceship.h"
#include "GameWindow.h"
#include <FL/fl_draw.H>

const double Spaceship::max_speed = 6;
const double Spaceship::accel_rate = 1.0;
const double Spaceship::deccel_rate = 0.1;
const double Spaceship::rotation_rate = 10;
const double Spaceship::bullet_speed = 8;

Spaceship::Spaceship(GameWindow* game, Vec2 pos, Vec2 velocity) :
    SpaceObject(game, pos, velocity, 7.0), orientation(90.0), accelerating(false), rotating_left(false), rotating_right(false),
    shooting(false) {
    
}

void Spaceship::updatePos() {
    if(accelerating) {
        accelerate();
    } else {
        //deccelerate
        if(orientation>=0 && orientation<=90) {
            //quadrant 1
            if(velocity.magnitude() > 0) {
                //Vec2 unit = velocity;
                Vec2 unit = Vec2::fromAngleDeg(orientation);
                unit *= deccel_rate;
                unit *= -1;
                Vec2 newSpeed = velocity + unit;
                if(newSpeed.x < 0 || newSpeed.y > 0) {
                    velocity = unit * 0;
                } else {
                    velocity = newSpeed;
                }
            }
        } else if(orientation>=90 && orientation <=180) {
            //quadrant 2
            if(velocity.magnitude() > 0) {
                //Vec2 unit = velocity;
                Vec2 unit = Vec2::fromAngleDeg(orientation);
                unit *= deccel_rate;
                unit *= -1;
                Vec2 newSpeed = velocity + unit;
                if(newSpeed.x > 0 || newSpeed.y > 0) {
                    velocity = unit * 0;
                } else {
                    velocity = newSpeed;
                }
            }
        } else if(orientation>=180 && orientation<=270) {
            //quadrant 3
            if(velocity.magnitude() > 0) {
                //Vec2 unit = velocity;
                Vec2 unit = Vec2::fromAngleDeg(orientation);
                unit *= deccel_rate;
                unit *= -1;
                Vec2 newSpeed = velocity + unit;
                if(newSpeed.x > 0 || newSpeed.y < 0) {
                    velocity = unit * 0;
                } else {
                    velocity = newSpeed;
                }
            }
        } else if(orientation>=270 && orientation<=360) {
            //quadrant 4
            if(velocity.magnitude() > 0) {
                //Vec2 unit = velocity;
                Vec2 unit = Vec2::fromAngleDeg(orientation);
                unit *= deccel_rate;
                unit *= -1;
                Vec2 newSpeed = velocity + unit;
                if(newSpeed.x < 0 || newSpeed.y < 0) {
                    velocity = unit * 0; 
                } else {
                    velocity = newSpeed;
                }
            }
        }
    }
    pos += velocity;
//    cout << "Velocity <" << velocity.x << ", " << velocity.y << ">" << " Orientation: " << orientation << endl;
    
    if(rotating_left) {
        rotateLeft();
    }
    
    if(rotating_right) {
        rotateRight();
    }
    
    if(shooting) {
        shoot();
    }
    
    if(pos.x<0 || pos.x>800 || pos.y<0 || pos.y>600) {
        pos %= Vec2(800, 600);
    }

}

void Spaceship::setAccelerating(bool status) {
    accelerating = status;
}

void Spaceship::setRotatingLeft(bool status) {
    rotating_left = status;
}

void Spaceship::setRotatingRight(bool status) {
    rotating_right = status;
}

void Spaceship::setShooting(bool status) {
    shooting = status;
}

void Spaceship::accelerate() {
    if(velocity.magnitude() < max_speed || rotating_left || rotating_right) {
        //cout << "move!" << endl;
        //Vec2 unit = velocity;
        Vec2 unit = Vec2::fromAngleDeg(orientation);
        unit *= accel_rate;
        Vec2 newSpeed = velocity + unit;
        if(newSpeed.magnitude() > max_speed) {
            velocity = unit * max_speed;
        } else {
            velocity += unit;
        }
     }
}

void Spaceship::rotateLeft() {
    orientation += rotation_rate;
    if(orientation > 360) {
        orientation -= 360;
    }
}

void Spaceship::rotateRight() {
    orientation -= rotation_rate;
    if(orientation < 0) {
        orientation += 360;
    }
}

void Spaceship::shoot() {
    Vec2 bullSpeed = Vec2::fromAngleDeg(orientation);
    bullSpeed *= bullet_speed;
    game->addBullet(pos, bullSpeed);
}

void Spaceship::draw() {
//    accelerating = true;
    if(accelerating) {
        fl_color(FL_WHITE);
        fl_push_matrix();
        fl_translate(pos.x, pos.y);
        fl_rotate(orientation-135);
        fl_begin_loop();
        
        fl_vertex(0.0, 0.0);
        fl_vertex(17.0, 0.0);
        fl_vertex(0.0, 17.0);
        
        fl_end_loop();
        
        fl_begin_line();
        
        fl_vertex(17.0, 0.0);
        fl_vertex(21.0, 0.0);
        
        fl_end_line();
        
        fl_begin_line();
        
        fl_vertex(0.0, 17.0);
        fl_vertex(0.0, 21.0);
        
        fl_end_line();
        
        fl_begin_line();
        
        fl_vertex(0.0, 17.0);
        fl_vertex(17.0, 17.0);
        
        fl_end_line();
        
        fl_begin_line();
        
        fl_vertex(17.0, 0.0);
        fl_vertex(17.0, 17.0);
        
        fl_end_line();
        
        fl_pop_matrix();
    } else {
        fl_color(FL_WHITE);
        fl_push_matrix();
        fl_translate(pos.x, pos.y);
        fl_rotate(orientation-135);
        
        fl_begin_loop();
        
        fl_vertex(0.0, 0.0);
        fl_vertex(17.0, 0.0);
        fl_vertex(0.0, 17.0);
        
        fl_end_loop();
        
        fl_begin_line();
        
        fl_vertex(17.0, 0.0);
        fl_vertex(21.0, 0.0);
        
        fl_end_line();
        
        fl_begin_line();
        
        fl_vertex(0.0, 17.0);
        fl_vertex(0.0, 21.0);
        
        fl_end_line();
        
        fl_pop_matrix();
    }
}
