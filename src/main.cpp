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
#include <time.h>


int main(){
    //srand(time(nullptr));
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.render(world);
}