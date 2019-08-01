#include "scene.hpp"
#include "box.hpp"
#include "Sphere.hpp"

bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs)
{
  return lhs->name_ < rhs-> name_;
};

Scene input(std::string datei_name/*, Scene scene*/)
 {
   Scene scene{};

    // std::string name;
    // float ka_r, ka_g, ka_b, kd_r, kd_g,kd_b, ks_r, ks_g, ks_b, m; 
    // Color ka{ka_r, ka_g, ka_b,};
    // Color kd{ kd_r, kd_g,kd_b};
    // Color ks{ks_r, ks_g, ks_b};
    // Material mat{name, ka, kd, ks, m};

    // std::vector<std::string> textFile;
    
    std::cout << "halloooo" << std::endl;

    std::string fileLine;
    std::ifstream file;
    file.open(datei_name);
    // std::ifstream file(datei_name);
    if(file.is_open() == true){
    //    std::cout << "huhu";
      while(std::getline(file, fileLine)){

        std::cout << "test" << std::endl;

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
              Color ka = {ka_r, ka_g, ka_b,};
              Color kd = { kd_r, kd_g,kd_b};
              Color ks = {ks_r, ks_g, ks_b};
              
              Material mat = {name, ka, kd, ks, m};
              //std::cout <<name << " " << mat.ka.r << " " << m << "\n";
              auto mat_ptr = std::make_shared<Material>(mat);
              // scene.container1.push_back(mat_ptr);
              // scene.container2.insert(mat_ptr);
              scene.materials.emplace(name, mat_ptr);
              // std::cout << mat.ka.r << " " << mat.ka.g << " " << mat.ka.b;

            }

            if("shape" == identifier) {
              line_stream >> identifier;

              if("box" == identifier) {
                std::string name;
                line_stream >> name;
                float minx, miny, minz, maxx, maxy, maxz;
                line_stream >> minx;
                line_stream >> miny;
                line_stream >> minz;
                line_stream >> maxx;
                line_stream >> maxy;
                line_stream >> maxz;
                glm::vec3 min = {minx, miny, minz};
                glm::vec3 max = {maxx, maxy, maxz};

                line_stream >> identifier;
                std::map<std::string, std::shared_ptr<Material>>::iterator it;
                it = scene.materials.find(identifier);
                auto mat_ptr = it->second;

                Box box = {name, mat_ptr, min, max};

                auto box_ptr = std::make_shared<Box>(box);
                scene.shapes.push_back(box_ptr);
                std::cout << "box added" << std::endl;
              }

              if("sphere" == identifier) {
                std::string name;
                line_stream >> name;
                float centerx, centery, centerz, radius;
                line_stream >> centerx;
                line_stream >> centery;
                line_stream >> centerz;
                line_stream >> radius;
                glm::vec3 center = {centerx, centery, centerz};

                line_stream >> identifier;
                std::map<std::string, std::shared_ptr<Material>>::iterator it;
                it = scene.materials.find(identifier);
                auto mat_ptr = it->second;

                Sphere sphere = {name, mat_ptr, center, radius};

                auto sphere_ptr = std::make_shared<Sphere>(sphere);
                scene.shapes.push_back(sphere_ptr);
                std::cout << "sphere added" << std::endl;

              }

            }

            if("light" == identifier) {
              std::string name;
              line_stream >> name;
              float x, y, z, r, g, b, intensitaet;
              line_stream >> x;
              line_stream >> y;
              line_stream >> z;
              line_stream >> r;
              line_stream >> g;
              line_stream >> b;
              line_stream >> intensitaet;
              glm::vec3 position = {x, y, z};
              Color farbe = {r, g, b};
              Light licht = {name, position, farbe, intensitaet};

              auto light_ptr = std::make_shared<Light>(licht);
              scene.lights.push_back(light_ptr);
              std::cout << "light added" << std::endl;

            }


        }

        if("ambient" == identifier) {
          float r, g, b;
          line_stream >> r;
          line_stream >> g;
          line_stream >> b;
          Color ambient_col = {r, g, b};
          Ambient amb = {ambient_col};
          auto ambient_ptr = std::make_shared<Ambient>(amb);

          scene.ambient = ambient_ptr;
        }

        //textFile.push_back(fileLine);
        //std::cout << fileLine << " \n";
        //char delimiter[] = " ";
        //char *ptr;
        //char str[1024];
        //strcpy(str,fileLine.c_str());
        //ptr = std::strtok(str, delimiter);
      }
      // std::cout << "fertig" << std::endl;
      file.close();
      return scene;
    }
 }