#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "Sphere.hpp"
#include "box.hpp"
#include "ray.hpp"
#include "hitpont.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

TEST_CASE("sphere: area() & volume()", "[sphere]"){
  std::cout<<"Task 1\n\n";
  Sphere s1 {"s1", {1.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f}, 5.0f}; //negativer radius?
  Sphere s2;
    
  REQUIRE(Approx(314.159) == s1.area());
  REQUIRE(Approx(523.599) == s1.volume());
  REQUIRE(Approx(0.0f) == s2.area());
  REQUIRE(Approx(0.0f) == s2.volume());
}

TEST_CASE("box: area() & volume()", "[box]"){
  Box b1{"b1", {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {5.0f,5.0f,5.0f}};
  Box b2{"b2", {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {3.0, -7.0f, 20.0f}};
  Box b3;

  REQUIRE(Approx(150.0f) == b1.area());
  REQUIRE(Approx(125.0f) == b1.volume());
  REQUIRE(Approx(-202.0f) == b2.area());
  REQUIRE(Approx(-420.0f) == b2.volume());
  REQUIRE(Approx(0.0f) == b3.area());
  REQUIRE(Approx(0.0f) == b3.volume());
}

TEST_CASE("box: print()", "[box]"){
  std::cout<<"\nTask 4 & 5\n\n";
  Box b1{"b1", {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {5.0f,5.0f,5.0f}};
  Box b2{"b2", {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {3.0, -7.0f, 20.0f}};
  Box b3;

  std::cout <<"Boxes: \n";
  std::cout << b1;
  std::cout << b2;
  std::cout << b3;
  std::cout << "\n";
}

TEST_CASE("sphere: print()", "[sphere]"){
  Sphere s1 {"s1", {1.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f}, 5.0f}; //negativer radius?
  Sphere s2;

  std::cout <<"Spheres: \n";
  std::cout << s1;
  std::cout << s2;
}

TEST_CASE ( "intersect_ray_sphere","[intersect]" )
{
  // Ray
  glm::vec3 ray_origin{0.0f , 0.0f , 0.0f }; //1
  // ray direction has to be normalized !
  // you can use :
  //v = glm::normalize ( some_vector )
  glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
  // Sphere
  glm::vec3 sphere_center{0.0f ,0.0f , 5.0f};
  float sphere_radius{1.0f };
  
  float distance = 0.0f;
  auto result = glm::intersectRaySphere (
    ray_origin , ray_direction ,
    sphere_center ,
    sphere_radius*sphere_radius , // squared radius !!!
    distance);
  REQUIRE (distance == Approx(4.0f));
  Color col = {0.0f, 0.0f, 1.0f};
  float distance1 = 0.0f;
  float distance2 = 0.0f;

  Sphere s1{" ", col, glm::vec3{0.0f, 0.0f, 4.0f}, 1.0f};
    Sphere s2{" ", col, glm::vec3{10.0f, 10.0f, 10.0f}, 1.0f};
    Ray ray1{{0.0f, 0.0f, -2.0f},{0.0f, 0.0f, 2.5f}};
    Ray ray2{{0.0f, 0.0f,  0.0f},{0.0f, -1.0f, 0.0f}};
    
    hitpoint a = s1.intersect(ray1, distance1);
    hitpoint b = s2.intersect(ray2, distance2);
    REQUIRE (distance1 == 5.0f);
    // REQUIRE (b.cut == false);
}

TEST_CASE("destruktor", "[destruktor]"){
  std::cout << "\nTask 8\n\n";
//mit virtual
//sphere0 konstruktor, sphere1 konstruktor, sphere0 destr, sphere1 destr
//ohne virtual
//sphere0 konstruktor, sphere1 konstruktor, shape destr, shape destr
  Color red {255 ,0 ,0 };
  glm::vec3 position{0.0f ,0.0f ,0.0f};
  Sphere* s1 = new Sphere{"sphere0", red, position ,1.2f};
  Shape* s2 = new Sphere{"sphere1",red ,position ,1.2f };
  s1-> print (std::cout);
  s2-> print (std::cout );
  delete s1;
  delete s2;
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
