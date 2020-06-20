#include "flock.h"
#include "boid.h"

#include <cmath>

Flock::Flock(const int numBoids): std::vector<Boid>(){
    this->resize(numBoids);
}

Flock::~Flock(){
    // technically speaking not necessary, as std::vector clears out within its own destructor
    // personal preference: clear it explicitly
    this->clear();
}

void Flock::randomInit(const int screen_width, const int screen_height){
    for (auto &boid: *this){
        boid.setBounds(screen_width/5,(screen_width*4)/5,
                       screen_height/5,(screen_height*4)/5);
        boid.setPosition(rand()%screen_width, rand()%screen_height);
        // TODO: find good init values, then parametrize them
        boid.initVelocity(rand()%100-50, rand()%100-50);
    }
}

void Flock::calculateCenterOfMassesAndVelocities(){
    for (auto& boid: *this){
        auto com_x = 0.0;
        auto com_y = 0.0;
        auto avg_vx = 0.0;
        auto avg_vy = 0.0;
        auto num_perceived_neighbors = 0;
        for (auto& other_boid: *this){
            if ( (&boid!=&other_boid) &&
                (boid.distanceToBoid(other_boid) < boid.visualRange())){
                com_x += other_boid.x();
                com_y += other_boid.y();
                avg_vx += other_boid.vx();
                avg_vy += other_boid.vy();
                ++num_perceived_neighbors;
            }
        }
        if (num_perceived_neighbors){
            com_x /= num_perceived_neighbors;
            com_y /= num_perceived_neighbors;

            avg_vx /= num_perceived_neighbors;
            avg_vy /= num_perceived_neighbors;
        }
        boid.perceived_center_of_flock_mass = std::make_tuple(com_x,com_y);
        boid.percieved_velocity_of_flock = std::make_tuple(avg_vx, avg_vy);
    }
}

void Flock::calculateMutualRepulsion(){
    for (auto& boid: *this){
        auto avoid_x = 0.0;
        auto avoid_y = 0.0;
        for (auto& other_boid: *this){
            if ( (&boid!=&other_boid) &&
                (boid.distanceToBoid(other_boid) < boid.minDistance())){
                avoid_x += boid.x() - other_boid.x();
                avoid_y += boid.y() - other_boid.y();
            }
        }
        boid.avoidance_vector = std::make_tuple(avoid_x, avoid_y);
    }
}

void Flock::calculateEnemyRepulsion(const int enemy_x, const int enemy_y){
    for (auto& boid: *this){
        auto avoid_x = 0.0;
        auto avoid_y = 0.0;
        if (boid.distanceTo(enemy_x, enemy_y) < boid.minDistance()){
            avoid_x += boid.x() - enemy_x;
            avoid_y += boid.y() - enemy_y;
        }
        boid.enemy_repulsion = std::make_tuple(avoid_x, avoid_y);
    }
}

