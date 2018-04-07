#ifndef _RANDOMENGINE_H
#define _RANDOMENGINE_H

#include <random>

static std::random_device rd;
typedef std::mt19937 MyRNG;
typedef std::uniform_real_distribution<double> double_dist;

static MyRNG rng;

//void initializeRandomEngine() {
//    rng.seed(rd());
//}

#endif //_RANDOMENGINE_H
