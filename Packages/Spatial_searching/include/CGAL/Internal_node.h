// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       :
// release_date  :
//
// file          : include/CGAL/Internal_node.h
// package       : APSPAS
// revision      : 1.0 
// revision_date : 2001/06/12 
// maintainer : Hans Tangelder (<hanst@cs.uu.nl>)
//
// ======================================================================

#ifndef CGAL_INTERNAL_NODE_H
#define CGAL_INTERNAL_NODE_H
#include <CGAL/base_node.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <iomanip>
#include <CGAL/IO/PS_stream.h>

namespace CGAL {

template < class Traits > // = Kd_tree_traits_2d >
class Internal_node : public Base_node<Traits>  {

public:
  typedef Traits::Item Item;
  typedef typename Item::FT NT;
  typedef Traits::Separator Separator;
  typedef Base_node<Traits> Node;
  typedef Point_2< Cartesian<NT> > Point_2D;
  typedef Segment_2< Cartesian<NT> > Segment_2D;

protected:
  Node* lower_ch;
  Node* upper_ch;
  Separator* sep;

public:
  inline const bool is_leaf() const { return 0;}
  inline Node* lower() const { return lower_ch; }
  inline Node* upper() const { return upper_ch; }
  inline const Separator* separator() const {return sep; }

  Internal_node() {}
  // Internal_node(const  Node* lower, const  Node* upper) :
  //			  lower_ch(lower), upper_ch(upper) {}

  Internal_node(Points_container<Item>& c, int bucket_size) {

    Traits tr;
	Points_container<Item> c_low(c.dimension());

    sep = tr.split(c, c_low, tr.selected_split_rule());

    if (c_low.size() > bucket_size)
      lower_ch = new Internal_node<Traits>(c_low,bucket_size);
    else
      lower_ch = new Leaf_node<Traits>(c_low);

    // delete *c_low;
    // delete []c_low;

    if (c.size() > bucket_size)
      upper_ch = new Internal_node<Traits>(c,bucket_size);
    else
      upper_ch = new Leaf_node<Traits>(c);
  }

  void data_to_postscript(PS_Stream& PS,
	const int i, const int j,
	const NT mini, const NT maxi,
	const NT minj, const NT maxj) {
	if (sep->cutting_dimension()==j) {
          Point_2D p(mini,sep->cutting_value());
	  Point_2D q(maxi,sep->cutting_value());
	  Segment_2D s(p,q);
	  // PS << border_color(BLACK);   works only for Visual
          PS << s;
	  lower_ch->data_to_postscript(PS,i,j,mini,maxi,minj,sep->cutting_value());
	  upper_ch->data_to_postscript(PS,i,j,mini,maxi,sep->cutting_value(),maxj);
	}
	else if  (sep->cutting_dimension()==i) {
      Point_2D p(sep->cutting_value(),minj);
	  Point_2D q(sep->cutting_value(),maxj);
	  Segment_2D s(p,q);
	  // PS << border_color(BLACK);  works only for Visual
          PS << s;
	  lower_ch->data_to_postscript(PS,i,j,mini,sep->cutting_value(),minj,maxj);
	  upper_ch->data_to_postscript(PS,i,j,sep->cutting_value(),maxi,minj,maxj);
	}
	else {
	  lower_ch->data_to_postscript(PS,i,j,mini,maxi,minj,maxj);
	  upper_ch->data_to_postscript(PS,i,j,mini,maxi,minj,maxj);
    }
  }

  ~Internal_node() {
  // std::cout << "~Internal_node called" << std::endl;
  // std::cout << "sep=" << sep << std::endl;
  delete sep; delete lower_ch; delete upper_ch;
        // std::cout << "~Internal_node_d called" << std::endl;
  }
};


} // namespace CGAL
#endif // CGAL_INTERNAL_NODE_H
