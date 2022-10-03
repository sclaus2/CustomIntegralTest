//Wrapping C++ class into C 
// This defines the functions listed in cwrapper.h 
// This is a C++ file that defines C calls 
#include <basix/finite-element.h>
#include <basix/cell.h>
#include <span>
#include "basix_cwrapper.h"

extern "C" {

basix_element* basix_element_create(const int basix_family, const int basix_cell_type, const int degree, 
                                    const int lagrange_variant, const int dpc_variant, const bool discontinuous, 
                                    const unsigned int gdim)
{
    basix_element* element = (basix_element*) malloc(sizeof(basix_element));
    element->basix_family = basix_family; 
    element->basix_cell_type = basix_cell_type;
    element->degree = degree;
    element->lagrange_variant = lagrange_variant; 
    element->dpc_variant = dpc_variant; 
    element->discontinuous = discontinuous; 
    element->gdim = gdim; 

    return element; 
}

void basix_element_destroy(basix_element *element)
{
    free(element);
}

basix_table* basix_element_tabulate(const basix_element *element, const double* points,
                            const unsigned int num_points, const int nd)
{
    //Specify which element is needed
    basix::element::family family = static_cast<basix::element::family>(element->basix_family); 
    basix::cell::type cell_type = static_cast<basix::cell::type>(element->basix_cell_type); 
    int k = element->degree;
    std::size_t gdim = element->gdim;
    basix::element::lagrange_variant lvariant = static_cast<basix::element::lagrange_variant>(element->lagrange_variant);

    //Create C++ basix element object
    basix::FiniteElement finite_element = basix::create_element(family, cell_type, k, lvariant);

    //Determine shape of tabulated values to allocate sufficient memory 
    std::array<std::size_t, 4> shape = finite_element.tabulate_shape(nd, num_points);
    //@todo create another C API function that takes in the shape as argument 
    unsigned int tab_data_size = shape[0]*shape[1]*shape[2]*shape[3]; 

    basix_table* table = (basix_table*) malloc(sizeof(basix_table));
    table->value_size = tab_data_size;
    table->shape_size = shape.size();
    table->values = (double*)malloc(tab_data_size*sizeof(double)); 
    table->shape = (long unsigned int*)malloc(shape.size()*sizeof(long unsigned int));

    //Copy shape values 
    std::copy(shape.begin(),shape.end(),table->shape);

    //Create span views on points and table values
    std::span<const double> points_view{points,num_points*gdim};
    std::span<double> basis{table->values, tab_data_size};
    std::array<std::size_t, 2> xshape{num_points,gdim};
    
    finite_element.tabulate(nd, points_view, {num_points, gdim}, basis);

    return table;
}

void basix_table_destroy(basix_table *table)
{
    if (table != NULL) {
        free(table->shape);
        free(table->values);
        free(table);
    }
}

//@todo: Is there a way to make this better, e.g. create 4 dimensional array in basix table? 
// (remark: this seems to be challenging in terms of memory management)
int shape_index(int i, int j, int k, int l, long unsigned int* shape)
{
   int index = i + j * shape[0] + k * shape[0] * shape[1] + l * shape[0] * shape[1] * shape[2];
   return index;
}

void tabulate_element(const basix_element *element, const double* points,
                      const unsigned int num_points, const int nd, 
                      double* table_data, int table_data_size)
{
     //Specify which element is needed
    basix::element::family family = static_cast<basix::element::family>(element->basix_family); 
    basix::cell::type cell_type = static_cast<basix::cell::type>(element->basix_cell_type); 
    int k = element->degree;
    std::size_t gdim = element->gdim;
    basix::element::lagrange_variant lvariant = static_cast<basix::element::lagrange_variant>(element->lagrange_variant);

    //Create C++ basix element object
    basix::FiniteElement finite_element = basix::create_element(family, cell_type, k, lvariant);

    //Create span views on points and table values
    std::span<const double> points_view{points,num_points*gdim};
    std::span<double> basis{table_data, table_data_size};
    std::array<std::size_t, 2> xshape{num_points,gdim};
    
    finite_element.tabulate(nd, points_view, {num_points, gdim}, basis);
}

}