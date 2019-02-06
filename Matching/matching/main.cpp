
#include <iostream>
#include "Hungarian.h"
#include <vector>
#include <cstdlib>
typedef std::vector< std::vector<int> > Table;

int** vector_to_matrix(Table &v, int rows,
        int cols) {
    int i, j;
    int** m;
    // allocate an array of pointers (arrays)
    m = (int**)calloc(rows,sizeof(int*));
    //assert(m);
    for(i = 0; i < rows; i++) {
        // allocate an array of integers
        m[i] = (int*)calloc(cols,sizeof(int));
        //assert(m[i]);
        for(j = 0; j < cols; j++) {
            m[i][j] = v[i][j];
        }
    }
    return m;
}

int main ()
{
    hungarian_problem_t p;
    int numFuncUnitsAvail = 10000;
    Table weights(numFuncUnitsAvail, std::vector<int>(numFuncUnitsAvail));
    weights[0][0] = 2,  weights[0][1] = 5;
    weights[1][0] = 5,  weights[1][1] = 3;
    Table assignments(numFuncUnitsAvail, std::vector<int>(numFuncUnitsAvail));
    int rows = weights.size();
    //assert(rows > 0);
    int cols = weights[0].size();
    //assert(cols > 0);

    // not necessary but good to enforce
    //assert(rows == cols);

    int** m = vector_to_matrix(weights, rows, cols);

    /* initialize the hungarian_problem using the cost matrix*/
    hungarian_init(&p, m, rows, cols,
            HUNGARIAN_MODE_MINIMIZE_COST);

    /* solve the assignement problem */
    hungarian_solve(&p);

    /*
    fprintf(stderr, "assignment matrix: %d rows and %d columns.\n\n",
            matrix_size, matrix_size);

    fprintf(stderr, "cost-matrix:");
    hungarian_print_costmatrix(&p);

    fprintf(stderr, "assignment:");
    hungarian_print_assignment(&p);
    */

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            assignments[i][j] = p.assignment[i][j];
        }
    }

    /* free used memory */
    hungarian_free(&p);
    for(int i = 0; i < rows; i++) {
        free(m[i]);
    }
    free(m);
    return 0;
}
