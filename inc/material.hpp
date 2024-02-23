#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include "ray.hpp"
#include "color.hpp"
#include "hittable.hpp"

class hit_record;

class material{

    public:

    virtual ~material() = default;

    virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {

    color albedo;

    public:

    lambertian(const color& a):albedo(a){}

    bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 direction = rec.normal + vec3::random_unit_vector();

        if(direction.near_zero()) direction = rec.normal;

        scattered = ray(rec.p, direction);
        attenuation = albedo;
        return true;
    }

};

class metal : public material {

    color albedo;

    public:

    metal(const color& a):albedo(a){}

    bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override{
        vec3 direction = vec3::reflect(vec3::unit_vector(ray_in.direction()), rec.normal);
        attenuation = albedo;
        scattered = ray(rec.p, direction);
        return true;
    }
};

#endif