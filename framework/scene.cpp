#include "scene.hpp"
#include "box.hpp"
#include "Sphere.hpp"
#include "camera.hpp"

bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs)
{
  return lhs->name_ < rhs-> name_;
};

Scene input(std::string datei_name/*, Scene scene*/) {

  /* Funktion zum Einlesen einer Szene aus einer SDF-Datei  */

  Scene scene{};

   std::string fileLine;
   std::ifstream file;
   file.open(datei_name);

   if(file.is_open() == true){

     while(std::getline(file, fileLine)){

        std::istringstream line_stream(fileLine);
        std::string identifier;

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

            if("camera" == identifier) {
              std::string name;
              line_stream >> name;
              float oeffnungswinkel;
              line_stream >> oeffnungswinkel;

              Camera cam{name, oeffnungswinkel};
              std::cout << "camera added" << std::endl;
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

        if("transform" == identifier) {
          Transformation t{};
          line_stream >> t.objekt_name_;
          line_stream >> t.transformationsart_;
          
          if("translate" == t.transformationsart_) {
            float a, b, c;
            line_stream >> a;
            line_stream >> b;
            line_stream >> c;
            // t.verschiebung_ = {a, b, c};

            t.transformationsmatrix_ = {
              glm::vec4 {1, 0, 0, 0},
              glm::vec4 {0, 1, 0, 0},
              glm::vec4 {0, 0, 1, 0},
              glm::vec4 {a, b, c, 1}
            };

            std::cout << "translation added" << std::endl;
          }

          if("scale" == t.transformationsart_) {
            float x, y, z;
            line_stream >> x;
            line_stream >> y;
            line_stream >> z;
            // t.zoom_ = {x, y, z};

            t.transformationsmatrix_ = {
              glm::vec4 {x, 0, 0, 0},
              glm::vec4 {0, y, 0, 0},
              glm::vec4 {0, 0, z, 0},
              glm::vec4 {0, 0, 0, 1}
            };

            std::cout << "scale added" << std::endl;
          }

          if("rotate" == t.transformationsart_) {
            // line_stream >> t.winkel_;
            // line_stream >> t.rotationsachse_.x;
            // line_stream >> t.rotationsachse_.y;
            // line_stream >> t.rotationsachse_.z;
            float winkel, x, y, z;
            line_stream >> winkel;
            line_stream >> x;
            line_stream >> y;
            line_stream >> z;

            if(x == 1 && y == 0 && z == 0) {

              t.transformationsmatrix_ = {
              glm::vec4 {1, 0, 0, 0},
              glm::vec4 {0, (std::cos(winkel / 2.0f * M_PI / 180) ), (std::sin(winkel / 2.0f * M_PI / 180) ), 0},
              glm::vec4 {0, -1 * (std::sin(winkel / 2.0f * M_PI / 180) ), (std::cos(winkel / 2.0f * M_PI / 180) ), 0},
              glm::vec4 {0, 0, 0, 1}
              };

            }

            if(x == 0 && y == 1 && z == 0) {

              t.transformationsmatrix_ = {
              glm::vec4 {(std::cos(winkel / 2.0f * M_PI / 180) ) , 0, -1 * (std::sin(winkel / 2.0f * M_PI / 180) ), 0},
              glm::vec4 {0, 1, 0, 0},
              glm::vec4 {(std::sin(winkel / 2.0f * M_PI / 180) ) , 0, (std::cos(winkel / 2.0f * M_PI / 180) ), 0},
              glm::vec4 {0, 0, 0, 1}
              };

            }

            if(x == 0 && y == 0 && z == 1) {

              t.transformationsmatrix_ = {
              glm::vec4 {(std::cos(winkel / 2.0f * M_PI / 180) ), (std::sin(winkel / 2.0f * M_PI / 180) ), 0, 0},
              glm::vec4 {- 1 * (std::sin(winkel / 2.0f * M_PI / 180) ), (std::cos(winkel / 2.0f * M_PI / 180) ), 0, 0},
              glm::vec4 {0, 0, 1, 0},
              glm::vec4 {0, 0, 0, 1}
              };

            }

            std::cout << "rotation added" << std::endl;
          }

          // auto transformation_ptr = std::make_shared<Transformation>(t);
          scene.transformations.push_back(t);

        }
      }

      for(auto s : scene.shapes) {
        std::string name = s->get_name();
        glm::mat4 translate = {
        glm::vec4 {1, 0, 0, 0},
        glm::vec4 {0, 1, 0, 0},
        glm::vec4 {0, 0, 1, 0},
        glm::vec4 {0, 0, 0, 1}
        };
        glm::mat4 rotate = translate;
        glm::mat4 scale = translate;

        for(auto t : scene.transformations) {
          if(name == t.objekt_name_) {
            if(t.transformationsart_ == "scale") {
              scale *= t.transformationsmatrix_;
            }
            if(t.transformationsart_ == "rotate") {
              rotate *= t.transformationsmatrix_;
            }
            if(t.transformationsart_ == "translate") {
              translate *= t.transformationsmatrix_;
            }
          }
        }

        s->world_transformation_ = translate * rotate;
        s->world_transformation_ = s->world_transformation_ * scale;
        s->world_transformation_invers_ = glm::inverse(s->world_transformation_);
      }


      // for(auto el : scene.transformations) {

      //   // glm::mat4 hilfsmatrix = el->transformationsmatrix_;
      //   glm::mat4 translate = {
      //     glm::vec4 {1, 0, 0, 0},
      //     glm::vec4 {0, 1, 0, 0},
      //     glm::vec4 {0, 0, 1, 0},
      //     glm::vec4 {0, 0, 0, 1}
      //   };
      //   glm::mat4 rotate = translate;
      //   glm::mat4 scale = translate;

      //   if(el->transformationsart_ == "translate") {
      //     translate = el->transformationsmatrix_;
      //   }

      //   if(el->transformationsart_ == "scale") {
      //     scale = el->transformationsmatrix_;
      //   }

      //   if(el->transformationsart_ == "rotate") {
      //     rotate = el->transformationsmatrix_;
      //   }

      //   for(auto element : scene.transformations) {

      //     if(el != element && el->objekt_name_ == element->objekt_name_) {

      //       if(element->transformationsart_ == "translate") {
      //         translate = element->transformationsmatrix_;
      //       }

      //       if(element->transformationsart_ == "scale") {
      //         scale = element->transformationsmatrix_;
      //       }

      //       if(element->transformationsart_ == "rotate") {
      //         rotate = element->transformationsmatrix_;
      //       }
      //     }

      //     for(auto e : scene.transformations) {

      //       if(el != element && el != e && element != e && el->objekt_name_ == element->objekt_name_ && element->objekt_name_ == e->objekt_name_) {
            
      //         if(e->transformationsart_ == "translate") {
      //           translate = e->transformationsmatrix_;
      //         }

      //         if(e->transformationsart_ == "scale") {
      //           scale = e->transformationsmatrix_;
      //         }

      //         if(e->transformationsart_ == "rotate") {
      //           rotate = e->transformationsmatrix_;
      //         }
      //       }
      //     }
      //   }  

      //   for(auto s : scene.shapes) {
      //     if(s->get_name() == el->objekt_name_) {
      //       s->world_transformation_ = translate * rotate;
      //       s->world_transformation_ = s->world_transformation_ * scale;
      //       s->world_transformation_invers_ = glm::inverse(s->world_transformation_);
      //     }
      //   }
      // }


      // std::cout << "fertig" << std::endl;
      file.close();
      return scene;
    }
 }