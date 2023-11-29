#include <iostream>
#include "Linalg.hpp"

using namespace std;

luint run_example_QAOA(int n, int * values) {
    luint N = static_cast<luint>(pow(2,n));
    cout << "Creating the initial state..." << endl;
    CCSparseVector phi = CCSparseVector(N);
    for (luint i = 0; i < N; i++) { phi.set_value(i, CC(1)); }

    cout << "Creating the matrix for H_P..." << endl;
    vector<CCSparseVector> U = vector<CCSparseVector>(N, N);
    for (luint i = 0; i < N; i++) { U[i].set_value(i, CC(values[i])); }
    vector<vector<CCSparseVector>> matrices = {U};

    cout << "Creating the starting subspace..." << endl;
    CCSubspace lumping = CCSubspace(N);
    lumping.absorb_new_vector(phi);
    cout << "Computing the lumping..." << endl;

    lumping.minimal_invariant_space(matrices);

    cout << "Found a reduction of size: " << lumping.dimension() << endl;    
    cout << "Norms of the vectors in lumping: " << endl;
    cout << "[";
    vector<double> lumping_norms = lumping.norms();
    for (double fl : lumping_norms) {
        cout << fl << ", ";
    }
    cout << "]" << endl;

    cout << "Beginning of the lumping matrix:" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    for (luint i = 0; i < min(lumping.dimension(), static_cast<luint>(20)); i++) {
        for (luint j = 0; j < min(N, static_cast<luint>(10)); j++) {
            cout << lumping.basis[i][j] << ",";
        }
        cout << "..." << endl;
    }
    cout << "-----------------------------------------------------------------------------------" << endl;

    CC **inner = NULL;
    inner = static_cast<CC**>(calloc(sizeof(CC *), lumping.dimension()));
    for (luint i = 0; i < lumping.dimension(); i++) {
        inner[i] = static_cast<CC *>(calloc(sizeof(CC),lumping.dimension()));
        for (luint j = 0; j < lumping.dimension(); j++) {
            inner[i][j] = lumping.basis[i].inner_product(lumping.basis[j]);
        }
    }
    
    cout << "Inner product matrix:" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    for (luint i = 0; i < lumping.dimension(); i++) {
        for (luint j = 0; j <lumping.dimension(); j++) {
            cout << phi.coeff_to_string(inner[i][j]) << ",\t";
        }
        cout << endl;
    }
    cout << "-----------------------------------------------------------------------------------" << endl;

    // Freeing memory
    for (luint i = 0; i < lumping.dimension(); i++) {
        free(inner[i]);
    }
    free(inner);

    return lumping.dimension();
}

luint example_QAOA_10_1() { // Should be 8?
    // We create the matrix for the formula
    // (-x_5 v x_2 v x_7) ^ (x_0 v x_9 v -x_6) ^ (-x_4 v x_5) ^ (x_1 v -x_2 v x_7) ^ (x_9 v -x_5 v x_2) ^ (x_6 v x_7 v -x_3) ^ (-x_0 v x_4 v -x_3) ^ 
    // (-x_1 v x_6 v -x_2) ^ (x_9 v -x_2 v x_4) ^ (x_6 v -x_9 v x_8) ^ (x_3 v x_1 v -x_5) ^ (x_3 v x_4 v -x_8) ^ (-x_4 v -x_5 v -x_7) ^ (x_3 v -x_9 v x_4) ^ 
    // (-x_9 v x_4) ^ (-x_2 v -x_0) ^ (x_3 v x_1 v -x_7) ^ (x_0 v -x_4 v -x_8) ^ (x_8 v x_5 v -x_3) ^ (-x_7 v x_5 v -x_3)
    int n = 10;
    int values[1024] = {20, 17, 19, 17, 19, 16, 18, 16, 19, 18, 18, 17, 18, 17, 17, 16, 17, 15, 16, 15, 17, 15, 16, 15, 16, 16, 15, 15, 16, 16, 15, 15, 19, 
                     18, 18, 18, 18, 17, 17, 17, 18, 19, 17, 18, 17, 18, 16, 17, 17, 17, 16, 17, 16, 16, 15, 16, 16, 18, 15, 17, 15, 17, 14, 16, 18, 16, 
                     19, 18, 18, 16, 19, 18, 18, 18, 19, 19, 17, 17, 18, 18, 17, 16, 17, 17, 19, 18, 19, 19, 17, 18, 17, 18, 18, 19, 18, 19, 17, 16, 17, 
                     17, 17, 16, 17, 17, 17, 18, 17, 18, 16, 17, 16, 17, 17, 17, 16, 17, 18, 18, 17, 18, 17, 19, 16, 18, 17, 19, 16, 18, 18, 16, 17, 16, 
                     18, 16, 17, 16, 17, 17, 16, 16, 17, 17, 16, 16, 17, 15, 16, 15, 17, 15, 16, 15, 16, 16, 15, 15, 16, 16, 15, 15, 18, 17, 17, 17, 18, 
                     17, 17, 17, 17, 18, 16, 17, 17, 18, 16, 17, 18, 17, 17, 17, 17, 16, 16, 16, 17, 18, 16, 17, 16, 17, 15, 16, 16, 15, 17, 17, 17, 16, 
                     18, 18, 16, 17, 17, 18, 16, 17, 17, 18, 17, 16, 17, 17, 19, 18, 19, 19, 17, 18, 17, 18, 18, 19, 18, 19, 16, 15, 16, 16, 17, 16, 17, 
                     17, 16, 17, 16, 17, 16, 17, 16, 17, 18, 17, 17, 17, 19, 18, 18, 18, 18, 19, 17, 18, 18, 19, 17, 18, 20, 17, 19, 17, 20, 17, 19, 17, 
                     19, 18, 18, 17, 19, 18, 18, 17, 18, 16, 17, 16, 19, 17, 18, 17, 17, 17, 16, 16, 18, 18, 17, 17, 19, 18, 18, 18, 19, 18, 18, 18, 18, 
                     19, 17, 18, 18, 19, 17, 18, 18, 18, 17, 18, 18, 18, 17, 18, 17, 19, 16, 18, 17, 19, 16, 18, 18, 16, 19, 18, 18, 16, 19, 18, 18, 18, 
                     19, 19, 17, 17, 18, 18, 17, 16, 17, 17, 19, 18, 19, 19, 17, 18, 17, 18, 18, 19, 18, 19, 17, 16, 17, 17, 17, 16, 17, 17, 17, 18, 17, 
                     18, 16, 17, 16, 17, 17, 17, 16, 17, 18, 18, 17, 18, 17, 19, 16, 18, 17, 19, 16, 18, 18, 16, 17, 16, 18, 16, 17, 16, 18, 18, 17, 17, 
                     18, 18, 17, 17, 18, 16, 17, 16, 18, 16, 17, 16, 18, 18, 17, 17, 18, 18, 17, 17, 18, 17, 17, 17, 18, 17, 17, 17, 18, 19, 17, 18, 18, 
                     19, 17, 18, 19, 18, 18, 18, 18, 17, 17, 17, 19, 20, 18, 19, 18, 19, 17, 18, 16, 15, 17, 17, 16, 15, 17, 17, 17, 18, 18, 19, 16, 17, 
                     17, 18, 17, 16, 17, 17, 18, 17, 18, 18, 18, 19, 18, 19, 18, 19, 18, 19, 16, 15, 16, 16, 16, 15, 16, 16, 17, 18, 17, 18, 16, 17, 16, 
                     17, 18, 17, 17, 17, 18, 17, 17, 17, 19, 20, 18, 19, 18, 19, 17, 18, 20, 17, 19, 17, 19, 16, 18, 16, 20, 18, 19, 17, 19, 17, 18, 16, 
                     17, 15, 16, 15, 17, 15, 16, 15, 17, 16, 16, 15, 17, 16, 16, 15, 19, 18, 19, 19, 18, 17, 18, 18, 19, 19, 19, 19, 18, 18, 18, 18, 17, 
                     17, 17, 18, 16, 16, 16, 17, 17, 18, 17, 18, 16, 17, 16, 17, 17, 15, 18, 17, 17, 15, 18, 17, 18, 17, 19, 18, 17, 16, 18, 17, 16, 15, 
                     16, 16, 18, 17, 18, 18, 17, 17, 17, 17, 18, 18, 18, 18, 17, 16, 18, 18, 17, 16, 18, 18, 18, 18, 19, 19, 17, 17, 18, 18, 17, 17, 17, 
                     18, 18, 18, 18, 19, 18, 19, 18, 19, 18, 19, 18, 19, 17, 15, 16, 15, 17, 15, 16, 15, 17, 16, 16, 15, 17, 16, 16, 15, 16, 14, 15, 14, 
                     16, 14, 15, 14, 16, 15, 15, 14, 16, 15, 15, 14, 17, 16, 17, 17, 17, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 16, 17, 17, 16, 
                     15, 16, 16, 17, 17, 17, 17, 16, 16, 16, 16, 14, 13, 15, 15, 15, 14, 16, 16, 15, 15, 16, 16, 15, 15, 16, 16, 15, 14, 15, 15, 17, 16, 
                     17, 17, 16, 16, 16, 16, 17, 17, 17, 17, 15, 14, 16, 16, 16, 15, 17, 17, 16, 16, 17, 17, 16, 16, 17, 17, 17, 16, 17, 17, 18, 17, 18, 
                     18, 18, 18, 18, 18, 18, 18, 18, 18, 20, 17, 19, 17, 20, 17, 19, 17, 20, 18, 19, 17, 20, 18, 19, 17, 18, 16, 17, 16, 19, 17, 18, 17, 
                     18, 17, 17, 16, 19, 18, 18, 17, 19, 18, 19, 19, 19, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 18, 18, 18, 19, 18, 18, 18, 19, 18, 
                     19, 18, 19, 18, 19, 18, 19, 17, 15, 18, 17, 17, 15, 18, 17, 18, 17, 19, 18, 17, 16, 18, 17, 16, 15, 16, 16, 18, 17, 18, 18, 17, 17, 
                     17, 17, 18, 18, 18, 18, 17, 16, 18, 18, 17, 16, 18, 18, 18, 18, 19, 19, 17, 17, 18, 18, 17, 17, 17, 18, 18, 18, 18, 19, 18, 19, 18, 
                     19, 18, 19, 18, 19, 17, 15, 16, 15, 17, 15, 16, 15, 18, 17, 17, 16, 18, 17, 17, 16, 17, 15, 16, 15, 17, 15, 16, 15, 18, 17, 17, 16, 
                     18, 17, 17, 16, 17, 16, 17, 17, 17, 16, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 17, 18, 18, 17, 16, 17, 17, 19, 19, 19, 19, 18, 
                     18, 18, 18, 14, 13, 15, 15, 14, 13, 15, 15, 16, 16, 17, 17, 15, 15, 16, 16, 15, 14, 15, 15, 16, 15, 16, 16, 17, 17, 17, 17, 17, 17, 
                     17, 17, 15, 14, 16, 16, 15, 14, 16, 16, 17, 17, 18, 18, 16, 16, 17, 17, 17, 16, 17, 17, 17, 16, 17, 17, 19, 19, 19, 19, 18, 18, 18, 
                     18};

    return run_example_QAOA(n, values);
}
luint example_QAOA_10_2() { // Should be 7?
    // We create the matrix for the formula
    // (x_1 v -x_7 v -x_6) ^ (x_6 v -x_2 v -x_0) ^ (x_3 v -x_1) ^ (x_1 v x_2 v -x_0) ^ (-x_1 v x_0) ^ (x_0 v -x_5 v -x_2) ^ (x_3 v -x_4 v x_8) ^ 
    // (x_7 v x_2 v -x_3) ^ (-x_9 v -x_4 v -x_7) ^ (x_0 v x_5 v -x_6) ^ (-x_4 v -x_7 v -x_0) ^ (-x_5 v x_9 v -x_2) ^ (-x_4 v -x_3) ^ (x_0 v x_6 v -x_5)
    int n = 10;
    int values[1024] = {14, 14, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 13, 13, 13, 13, 13, 
                     13, 14, 14, 13, 12, 14, 13, 12, 12, 13, 13, 11, 10, 12, 11, 12, 12, 13, 13, 12, 11, 13, 12, 13, 13, 14, 14, 12, 11, 13, 12, 13, 13, 
                     13, 13, 14, 14, 14, 14, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 
                     12, 13, 12, 13, 12, 11, 11, 11, 11, 11, 10, 11, 10, 11, 11, 11, 11, 12, 11, 12, 11, 12, 12, 12, 12, 12, 11, 12, 11, 14, 14, 14, 14, 
                     14, 14, 14, 14, 13, 13, 13, 13, 12, 12, 12, 12, 11, 12, 11, 12, 11, 12, 11, 12, 12, 13, 12, 13, 11, 12, 11, 12, 13, 13, 14, 14, 13, 
                     12, 14, 13, 12, 12, 13, 13, 11, 10, 12, 11, 10, 11, 11, 12, 10, 10, 11, 11, 11, 12, 12, 13, 10, 10, 11, 11, 14, 14, 14, 14, 14, 14, 
                     14, 14, 13, 13, 13, 13, 12, 12, 12, 12, 11, 12, 11, 12, 11, 12, 11, 12, 12, 13, 12, 13, 11, 12, 11, 12, 13, 13, 13, 13, 13, 12, 13, 
                     12, 12, 12, 12, 12, 11, 10, 11, 10, 10, 11, 10, 11, 10, 10, 10, 10, 11, 12, 11, 12, 10, 10, 10, 10, 12, 12, 12, 12, 12, 12, 12, 12, 
                     11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 11, 11, 12, 12, 11, 10, 12, 11, 10, 
                     10, 11, 11, 10, 9, 11, 10, 10, 10, 11, 11, 10, 9, 11, 10, 11, 11, 12, 12, 11, 10, 12, 11, 12, 12, 12, 12, 13, 13, 13, 13, 11, 11, 11, 
                     11, 12, 12, 12, 12, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 11, 11, 11, 11, 12, 11, 12, 11, 10, 10, 10, 10, 
                     11, 10, 11, 10, 10, 10, 10, 10, 11, 10, 11, 10, 11, 11, 11, 11, 12, 11, 12, 11, 12, 12, 12, 12, 12, 12, 12, 12, 11, 11, 11, 11, 11, 
                     11, 11, 11, 9, 10, 9, 10, 9, 10, 9, 10, 10, 11, 10, 11, 10, 11, 10, 11, 11, 11, 12, 12, 11, 10, 12, 11, 10, 10, 11, 11, 10, 9, 11, 
                     10, 8, 9, 9, 10, 8, 8, 9, 9, 9, 10, 10, 11, 9, 9, 10, 10, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 12, 12, 12, 12, 12, 10, 11, 
                     10, 11, 10, 11, 10, 11, 11, 12, 11, 12, 11, 12, 11, 12, 12, 12, 12, 12, 12, 11, 12, 11, 11, 11, 11, 11, 11, 10, 11, 10, 9, 10, 9, 10, 
                     9, 9, 9, 9, 10, 11, 10, 11, 10, 10, 10, 10, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 
                     13, 13, 13, 13, 13, 12, 12, 12, 12, 12, 12, 13, 13, 11, 10, 12, 11, 12, 12, 13, 13, 10, 9, 11, 10, 12, 12, 13, 13, 11, 10, 12, 11, 12, 
                     12, 13, 13, 10, 9, 11, 10, 12, 12, 12, 12, 13, 13, 13, 13, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 12, 12, 12, 
                     12, 12, 12, 12, 12, 11, 11, 11, 11, 11, 10, 11, 10, 11, 11, 11, 11, 10, 9, 10, 9, 11, 11, 11, 11, 11, 10, 11, 10, 11, 11, 11, 11, 10, 
                     9, 10, 9, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 13, 13, 13, 13, 12, 13, 12, 13, 12, 13, 12, 13, 13, 14, 13, 14, 12, 13, 12, 
                     13, 12, 12, 13, 13, 11, 10, 12, 11, 13, 13, 14, 14, 11, 10, 12, 11, 11, 12, 12, 13, 10, 10, 11, 11, 12, 13, 13, 14, 10, 10, 11, 11, 13, 
                     13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 13, 13, 13, 13, 12, 13, 12, 13, 12, 13, 12, 13, 13, 14, 13, 14, 12, 13, 12, 13, 12, 12, 12, 
                     12, 11, 10, 11, 10, 13, 13, 13, 13, 11, 10, 11, 10, 11, 12, 11, 12, 10, 10, 10, 10, 12, 13, 12, 13, 10, 10, 10, 10, 13, 13, 13, 13, 13, 
                     13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 13, 13, 11, 10, 12, 
                     11, 12, 12, 13, 13, 11, 10, 12, 11, 12, 12, 13, 13, 11, 10, 12, 11, 12, 12, 13, 13, 11, 10, 12, 11, 13, 13, 13, 13, 14, 14, 14, 14, 13, 
                     13, 13, 13, 14, 14, 14, 14, 13, 13, 13, 13, 14, 14, 14, 14, 13, 13, 13, 13, 14, 14, 14, 14, 12, 12, 12, 12, 12, 11, 12, 11, 12, 12, 12, 
                     12, 12, 11, 12, 11, 12, 12, 12, 12, 12, 11, 12, 11, 12, 12, 12, 12, 12, 11, 12, 11, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 
                     13, 13, 13, 11, 12, 11, 12, 11, 12, 11, 12, 12, 13, 12, 13, 12, 13, 12, 13, 11, 11, 12, 12, 10, 9, 11, 10, 12, 12, 13, 13, 11, 10, 12, 11, 
                     10, 11, 11, 12, 9, 9, 10, 10, 11, 12, 12, 13, 10, 10, 11, 11, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 12, 13, 12, 
                     13, 12, 13, 12, 13, 13, 14, 13, 14, 13, 14, 13, 14, 12, 12, 12, 12, 11, 10, 11, 10, 13, 13, 13, 13, 12, 11, 12, 11, 11, 12, 11, 12, 10, 
                     10, 10, 10, 12, 13, 12, 13, 11, 11, 11, 11};

    return run_example_QAOA(n, values);
}
luint example_QAOA_10_3() { // Should be 10?
    // We create the matrix for the formula
    // (-x_0 v -x_2 v x_8) ^ (-x_1 v -x_9 v x_8) ^ (x_3 v -x_2 v x_7) ^ (x_8 v -x_6 v -x_0) ^ (x_6 v -x_5 v x_8) ^ (-x_0 v -x_9 v -x_6) ^ 
    // (x_1 v -x_2 v x_8) ^ (x_1 v x_2) ^ (-x_9 v -x_4 v x_5) ^ (-x_1 v x_5 v -x_6) ^ (-x_1 v -x_5 v -x_0) ^ (-x_2 v x_7 v -x_0) ^ 
    // (x_6 v -x_2 v -x_8) ^ (x_9 v -x_8 v -x_6) ^ (x_6 v -x_4 v x_7) ^ (x_0 v -x_9 v -x_3) ^ (x_0 v x_4 v x_8) ^ (-x_9 v -x_6 v x_8) ^ 
    // (x_0 v x_4 v x_3) ^ (x_3 v x_1 v -x_6) ^ (x_1 v x_2 v x_5) ^ (-x_5 v x_7 v -x_6) ^ (x_0 v -x_7 v x_5)
    int n = 10;
    int values[1024] = {19, 19, 20, 20, 18, 18, 19, 19, 18, 17, 18, 19, 17, 16, 17, 18, 19, 19, 21, 21, 19, 19, 21, 21, 18, 17, 18, 19, 19, 18, 
                     19, 20, 20, 19, 20, 19, 20, 19, 20, 19, 20, 18, 19, 19, 19, 17, 18, 18, 20, 20, 21, 21, 21, 21, 22, 22, 20, 19, 19, 20, 
                     21, 20, 20, 21, 20, 19, 21, 20, 19, 18, 20, 19, 20, 18, 20, 20, 19, 17, 19, 19, 20, 19, 22, 21, 20, 19, 22, 21, 20, 18, 
                     20, 20, 21, 19, 21, 21, 20, 18, 20, 18, 20, 18, 20, 18, 21, 18, 20, 19, 20, 17, 19, 18, 20, 19, 21, 20, 21, 20, 22, 21, 
                     21, 19, 20, 20, 22, 20, 21, 21, 19, 19, 20, 20, 19, 19, 20, 20, 18, 17, 19, 20, 18, 17, 19, 20, 18, 18, 20, 20, 19, 19, 
                     21, 21, 17, 16, 18, 19, 19, 18, 20, 21, 20, 19, 20, 19, 21, 20, 21, 20, 20, 18, 20, 20, 20, 18, 20, 20, 19, 19, 20, 20, 
                     21, 21, 22, 22, 19, 18, 19, 20, 21, 20, 21, 22, 21, 20, 22, 21, 20, 19, 21, 20, 21, 19, 22, 22, 20, 18, 21, 21, 20, 19, 
                     22, 21, 20, 19, 22, 21, 20, 18, 21, 21, 21, 19, 22, 22, 21, 19, 21, 19, 21, 19, 21, 19, 22, 19, 22, 21, 21, 18, 21, 20, 
                     20, 19, 21, 20, 21, 20, 22, 21, 21, 19, 21, 21, 22, 20, 22, 22, 21, 20, 22, 22, 20, 19, 21, 21, 20, 18, 20, 21, 19, 17, 
                     19, 20, 20, 19, 22, 22, 20, 19, 22, 22, 20, 18, 20, 21, 21, 19, 21, 22, 22, 20, 22, 21, 22, 20, 22, 21, 22, 19, 21, 21, 
                     21, 18, 20, 20, 21, 20, 22, 22, 22, 21, 23, 23, 22, 20, 21, 22, 23, 21, 22, 23, 22, 20, 23, 22, 21, 19, 22, 21, 21, 18, 
                     21, 21, 20, 17, 20, 20, 21, 19, 23, 22, 21, 19, 23, 22, 21, 18, 21, 21, 22, 19, 22, 22, 22, 19, 22, 20, 22, 19, 22, 20, 
                     22, 18, 21, 20, 21, 17, 20, 19, 21, 19, 22, 21, 22, 20, 23, 22, 22, 19, 21, 21, 23, 20, 22, 22, 20, 19, 20, 20, 20, 19, 
                     20, 20, 19, 17, 19, 20, 19, 17, 19, 20, 19, 18, 20, 20, 20, 19, 21, 21, 19, 17, 19, 20, 21, 19, 21, 22, 21, 19, 20, 19, 
                     22, 20, 21, 20, 21, 18, 20, 20, 21, 18, 20, 20, 20, 19, 20, 20, 22, 21, 22, 22, 21, 19, 20, 21, 23, 21, 22, 23, 22, 20, 
                     22, 21, 21, 19, 21, 20, 21, 18, 21, 21, 20, 17, 20, 20, 21, 19, 22, 21, 21, 19, 22, 21, 21, 18, 21, 21, 22, 19, 22, 22, 
                     22, 19, 21, 19, 22, 19, 21, 19, 22, 18, 21, 20, 21, 17, 20, 19, 21, 19, 21, 20, 22, 20, 22, 21, 22, 19, 21, 21, 23, 20, 
                     22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 19, 17, 19, 19, 19, 17, 19, 19, 21, 21, 22, 22, 21, 21, 22, 22, 19, 17, 19, 19, 
                     20, 18, 20, 20, 20, 19, 20, 19, 21, 20, 21, 20, 19, 16, 19, 18, 19, 16, 19, 18, 20, 20, 21, 21, 21, 21, 22, 22, 19, 17, 
                     19, 19, 20, 18, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 20, 18, 20, 20, 20, 18, 20, 20, 21, 21, 22, 22, 21, 21, 22, 22, 
                     20, 18, 20, 20, 21, 19, 21, 21, 20, 19, 20, 19, 21, 20, 21, 20, 20, 17, 20, 19, 20, 17, 20, 19, 20, 20, 21, 21, 21, 21, 
                     22, 22, 20, 18, 20, 20, 21, 19, 21, 21, 19, 19, 20, 20, 21, 21, 22, 22, 17, 15, 19, 19, 19, 17, 21, 21, 18, 18, 20, 20, 
                     20, 20, 22, 22, 16, 14, 18, 18, 19, 17, 21, 21, 18, 17, 19, 18, 21, 20, 22, 21, 17, 14, 19, 18, 19, 16, 21, 20, 17, 17, 
                     19, 19, 20, 20, 22, 22, 16, 14, 18, 18, 19, 17, 21, 21, 20, 20, 21, 21, 21, 21, 22, 22, 19, 17, 21, 21, 20, 18, 22, 22, 
                     19, 19, 21, 21, 20, 20, 22, 22, 18, 16, 20, 20, 20, 18, 22, 22, 19, 18, 20, 19, 21, 20, 22, 21, 19, 16, 21, 20, 20, 17, 
                     22, 21, 18, 18, 20, 20, 20, 20, 22, 22, 18, 16, 20, 20, 20, 18, 22, 22, 23, 22, 23, 23, 23, 22, 23, 23, 21, 18, 21, 21, 
                     21, 18, 21, 21, 21, 20, 22, 22, 21, 20, 22, 22, 20, 17, 20, 20, 21, 18, 21, 21, 22, 20, 22, 21, 23, 21, 23, 22, 21, 17, 
                     21, 20, 21, 17, 21, 20, 20, 19, 21, 21, 21, 20, 22, 22, 20, 17, 20, 20, 21, 18, 21, 21, 23, 22, 23, 23, 23, 22, 23, 23, 
                     21, 18, 21, 21, 21, 18, 21, 21, 21, 20, 22, 22, 21, 20, 22, 22, 20, 17, 20, 20, 21, 18, 21, 21, 22, 20, 22, 21, 23, 21, 
                     23, 22, 21, 17, 21, 20, 21, 17, 21, 20, 20, 19, 21, 21, 21, 20, 22, 22, 20, 17, 20, 20, 21, 18, 21, 21, 20, 19, 20, 20, 
                     22, 21, 22, 22, 18, 15, 19, 19, 20, 17, 21, 21, 18, 17, 19, 19, 20, 19, 21, 21, 17, 14, 18, 18, 20, 17, 21, 21, 19, 17, 
                     19, 18, 22, 20, 22, 21, 18, 14, 19, 18, 20, 16, 21, 20, 17, 16, 18, 18, 20, 19, 21, 21, 17, 14, 18, 18, 20, 17, 21, 21, 
                     21, 20, 21, 21, 22, 21, 22, 22, 19, 16, 20, 20, 20, 17, 21, 21, 19, 18, 20, 20, 20, 19, 21, 21, 18, 15, 19, 19, 20, 17, 
                     21, 21, 20, 18, 20, 19, 22, 20, 22, 21, 19, 15, 20, 19, 20, 16, 21, 20, 18, 17, 19, 19, 20, 19, 21, 21, 18, 15, 19, 19, 
                     20, 17, 21, 21};

    return run_example_QAOA(n, values);
}
luint example_QAOA_10_4() { // Should be 11?
    // We create the matrix for the formula
    // (x_0 v x_6 v -x_8) ^ (-x_9 v -x_5) ^ (-x_1 v x_6 v x_0) ^ (x_6 v -x_7 v x_4) ^ (x_4 v -x_3 v x_8) ^ (-x_9 v -x_4 v x_7) ^ (x_7 v x_5 v -x_6) ^ 
    // (x_1 v -x_2 v x_7) ^ (x_3 v x_5) ^ (x_0 v -x_7 v x_8) ^ (-x_7 v x_2) ^ (x_3 v x_1) ^ (-x_9 v x_1 v -x_3) ^ (x_3 v x_1 v -x_5) ^ (x_7 v -x_0) ^ 
    // (x_6 v -x_2 v x_8) ^ (-x_5 v -x_8 v x_4) ^ (x_9 v x_4 v -x_6) ^ (-x_5 v x_8) ^ (-x_1 v x_4 v x_0) ^ (x_0 v -x_9 v -x_2) ^ (x_9 v -x_7 v -x_8) ^ 
    // (x_3 v x_9) ^ (x_0 v x_9 v -x_5) ^ (x_3 v x_2) ^ (-x_1 v x_6 v x_5) ^ (x_6 v -x_9 v -x_3) ^ (x_1 v -x_4 v -x_5)
    int n = 10;
    int values[1024] = {24, 25, 23, 24, 21, 22, 20, 22, 22, 24, 22, 24, 21, 23, 21, 24, 22, 23, 21, 22, 19, 20, 18, 20, 21, 23, 21, 23, 19, 21, 19, 22, 
                     24, 24, 23, 23, 22, 23, 21, 23, 23, 23, 23, 23, 22, 23, 22, 24, 21, 21, 21, 21, 19, 20, 19, 21, 21, 21, 22, 22, 19, 20, 20, 22, 
                     27, 25, 27, 25, 24, 22, 24, 23, 25, 25, 26, 26, 24, 24, 25, 26, 25, 23, 25, 23, 22, 20, 22, 21, 24, 24, 25, 25, 22, 22, 23, 24, 
                     28, 25, 27, 24, 26, 24, 25, 24, 27, 25, 27, 25, 26, 25, 26, 26, 25, 22, 25, 22, 23, 21, 23, 22, 25, 23, 26, 24, 23, 22, 24, 24, 
                     23, 23, 23, 23, 22, 22, 22, 23, 22, 23, 22, 23, 23, 24, 23, 25, 21, 21, 21, 21, 20, 20, 20, 21, 21, 22, 21, 22, 21, 22, 21, 23, 
                     23, 22, 23, 22, 23, 23, 23, 24, 23, 22, 23, 22, 24, 24, 24, 25, 20, 19, 21, 20, 20, 20, 21, 22, 21, 20, 22, 21, 21, 21, 22, 23, 
                     25, 22, 26, 23, 24, 21, 25, 23, 24, 23, 25, 24, 25, 24, 26, 26, 23, 20, 24, 21, 22, 19, 23, 21, 23, 22, 24, 23, 23, 22, 24, 24, 
                     26, 22, 26, 22, 26, 23, 26, 24, 26, 23, 26, 23, 27, 25, 27, 26, 23, 19, 24, 20, 23, 20, 24, 22, 24, 21, 25, 22, 24, 22, 25, 24, 
                     22, 23, 21, 22, 19, 20, 18, 20, 22, 24, 22, 24, 21, 23, 21, 24, 22, 23, 21, 22, 19, 20, 18, 20, 22, 24, 22, 24, 20, 22, 20, 23, 
                     23, 23, 22, 22, 21, 22, 20, 22, 24, 24, 24, 24, 23, 24, 23, 25, 23, 23, 23, 23, 21, 22, 21, 23, 24, 24, 25, 25, 22, 23, 23, 25, 
                     24, 23, 24, 23, 21, 20, 21, 21, 24, 25, 25, 26, 23, 24, 24, 26, 23, 22, 23, 22, 20, 19, 20, 20, 23, 24, 24, 25, 21, 22, 22, 24, 
                     26, 24, 25, 23, 24, 23, 23, 23, 27, 26, 27, 26, 26, 26, 26, 27, 25, 23, 25, 23, 23, 22, 23, 23, 26, 25, 27, 26, 24, 24, 25, 26, 
                     22, 22, 22, 22, 20, 20, 20, 21, 23, 24, 23, 24, 23, 24, 23, 25, 22, 22, 22, 22, 20, 20, 20, 21, 23, 24, 23, 24, 22, 23, 22, 24, 
                     23, 22, 23, 22, 22, 22, 22, 23, 25, 24, 25, 24, 25, 25, 25, 26, 23, 22, 24, 23, 22, 22, 23, 24, 25, 24, 26, 25, 24, 24, 25, 26, 
                     23, 21, 24, 22, 21, 19, 22, 21, 24, 24, 25, 25, 24, 24, 25, 26, 22, 20, 23, 21, 20, 18, 21, 20, 23, 23, 24, 24, 22, 22, 23, 24, 
                     25, 22, 25, 22, 24, 22, 24, 23, 27, 25, 27, 25, 27, 26, 27, 27, 24, 21, 25, 22, 23, 21, 24, 23, 26, 24, 27, 25, 25, 24, 26, 26, 
                     23, 24, 23, 24, 22, 23, 21, 23, 21, 23, 21, 23, 22, 24, 21, 24, 22, 22, 22, 22, 21, 21, 20, 21, 21, 22, 21, 22, 21, 22, 20, 22, 
                     23, 23, 23, 23, 23, 24, 22, 24, 22, 22, 22, 22, 23, 24, 22, 24, 21, 20, 22, 21, 21, 21, 21, 22, 21, 20, 22, 21, 21, 21, 21, 22, 
                     26, 24, 27, 25, 25, 23, 25, 24, 24, 24, 25, 25, 25, 25, 25, 26, 25, 22, 26, 23, 24, 21, 24, 22, 24, 23, 25, 24, 24, 23, 24, 24, 
                     27, 24, 27, 24, 27, 25, 26, 25, 26, 24, 26, 24, 27, 26, 26, 26, 25, 21, 26, 22, 25, 22, 25, 23, 25, 22, 26, 23, 25, 23, 25, 24, 
                     22, 23, 23, 24, 23, 24, 23, 25, 21, 23, 21, 23, 24, 26, 23, 26, 21, 21, 22, 22, 22, 22, 22, 23, 21, 22, 21, 22, 23, 24, 22, 24, 
                     22, 22, 23, 23, 24, 25, 24, 26, 22, 22, 22, 22, 25, 26, 24, 26, 20, 19, 22, 21, 22, 22, 23, 24, 21, 20, 22, 21, 23, 23, 23, 24, 
                     24, 22, 26, 24, 25, 23, 26, 25, 23, 23, 24, 24, 26, 26, 26, 27, 23, 20, 25, 22, 24, 21, 25, 23, 23, 22, 24, 23, 25, 24, 25, 25, 
                     25, 22, 26, 23, 27, 25, 27, 26, 25, 23, 25, 23, 28, 27, 27, 27, 23, 19, 25, 21, 25, 22, 26, 24, 24, 21, 25, 22, 26, 24, 26, 25, 
                     23, 24, 23, 24, 22, 23, 21, 23, 22, 24, 22, 24, 23, 25, 22, 25, 24, 24, 24, 24, 23, 23, 22, 23, 23, 24, 23, 24, 23, 24, 22, 24, 
                     23, 23, 23, 23, 23, 24, 22, 24, 23, 23, 23, 23, 24, 25, 23, 25, 24, 23, 25, 24, 24, 24, 24, 25, 24, 23, 25, 24, 24, 24, 24, 25, 
                     25, 24, 26, 25, 24, 23, 24, 24, 24, 25, 25, 26, 25, 26, 25, 27, 25, 23, 26, 24, 24, 22, 24, 23, 24, 24, 25, 25, 24, 24, 24, 25, 
                     26, 24, 26, 24, 26, 25, 25, 25, 26, 25, 26, 25, 27, 27, 26, 27, 26, 23, 27, 24, 26, 24, 26, 25, 26, 24, 27, 25, 26, 25, 26, 26, 
                     23, 24, 24, 25, 23, 24, 23, 25, 23, 25, 23, 25, 25, 27, 24, 27, 24, 24, 25, 25, 24, 24, 24, 25, 24, 25, 24, 25, 25, 26, 24, 26, 
                     23, 23, 24, 24, 24, 25, 24, 26, 24, 24, 24, 24, 26, 27, 25, 27, 24, 23, 26, 25, 25, 25, 26, 27, 25, 24, 26, 25, 26, 26, 26, 27, 
                     24, 23, 26, 25, 24, 23, 25, 25, 24, 25, 25, 26, 26, 27, 26, 28, 24, 22, 26, 24, 24, 22, 25, 24, 24, 24, 25, 25, 25, 25, 25, 26, 
                     25, 23, 26, 24, 26, 25, 26, 26, 26, 25, 26, 25, 28, 28, 27, 28, 25, 22, 27, 24, 26, 24, 27, 26, 26, 24, 27, 25, 27, 26, 27, 27};

    return run_example_QAOA(n, values);
}

luint example_QAOA_4_1() { // Should be 4?
    // We create the matrix for the formula
    // (x_3 v -x_2) ^ (-x_2 v -x_0) ^ (x_0 v -x_2) ^ (-x_1 v -x_3 v -x_0) ^ (x_3 v x_2) ^ (x_1 v x_2) ^ (x_0 v x_2 v -x_3) ^ (x_1 v -x_0) ^ (x_3 v -x_1 v x_0) ^ (x_0 v -x_2 v x_3)
    int n = 4;
    int values[16] = {8, 8, 7, 9, 8, 9, 6, 9, 7, 8, 7, 8, 9, 9, 8, 8};

    return run_example_QAOA(n, values);
}
luint example_QAOA_4_2() { // Should be 4?
    // We create the matrix for the formula
    // (x_2 v -x_0) ^ (x_3 v -x_2 v x_0) ^ (-x_1 v -x_3 v -x_0) ^ (x_0 v -x_2 v -x_3) ^ (x_0 v x_1 v x_3) ^ (x_3 v -x_2 v -x_0) ^ (-x_1 v -x_0 v -x_3)
    int n = 4;
    int values[16] = {6, 7, 5, 6, 7, 7, 6, 6, 6, 6, 6, 7, 6, 4, 6, 5};

    return run_example_QAOA(n, values);
}

int main(int, char**) {
    // QQSparseVector u = QQSparseVector({QQ(1),QQ(),QQ(),QQ(2)});

    // cout << "My vector density: " << u.coeff_to_string(QQ(4,2)) << endl;
    example_QAOA_10_1(); // Got 8
    // example_QAOA_10_2(); // Got 7
    // example_QAOA_10_3(); // Got 10
    // example_QAOA_10_4(); // Got 11

    // example_QAOA_4_1(); // Got 4
    // example_QAOA_4_2(); // Got 4
    return 0;
}