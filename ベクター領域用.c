
// vector領域確保
double *dvector(int i, int j){
    double *a;
    if ( (a = (double *)malloc( ((j-i+1)*sizeof(double))) ) == NULL ){
        printf("memory allocation error \n");
        exit(1);
    }
    return(a-i);
}

// メモリ解放
void free_dvector(double *a, int i){
    free( (void *)(a + i) );
}
