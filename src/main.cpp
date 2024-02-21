#include <iostream>
#include "../inc/vec3.hpp"
#include "../inc/color.hpp"
#include "../inc/ray.hpp"
#define ROW 256
#define COLUMN 256
#define MAX_COLOR 255

color ray_color(const ray& r){
    vec3 unit_direction = vec3::unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
}

int main(){

    double aspect_ratio = 16.0/9.0;
    int image_width = 400;
    int image_height = static_cast<int>(image_width/aspect_ratio);
    image_height = (image_height < 0)? 1 : image_height;

    double focal_length = 2.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (static_cast<double>(image_height)/image_width);
    point3 camera_center = point3(0,0,0);

    vec3 viewport_u = vec3(viewport_width,0,0);
    vec3 viewport_v = vec3(0,-viewport_height,0);

    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    point3 viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;

    point3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);    

    std::cout<<"P3"<<"\n";
    std::cout<<image_width<<" "<<image_height<<"\n";
    std::cout<<255<<"\n";
    
    for(int j = 0;j<image_height;j++){
        std::clog << "\nLines remaining " << (image_height - j) <<" "<<std::flush;
        for(int i = 0;i<image_width;i++){
            point3 pixel_center = pixel00_loc + i * pixel_delta_u + j * pixel_delta_v;
            vec3 ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            write_color(std::cout,ray_color(r));
        }
    }

    std::clog << "\nDone\n" << std::flush;
    
}