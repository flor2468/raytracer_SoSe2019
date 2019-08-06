// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "scene.hpp"
#include "hitpont.hpp"
#include "light.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <cmath>
#include <iterator>
#include <vector>

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene scene)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
  , scene_(scene)
{}

void Renderer::render() {

  /* Funktion zum Rendern einer Szene */

  std::size_t const checker_pattern_size = 20;
  Camera cam;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);

      /* 
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }
  */

      // if(y > height_/ 3) { 
      //   p.color = Color(1.0, 0.0, 0.0);
      // }
      // if(y < (height_/ 3)){
      //   p.color = Color(1.0f, 1.0f, 0.0f);
      // }
      // if(y > height_ * 2/3) {
      //   p.color = Color{0.0f, 0.0f, 0.0f};
      // }

      // p.color = Color(0.0f, 1.0f, 0.0f);

      Ray strahlcurrent = cam.calcEyeRay(x, y);
      p.color = trace(strahlcurrent, scene_);

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}


Color Renderer::trace(Ray const& strahl, Scene const& scene) {
  
/* Die trace-Funktion sucht das vorderste Objekt in der Szene und ruft die shade-Funktion auf */

Color result{1, 1, 0.6};
  hitpoint closest_hit = hitpoint();
  std::shared_ptr<Shape> first = nullptr;
  Color schatten_col = {0.0f, 0.0f, 0.0f};

  float closest_dist = std::numeric_limits<float>::max();
  for(auto element : scene.shapes) {
    hitpoint hit = element->intersect(strahl);
    if(hit.cut == true){
      if(hit.distance < closest_dist){
        closest_dist = hit.distance;
        closest_hit = hit;
        first = element;
      }
    }

    // schatten_col = shadow(hit, scene);

      // if(element->intersect(strahl).distance < smallest.distance){
      //   return shade(element->intersect(strahl), scene);
      // }
      //return {1.0f, 1.0f, 1.0f};
  }
  if (closest_hit.cut) {
    result = shade(closest_hit, scene, first);

    // Normieren (3D-Effekte waren weg)
    // float sum = result.r + result.g + result.b;
    // result.r = result.r / sum;
    // result.g = result.g / sum;
    // result.b = result.b / sum;

    // result.r *= 0.1f;
    // result.g *= 0.1f;
    // result.b *= 0.1f;

    // result = tone_mapping(result); // -> wieder einfuegen!
  }
  
  return result;
}

Color Renderer::shade(hitpoint const& h, Scene const& scene, std::shared_ptr<Shape> const& shape_ptr) {

  /* Funktion zum "Schattieren" der Objekte, um einen 3D-Effekt zu erzeugen (-> z.B. sieht man statt eines Kreises eine Kugel :D) */

  Color result{0,0,0};
  Color schatten_col{0,0,0};

  for(auto it = scene.lights.begin(); it != scene.lights.end(); ++it) {
    
    /* fuer alle Lichtquellen wird ein Strahl vom Schnittpunkt auf dem Objekt zur Lichtquelle geschickt */

    glm::vec3 richtung_licht = (*it)->position_ - h.point3d;
    glm::vec3 normal = h.normale_; 
    float cos_angle = glm::cos(glm::angle(glm::normalize(normal), glm::normalize(richtung_licht)));
    // Ray strahl = {h.point3d + h.normale_ * 0.1f, richtung_licht};

    // hitpoint hit = shape_ptr->intersect(strahl);

    if (cos_angle > 0) {
      float value = cos_angle * scene.lights[0]->intensitaet_;

      float shade_r = (*it)->farbe_.r * h.col->kd.r * value;
      float shade_g = (*it)->farbe_.g * h.col->kd.g * value;
      float shade_b = (*it)->farbe_.b * h.col->kd.b * value;
      // std::cout << "{" << shade_r << ", " << shade_g << ", " << shade_b << "}\n";

      // schatten_col = shadow(h, scene); // -> wieder einfuegen!
      result += Color{shade_r, shade_g, shade_b};
      
      // if(hit.cut == true) { 
       
      //   // result.r = 1;
      //   // result.g = 1;
      //   result.b = 1; 
        
        
      // }
      // std::cout << result.b << "\n";
    }
  }
  // std::cout << result;


  // "provisorische" shadow-Funktion ;)
  for(auto shape : scene.shapes){
    if(shape == shape_ptr){
      // continue;
    }
    else{

      // Strahl wird vom Schnittpunkt des Objekts zur Lichtquelle geschossen
      glm::vec3 richtung_licht = (scene.lights[0])->position_ - h.point3d;
      Ray strahl = {h.point3d + h.normale_ * 0.1f, richtung_licht};

      // ueberpruefen, ob ein (anderes) Objekt zwischen dem Schnittpunkt (des Objekts) und der Lichtquelle liegt
      hitpoint hit = shape->intersect(strahl);

      if (hit.cut == true){
        result.b *= 0.8;
        result.r *= 0.8;
        result.g *= 0.8;
        // shape_ptr->print(std::cout);
      }
    }
  }
  


  // Schatten
  // result.r = result.r * schatten_col.r;
  // result.g = result.g * schatten_col.g;
  // result.b = result.b * schatten_col.b;
  // result += schatten_col; // -> wieder einfuegen!

  // Ambiente Beleuchtung dazuaddieren
  // result += calculate_ambient(shape_ptr, scene);

  // float shade_r = h.col->kd.r / (h.distance + h.col->kd.r);
  // float shade_g = h.col->kd.g / (h.distance + h.col->kd.g);
  // float shade_b = h.col->kd.b / (h.distance + h.col->kd.b);

  return result;
}

Color Renderer::shadow(hitpoint const& h, Scene const& scene) {

  /* Funktion, die Schatten auf das Objekt A werfen soll, wenn ein Objekt B zwischen der Lichtquelle und einem Objekt A liegt */

  Color schatten = {1.0f, 1.0f, 1.0f};
  Color farbe = {0.0f, 0.0f, 0.0f};
  float shadow_r = 1;
  float shadow_g = 1;
  float shadow_b = 1;
  bool we_see_light = false;

  for(auto light : scene.lights) {
    we_see_light = true;
    glm::vec3 strahl_objekt_zu_lichtquelle = glm::normalize(light->position_ - h.point3d);
    Ray strahl{};
    strahl.origin = h.point3d + 0.1f * h.normale_; // + 0.1f * h.normale gegen Rundungsfehler (Punkt koennte innerhalb des Objektes liegen)
    strahl.direction = strahl_objekt_zu_lichtquelle;
    for(auto shape : scene.shapes) {
      hitpoint object_point = shape->intersect(strahl);
   
      if(object_point.cut == true) {

        // h.col->kd = glm::normalize(h.col->kd + schatten + scene.ambient->standard_);
        // return h.col->kd;
        
        we_see_light = false;
        // return Color{0,0,0};
        break;

      }
    }

    if(we_see_light == true) {
      // std::cout << "we see light";
      // farbe += light->farbe_;
      
      float skalarprodukt = (h.normale_.x * strahl_objekt_zu_lichtquelle.x + h.normale_.y * strahl_objekt_zu_lichtquelle.y + h.normale_.z * strahl_objekt_zu_lichtquelle.z);
      if(skalarprodukt > 0) {
      
        // std::cout << "huhu";
        // std::cout << skalarprodukt << " ";
      
        float r = h.col->kd.r * light->intensitaet_ * skalarprodukt;
        float g = h.col->kd.g * light->intensitaet_ * skalarprodukt;
        float b = h.col->kd.b * light->intensitaet_ * skalarprodukt;
        Color current_farbe = {r, g, b};
        schatten.r += current_farbe.r;
        schatten.g += current_farbe.g;
        schatten.b += current_farbe.b;

        // schatten.r *= 0.1f;
        // schatten.g *= 0.1f;
        // schatten.b *= 0.1f;

        // std::cout << "Rot: " << schatten.r << " Gruen: " << schatten.g << " Blau: " << schatten.b;

        // if(schatten.r > 1) {
        //   schatten.r = 1;
        // }
        // else if(schatten.r < 0) {
        //   schatten.r = 0;
        // }
        // if(schatten.g > 1) {
        //   schatten.g = 1;
        // }
        // else if(schatten.g < 0) {
        //   schatten.g = 0;
        // }
        // if(schatten.b > 1) {
        //   schatten.b = 1;
        // }
        // else if(schatten.b < 0) {
        //   schatten.b = 0;
        // }

        // return schatten;
        return Color{1,1,1};
        // return farbe;
      }
    }
  }
  return Color{0,0,0};
  // return h.col->kd;
}

Color Renderer::calculate_ambient(std::shared_ptr<Shape> shape, Scene const& scene) {

  /* Funktion berechnet das ambiente Licht */

 float amb_r =  scene.ambient->standard_.r * shape->get_Material()->ka.r;
 float amb_g =  scene.ambient->standard_.g * shape->get_Material()->ka.g;
 float amb_b =  scene.ambient->standard_.b * shape->get_Material()->ka.b;

  return Color{amb_r, amb_g, amb_b};
} 

Color Renderer::tone_mapping(Color& color){
  float tone_r = color.r / (color.r + 1);
  float tone_g = color.g / (color.g + 1);
  float tone_b = color.b / (color.b + 1);

  return Color{tone_r, tone_g, tone_b};
}