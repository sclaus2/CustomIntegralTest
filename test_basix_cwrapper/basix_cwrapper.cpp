//Wrapping C++ class into C 
// This defines the functions listed in cwrapper.h 
// This is a C++ files that defines C calls 
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

    //Tabulate data 
    std::span<const double> points_view{points,num_points};
    
    //return value std::pair<std::vector<double>, std::array<std::size_t, 4>>
    auto [tab_data, shape] = finite_element.tabulate(nd, points_view, {num_points/gdim, gdim});

    //Allocate memory for basis_table 
    basix_table* table = (basix_table*) malloc(sizeof(basix_table));

    //Return: take generated data and assign it to tbl_shape and values
    table->shape = (long unsigned int*)malloc(shape.size()*sizeof(long unsigned int));
    table->values = (double*)malloc(tab_data.size()*sizeof(double)); 

    table->shape_size = shape.size();
    table->shape = shape.data();
    table->value_size = tab_data.size();
    table->values = tab_data.data();
    
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

//create pointer to struct object from C++ object
//this function can be called from C
// CBasixFiniteElement* basix_finite_element_create(basix_element_family cfamily, basix_cell_type ccell_type, int k, basix_element_lagrange_variant cvariant)
// {
//     basix::element::family family = static_cast<basix::element::family>(cfamily);
//     basix::cell::type cell_type = static_cast<basix::cell::type>(ccell_type);
//     basix::element::lagrange_variant variant = static_cast<basix::element::lagrange_variant>(cvariant);
    
//     //use family (translated cfamily) below
//     basix::FiniteElement element = basix::create_element(family, cell_type, k, variant);
//     basix::FiniteElement *ptr_element = &element;
//     return reinterpret_cast<CBasixFiniteElement*>(ptr_element);
// }

// void basix_finite_element_destroy(CBasixFiniteElement* c)
// {
//     basix::FiniteElement *element = reinterpret_cast<basix::FiniteElement*>(c);
//     delete c;
// }

// void basix_finite_element_methods()
// {
//     basix::FiniteElement *element = reinterpret_cast<basix::FiniteElement*>(c);
//     //element->do_something();
// }

}