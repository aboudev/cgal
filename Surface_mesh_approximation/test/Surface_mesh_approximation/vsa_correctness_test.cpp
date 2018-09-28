#include <iostream>
#include <fstream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>

#include <CGAL/Polygon_mesh_processing/remesh.h>

#include <CGAL/Variational_shape_approximation.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Surface_mesh<Kernel::Point_3> Mesh;
typedef boost::graph_traits<Mesh>::face_descriptor face_descriptor;

typedef boost::property_map<Mesh, boost::vertex_point_t>::type Vertex_point_map;
typedef CGAL::Variational_shape_approximation<Mesh, Vertex_point_map> L21_approx;
typedef L21_approx::Error_metric L21_metric;

bool test_shape(const char *file_name, const std::size_t target_num_proxies)
{
  Mesh mesh;
  std::ifstream input(file_name);
  if (!input || !(input >> mesh) || !CGAL::is_triangle_mesh(mesh)) {
    std::cout << "Invalid input file." << std::endl;
    return false;
  }

  std::cout << "Testing \"" << file_name << '\"' << std::endl;
  // algorithm instance
  L21_metric error_metric(mesh,
    get(boost::vertex_point, const_cast<Mesh &>(mesh)));
  L21_approx approx(mesh,
    get(boost::vertex_point, const_cast<Mesh &>(mesh)),
    error_metric);

  // approximation, seeding from error, drop to the target error incrementally
  // should reach targeted number of proxies gradually
  const Kernel::FT drop(1e-8);
  const std::size_t num_iterations = 20;
  const std::size_t inner_iterations = 10;
  approx.initialize_seeds(CGAL::parameters::seeding_method(CGAL::Surface_mesh_approximation::INCREMENTAL)
    .min_error_drop(drop)
    .number_of_relaxations(inner_iterations));
  approx.run(num_iterations);

  // eliminate redundant area (local minima) by merging
  boost::optional<std::pair<std::size_t, std::size_t> > best_pair = boost::none;
  while ((best_pair = approx.find_best_merge(true)) != boost::none) {
    approx.merge(best_pair->first, best_pair->second);
    approx.run(num_iterations);
  }

  if (approx.number_of_proxies() != target_num_proxies) {
    std::cout << "#targeted - #result "
      << target_num_proxies << ' '
      << approx.number_of_proxies() << std::endl;

    std::cout << "Failed." << std::endl;
    return false;
  }

  std::cout << "Succeeded." << std::endl;
  return true;
}

/**
 * This file tests the correctness of the algorithm.
 * The correctness is verified by seeding by error
 * and check if the number of desired proxies are generated.
 * Basically we input a cube mesh and see if it outputs 6 proxies.
 */
int main()
{
  std::cout << "Correctness test." << std::endl;
  if (!test_shape("./data/cube.off", 6))
    return EXIT_FAILURE;

  if (!test_shape("./data/cube-ouvert.off", 5))
    return EXIT_FAILURE;

  std::cout << "Surface with disconnected components test." << std::endl;
  if (!test_shape("./data/cubes-merged.off", 11))
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
