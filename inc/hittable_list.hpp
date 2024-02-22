#ifndef _HITTABLE_LIST_HPP_
#define _HITTABLE_LIST_HPP_

#include <vector>
#include <memory>
#include "hittable.hpp"

class hittable_list : public hittable{
    std::vector<std::shared_ptr<hittable>> objects;

    public:
    
    hittable_list() {}

    hittable_list(std::shared_ptr<hittable> object){
        add(object);
    }

    void add(std::shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    void clear(){
        objects.clear();
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
        hit_record temp;
        bool hit_anything = false;
        double closest = ray_t.max;

        for(const auto& object: objects){
            if(object->hit(r,interval(ray_t.min, closest),temp)){
                closest = temp.t;
                hit_anything = true;
                rec = temp;
            }
        }

        return hit_anything;
    }

};

#endif