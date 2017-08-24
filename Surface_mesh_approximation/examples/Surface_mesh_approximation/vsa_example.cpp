#include <iostream>
#include <fstream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/vsa_mesh_approximation.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;

int main()
{
  // create and read Polyhedron
  Polyhedron input;
  std::ifstream file("data/bear.off");
  if (!file || !(file >> input) || input.empty()) {
    std::cerr << "Invalid off file." << std::endl;
    return EXIT_FAILURE;
  }

  // output data
  Polyhedron output;
  std::vector<int> triangles;
  std::vector<Kernel::Point_3> anchors;

  // free function interface with named parameters, seperated with dots
  CGAL::vsa_mesh_approximation(input, output,
    CGAL::VSA::parameters::number_of_proxies(200). // number of fitting proxies
      number_of_iterations(30). // number of iterations
      init_method(1). // hierarchical init
      anchor_point(std::back_inserter(anchors)). // get anchor points
      indexed_triangles(std::back_inserter(triangles))); // get indexed triangles

  std::cout << "#anchors: " << anchors.size() << std::endl;
  std::cout << "#triangles: " << triangles.size() << std::endl;

  return EXIT_SUCCESS;
}
