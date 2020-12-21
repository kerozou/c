#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ガウス消去法

// 条件の定義
double A[105][105];
double b[105];
double x[105];
int pivot_check[105][105];
const int N = 4;
const double eps = 1e-6;

// スワップ関数
void swap(double *k1, double *k2) {
    double tmp;
    tmp = *k1;
    *k1 = *k2;
    *k2 = tmp;
}

// 部分ピボット選択(ピボット選択する行番号を返す)
int pivot(int k){
    if(fabs(A[k][k]) >= eps)return k;
    else{
        double maxtmp = 0.0;
        int index = k;
        for(int i = k;i < N;i++){
            if(fabs(maxtmp) < fabs(A[i][k])){
                maxtmp = A[i][k];
                index = i;
            }
        }
        return index;
    }
}

// 部分ピボット選択付き_前進消去
void P_advance(){
    for(int k = 0;k < N;k++){
        // pivot
        int p = pivot(k);
        // swap
        if(p != k){
            pivot_check[k][p] = 1;
            for(int l = k;l <= N;l++){
                if(l == N)swap(&b[p],&b[k]);
                else swap(&A[k][l],&A[p][l]);
            }
        }
        // 前進消去
        for(int i = k+1;i < N;i++){
            double tmp = A[i][k] / A[k][k];
            for(int j = k;j < N;j++){
                A[i][j] -= (tmp * A[k][j]);
            }
            b[i] -= (tmp * b[k]); 
        }
    }
}

// 後退代入
void recession(){
    x[N-1] = b[N-1]/A[N-1][N-1];
    for(int k = N-2;k >= 0;k--){
        double sum = 0.0;
        for(int i = k+1;i < N;i++){
            sum += (A[k][i]*x[i]);
        }
        x[k] = (b[k]-sum)/A[k][k];
    }
}

int main(){

    // 標準入力
    for(int i = 0;i < N;i++){
        for(int j = 0;j <= N;j++){
            if(j == N)scanf("%le",&b[i]);
            else scanf("%le",&A[i][j]);
        }
    }

    // (1)前進消去
    P_advance();

    printf("(1)前進消去\n\n");
    printf("A =\n");
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            printf("(%le) " ,A[i][j]);
        }
        printf("\n");
    }
    printf("b =\n");
    for(int i = 0;i < N;i++){
        printf("(%le)\n" ,b[i]);
    } 

    printf("ピボット選択をした部分 (i,j) := (i行目を操作中にi行目をj行目と交換)\n");
    printf("※行番号は0-indexになってる\n");
    int ct = 0;
    for(int i = 0;i < N;i++)for(int j = 0;j < N;j++){
        if(pivot_check[i][j] == 1){
            printf("(%d,%d) " , i,j);
        }
        if(ct == 5){
            printf("\n");
            ct = 0;
        }
        else ct++;
    }
    printf("\n");

    printf("--------------\n");

    // (2)後退代入
    recession();

    printf("(2)後退代入\n");
    printf("x =\n");
    for(int i = 0;i < N;i++){
        printf("(%le)\n" ,x[i]);
    }
}