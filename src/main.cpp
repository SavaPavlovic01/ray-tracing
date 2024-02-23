#include <iostream>
#include "../inc/vec3.hpp"
#include "../inc/color.hpp"
#include "../inc/ray.hpp"
#include "../inc/main.hpp"
#include "../inc/hittable.hpp"
#include "../inc/hittable_list.hpp"
#include "../inc/sphere.hpp"
#include "../inc/interval.hpp"
#include "../inc/camera.hpp"
#include "../inc/material.hpp"
#include <time.h>


int main(){
    
    auto material_ground = std::make_shared<lambertian>(color(0.8,0.8,0.2));
    auto material_center = std::make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left = std::make_shared<metal>(color(0.8,0.8,0.8));
    auto material_right = std::make_shared<metal>(color(0.8,0.6,0.2));

    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5, material_center));
    world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
    world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.render(world);
}