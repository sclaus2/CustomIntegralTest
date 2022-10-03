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
int nd = 0; 

basix_table* table = basix_element_tabulate(element, points, num_points, nd);

int i = 0;
printf("table_shape=[");
for (i = 0; i < table->shape_size; i++)
{
    printf("%ld, ", table->shape[i]);
}
printf("]\n ");

printf("table_values=[");
for (i = 0; i < table->value_size; i++)
{
    printf("%f, ", table->values[i]);
}
printf("]\n ");

printf("Tabulate data (0, 0, :, 0): [ ");
for(i = 0; i < table->shape[2]; ++i)
{
    int index = shape_index(0, 0, i, 0, table->shape);
    printf("%f ", table->values[index]);
}
printf("]\n");

double table_test[1][5][3][1];
int table_test_size = 1*5*3*1; 

tabulate_element(element, points,num_points, nd, (double*) table_test, table_test_size);


printf("table_values=[");
for (i = 0; i < 3; i++)
{
    printf("%f, ", table_test[0][0][i][0]);
}
printf("]\n ");

//Free memory 
basix_element_destroy(element);
basix_table_destroy(table);

return 0;
}