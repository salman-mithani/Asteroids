#include <FL/Fl.H>
#include "GameWindow.h"
#include <ctime>
//#include "Asteroid.h"
#include <iostream>
using namespace std;

const int GameWindow::max_asteroids = 6;
const int GameWindow::spawn_interval = 10;
const double GameWindow::asteroid_speed = 3;

GameWindow::GameWindow(int w, int h) : Fl_Window(w, h), cycles_survived(0), asteroids_hit(0) {
    this->color(0);
    ship = new Spaceship(this, Vec2(w/2, h/2), Vec2(0,0));
      
    for(int i = 0; i<(max_asteroids/2); i++) {
        spawnAsteroid();
    }
    
    //TESTING DRAWING A SINGLE ASTEROID
//    Asteroid* box = new Asteroid(this, Vec2(w/2, h/2), Vec2(0,0));
//    box->draw();
    
    this->end();
    this->show();
    
    Fl::add_timeout(0.033, timer_cb, this);
}

void GameWindow::timer_cb(void *ptr) {
    GameWindow* a = static_cast<GameWindow*>(ptr);
    a->refreshGame();
    Fl::repeat_timeout(0.033, timer_cb, ptr);
}

void GameWindow::spawnAsteroid() {
    //cout << "asteroid spawned" << endl;
    this->begin();
    Vec2 newSpeed = Vec2::fromAngleDeg(rand() % 361);
    newSpeed *= asteroid_speed;
    vector<Vec2> startingPoints;                            //vector of possible starting points
    startingPoints.push_back(Vec2(rand()%800, 0));          //any random point on top border
    startingPoints.push_back(Vec2(0, rand()%600));          //any random point on left border
    startingPoints.push_back(Vec2(800, rand()%600));        //any random point on right border
    startingPoints.push_back(Vec2(rand()%800, 600));        //any random point on bottom border
    int index = rand() % 4;                                 //random index from 0-3 to choose a random edge for spawn
    Vec2 newPos = startingPoints.at(index);
    Asteroid* ast = new Asteroid(this, newPos, newSpeed);
    asteroids.push_back(ast);
    this->end();
}

void GameWindow::addBullet(Vec2 pos, Vec2 velocity) {
    this->begin();
    Bullet* bul = new Bullet(this, pos, velocity);
    bullets.push_back(bul);
    this->end();
}

void GameWindow::refreshGame() {
    updatePositions();
    checkBullets();
    if(cycles_survived>spawn_interval && asteroids.size()<max_asteroids) {
        spawnAsteroid();
    }
//    if(asteroids.size()<max_asteroids) {
//        spawnAsteroid();
//    }
    checkEndGame();
    this->redraw();
}

void GameWindow::updatePositions() {
    for(int i = 0; i<asteroids.size(); ++i) {
        asteroids.at(i)->updatePos();
    }
    
    for(int i = 0; i<bullets.size(); ++i) {
        bullets.at(i)->updatePos();
    }
    ship->updatePos();
}

void GameWindow::checkBullets() {
    for(int i = 0; i<bullets.size(); ++i) {
        if(bullets.at(i)->checkOutOfBounds()) {
            Fl::delete_widget(bullets.at(i));
            bullets.erase(bullets.begin() + i);
            break;
            //cout << bullets.size() << endl;
        } else {
            for(int k = 0; k<asteroids.size(); ++k) {
                if(bullets.at(i)->checkCollision(asteroids.at(k))) {
                    Fl::delete_widget(bullets.at(i));
                    bullets.erase(bullets.begin() + i);
                    Fl::delete_widget(asteroids.at(k));
                    asteroids.erase(asteroids.begin() + k);
                    ++asteroids_hit;
                    break;
                }
            }
        }
    }
}

void GameWindow::checkEndGame() {
    for(int i = 0; i<asteroids.size(); ++i) {
        if(ship->checkCollision(asteroids.at(i))) {
            cout << "Game Over!" << endl;
            cout << "Cycles survived: " << (cycles_survived/30) << endl;
            cout << "Asteroids destroyed: " << asteroids_hit << endl;
            this->hide();
        }
    }
    ++cycles_survived;
}

int GameWindow::handle(int event) {
    
    switch(event) {
        case FL_KEYDOWN:
            if(Fl::event_key() == 32) {
                //spacebar was pressed
                ship->setShooting(true);
                //cout << "shooting = true" << endl;
                return 1;
            }
            if(Fl::event_key() == FL_Up) {
                //up key was pressed
                ship->setAccelerating(true);
                return 1;
            }
            if(Fl::event_key() == FL_Left) {
                //Left key was pressed
                ship->setRotatingLeft(true);
                return 1;
            }
            if(Fl::event_key() == FL_Right) {
                //Right key was pressed
                ship->setRotatingRight(true);
                return 1;
            }
        case FL_KEYUP:
            if(Fl::event_key() == 32) {
                //spacebar was released
                ship->setShooting(false);
                //cout << "shooting = false" << endl;
                return 1;
            }
            if(Fl::event_key() == FL_Up) {
                //up key was released
                ship->setAccelerating(false);
                return 1;
            }
            if(Fl::event_key() == FL_Left) {
                //Left key was released
                ship->setRotatingLeft(false);
                return 1;
            }
            if(Fl::event_key() == FL_Right) {
                //Right key was released
                ship->setRotatingRight(false);
                return 1;
            }
        default:
            return Fl_Widget::handle(event);
    }
    
}
