#ifndef __FLOCK_H__
#define __FLOCK_H__

#include <vector>
#include "boid.h"

class Flock: public std::vector<Boid> {
    public:
        Flock(const int numBoids);
        ~Flock();
        void randomInit(const int screen_width, const int screen_height);
        void calculateCenterOfMassesAndVelocities();
        void calculateMutualRepulsion();
        void calculateEnemyRepulsion(const int enemy_x, const int enemy_y);

    private:
};

#endif //__FLOCK_H__
