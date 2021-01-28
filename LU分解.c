#include <stdio.h>

int main() {
    // 分数表示するために分子と分母を分ける
    // 行列を0-indexで表記している

    int Lsi[5][5];  // 分子
    int Lbo[5][5];  // 分母
    int Usi[5][5];  // 分子
    int Ubo[5][5];  // 分母
    int A[5][5];

    // 入力受け取り
    for(int i = 0;i < 5;++i){
        for(int j = 0;j < 5;++j){
            scanf("%d",&A[i][j]);
        }
    }

/*  入力内容
4 -1 0 0 0
-1 4 -1 0 0
0 -1 4 -1 0
0 0 -1 4 -1
0 0 0 -1 4
*/

    // 初期条件
    for(int i = 0;i < 5;i++)for(int j = 0;j < 5;j++)Lsi[i][j] = 0;

    Lsi[0][0] = A[0][0];
    Lbo[0][0] = 1;
    for(int i = 0;i < 5;++i){
        for(int j = 0;j < 5;++j){
            if(i == j)Usi[i][j] = 1;
            else Usi[i][j] = 0;
            Lbo[i][j] = 1;
            Ubo[i][j] = 1;
            if(i < 4)Lsi[i+1][i] = -1;
        }
    }



    // LU分解
    for(int i = 0;i <= 3;++i){
        Usi[i][i+1] = A[i][i+1] * Lbo[i][i];
        Ubo[i][i+1] = Lsi[i][i];
        Lsi[i+1][i+1] = A[i+1][i+1]*Ubo[i][i+1]*Lbo[i+1][i] - Usi[i][i+1]*Lsi[i+1][i];
        Lbo[i+1][i+1] = Ubo[i][i+1]*Lbo[i+1][i];
    }

    // 出力
    printf("L =\n");
    for(int i = 0;i < 5;++i){
        for(int j = 0;j < 5;j++){
            printf("(%d " ,Lsi[i][j]);
            printf(" / %d)" ,Lbo[i][j]);
        }
        printf("\n");
    }

    printf("U =\n");
    for(int i = 0;i < 5;++i){
        for(int j = 0;j < 5;j++){
            printf("(%d " ,Usi[i][j]);
            printf(" / %d)" ,Ubo[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/* 出力結果

L =
(4  / 1)(0  / 1)(0  / 1)(0  / 1)(0  / 1)
(-1  / 1)(15  / 4)(0  / 1)(0  / 1)(0  / 1)
(0  / 1)(-1  / 1)(56  / 15)(0  / 1)(0  / 1)
(0  / 1)(0  / 1)(-1  / 1)(209  / 56)(0  / 1)
(0  / 1)(0  / 1)(0  / 1)(-1  / 1)(780  / 209)
U =
(1  / 1)(-1  / 4)(0  / 1)(0  / 1)(0  / 1)
(0  / 1)(1  / 1)(-4  / 15)(0  / 1)(0  / 1)
(0  / 1)(0  / 1)(1  / 1)(-15  / 56)(0  / 1)
(0  / 1)(0  / 1)(0  / 1)(1  / 1)(-56  / 209)
(0  / 1)(0  / 1)(0  / 1)(0  / 1)(1  / 1)

*/