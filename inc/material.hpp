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
    double fuzz;

    public:

    metal(const color& a, double _fuzz):albedo(a), fuzz(_fuzz){}

    bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override{
        vec3 direction = vec3::reflect(vec3::unit_vector(ray_in.direction()), rec.normal) + vec3::random_unit_vector()*fuzz;
        attenuation = albedo;
        scattered = ray(rec.p, direction);
        return vec3::dot(scattered.direction(),rec.normal) > 0;
    }
};

class dielectric : public material {

    double ir;

    static double reflectance(double cosine, double ref_idx){
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1-cosine),5);
    }

    public:

    dielectric(double _ir):ir(_ir){}

    bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color(1,1,1);
        double refraction_index = (rec.front_face)? (1.0/ir):ir;

        vec3 unit_vector = vec3::unit_vector(ray_in.direction());
        vec3 direction;

        double cos_theta = fmin(vec3::dot(-unit_vector, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = refraction_index*sin_theta > 1.0;

        if(cannot_refract || reflectance(cos_theta, refraction_index) > random_double())
            direction = vec3::reflect(unit_vector, rec.normal); 
        else 
            direction = vec3::refract(unit_vector, rec.normal, refraction_index);
        
        scattered = ray(rec.p, direction);
        return true;

    }

};

#endif