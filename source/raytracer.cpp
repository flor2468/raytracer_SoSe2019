#include <renderer.hpp>
#include <window.hpp>
#include "scene.hpp"
#include "shape.hpp"
#include "Sphere.hpp"
#include "box.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./checkerboard.ppm";
  
  std::string const filename2 = "Beispiel1.sdf";

  Renderer renderer{image_width, image_height, filename};

  Camera /*const&*/ cam1{};
  Scene scene1 = Scene {};
  Material mat1{"mat1", Color{1.0f, 1.0f, 1.0f}, Color{1.0f, 1.0f, 1.0f}, Color{1.0f, 1.0f, 1.0f}, 2.0f};
  auto mat_ptr1 = std::make_shared<Material>(mat1);
  Sphere sphere1{"Kugel 1", mat_ptr1, {0.0f, 0.0f, -5.0f}, 1.0f};
  std::shared_ptr<Shape> sphere_ptr1 = std::make_shared<Sphere>(sphere1);
  scene1.shapes.push_back(sphere_ptr1);

  //create separate thread to see updates of pixels while rendering
  std::thread render_thread([&renderer]() {renderer.render();});

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  render_thread.join();
  return 0;
}
