#ifndef _COLOR_HPP_
#define _COLOR_HPP_
#include "vec3.hpp"
#include "interval.hpp"

using color = vec3;

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel){
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    double scale = 1.0/samples_per_pixel;

    r *= scale;
    g *= scale;
    b *= scale;

    static const interval intensity(0.000, 0.999);
    
    out <<static_cast<int>(256*intensity.clamp(r))<<" "
        <<static_cast<int>(256*intensity.clamp(g))<<" "
        <<static_cast<int>(256*intensity.clamp(b))<<"\n";
}

#endif