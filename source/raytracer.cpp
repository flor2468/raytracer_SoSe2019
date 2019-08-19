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
  std::string const bildname1 = "./checkerboard.ppm";
  
  std::string filename1 = "./Test.sdf";
  
  if(argc > 1) {
    filename1 = argv[1];
  }



  for(int num = 0; num <= 360; ++num) {

    std::stringstream s; // = "./Testbild" << num << ".ppm";
    s << "./Kugelbild" << num << ".ppm";

    std::string const bildname2 = s.str();
    
    std::string const filename2 = "./Kugel_Scene.sdf";

    // Renderer renderer{image_width, image_height, filename};

    // Camera /*const&*/ cam1{};
    // Scene scene1 = Scene {};
    // Material mat1{"mat1", Color{1.0f, 1.0f, 1.0f}, Color{1.0f, 1.0f, 1.0f}, Color{1.0f, 1.0f, 1.0f}, 2.0f};
    // auto mat_ptr1 = std::make_shared<Material>(mat1);
    // Sphere sphere1{"Kugel 1", mat_ptr1, {0.0f, 0.0f, -5.0f}, 1.0f};
    // std::shared_ptr<Shape> sphere_ptr1 = std::make_shared<Sphere>(sphere1);
    // scene1.shapes.push_back(sphere_ptr1);

    Scene scene1 = input(filename1);

    Scene scene2 = output(filename2, num);

    Renderer renderer{image_width, image_height, bildname1, scene1};

    Renderer renderer_animation{image_width, image_height, bildname2, scene2};

    
    // // TEST Anfang
    // Ray testray;
    // renderer.trace(testray, scene1);
    // renderer.render();
    // // TEST Ende

    //create separate thread to see updates of pixels while rendering
    //std::thread render_thread([&renderer]() {renderer.render();});

    renderer_animation.render();

    // Window window{{image_width, image_height}};

    // while (!window.should_close()) {
    //   if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    //     window.close();
    //   }
    //   window.show(renderer.color_buffer());
    // // window.close();
    // }

    //"join" threads, i.e. synchronize main thread with render_thread
    //render_thread.join();

    std::cout << "hallooo";

  }
  return 0;
}
