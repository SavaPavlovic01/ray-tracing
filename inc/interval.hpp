#ifndef _INTERVAL_HPP_
#define _INTERVAL_HPP_

#include "main.hpp"

class interval{
    
    public:

    double max;
    double min;

    public:

    interval():max(infinity),min(-infinity){}

    interval (double _min, double _max):max(_max),min(_min){}

    double clamp(double x) const {
        if(x>max) return max;
        if(x<min) return min;
        return x;
    }

    bool contains(double x) const{
        return x>=min && x<=max;
    }

    bool surrounds(double x) const{
        return x > min && x < max;
    }

    static const interval empty, universe;
};

const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);


#endif