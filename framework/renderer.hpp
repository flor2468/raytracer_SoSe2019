// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file, Scene scene);

  // vorher:
  // void render(Camera const& camera1, Scene const& s1);

  void render();
  void write(Pixel const& p);
  Color trace(Ray const& strahl, Scene const& scene);
  Color shade(hitpoint const& h, Scene const& scene, std::shared_ptr<Shape> const& shape_ptr);
  Color shadow(hitpoint const& h, Scene const& scene);
  Color calculate_ambient(std::shared_ptr<Shape> shape, Scene const& scene);
  Color calculate_diffus(std::shared_ptr<Shape> shape, Scene const& scene);
  Color calculate_specular(std::shared_ptr<Shape> shape, Scene const& scene);
  Color tone_mapping(Color& color);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
  //neu
  Scene scene_;
};

#endif // #ifndef BUW_RENDERER_HPP
