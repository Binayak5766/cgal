// examples/Skin_surface_3/skin_surface_simple.C
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Skin_surface_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_skin_surface_3.h>
#include <list>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mixed_complex_traits_3<K>                     Traits;
typedef CGAL::Skin_surface_3<Traits>                        Skin_surface_3;
typedef Skin_surface_3::RT                                  RT;
typedef Skin_surface_3::Weighted_point                      Weighted_point;
typedef Weighted_point::Point                               Bare_point;
typedef CGAL::Polyhedron_3<CGAL::Simple_cartesian<double> > Polyhedron;

int main(int argc, char *argv[]) {
  std::list<Weighted_point> l;
  RT                        shrinkfactor = 0.5;

  l.push_front(Weighted_point(Bare_point( 1,-1,-1), 1.25));
  l.push_front(Weighted_point(Bare_point( 1, 1, 1), 1.25));
  l.push_front(Weighted_point(Bare_point(-1, 1,-1), 1.25));

  Skin_surface_3 skin_surface(l.begin(), l.end(), shrinkfactor);

  Polyhedron p;
  CGAL::mesh_skin_surface_3(skin_surface, p);

  return 0;
}
