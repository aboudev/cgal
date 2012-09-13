
namespace CGAL {

/*!
\ingroup PkgSurfaceMeshSimplification

The class `Surface_mesh_simplification::LindstromTurk_cost` provides a model for the `GetCost` concept. 
It computes the collapse cost following the Lindstrom-Turk strategy 
(Section \ref SurfaceMeshSimplificationLindstromTurkStrategy) 

The class `Surface_mesh_simplification::LindstromTurk_cost` has one template argument: the type of surface being simplified. 
It must be a model of the `EdgeCollapsableMesh` concept. 

\models ::GetCost 

\sa `CGAL::Surface_mesh_simplification::LindstromTurk_placement<ECM>` 

*/
template< typename ECM >
class Surface_mesh_simplification::LindstromTurk_cost {
public:

/// \name Creation 
/// @{

/*! 
Initializes the policy with the given <I>weighting unit factor</I>. 
See \ref SurfaceMeshSimplificationLindstromTurkStrategy for details on the meaning of this factor. 
*/ 
LindstromTurk_cost<ECM>( FT const& factor = FT(0.5) ); 

/// @} 

/// \name Operations 
/// @{

/*! 
Returns the cost of collapsing the edge (represented by its profile) considering 
the new `placement` computed for it. 
*/ 
result_type operator()( Profile const& profile 
, boost::optional<Point> const& placement ) const; 

/// @}

}; /* end Surface_mesh_simplification::LindstromTurk_cost */
} /* end namespace CGAL */
