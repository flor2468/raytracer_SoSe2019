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
#include <cmath>

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render(Camera const& camera1, Scene const& s1)
{
  std::size_t const checker_pattern_size = 20;

  Camera cam = camera1;

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

      if(y > height_/ 3) { 
        p.color = Color(1.0, 0.0, 0.0);
      }
      if(y < (height_/ 3)){
        p.color = Color(1.0f, 1.0f, 0.0f);
      }
      if(y > height_ * 2/3) {
        p.color = Color{0.0f, 0.0f, 0.0f};
      }

      Ray strahlcurrent = cam.calcEyeRay(x, y);
      trace(strahlcurrent, s1);

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
  hitpoint smallest;
  for(auto element : scene.shapes) {
    if((element->intersect(strahl)).cut == true){
      // if(element->intersect(strahl).distance < smallest.distance){
      //   return shade(element->intersect(strahl), scene);
      // }
      return {1.0f, 1.0f, 1.0f};
    }
  }
  return {0.0f, 0.0f, 0.0f};
}

Color Renderer::shade(hitpoint const& h, Scene const& scene) {

}
