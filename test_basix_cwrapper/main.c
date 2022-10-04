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

//Calculate shape
int shape[4]; 
basix_element_tabulate_shape(element, num_points, nd, shape);

double table[shape[0]][shape[1]][shape[2]][shape[3]];
int table_size = shape[0]*shape[1]*shape[2]*shape[3]; 

basix_element_tabulate(element, points, num_points, nd, (double*) table, table_size);

int i = 0;
printf("table_shape=[");
for (i = 0; i < 4 ; i++)
{
    printf("%d, ", shape[i]);
}
printf("]\n ");

printf("table=[");
for (i = 0; i < shape[0]; i++)
{
    for (int j = 0; j < shape[1]; j++)
    {
        for (int k = 0; k < shape[2]; k++)
        {
            for (int l = 0; l < shape[3]; l++)
            {
                printf("%f, ", table[i][j][k][l]);
            }
        }
    }
}
printf("]\n ");

printf("table_slice=[");
for (i = 0; i < 3; i++)
{
    printf("%f, ", table[0][0][i][0]);
}
printf("]\n ");

//Free memory 
basix_element_destroy(element);

return 0;
}