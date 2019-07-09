#ifndef SCENE_HPP
#define SCENE_HPP
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "material.hpp"

struct Scene{
    std::vector<std::shared_ptr<Material>> container1;
    std::set<std::shared_ptr<Material>> container2;
    std::map<std::string, std::shared_ptr<Material>> container3;
};

void input(std::string datei_name) {
// Versuch 1
//     std::ifstream f;    
//     std::string s;
//     // f.open(datei_name, std::ios::out);
//    //// f.open(argv[1], std::ios::in);
//     while(!(f.eof())){
//         getline(f, s);
//         std::cout << s << std::endl;
//     }
//     f.close();

// Versuch 2
    // char filename[128];
    // std::ifstream file;
    // char zeile[1024];
    // std::cout << "Dateiname: " << std::flush;
    // std::cin.getline(filename, 127);
    // file.open(filename, std::ios::in);
    // while(!(file.eof())) {
    //     file.getline(zeile, 1024);
    // }

//Versuch 3 :)

    std::vector<std::string> textFile;
    std::string fileLine;
    std::ifstream file;

    file.open("Beispiel-Datei.sdf");
    if(file.is_open() == true){
    //    std::cout << "huhu";
      while(std::getline(file, fileLine)){
        textFile.push_back(fileLine);
        std::cout << fileLine << " \n";
      }
      file.close();
    }
}

#endif