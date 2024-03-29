#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "vec3.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "color.hpp"
#include "material.hpp"

class camera {

    public:

    double aspect_ratio = 16.0/9.0; 
    int samples_per_pixel = 10;
    int image_width = 100;
    int max_depth = 10;
    double vfov = 90;
    point3 lookfrom = point3(0,0,-1);
    point3 lookat = point3(0,0,0);
    vec3 vup = vec3(0,1,0);

    void render(const hittable& world){
        init();

        std::cout<<"P3"<<"\n";
        std::cout<<image_width<<" "<<image_height<<"\n";
        std::cout<<255<<"\n";
    
        for(int j = 0;j<image_height;j++){
            std::clog << "\nLines remaining " << (image_height - j) <<" "<<std::flush;
            for(int i = 0;i<image_width;i++){
                color pixel_color(0,0,0);
                for(int sample = 0;sample<samples_per_pixel;sample++){
                    ray r =  get_ray(i,j);
                    pixel_color += ray_color(r,max_depth,world);
                }
                write_color(std::cout,pixel_color,samples_per_pixel);
            }
        }

        std::clog << "\nDone\n" << std::flush;

    }


    private:

    int image_height;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    vec3 u,v,w;

    color ray_color(const ray& r, int depth, const hittable& world){

        if(depth <=0) return color(0,0,0);

        hit_record rec;
        
        if(world.hit(r,interval(0.001,infinity),rec)){
            ray scattered_ray;
            color attenuation;
            if(rec.mat->scatter(r,rec,attenuation,scattered_ray))
                return attenuation * ray_color(scattered_ray,depth-1,world);
           return color(0,0,0);
        }    

        vec3 unit_direction = vec3::unit_vector(r.direction());
        double a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0); 
    }

    ray get_ray(int i, int j) const{
        point3 pixel_center = pixel00_loc + i * pixel_delta_u + j * pixel_delta_v;
        point3 pixel_sample = pixel_center + pixel_sample_square();

        vec3 dir = pixel_sample - center;
        return ray(center, dir);
    }

    vec3 pixel_sample_square() const {
        double px = -0.5 + random_double();
        double py = -0.5 + random_double();
        return px*pixel_delta_u + py*pixel_delta_v;
    }

    void init(){
        image_height = static_cast<int>(image_width/aspect_ratio);
        image_height = (image_height < 1)? 1 : image_height;

        double focal_length = (lookfrom - lookat).len();
        double theta = degrees_to_radians(vfov);
        double h = focal_length * tan(theta/2);
        double viewport_height = 2*h;
        double viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
        center = lookfrom;

        w = vec3::unit_vector(lookfrom - lookat);
        u = vec3::unit_vector(vec3::cross(vup, w));
        v = vec3::cross(w,u);

        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * (-v);

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        point3 viewport_upper_left = center - (focal_length*w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);    

    }
};

#endif