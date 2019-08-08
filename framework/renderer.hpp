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
  Color calculate_diffus(std::shared_ptr<Shape> shape, Scene const& scene, hitpoint const& h);
  Color calculate_specular(std::shared_ptr<Shape> shape, Scene const& scene, hitpoint const& h);
  Color tone_mapping(Color& color);
  // Ray transformRay(glm::mat4 const& mat, Ray const& ray);
  void transformation(std::shared_ptr<Shape> const& s, Scene const& scene, glm::vec3 verschiebung);

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

Ray transformRay(glm::mat4 const& mat, Ray const& ray);
glm::vec3 reTransformPoint(glm::vec4 const& p);
glm::vec3 reTransformVector(glm::vec4 const& v);
glm::vec3 reTransformNormale(glm::vec4 const& n);

#endif // #ifndef BUW_RENDERER_HPP
