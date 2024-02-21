#ifndef _COLOR_HPP_
#define _COLOR_HPP_
#include "vec3.hpp"

using color = vec3;

void write_color(std::ostream& out, color pixel_color){
    out <<static_cast<int>(255.999*pixel_color.x())<<" "
        <<static_cast<int>(255.999*pixel_color.y())<<" "
        <<static_cast<int>(255.999*pixel_color.z())<<"\n";
}

#endif