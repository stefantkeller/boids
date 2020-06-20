#ifndef __BOID_H__
#define __BOID_H__

#include <SFML/Graphics.hpp>
#include "drawable.h"

class Boid: public Drawable {
    public:
        Boid();
        Boid(const int pos_x, const int pos_y);
        Boid(const std::string &filename, int pos_x, int pos_y);
        ~Boid();
        void initVelocity(const float vx, const float vy);
        void setBounds(const int min_x, const int max_x,
                       const int min_y, const int max_y);
        float distanceTo(const float coord_x, const float coord_y);
        float distanceToBoid(const Boid& other_boid);
        float visualRange();
        float minDistance();
        float minEnemyDistance();
        float vx() const;
        float vy() const;
        void vx(float v);
        void vy(float v);

        void avoidEnemy(const float enemy_x, const float enemy_y);
        void update(const float elapsed_time, const float enemy_x, const float enemy_y);

        void drawOn(sf::RenderWindow &window) override;

        std::tuple<float,float> perceived_center_of_flock_mass;
        std::tuple<float,float> percieved_velocity_of_flock;
        std::tuple<float,float> avoidance_vector;
        std::tuple<float,float> enemy_repulsion;

    private:
        float vx_;
        float vy_;
        float visual_range_ = 20;
        // screen limitations
        const int self_margin_ = 20;
        const int self_size_ = 4;
        int min_x_;
        int max_x_;
        int min_y_;
        int max_y_;
        //
        const float centering_tendency_ = 0.001;
        const float avoid_factor_ = 0.5;
        const float velocity_matching_tendency_ = 0.05;
        const float enemy_aversion_ = 20.0;
        const float min_enemy_distance_ = 50;
        const float max_speed_ = 200;
        //
        void flyTowardsCenter_();
        void avoidOthers_();
        void matchVelocity_();
        void limitSpeed_();
        void keepWithinBounds_();
};

#endif // __BOID_H__
