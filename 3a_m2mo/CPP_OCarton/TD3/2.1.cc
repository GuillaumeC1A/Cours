// Computes the trace (sum of elements of the diagonal) of a square NxN matrix,
// flattened in memory.
double trace(double* matrix, int N) {
    double trace_ = 0;
    for (int i = 0; i < N; i++) { //Comme la matrice est carrée (NxN), on va se déplacer de N+1 en N+1 pour parcourir la diagonale. 
        trace_ += matrix[i * (N+1)];
    }
    return trace_;
}