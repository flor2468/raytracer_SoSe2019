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

struct Scene{
    std::vector<std::shared_ptr<Material>> container1;
    std::set<std::shared_ptr<Material>> container2;
    std::map<std::string, std::shared_ptr<Material>> container3;
};

void input(std::string datei_name, Scene* scene) {

    std::vector<std::string> textFile;
    std::string fileLine;
    std::ifstream file;
    Material mat;
    file.open("Beispiel-Datei.sdf");
    if(file.is_open() == true){
    //    std::cout << "huhu";
      while(std::getline(file, fileLine)){
        std::istringstream line_stream(fileLine);
        std::string identifier;
        line_stream >> identifier;
        if("define" == identifier){
            line_stream >>identifier;
            if("material" == identifier){
                line_stream >> identifier;

            }
        }
        //textFile.push_back(fileLine);
        std::cout << fileLine << " \n";
        char delimiter[] = " ";
        char *ptr;
        char str[1024];
        strcpy(str,fileLine.c_str());
        ptr = std::strtok(str, delimiter);


      }
      file.close();
    }
}

#endif