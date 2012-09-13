
namespace CGAL {

/*!
\ingroup PkgSurfaceMeshSimplification

The class `Surface_mesh_simplification::LindstromTurk_placement` provides a model for the `GetPlacement` concept. 
It computes the placement, that is, the new position for the remaining vertex after 
a halfedge-collapse, following the Lindstrom-Turk strategy 
(Section \ref SurfaceMeshSimplificationLindstromTurkStrategy). 

The class `Surface_mesh_simplification::LindstromTurk_placement` has one template argument: the type of surface being simplified. 
It must be a model of the `EdgeCollapsableMesh` concept. 

\models ::GetPlacement 

\sa `CGAL::Surface_mesh_simplification::LindstromTurk_cost<ECM>` 

*/
template< typename ECM >
class Surface_mesh_simplification::LindstromTurk_placement {
public:

/// \name Creation 
/// @{

/*! 
Initializes the policy with the given <I>weighting unit factor</I>. 
See \ref SurfaceMeshSimplificationLindstromTurkStrategy for details on the meaning of this factor. 
*/ 
LindstromTurk_placement<ECM>( FT const& factor = FT(0.5) ); 

/// @} 

/// \name Operations 
/// @{

/*! 
Returns the new position for the remaining vertex after collapsing the edge 
(represented by its profile). 
*/ 
result_type operator()( Profile const& edge_profile ) const; 

/// @}

}; /* end Surface_mesh_simplification::LindstromTurk_placement */
} /* end namespace CGAL */
