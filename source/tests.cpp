#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "../framework/shape.hpp"
#include "../framework/Sphere.hpp"
#include "../framework/box.hpp"
#include "../framework/ray.hpp"
#include "../framework/hitpont.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "../framework/material.hpp"
#include "scene.hpp"
#include <memory>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

/*TEST_CASE("sphere: area() & volume()", "[sphere]"){
  std::cout<<"Task 1\n\n";
  Material mat{"mat",Color{0.0f,0.0f,0.0f},Color{1.0f,1.0f,1.0f},Color{1.0f,0.0f,1.0f}, 2.0f};
  auto mat1 = std::make_shared<Material>(mat);
  Sphere s1 {"s1",mat1,{-10.0f,-10.0f,-10.0f}, 3.0f}; //negativer radius?
  Sphere s2;
    
  REQUIRE(Approx(314.159) == s1.area());
  REQUIRE(Approx(523.599) == s1.volume());
  REQUIRE(Approx(0.0f) == s2.area());
  REQUIRE(Approx(0.0f) == s2.volume());
}*/

// TEST_CASE("box: area() & volume()", "[box]"){
//   Box b1{"b1", {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {5.0f,5.0f,5.0f}};
//   Box b2{"b2", {0.0f, 1.0f, 0.0f},  {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f}, {3.0, -7.0f, 20.0f}};
//   Box b3;

//   REQUIRE(Approx(150.0f) == b1.area());
//   REQUIRE(Approx(125.0f) == b1.volume());
//   REQUIRE(Approx(-202.0f) == b2.area());
//   REQUIRE(Approx(-420.0f) == b2.volume());
//   REQUIRE(Approx(0.0f) == b3.area());
//   REQUIRE(Approx(0.0f) == b3.volume());
// }

// TEST_CASE("box: print()", "[box]"){
//   std::cout<<"\nTask 4 & 5\n\n";
//   Box b1{"b1", {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {5.0f,5.0f,5.0f}};
//   Box b2{"b2", {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {3.0, -7.0f, 20.0f}};
//   Box b3;

//   std::cout <<"Boxes: \n";
//   std::cout << b1;
//   std::cout << b2;
//   std::cout << b3;
//   std::cout << "\n";
// }

// TEST_CASE("sphere: print()", "[sphere]"){
//   Sphere s1 {"s1", {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f}, 5.0f}; //negativer radius?
//   Sphere s2;

//   std::cout <<"Spheres: \n";
//   std::cout << s1;
//   std::cout << s2;
// }

TEST_CASE ( "intersect_ray_sphere","[intersect]" )
{
//   // Ray
//   glm::vec3 ray_origin{0.0f , 0.0f , 0.0f }; //1
//   // ray direction has to be normalized !
//   // you can use :
//   //v = glm::normalize ( some_vector )
//   glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
//   // Sphere
//   glm::vec3 sphere_center{0.0f ,0.0f , 5.0f};
//   float sphere_radius{1.0f };
  
//   float distance = 0.0f;
//   auto result = glm::intersectRaySphere (
//     ray_origin , ray_direction ,
//     sphere_center ,
//     sphere_radius*sphere_radius , // squared radius !!!
//     distance);
//   REQUIRE (distance == Approx(4.0f));
//   Color col = {0.0f, 0.0f, 1.0f};
//   float distance1 = 0.0f;
//   float distance2 = 0.0f;

//   Sphere s1{" ", col, glm::vec3{0.0f, 0.0f, 4.0f}, 1.0f};
//     Sphere s2{" ", col, glm::vec3{10.0f, 10.0f, 10.0f}, 1.0f};
//     Ray ray1{{0.0f, 0.0f, -2.0f},{0.0f, 0.0f, 2.5f}};
//     Ray ray2{{0.0f, 0.0f,  0.0f},{0.0f, -1.0f, 0.0f}};
    
//     hitpoint a = s1.intersect(ray1);
//     hitpoint b = s2.intersect(ray2);
//     REQUIRE (a.distance == 5.0f);
//     // REQUIRE (b.cut == false);

Material mat = {"mat", {1,1,1}, {1,1,1}, {1,1,1}, 400};
auto m = std::make_shared<Material>(mat);
Sphere s{"Kugel", m, glm::vec3{0,0,0}, 5.0f};
Ray r = {{0,0,4}, {0,0,-1}};

hitpoint h = s.intersect(r);
std::cout << "xxx {" << h.point3d.x << ", " << h.point3d.y << ", " << h.point3d.z << "} \n"; 


}

// TEST_CASE("destruktor", "[destruktor]"){
//   std::cout << "\nTask 8\n\n";
// //mit virtual
// //sphere0 konstruktor, sphere1 konstruktor, sphere0 destr, sphere1 destr
// //ohne virtual
// //sphere0 konstruktor, sphere1 konstruktor, shape destr, shape destr
//   Color red {255 ,0 ,0 };
//   glm::vec3 position{0.0f ,0.0f ,0.0f};
//   Sphere* s1 = new Sphere{"sphere0", red, position ,1.2f};
//   Shape* s2 = new Sphere{"sphere1",red ,position ,1.2f };
//   s1-> print (std::cout);
//   s2-> print (std::cout );
//   delete s1;
//   delete s2;
// }

TEST_CASE("intersect Box", "[Task 6.3]") {
  Color col = {0.0f, 0.0f, 1.0f};
  float distance1 = 0.0f;
  Material mat{"mat",Color{0.0f,0.0f,0.0f},Color{1.0f,1.0f,1.0f},Color{1.0f,0.0f,1.0f}, 2.0f};
  auto mat1 = std::make_shared<Material>(mat);

  glm::vec3 v = {0.0f, 1.0f, 0.0f};
  glm::normalize(v);
  Box b1("Box 1",mat1 , {-1.0f, 1.0f, -2.0f}, {6.0f, 4.0f, 1.0f});
  Ray ray1{{0.0f, 0.0f, 0.0f}, v};

  hitpoint a = b1.intersect(ray1);
  std::cout <<"\n" << b1;
  REQUIRE(a.distance == 1.0f);
  REQUIRE(a.cut == true);
}

TEST_CASE("input Datei", "[Task 6.5]") {
  Scene obj;
  std::string s = "Beispiel1.sdf";
  obj = input(s/*, obj*/);
  //std::cout << obj.container1.at(0)->ka.r;
}

// TEST_CASE("find_vector", "[Task 6.5]"){
//   std::cout << "Task 6.5 find-Funktionen" << std::endl;
//   Scene obj;
//   std::string s = "Beispiel-Datei.sdf";
//   obj = input(s, obj);
//   std::string test = "green";
//   auto p = obj.find_vector(test);
//   REQUIRE(p->name_ == test);
//   REQUIRE(p->m == 50);

//   std::string test2 = "red";
//   auto p2 = obj.find_vector(test2);
//   REQUIRE(p2->name_ == test2);
//   REQUIRE(p2->m == 20);

//   std::string test3 = "blue";
//   auto p3 = obj.find_vector(test3);
//   REQUIRE(p3->name_ == test3);
//   REQUIRE(p3->m == 10);

//   std::string test4 = "yellow";
//   auto p4 = obj.find_vector(test4);
//   REQUIRE(p4 == nullptr);
// }

// TEST_CASE("find_set", "[Task 6.5]"){
//   Scene obj;
//   std::string s = "Beispiel-Datei.sdf";
//   obj = input(s, obj);
//   std::string test = "green";
//   auto p = obj.find_set(test);
//   REQUIRE(p->name_ == test);
//   REQUIRE(p->m == 50);

//   std::string test2 = "red";
//   auto p2 = obj.find_set(test2);
//   REQUIRE(p2->name_ == test2);
//   REQUIRE(p2->m == 20);

//   std::string test3 = "blue";
//   auto p3 = obj.find_set(test3);
//   REQUIRE(p3->name_ == test3);
//   REQUIRE(p3->m == 10);

//   std::string test4 = "yellow";
//   auto p4 = obj.find_set(test4);
//   REQUIRE(p4 == nullptr);
// }


TEST_CASE("find_map", "[Task 6.5]"){
  std::cout << "Task 6.5 find-map-Funktion" << std::endl;
  Scene obj;
  std::string s = "Beispiel-Datei.sdf";
  obj = input(s/*, obj*/);
  std::string test = "green";
  auto p = obj.find_map(test);
  REQUIRE(p->name_ == test);
  REQUIRE(p->m == 50);

  std::string test2 = "red";
  auto p2 = obj.find_map(test2);
  REQUIRE(p2->name_ == test2);
  REQUIRE(p2->m == 20);

  std::string test3 = "blue";
  auto p3 = obj.find_map(test3);
  REQUIRE(p3->name_ == test3);
  REQUIRE(p3->m == 10);

  std::string test4 = "yellow";
  auto p4 = obj.find_map(test4);
  REQUIRE(p4 == nullptr);
}


int main(int argc, char *argv[])
{
    // std::ifstream f;    
    // std::string s;
    // f.open(argv[1], std::ios::in);
    // while(!(f.eof())){
    //     getline(f, s);
    //     std::cout << s << std::endl;
    // }
    // f.close();

    // std::fstream f;  
    // char cstring[256];
    // f.open(argv[1], std::ios::in);
    // while(!(f.eof())){
    //     f.getline(cstring, sizeof(cstring));
    //     std::cout << cstring << std::endl;
    // }
    // f.close();

    // std::vector<std::string> textFile;
    // std::string fileLine;
    // std::ifstream file;

    // file.open("Beispiel-Datei.sdf");
    // if(file.is_open() == true){
    //    std::cout << "huhu";
    //   while(std::getline(file, fileLine)){
    //     textFile.push_back(fileLine);
    //     std::cout << fileLine;
    //   }
    //   file.close();
    // }
   

  return Catch::Session().run(argc, argv);
}
