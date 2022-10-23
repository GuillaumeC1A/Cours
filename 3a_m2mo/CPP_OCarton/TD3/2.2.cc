// Computes the matrix product of two matrices A and B of respective sizes NxM and MxP,
// and returns a newly allocated NxP matrix. All matrices are flattened.
double* matrix_prod(int n, int m, int p, double* a, double *b) {
    double* C = new double[n*p]; //On fait un produit de NxM et MxP, donc on a un tableau de taille NxP
    
    for (int i = 0; i < n; i++) { //Lignes de A
        for (int j = 0; j < p; j++) { //Colonnes de B
            C[i*p + j] = 0; //On met la case à 0 (indispensable puisqu'on ne sait pas ce qu'il y a dedans)

            //Pour chaque case, on doit à nouveau reparcourir la bonne colonne de A et la bonne ligne de B :
            for (int k = 0; k < m; k++) { 
                C[i*p + j] += a[i*m + k] * b[k*p + j]; 
            }
        }
    }
    return C;   
}
// Notre code utilise bien des matrices flattened, en ligne (double*) et pas en 2D (double**).