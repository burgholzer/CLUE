#include "Linalg.hpp"

#include <queue>
#include <vector>
#include <iostream>

/*******************************************************************************************************************
 * 
 * CLASS FOR SUBSPACE
 * 
********************************************************************************************************************/
/*********************************************************************/
/* ATTRIBUTE/PROPERTIES */
template <typename V, typename M, typename C>
vector<double> Subspace<V,M,C>::norms() {
    vector<double> result = vector<double>(this->dimension());

    for (luint i = 0; i < this->dimension(); i++) {
        result[i] = this->norm(this->basis[i]);
    }

    return result;
}

/*********************************************************************/
/* GETTING/SETTING DATA METHODS */
template <typename V, typename M, typename C>
V* Subspace<V,M,C>::reduce_vector(V* vector) {
    V* result = this->scale(vector, this->coeff(1.)); // We copy the input vector

    cout << "\t\tReducing vector using " << this->dimension() << " vectors:" << endl;
    
    /* This method does a MGS reduction of a vector, becoming numericaly stable*/
    for (luint i = 0; i < this->dimension(); i++) {
        V* to_rem = this->scale(this->basis[i], this->inner_product(this->basis[i], vector)*this->coeff(-1.));
        V* aux = this->add(result, to_rem);
        this->free_vector(result); result = aux;
    }
    cout << "\t\t\t" << this->print_vector(vector) << "\n\t\t\t->\n\t\t\t" << this->print_vector(result) << endl;

    return result;
}

template <typename V, typename M, typename C>
bool Subspace<V,M,C>::contains(V* vector) {
    V* reduced = this->reduce_vector(vector);
    bool result = this->norm(reduced) <= this->max_error;
    this->free_vector(reduced); //Removing memory for reduced vector
    return result;
}

template <typename V, typename M, typename C>
bool Subspace<V,M,C>::absorb_new_vector(V* vector) {
    cout << "\t Trying to absorb a new vector:" << endl << "\t\t" << this->print_vector(vector) << endl;
    V* reduced = this->reduce_vector(vector);
    cout << "\t\tReduced:\n\t\t" << this->print_vector(reduced) << endl;
    cout << "\t\tNorm: " << this->norm(reduced) << endl;
    bool result = false;
    if (this->norm(reduced) > this->max_error) {
        V* to_add = this->scale(reduced, this->coeff(1/this->norm(reduced)));
        cout << "\t\tScaled:\n\t\t" << this->print_vector(to_add) << endl;
        this->basis.push_back(to_add);
        result = true;
    } else {
        cout << "Found an element inside: " << this->norm(vector) << endl;
    }
    this->free_vector(reduced); //Removing memory for reduced vector
    return result;
}

/*********************************************************************/
/* COMPUTATIONAL METHODS */
template <typename V, typename M, typename C>
luint Subspace<V,M,C>::minimal_invariant_space(vector<M>& matrices) {
    // We create a queue with the first round we need to check
    queue<V*> to_process;

    for (V* current : this->basis) {
        cout << "Element of the basis: " << endl << this->print_vector(current) << endl;
        cout << "Generated:" << endl;
        for (M matrix : matrices) {
            // We do multiplication matrix*current
            V* result = this->apply(current, matrix);
            cout << "\t[-] " << this->print_vector(result) << endl; 
            V* conj = this->conjugate(result);
            cout << "\t[C] " << this->print_vector(conj) << endl; 
            // We add this vector to the queue
            to_process.push(result);
        }
    }

    //We now iterate on the queue until this is empty
    while ((!to_process.empty()) && (this->dimension() < this->ambient_dimension())) {
        cout << "Remaining vectors: " << to_process.size() << endl;
        V* current = to_process.front(); to_process.pop(); // We take the first element
        

        cout << this->print_vector(current) << endl;
        bool absorbed = this->absorb_new_vector(current);
        cout << "Was absorbed: " << absorbed << endl;
        // We release the memory for the processed vector
        this->free_vector(current);
        if (absorbed) { // We have increased the dimension, we need to add new vectors
            current = this->basis[this->dimension()-1];
            cout << "Added vector:\n\t[+] " << this->print_vector(current) << endl;
            cout << "Generated:" << endl;
            for (M matrix : matrices) {
                // We do multiplication matrix*current
                V* result = this->apply(current, matrix);
                cout << "\t[-] " << this->print_vector(result) << endl; 
                // We add this vector to the queue
                to_process.push(result);
            } 
        }
    }
    // We release the memory if any vector remains on the queue
    while (!to_process.empty()) {
        V* current = to_process.front(); to_process.pop();
        this->free_vector(current);
    }

    // We return the new dimension of the subspace
    return this->dimension();
}
template <typename V, typename M, typename C>
vector<vector<C>> Subspace<V,M,C>::reduced_matrix(M& matrix) {
    vector<vector<C>> result = vector<vector<C>>(this->dimension());
    for (luint i = 0; i < this->dimension(); i++) {
        V* conj = this->conjugate(this->basis[i]);
        V* Uld = this->apply(conj, matrix);
        result[i] = vector<C>(this->dimension());
        for (luint j = 0; j < this->dimension(); j++) {
            result[i][j] = this->inner_product(this->basis[i], Uld);
        }
        // Freeing memory if needed
        this->free_vector(Uld); 
        this->free_vector(conj); // Freeing memory in the loop
    }

    return result;
}

template class Subspace<CCSparseVector, vector<CCSparseVector>, CC>;
template class Subspace<DDVector, dd::mEdge, dd::ComplexValue>;
template class Subspace<dd::vEdge, qc::QuantumComputation, dd::ComplexValue>;

/*******************************************************************************************************************
 * 
 * CLASS FOR CC-SUBSPACE
 * 
********************************************************************************************************************/

double CCSubspace::norm(CCSparseVector* vector) {
    return vector->norm();
}
CC CCSubspace::coeff(double coeff) {
    return CC(coeff);
}
CCSparseVector* CCSubspace::apply(CCSparseVector* u, vector<CCSparseVector>& M) {
    // Computes M*u so the result is nrows(M) x 1
    CCSparseVector * result = new CCSparseVector(M.size());
    CCSparseVector conj = u->conjugate();
    for (luint i = 0; i < M.size(); i++) {
        result->set_value(i, M[i].inner_product(conj));
    }

    return result;
}
CCSparseVector* CCSubspace::scale(CCSparseVector* u, CC c) {
    CCSparseVector * result = new CCSparseVector(u->dimension());

    std::unordered_set<luint>::iterator it = u->nonzero_iterator();
    while (it != u->nonzero_iterator_end()) {
        result->set_value(*it, c*u->get_value(*it));
        it++;
    }

    return result;
}
CCSparseVector* CCSubspace::add(CCSparseVector* u, CCSparseVector* v) {
    CCSparseVector *result = new CCSparseVector(u->dimension());
    
    *result = u->operator+(*v); // Using the copy operator on the sum of two vectors

    return result;
}
CC CCSubspace::inner_product(CCSparseVector* u, CCSparseVector*v) {
    return u->inner_product(*v);
}
CCSparseVector* CCSubspace::conjugate(CCSparseVector* u) {
    CCSparseVector* result = new CCSparseVector(u->dimension());
    *result = u->conjugate();

    return result;
}
