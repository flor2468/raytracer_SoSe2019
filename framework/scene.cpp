#include "scene.hpp"


bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs)
{
  return lhs->name_ < rhs-> name_;
};


Scene input(std::string datei_name, Scene scene)
 {
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
        std::istringstream line_stream(fileLine);
        std::string identifier;
        //line_stream.str(fileLine);
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