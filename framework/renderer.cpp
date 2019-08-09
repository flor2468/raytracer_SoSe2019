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

  }
  if (closest_hit.cut) {
    result = shade(closest_hit, scene, first);

    // result = tone_mapping(result); 
  }
  
  return result;
}

Color Renderer::shade(hitpoint const& h, Scene const& scene, std::shared_ptr<Shape> const& shape_ptr) {

  /* Funktion zum "Schattieren" der Objekte, um einen 3D-Effekt zu erzeugen (-> z.B. sieht man statt eines Kreises eine Kugel :D) */

  Color result{0,0,0};
  Color ambient = calculate_ambient(shape_ptr, scene); 
  Color diffus = calculate_diffus(shape_ptr, scene, h);
  Color specular = calculate_specular(shape_ptr, scene, h);

  for(auto light : scene.lights){

    bool light_visible = true;

    for(auto shape : scene.shapes) {

      hitpoint hit{};

      if(shape != shape_ptr) {

        // Strahl wird vom Schnittpunkt des Objekts zur Lichtquelle geschossen
        glm::vec3 richtung_licht = light->position_ - h.point3d;
        Ray strahl = {h.point3d + h.normale_ * 0.1f, richtung_licht};

        // ueberpruefen, ob ein (anderes) Objekt zwischen dem Schnittpunkt (des Objekts) und der Lichtquelle liegt
        hit = shape->intersect(strahl);

        if(hit.cut == true){
          light_visible = false;
        }
      }

      // Berechnung der Farben = Ambient + Diffus + Specular 
      //if (hit.cut == false || hit.distance < 0) {
      if (light_visible == true || hit.distance < 0) {

        result.r = result.r + (light->farbe_.r * (diffus.r + specular.r));
        result.g = result.g + (light->farbe_.g * (diffus.g + specular.g));
        result.b = result.b + (light->farbe_.b * (diffus.b + specular.b));

        result = tone_mapping(result);

      }
    }
  }

  result += ambient;

  return result;
}

Color Renderer::calculate_ambient(std::shared_ptr<Shape> shape, Scene const& scene) {

  /* Funktion berechnet das ambiente Licht */

 float amb_r =  scene.ambient->standard_.r * shape->get_Material()->ka.r;
 float amb_g =  scene.ambient->standard_.g * shape->get_Material()->ka.g;
 float amb_b =  scene.ambient->standard_.b * shape->get_Material()->ka.b;

  return Color{amb_r, amb_g, amb_b};
} 

Color Renderer::calculate_diffus(std::shared_ptr<Shape> shape, Scene const& scene, hitpoint const& h) {

  Color sum{0,0,0};

  for(auto it = scene.lights.begin(); it != scene.lights.end(); ++it) {
    
    /* fuer alle Lichtquellen wird ein Strahl vom Schnittpunkt auf dem Objekt zur Lichtquelle geschickt */
    /* Berechnung des diffuses Lichts (Schattierung -> d.h. man sieht eine Kugel anstatt eines Kreises) */

    glm::vec3 richtung_licht = (*it)->position_ - h.point3d;
    glm::vec3 normal = h.normale_; 
    float cos_angle = glm::cos(glm::angle(glm::normalize(normal), glm::normalize(richtung_licht)));

    if (cos_angle > 0) {
      float value = cos_angle * scene.lights[0]->intensitaet_;

      float shade_r = (*it)->farbe_.r * h.col->kd.r * value;
      float shade_g = (*it)->farbe_.g * h.col->kd.g * value;
      float shade_b = (*it)->farbe_.b * h.col->kd.b * value;

      sum += Color{shade_r, shade_g, shade_b};
    }
  }

  return sum;
}

Color Renderer::calculate_specular(std::shared_ptr<Shape> shape, Scene const& scene, hitpoint const& h) {
  Color sum{0,0,0};

  for(auto it = scene.lights.begin(); it != scene.lights.end(); ++it) {

    glm::vec3 richtung_licht = (*it)->position_ - h.point3d;
    richtung_licht = glm::normalize(richtung_licht);
    glm::vec3 r = {};
    
    // r.x = (2 * (h.normale_.x * richtung_licht.x) * h.normale_.x) - richtung_licht.x;
    // r.y = (2 * (h.normale_.y * richtung_licht.y) * h.normale_.y) - richtung_licht.y;
    // r.z = (2 * (h.normale_.z * richtung_licht.z) * h.normale_.z) - richtung_licht.z;

    r = 2 * glm::dot(h.normale_, richtung_licht) * h.normale_ - richtung_licht;

    r = glm::normalize(r);

    glm::vec3 v = {0,0,0};
    v = v - h.point3d;
    v = glm::normalize(v);

    float cos_beta;

    if(glm::dot(r, v) > 0) {
      cos_beta = std::pow(glm::dot(r, v), h.col->m);
    }
    else{
      cos_beta = 0;
    }

    sum.r += ((*it)->farbe_.r * h.col->ks.r * cos_beta);
    sum.g += ((*it)->farbe_.g * h.col->ks.g * cos_beta);
    sum.b += ((*it)->farbe_.b * h.col->ks.b * cos_beta);

  }
  return sum;
}

Color Renderer::tone_mapping(Color& color){
  float tone_r = color.r / (color.r + 1);
  float tone_g = color.g / (color.g + 1);
  float tone_b = color.b / (color.b + 1);

  return Color{tone_r, tone_g, tone_b};
}

Ray transformRay(glm::mat4 const& mat, Ray const& ray) {

  glm::vec4 origin_homogen = {ray.origin.x, ray.origin.y, ray.origin.z, 1};
  glm::vec4 direction_homogen = {ray.direction.x, ray.direction.y, ray.direction.z, 0};

  origin_homogen = mat * origin_homogen;
  direction_homogen = mat * direction_homogen;

  glm::vec3 transform_origin = {origin_homogen.x, origin_homogen.y, origin_homogen.z}; 
  glm::vec3 transform_direction = {direction_homogen.x, direction_homogen.y, direction_homogen.z}; 

  return Ray{transform_origin, transform_direction};
}

void Renderer::transformation(std::shared_ptr<Shape> const& s, Scene const& scene, glm::vec3 verschiebung) {
  /* Verschiebung des Objekts || Zoomen des Objekts || Drehen des Objekts */

  // Berechnen: Vektoren, Punkte und Normalen

}

glm::vec3 reTransformPoint(glm::vec3 const& p, glm::mat4 mat) {
  glm::vec4 p_homogen = {p.x, p.y, p.z, 1};
  glm::vec4 punkt_retransformiert = mat * p_homogen;
  return glm::vec3{punkt_retransformiert.x, punkt_retransformiert.y, punkt_retransformiert.z};
}

glm::vec3 reTransformVector(glm::vec3 const& v, glm::mat4 mat) {
  glm::vec4 v_homogen = {v.x, v.y, v.z, 0};

  // glm::mat4 testmatrix = {
  //   glm::vec4 {1, 0, 0, 0},
  //   glm::vec4 {0, 1, 0, 0},
  //   glm::vec4 {0, 0, 1, 0},
  //   glm::vec4 {0, 0, 0, 1},
  // };

  // testmatrix[0][1] = 2;
  // testmatrix[0][2] = 3;
  // testmatrix[0][3] = 4;

  // std::cout << "{" << testmatrix[0].x << ", " << testmatrix[0].y << ", " << testmatrix[0].z << ", " << testmatrix[0].w << "}" << std::endl;

  mat[0][0] = 1;

  glm::vec4 vector_retransformiert = mat * v_homogen;
  return glm::vec3{vector_retransformiert.x, vector_retransformiert.y, vector_retransformiert.z};
}

glm::vec3 reTransformNormale(glm::vec3 const& n, glm::mat4 inverse) {
  // Transponierte inverse world_transformation_matrix

  glm::mat4 transponierte_inverse = glm::transpose(inverse);
  glm::vec4 normale_retransformiert = {n.x, n.y, n.z, 0};
  normale_retransformiert = transponierte_inverse * normale_retransformiert;
  return glm::vec3{n.x, n.y, n.z};
}
