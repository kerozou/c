#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Runge_Kutta法

// 条件
double xs;
double ys;
double zs;
double h;
double c;   // パラメータ
int N;    // 刻みの個数

// 微分方程式
double fx(double t,double x,double y,double z){
    return (-1.0*y - z);
}
double fy(double t,double x,double y,double z){
    return (x + 0.2*y);
}
double fz(double t,double x,double y,double z){
    return (0.2 + z*(x-c));
}

// Runge-Kutta
void Runge_Kutta(){
    double k1,l1,m1,k2,l2,m2,k3,l3,m3,k4,l4,m4;
    double t = 0;
    double x = xs;
    double y = ys;
    double z = zs;
    for(int i = 0;i < N;i++){
        k1 = h*fx(t,x,y,z);
        l1 = h*fy(t,x,y,z);
        m1 = h*fz(t,x,y,z);
        k2 = h*fx(t+h/2, x+k1/2, y+l1/2, z+m1/2);
        l2 = h*fy(t+h/2, x+k1/2, y+l1/2, z+m1/2);
        m2 = h*fz(t+h/2, x+k1/2, y+l1/2, z+m1/2);
        k3 = h*fx(t+h/2, x+k2/2, y+l2/2, z+m2/2);
        l3 = h*fy(t+h/2, x+k2/2, y+l2/2, z+m2/2);
        m3 = h*fz(t+h/2, x+k2/2, y+l2/2, z+m2/2);
        k4 = h*fx(t+h, x+k3, y+l3, z+m3);
        l4 = h*fy(t+h, x+k3, y+l3, z+m3);
        m4 = h*fz(t+h, x+k3, y+l3, z+m3);

        x += (k1 + 2*k2 + 2*k3 + k4)/6.0;
        y += (l1 + 2*l2 + 2*l3 + l4)/6.0;
        z += (m1 + 2*m2 + 2*m3 + m4)/6.0;
        t += h;

        printf("%lf %e %e %e\n" , t ,x ,y ,z );
    }
    return;
}


int main(){
    printf("入力:x0 y0 z0 h c N\n");
    scanf("%lf %lf %lf %lf %lf %d", &xs, &ys, &zs ,&h ,&c ,&N);
    Runge_Kutta();

    return 0;
}