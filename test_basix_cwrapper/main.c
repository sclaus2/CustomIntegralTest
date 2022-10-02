#include "basix_cwrapper.h"
#include <stdio.h> 

int main(int argc, char* argv[]) {

int basix_family = 1; 
int basix_cell_type = 2; 
int degree = 1;
int lagrange_variant = 0; 
int dpc_variant = -1; 
bool discontinuous = false; 
unsigned int gdim = 2;

basix_element* element = basix_element_create(basix_family, basix_cell_type, degree, lagrange_variant, dpc_variant, discontinuous, gdim);

double points[10] = {0.0, 0.0, 0.1, 0.1, 0.2, 0.3, 0.3, 0.6, 0.4, 1.0};
unsigned int num_points = 5;
int nd = 1; 

long unsigned int* tbl_shape;
double* values;
int value_size;

basix_table* table = basix_element_tabulate(element, points, num_points, nd);

int i = 0;
printf("table_values=[");
for (i = 0; i < table->value_size; ++i)
{
    printf("%f, ", table->values[i]);
}
printf("]\n ");

return 0;
}