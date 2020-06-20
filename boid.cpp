#include <cmath>
#include <SFML/Graphics.hpp>
#include "drawable.h"
#include "boid.h"

Boid::Boid(): Drawable("graphics/boid.png", 0, 0){}
Boid::Boid(const int pos_x, const int pos_y): Drawable("graphics/boid.png", pos_x, pos_y){}
Boid::Boid(const std::string &filename, int pos_x, int pos_y):
    Drawable(filename, pos_x, pos_y){}
Boid::~Boid(){}

void Boid::initVelocity(const float vx, const float vy) {
    this->vx(vx);
    this->vy(vy);
}

float Boid::vx() const{
    return vx_;
}
float Boid::vy() const{
    return vy_;
}
void Boid::vx(float v){
    vx_ = v;
}
void Boid::vy(float v){
    vy_ = v;
}

void Boid::setBounds(const int min_x, const int max_x,
                     const int min_y, const int max_y){
    min_x_=min_x;
    min_y_=min_y;
    max_x_=max_x;
    max_y_=max_y;
}

float Boid::visualRange(){
    return visual_range_;
}
float Boid::minDistance(){
    return self_margin_;
}

float Boid::minEnemyDistance(){
    return min_enemy_distance_;
}

float Boid::distanceTo(const float coord_x, const float coord_y){
    return sqrt(pow( x() - coord_x, 2 ) + pow( y() - coord_y, 2 ));
}

float Boid::distanceToBoid(const Boid& other_boid){
    return distanceTo(other_boid.x(), other_boid.y());
}

void Boid::flyTowardsCenter_(){
    auto com_x = std::get<0>(perceived_center_of_flock_mass);
    auto com_y = std::get<1>(perceived_center_of_flock_mass);
    if (com_x != 0 || com_y != 0) {
        vx(vx() + (com_x - x())*centering_tendency_);
        vy(vy() + (com_y - y())*centering_tendency_);
   }
}

void Boid::avoidOthers_(){
    auto avoid_x = std::get<0>(avoidance_vector);
    auto avoid_y = std::get<1>(avoidance_vector);
    if (avoid_x != 0 || avoid_y != 0) {
        vx(vx() + avoid_x*avoid_factor_);
        vy(vy() + avoid_y*avoid_factor_);
    }
}

void Boid::matchVelocity_(){
    auto avg_vx = std::get<0>(percieved_velocity_of_flock);
    auto avg_vy = std::get<1>(percieved_velocity_of_flock);
    if (avg_vx != 0 || avg_vy != 0) {
        vx(vx() + (avg_vx - x())*velocity_matching_tendency_);
        vy(vy() + (avg_vy - y())*velocity_matching_tendency_);
   }
}

void Boid::limitSpeed_(){
    auto speed = sqrt( pow(vx(),2) + pow(vy(),2) );
    if (speed > max_speed_){
        vx( vx()/speed * max_speed_ );
        vy( vy()/speed * max_speed_ );
    }
}

void Boid::keepWithinBounds_(){
    auto x = (int)this->x()+self_size_/2;
    auto y = (int)this->y()+self_size_/2;
    if (x < min_x_+self_margin_) vx(vx()+5);
    if (x > max_x_-self_margin_) vx(vx()-5);
    if (y < min_y_+self_margin_) vy(vy()+5);
    if (y > max_y_-self_margin_) vy(vy()-5);
}

void Boid::avoidEnemy(const float enemy_x, const float enemy_y) {
    auto avoid_x = 0.0;
    auto avoid_y = 0.0;
    if (distanceTo(enemy_x, enemy_y) < minEnemyDistance()){
        avoid_x += x() - enemy_x;
        avoid_y += y() - enemy_y;
    }
    vx(vx() + avoid_x*enemy_aversion_);
    vy(vy() + avoid_y*enemy_aversion_);
}

void Boid::update(const float elapsed_time, const float enemy_x, const float enemy_y){ 
    flyTowardsCenter_();
    avoidOthers_();
    matchVelocity_();
    limitSpeed_();
    keepWithinBounds_();
    avoidEnemy(enemy_x, enemy_y);
    // update new position according to above calculated constraints
    // note, elapsed_time is calculated outside this update() function
    // i.e. the elapsed_time takes into account the time it took to perform the above calculations
    // of the previous update, but not the current one.
    // However, to accurately taking into account the time it took to perform these local calculations
    // we'd have to reset the clock inside update().
    // But this would reset the clock then for every single Boid,
    // which doesn't correspond to the real elapsed time either.
    // Plus, resetting the clock inside a Boid function would make concurrency difficult (I guess?!)
    setPosition(x()+vx()*elapsed_time,
                y()+vy()*elapsed_time);
}

void Boid::drawOn(sf::RenderWindow &window){
    auto const pi = 3.14159;
    auto angle = atan2(vy(),vx());
    auto angle_deg = angle/pi*180;
    setRotation(angle_deg);
    Drawable::drawOn(window);
}
