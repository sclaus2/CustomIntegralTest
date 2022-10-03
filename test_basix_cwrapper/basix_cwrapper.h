/**
 * cwrapper.h
 *
 * Declares a simple C API wrapper around C++.
 * 
 */

#ifndef BASIX_CWRAPPER_H_
#define BASIX_CWRAPPER_H_

#include <stdbool.h>

#ifdef __cplusplus
// extern C indicates to C++ compiler that the following code 
// is meant to be called by a C compiler 
// i.e. tells the compiler that C naming conventions etc should be used
extern "C" {
#endif

//FIXME: Could this be replaced by ufcx_finite_element? 
// The following int values indicate the position of the values in the corresponding 
// enum classes in basix
typedef struct basix_element
{    
  /// Basix identifier of the family 
  int basix_family;
  /// Basix identifier of the cell type
  int basix_cell_type;
  /// Polynomial degree 
  int degree;
  /// The Lagrange variant to be passed to Basix's create_element function
  int lagrange_variant;
  /// The DPC variant to be passed to Basix's create_element function
  int dpc_variant;
  /// Indicates whether or not this is the discontinuous version of the element
  bool discontinuous;
  //The geometric dimension
  int gdim;
} basix_element;

typedef struct basix_table
{
  long unsigned int* shape;
  int shape_size;
  double* values;
  int value_size;
} basix_table;

basix_element* basix_element_create(const int basix_family, const int basix_cell_type, const int degree, 
                                    const int lagrange_variant, const int dpc_variant, const bool discontinuous, 
                                    const unsigned int gdim);

void basix_element_destroy(basix_element *element);

basix_table* basix_element_tabulate(const basix_element *element, const double* points,
                            const unsigned int num_points, const int nd); 

void tabulate_element(const basix_element *element, const double* points,
                      const unsigned int num_points, const int nd, 
                      double* table_data, int table_data_size);

void basix_table_destroy(basix_table *table);

int shape_index(int i, int j, int k, int l, long unsigned int* shape);

void test(double* table_data);

// //Redefine enums necessary for basix element creation
// typedef enum basix_element_lagrange_variant
// {
//   lagrange_variant_unset = -1,
//   lagrange_variant_equispaced = 0,
//   lagrange_variant_gll_warped = 1,
//   lagrange_variant_gll_isaac = 2,
//   lagrange_variant_gll_centroid = 3,
//   lagrange_variant_chebyshev_warped = 4,
//   lagrange_variant_chebyshev_isaac = 5,
//   lagrange_variant_chebyshev_centroid = 6,
//   lagrange_variant_gl_warped = 7,
//   lagrange_variant_gl_isaac = 8,
//   lagrange_variant_gl_centroid = 9,
//   lagrange_variant_legendre = 10,
//   lagrange_variant_bernstein = 11,
//   lagrange_variant_vtk = 20,
// } basix_element_lagrange_variant;

// typedef enum basix_element_dpc_variant
// {
//   dpc_variant_unset = -1,
//   dpc_variant_simplex_equispaced = 0,
//   dpc_variant_simplex_gll = 1,
//   dpc_variant_horizontal_equispaced = 2,
//   dpc_variant_horizontal_gll = 3,
//   dpc_variant_diagonal_equispaced = 4,
//   dpc_variant_diagonal_gll = 5,
//   dpc_variant_legendre = 6,
// } basix_element_dpc_variant;

// typedef enum basix_element_family
// {
//   custom = 0,
//   P = 1,
//   RT = 2,
//   N1E = 3,
//   BDM = 4,
//   N2E = 5,
//   CR = 6,
//   Regge = 7,
//   DPC = 8,
//   bubble = 9,
//   serendipity = 10,
//   HHJ = 11,
//   Hermite = 12
// } basix_element_family;

// typedef enum basix_cell_type
// {
//   point = 0,
//   interval = 1,
//   triangle = 2,
//   tetrahedron = 3,
//   quadrilateral = 4,
//   hexahedron = 5,
//   prism = 6,
//   pyramid = 7
// } basix_cell_type;

#ifdef __cplusplus
}
#endif


#endif /* BASIX_CWRAPPER_H_ */