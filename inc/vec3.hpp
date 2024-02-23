#ifndef _VEC3_HPP_
#define _VEC3_HPP_
#include <iostream>
#include <math.h>
#include "main.hpp"

class vec3 {

    public:
    double e[3];

    vec3():e{0,0,0}{};

    vec3(double e1,double e2, double e3): e{e1,e2,e3} {};

    double x() const {return e[0];}

    double y() const {return e[1];}

    double z() const {return e[2];}

    vec3 operator-() const {return vec3(-e[0],-e[1],-e[2]);}

    double operator[](int i) const {return e[i];}

    double& operator[](int i) {return e[i];}

    vec3& operator+=(const vec3& vec){
        e[0] += vec[0];
        e[1] += vec[1];
        e[2] += vec[2];
        return *this;
    }

    vec3& operator-=(const vec3& vec){
        e[0] -= vec[0];
        e[1] -= vec[1];
        e[2] -= vec[2];
        return *this;
    }

    vec3& operator*=(double mul){
        e[0] *= mul;
        e[1] *= mul;
        e[2] *= mul;
        return *this;
    }

    vec3& operator/=(double div){
        return *this *= 1/div;
    }

    double len() const {
        return sqrt(len_squared());
    }

    double len_squared() const {
        return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
    }

    friend std::ostream& operator<<(std::ostream& out,const vec3& vec);

    friend vec3 operator+(const vec3& first, const vec3& second);

    friend vec3 operator-(const vec3& first, const vec3& second);

    friend vec3 operator*(const vec3& first, const vec3& second);

    friend vec3 operator*(const vec3& first, double add);

    friend vec3 operator*(double add, const vec3& second);

    friend vec3 operator/(const vec3& first, double div);

    static double dot(const vec3& first, const vec3& second);

    static vec3 cross(const vec3& first, const vec3& second);

    static vec3 unit_vector (vec3 vec);

    static vec3 random(){
        return vec3(random_double(),random_double(),random_double());
    }

    static vec3 random(double min, double max){
        return vec3(random_double(min,max),random_double(min,max),random_double(min,max));
    }

    static vec3 random_in_unit_sphere(){
        //return random(-1,1);
        while(true){
            vec3 cur = random(-1,1);
            if(cur.len_squared()<1.0) return cur;
        }
    }

    bool near_zero() const {
        auto s = 1e-8;
        return (fabs(e[0])<0) && (fabs(e[1])<s) && (fabs(e[2])<s);
    }

    static vec3 random_unit_vector(){
        return unit_vector(random_in_unit_sphere());
    }

    static vec3 random_on_hemisphere(const vec3& normal){
        vec3 unit = random_unit_vector();
        if(dot(unit,normal)>0) return unit;
        return -unit;
    }

    static vec3 reflect(const vec3& v, const vec3& n){
        return v - 2*dot(v,n)*n;
    }
};

using point3 = vec3;

#endif