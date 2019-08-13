#ifndef SCENE_HPP
#define SCENE_HPP
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "camera.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "ambient.hpp"
#include "transformation.hpp"
#include <stdio.h>
#include <string.h>
#include <memory>
#include <ostream>
#include <sstream>


struct Scene{
    // std::vector<std::shared_ptr<Material>> container1;
    // std::set<std::shared_ptr<Material>> container2;

    std::map<std::string, std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<Shape>> shapes;
    std::shared_ptr<Ambient> ambient;
    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<Camera> camera;
    std::vector<Transformation> transformations; 

    // std::shared_ptr<Material> find_vector(std::string color_name){
    //   for(std::vector<std::shared_ptr<Material>>::size_type i = 0; i!= container1.size(); i++){
    //     if(container1.at(i)->name_ == color_name){ 
    //       return container1.at(i);
    //     }
    //   }
    //   return nullptr;
    // }

    // std::shared_ptr<Material> find_set(std::string color_name){
    //   for(auto element : container2){
    //     if(element->name_ == color_name){
    //       return element;
    //     }
    //   }
    //   return nullptr;
    // }

    std::shared_ptr<Material> find_map(std::string color_name){
      for(std::pair<std::string, std::shared_ptr<Material>> element : materials){
        if(element.first == color_name){
          return element.second;
        }
      }
      return nullptr; 
    }
};

bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs);

Scene input(std::string datei_name/*, Scene scene*/);

#endif