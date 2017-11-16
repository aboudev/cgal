#ifndef CGAL_SURFACE_MESH_APPROXIMATION_VSA_MESH_SEGMENTATION_H
#define CGAL_SURFACE_MESH_APPROXIMATION_VSA_MESH_SEGMENTATION_H

#include <CGAL/license/Surface_mesh_approximation.h>


#include <CGAL/vsa_metrics.h>
#include <CGAL/vsa_approximation.h>
#include <CGAL/internal/Surface_mesh_approximation/named_function_params.h>
#include <CGAL/internal/Surface_mesh_approximation/named_params_helper.h>

#include <CGAL/Polyhedron_3.h>
#include <CGAL/property_map.h>

#include <boost/graph/graph_traits.hpp>
#include <boost/optional.hpp>

namespace CGAL {
namespace VSA {

/*!
 * \ingroup PkgTSMA
 * @brief variational shape approximation segmentation a triangulated mesh.
 * This function segment the input triangulated mesh by the variational shape approximation algorithm.
 *
 * @tparam TriangleMesh model of `FaceGraph`.
 *         The descriptor types `boost::graph_traits<TriangleMesh>::%face_descriptor`
 *         and `boost::graph_traits<TriangleMesh>::%halfedge_descriptor` must be
 *         models of `Hashable`.
 *         If `TriangleMesh` has an internal property map for `CGAL::face_index_t`,
 *         and no `face_index_map` is given
 *         as a named parameter, then the internal one should be initialized
 * @tparam NamedParameters a sequence of \ref namedparameters
 *
 * @param tm_in a triangulated surface mesh to be segmented
 * @param np optional sequence of \ref namedparameters among the ones listed below
 *
 * \cgalNamedParamsBegin
 *  \cgalParamBegin{geom_traits} a geometric traits class instance, model of `Kernel`.
 *    Exact constructions kernels are not supported by this function.
 *  \cgalParamEnd
 *  \cgalParamBegin{vertex_point_map} the property map with the points associated
 *    to the vertices of `tm_in`. Instance of a class model of `ReadWritePropertyMap`.
 *  \cgalParamEnd
 *  \cgalParamBegin{init_method} the selection of seed initialization method.
 *  \cgalParamEnd
 *  \cgalParamBegin{max_nb_proxies} the maximum number of proxies is reached.
 *  \cgalParamEnd
 *  \cgalParamBegin{min_error_drop} the minimum error drop of the approximation.
 *  \cgalParamEnd
 *  \cgalParamBegin{iterations} the relaxation iterations after seeding.
 *  \cgalParamEnd
 *  \cgalParamBegin{inner_iterations} the relaxation iterations when seeding.
 *  \cgalParamEnd
 *  \cgalParamBegin{face_proxy_map} a property map containing the assigned proxy index of each face of `tm_in`
 *  \cgalParamEnd
 *  \cgalParamBegin{proxies} the plane proxies
 *  \cgalParamEnd
 * \cgalNamedParamsEnd
 */
template <typename TriangleMesh,
  typename NamedParameters>
void mesh_segmentation(const TriangleMesh &tm_in, const NamedParameters &np)
{
  using boost::get_param;
  using boost::choose_param;

  typedef typename GetGeomTraits<TriangleMesh, NamedParameters>::type Geom_traits;
  typedef typename Geom_traits::FT FT;

  typedef typename GetVertexPointMap<TriangleMesh, NamedParameters>::type Vertex_point_map;
  Vertex_point_map point_pmap = choose_param(get_param(np, internal_np::vertex_point),
    get_property_map(vertex_point, const_cast<TriangleMesh &>(tm_in)));

  typedef CGAL::VSA::Mesh_approximation<TriangleMesh, Vertex_point_map> L21_approx;
  typedef typename L21_approx::Error_metric L21_metric;
  typedef typename L21_approx::Proxy_fitting L21_proxy_fitting;

  L21_approx approx(tm_in, point_pmap);
  L21_metric l21_metric(tm_in);
  L21_proxy_fitting l21_fitting(tm_in);
  approx.set_metric(l21_metric, l21_fitting);

  // default random initialization
  CGAL::VSA::Seeding method = choose_param(
    get_param(np, internal_np::init_method), CGAL::VSA::Hierarchical);
  boost::optional<std::size_t> max_nb_proxies = choose_param(
    get_param(np, internal_np::max_nb_proxies), boost::optional<std::size_t>());
  boost::optional<FT> min_error_drop = choose_param(
    get_param(np, internal_np::min_error_drop), boost::optional<FT>());
  std::size_t inner_iterations = choose_param(get_param(np, internal_np::inner_iterations), 10);
  if (max_nb_proxies && !min_error_drop) {
    if (*max_nb_proxies < num_faces(tm_in))
      approx.init_by_number(method, *max_nb_proxies, inner_iterations);
    else {
#ifdef CGAL_SURFACE_MESH_APPROXIMATION_DEBUG
      std::cerr << "Error: max_nb_proxies out of range." << std::endl;
#endif
      return;
    }
  }
  else if (!max_nb_proxies && min_error_drop)
    approx.init_by_error(method, *min_error_drop, inner_iterations);
  else if (max_nb_proxies && min_error_drop)
    approx.init(method, *max_nb_proxies, *min_error_drop, inner_iterations);
  else // default by minimum error drop of 10%
    approx.init_by_error(method, FT(0.1), inner_iterations);

  const std::size_t iterations = choose_param(get_param(np, internal_np::iterations), 10);
  approx.run(iterations);

#ifdef CGAL_SURFACE_MESH_APPROXIMATION_DEBUG
  std::cout << "#px = " << approx.get_proxies_sizes()
    << ", #itr = " << iterations
    << ", #inner_itr = " << inner_iterations << std::endl;
#endif

  typedef typename boost::lookup_named_param_def<
    internal_np::facet_proxy_map_t,
    NamedParameters,
    internal_np::vsa_no_output_t>::type FPMap;
  FPMap fproxymap = choose_param(
    get_param(np, internal_np::facet_proxy_map), internal_np::vsa_no_output);
  get_proxy_map(approx, fproxymap);

  typedef typename boost::lookup_named_param_def <
    internal_np::proxies_t,
    NamedParameters,
    internal_np::vsa_no_output_t>::type ProxiesOutItr;
  ProxiesOutItr pxies_out_itr = choose_param(
    get_param(np, internal_np::proxies), internal_np::vsa_no_output);
  get_proxies(approx, pxies_out_itr);
}

} // end namespace VSA
} // end namespace CGAL

#endif // CGAL_SURFACE_MESH_APPROXIMATION_VSA_MESH_SEGMENTATION_H
