#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定数
const double dx = 0.01;
const double dt = 0.01;
const double Du = 0.00004;
const double Dv = 0.00002;
const int x_lim = 100;
const int t_lim = 500000;
double a;
double b;

// 関数 u v
double u[110][500010];
double v[110][500010];

// 陽的オイラー法用の計算式
double func_u(int i,int j){
    double tmp;
    int N = x_lim;
    if(i == 0 || i == N)tmp = u[i][j] - dt*u[i][j]*v[i][j]*v[i][j] + dt*a*(1-u[i][j]);
    else tmp = u[i][j] + dt*(Du*(u[i+1][j] - 2*u[i][j] + u[i-1][j])/(dx*dx) - u[i][j]*v[i][j]*v[i][j] + a*(1 - u[i][j]));
    
    return tmp;
}

double func_v(int i,int j){
    double tmp;
    int N = x_lim;
    if(i == 0 || i == N)tmp = v[i][j] + dt*u[i][j]*v[i][j]*v[i][j] - b*v[i][j];
    else tmp = v[i][j] + dt*(Dv*(v[i+1][j] - 2*v[i][j] + v[i-1][j])/(dx*dx) + u[i][j]*v[i][j]*v[i][j] - b*v[i][j]);
    return tmp;
}

void ex_Euler(){
    for(int j = 1;j <= t_lim;j++){
        for(int i = 0;i <= x_lim;i++){
            u[i][j] = func_u(i,j-1);
            v[i][j] = func_v(i,j-1);
        }
    }
}


// 出力用
void output(int t_input) {

    char filename[100];
    sprintf(filename, "uv_n%d_%d.dat", x_lim, t_input);
    FILE *fout = fopen(filename, "w");
  
    if (fout == NULL) {
        printf("cannot open the file.\n");
        exit(1);
    }

    t_input *= 100;

    for(int i = 0;i <= x_lim;i++){
        double t = t_input / 100;
        double ut = u[i][t_input];
        double vt = v[i][t_input];
        double x = dx * i;
        fprintf(fout,"%lf %e %e %e\n" , t ,x ,ut ,vt);
    }

    fclose(fout);
}


int main(){


    // 入力
    printf("入力後にdatファイルが大量に生成されるので注意\n");
    printf("生成数は 100 行目の for文の条件式で指定する\n");
    printf("※※※※※※※※\n");
    printf("入力:a b\n");
    scanf("%lf %lf" ,&a ,&b);


    // 初期条件の設定
    for(int i = 0;i <= x_lim;i++){
        u[i][0] = 1;
        double tmp = dx * i;
        if((0 <= tmp && tmp < 0.35) || (0.4 <= tmp && tmp <= 1)){
            v[i][0] = 0;
        }
        else if(0.35 <= tmp && tmp < 0.4){
            v[i][0] = 0.5;
        }
    }

    // 陽的オイラー法
    ex_Euler();


    // 出力
    for(int i = 0;i <= 50;i++){
        output(i);
    }

    return 0;
}


