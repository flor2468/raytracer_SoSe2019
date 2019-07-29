#ifndef SCENE_HPP
#define SCENE_HPP
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "material.hpp"
#include <stdio.h>
#include <string.h>
#include <memory>
#include <ostream>


struct Scene{
    // std::vector<std::shared_ptr<Material>> container1;
    // std::set<std::shared_ptr<Material>> container2;
    std::map<std::string, std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<Shape>> shapes;

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

bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs){
  return lhs->name_ < rhs-> name_;
};


Scene input(std::string datei_name, Scene scene) {
    std::string name;
    float ka_r, ka_g, ka_b, kd_r, kd_g,kd_b, ks_r, ks_g, ks_b, m; 
    Color ka{ka_r, ka_g, ka_b,};
    Color kd{ kd_r, kd_g,kd_b};
    Color ks{ks_r, ks_g, ks_b};
    Material mat{name, ka, kd, ks, m};
    std::vector<std::string> textFile;
    std::string fileLine;
    std::ifstream file;
    file.open(datei_name);
    if(file.is_open() == true){
    //    std::cout << "huhu";
      while(std::getline(file, fileLine)){
        //std::getline(file, fileLine);
        std::istringstream line_stream ;//(fileLine);
        std::string identifier;
        line_stream.str(fileLine);
        line_stream >> identifier;
        std::cout <<fileLine << "\n"; 
        if("define" == identifier){
            line_stream >>identifier;
            if("material" == identifier){
              std::string name;
              line_stream >> name;
              float ka_r, ka_g, ka_b, kd_r, kd_g,kd_b, ks_r, ks_g, ks_b, m; 
              line_stream >> ka_r;
              line_stream >> ka_g;
              line_stream >> ka_b;
              line_stream >> kd_r;
              line_stream >> kd_g;
              line_stream >> kd_b;
              line_stream >> ks_r;
              line_stream >> ks_g;
              line_stream >> ks_b;
              line_stream >> m;
              ka = {ka_r, ka_g, ka_b,};
              kd = { kd_r, kd_g,kd_b};
              ks = {ks_r, ks_g, ks_b};
              
              mat = {name, ka, kd, ks, m};
              //std::cout <<name << " " << mat.ka.r << " " << m << "\n";
              auto mat_ptr = std::make_shared<Material>(mat);
              // scene.container1.push_back(mat_ptr);
              // scene.container2.insert(mat_ptr);
              scene.materials.emplace(name, mat_ptr);
              // std::cout << mat.ka.r << " " << mat.ka.g << " " << mat.ka.b;

            }
        }
        //textFile.push_back(fileLine);
        //std::cout << fileLine << " \n";
        //char delimiter[] = " ";
        //char *ptr;
        //char str[1024];
        //strcpy(str,fileLine.c_str());
        //ptr = std::strtok(str, delimiter);
      }
      file.close();
      return scene;
    }
}


#endif