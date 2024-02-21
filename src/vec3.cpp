#include "../inc/vec3.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& out,const vec3& vec){
    out<<vec.x()<<" "<<vec.y()<<" "<<vec.z()<<"\n";
    return out;
}

vec3 operator+(const vec3& first, const vec3& second){
    return vec3(first[0]+second[0],first[1]+second[1],first[2]+second[2]);
}

vec3 operator-(const vec3& first, const vec3& second){
    return vec3(first[0]-second[0],first[1]-second[1],first[2]-second[2]);
}

vec3 operator*(const vec3& first, const vec3& second){
    return vec3(first[0]*second[0],first[1]*second[1],first[2]*second[2]);
}

vec3 operator*(const vec3& first, double add){
    return vec3(first[0]*add,first[1]*add,first[2]*add);
}

vec3 operator*(double add, const vec3& second){
    return vec3(second[0]*add,second[1]*add,second[2]*add);
}

vec3 operator/(const vec3& first, double div){
    return vec3(first[0]/div,first[1]/div,first[2]/div);
}

double vec3::dot(const vec3& first, const vec3& second){
    return first[0]*second[0]+first[1]*second[1]+first[2]*second[2];
}

vec3 vec3::cross(const vec3& first, const vec3& second){
    return vec3(first[1] * second[2] - first[2] * second[1],
                first[2] * second[0] - first[0] * second[2],
                first[0] * second[1] - first[1] * second[0]);
}

vec3 vec3::unit_vector(vec3 vec){
    return vec/vec.len();
}

