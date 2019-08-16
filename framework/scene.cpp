#include "scene.hpp"
#include "box.hpp"
#include "Sphere.hpp"
#include "camera.hpp"
#include "iostream"

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

      // std::cout << "fertig" << std::endl;
      file.close();
      return scene;
    }
 }

Scene output(std::string datei_name, float num) {

  Scene scene;
  std::ofstream file;
  std::string fileLine;

  file.open(datei_name);
  
  if(file.is_open() == true) {
    /*
    // Test-Szene fuer Test_Animation.mp4 (Bilder: Testbild%d.ppm)
    file << "define material pink 0.8 0.1 0.5 0.8 0.1 0.5 0.8 0.1 0.5 800 \n";
    file << "define shape box rbottom 1 -1 -11.5 3 1 -9.5 pink \n";
    file << "transform rbottom rotate " << num * 2 << " 0 0 1 \n"; 
    file << "define light lichtvonvorne 0 0 0 1 1 1 1 \n";
    file << "ambient 0.4 0.4 0.4 \n";
    file << "define camera eye 60.0 \n";
    */

    file << "define material gruen 0 0.9 0.1 0 0.9 0.1 0 0.9 0.1 50 \n";
    file << "define material hellblau 0 0.8 0.9 0 0.8 0.9 0 0.8 0.9 50 \n";
    file << "define material lila 0.7 0 0.5 0.7 0 0.5 0.7 0 0.5 50 \n";
    file << "define material orange 1 0.3 0 1 0.3 0 1 0.3 0 50 \n";
    file << "define material pink 1 0.4 0.7 1 0.4 0.7 1 0.4 0.7 50 \n";
    file << "define material gelb 1 1 0 1 1 0 1 1 0 50 \n";
    file << "define material rot 1 0 0.1 1 0 0.1 1 0 0.1 50 \n";
    file << "define material blau 0.1 0.1 1 0.1 0.1 1 0.1 0.1 1 50 \n";
    file << "define material grau 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 50 \n";

    file << "define shape sphere kugel1 -7 -5 -20 5 gruen \n";
    file << "define shape sphere kugel2 -9 0 -20 3 lila \n";
    file << "define shape sphere kugel3 -8 6 -20 4 hellblau \n";
    file << "define shape sphere kugel4 -11 3 -20 1 gelb \n";
    file << "define shape sphere kugel5 -3.5 2 -20 3.5 pink \n";
    file << "define shape sphere kugel6 -2.5 7.6 -20 2.7 orange \n";
    file << "define shape sphere kugel7 -1 -7 -20 3 rot \n";
    file << "define shape sphere kugel8 -1 -3 -20 4 gelb \n";
    file << "define shape sphere kugel9 4 -6 -20 3.5 blau \n";
    file << "define shape sphere kugel10 3 1 -20 4 rot \n";
    file << "define shape sphere kugel11 1.3 5.9 -20 3 gruen \n";
    file << "define shape sphere kugel12 4.8 6.8 -20 2.5 lila \n";
    file << "define shape sphere kugel13 9 -7.5 -20 2.5 pink \n";
    file << "define shape sphere kugel14 8 -2 -20 3.5 orange \n";
    file << "define shape sphere kugel15 11 -5 -20 1.5 lila \n";
    file << "define shape sphere kugel16 9.5 2.4 -20 3.2 hellblau \n";
    file << "define shape sphere kugel17 7 4.9 -20 1.5 pink \n";
    file << "define shape sphere kugel18 9 6.5 -20 3 gelb \n";
    file << "define shape sphere startkugel 9 6.5 -18.5 2 grau \n";

    float tempx, tempy, tempz;

    
      // if(num <= 100) {
      //   for(int i = 0; i <= 100; ++i) {
      //     file << "transform startkugel translate " << -0.15 * i << " 0 0 \n";
      //   }
      // }  
      
      // if(num > 100 && num <= 130) {
      //   for(int j = 0; j <= 30; ++j) {
      //     file << "transform startkugel translate 0 " << -0.15 * j << " 0 \n";
      //   }
      // }

      // if(num > 130 && num <= 230) {
      //   for(int i = 0; i <= 100; ++i) {
      //     file << "transform startkugel translate " << 0.15 * i << " 0 0 \n";
      //   }
      // }
      
      // if(num > 230 && num <= 260) {
      //   for(int j = 0; j <= 30; ++j) {
      //     file << "transform startkugel translate 0 " << -0.15 * j << " 0 \n";
      //   }
      // }

      // if(num > 260 && num <= 360) {
      //   for(int i = 0; i <= 100; ++i) {
      //     file << "transform startkugel translate " << -0.15 * i << "0 0 \n";
      //   }
      // }

      


    // if(num <= 100) {
    //   file << "transform startkugel translate " << -0.15 * num << " 0 0 \n";

    //   // if(num == 100) {
    //   //   tempx = -0.15 * 100;
    //   // }
    // }

    // if(num > 100 && num <= 130) {
    //   file << "transform startkugel translate 0 " << -0.15 * num << " 0 \n";
    // }

    // if(num > 130 && num <= 230) {
    //   file << "transform startkugel translate " << 0.15 * num << " 0 0 \n";
    // }

    // if(num > 230 && num <= 260) {
    //   file << "transform startkugel translate 0 " << -0.15 * num << " 0 \n";
    // }

    // if(num > 260 && num <= 360) {
    //   file << "transform startkugel translate " << -0.15 * num << "0 0 \n";
    // }

    // funktioniert
    if(num <= 100) {
      file << "transform startkugel translate " << -0.15 * num << " 0 0 \n";

      if(num == 100) {
        tempx = -0.15 * num;
      }
    }

    // if(num == 101) {
    //   file << "transform startkugel translate " << "-15" << " " << "0" << " 0 \n";
    // }

    // funktioniert
    if(num > 100 && num <= 130) {
      // file << "define shape sphere startkugel -6 6.5 -18.5 2 grau \n";
      // if(num == 101) {
      //   file << "transform startkugel translate " << "-15" << " " << "0" << " 0 \n";
      // }

      file << "transform startkugel translate " << /*tempx*/ "-15" << " " << -0.15 * (num - 99) << " 0 \n";

      if(num == 130) {
        tempy = -0.15 * num;
      }
    }

    if(num > 130 && num <= 230) {
      // file << "define shape sphere startkugel -6 2 -18.5 2 grau \n";
      file << "transform startkugel translate " << -15 + 0.15 * (num - 129) << " " << /*tempy*/ "-4.5" << " 0 \n";

      if(num == 230) {
        tempx = 0.15 * num;
      }
    }

    if(num > 230 && num <= 260) {
      // file << "define shape sphere startkugel 9 2 -18.5 2 grau \n";
      file << "transform startkugel translate " << /*tempx*/ "15" << " " << -4.5 - (-0.15 * (num - 229)) << " 0 \n";

      if(num == 260) {
        tempy = -0.15 * num;
      }
    }

    if(num > 260 && num <= 360) {
      // file << "define shape sphere startkugel 9 -2.5 -18.5 2 grau \n";
      file << "transform startkugel translate " << 9 + (-0.15 * (num - 259)) << " " << /*tempy*/ "-4.5" << " 0 \n";
    }

    file << "define light lichtvonvorne 0 0 0 1 1 1 1 \n";
    file << "ambient 0.4 0.4 0.4 \n";
    file << "define camera eye 60.0 \n";

    file.close();
  }
  
  scene = input(datei_name);

  // file << "hallihallo :)";
  
  return scene;
}