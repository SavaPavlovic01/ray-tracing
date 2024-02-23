#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_
#include "hittable.hpp"

class sphere : public hittable{

    point3 center;
    double radius;
    std::shared_ptr<material> mat;

    public:

    sphere(point3 _center, double _radius, std::shared_ptr<material> _mat):center(_center),radius(_radius),mat(_mat){}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
        double a = r.direction().len_squared();
        double half_b = vec3::dot(r.direction(),oc);
        double c = oc.len_squared() - radius*radius;

        double discriminant = half_b*half_b - a*c;

        if(discriminant < 0) return false;
        double sqrtd = sqrt(discriminant);
        double root = (-half_b - sqrtd) / a;

        if(!ray_t.surrounds(root)){
            root = (-half_b + sqrtd) / a;
            if(!ray_t.surrounds(root)) return false;
        }

        rec.t = root;
        rec.p = r.at(root);
        vec3 outward_normal = (r.at(root) - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;
        return true;

    }    
};

#endif