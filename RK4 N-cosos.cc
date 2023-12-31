#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE* Sol;
FILE* Tierra;
FILE* Marte;
FILE* Jupiter;


#define P 781

int h = 24*60*60;

double G= 6.674E-11;
double UA= 149597870700.0;

double Masas[4] = {(1.99E30)/(5.97E24), (5.97E24)/(5.97E24), (6.42E23)/(5.97E24), (1.90E27)/(5.97E24)};
double xo[4] = {(-1.218E9)/(UA) , (1.471E11)/(UA), (-2.471E11)/(UA), (6.427E11)/(UA)};
double yo[4] = {(6.361E8)/(UA), (-2.514E10)/(UA), (-1.422E10)/(UA), (-3.853E11)/(UA)};
double zo[4] = {(2.326E7)/(UA), (2.398E7)/(UA), (5.744E9)/(UA), (-1.278E10)/(UA)};

double X[4][P]; double Y[4][P]; double Z[4][P];
double Mangx[4][P]; double Mangy[4][P]; double Mangz[4][P];

double vx[4][P]; double vy[4][P]; double vz[4][P];

double K1x[4][P]; double K2x[4][P]; double K3x[4][P]; double K4x[4][P];
double K1y[4][P]; double K2y[4][P]; double K3y[4][P]; double K4y[4][P];
double K1z[4][P]; double K2z[4][P]; double K3z[4][P]; double K4z[4][P];

double L1x[4][P]; double L2x[4][P]; double L3x[4][P]; double L4x[4][P];
double L1y[4][P]; double L2y[4][P]; double L3y[4][P]; double L4y[4][P];
double L1z[4][P]; double L2z[4][P]; double L3z[4][P]; double L4z[4][P];

double x0[4]; double x1[4]; double x2[4]; double x3[4];
double y4[4]; double y5[4]; double y2[4]; double y3[4];
double z4[4]; double z5[4]; double z2[4]; double z3[4];


int main(){
    


    double t0 = pow((pow(UA, 3.0)/(G*5.97E24)), 1.0/2.0);
    double v0=t0/UA;
    double vxo[4] = {(-8.131)*v0, (4598)*v0, (2354)*v0, (6560)*v0}; double vyo[4] = {(-13.68)*v0, (29220)*v0, (-22120)*v0, (11820)*v0};double vzo[4] = {(0.3036)*v0, (0.0165)*v0, (-521.1)*v0, (-195.8)*v0};
    for (int a = 0; a<4; a = a + 1){X[a][0] = xo[a]; Y[a][0] = yo[a]; Z[a][0] = zo[a]; vx[a][0] = vxo[a]; vy[a][0] = vyo[a]; vz[a][0] = vzo[a];}




    for(int paso = 0; paso < P; paso = paso + 1){

//K1 | L1
        for(int j = 0; j<4; j++){K1x[j][paso] = vx[j][paso]; K1y[j][paso] = vy[j][paso]; K1z[j][paso] = vz[j][paso] ;x0[j] = X[j][paso]; y4[j] = Y[j][paso]; z4[j] = Z[j][paso];
         Mangx[j][paso] = Y[j][paso]*Masas[j]*vz[j][paso] - Z[j][paso]*Masas[j]*vy[j][paso]; Mangy[j][paso] = Z[j][paso]*Masas[j]*vx[j][paso] - X[j][paso]*Masas[j]*vz[j][paso]; Mangz[j][paso] = X[j][paso]*Masas[j]*vy[j][paso] - Y[j][paso]*Masas[j]*vx[j][paso];}

        for(int j = 0; j<4; j++){
            for(int l = 0; l<4; l++){
                if(l != j){
            L1x[j][paso] += -Masas[l]*(x0[j] - x0[l])/pow(pow(x0[j] - x0[l],2) + pow(y4[j] - y4[l],2) + pow(z4[j] - z4[l],2), 3.0/2.0);
            L1y[j][paso] += -Masas[l]*(y4[j] - y4[l])/pow(pow(x0[j] - x0[l],2) + pow(y4[j] - y4[l],2) + pow(z4[j] - z4[l],2), 3.0/2.0);
            L1z[j][paso] += -Masas[l]*(z4[j] - z4[l])/pow(pow(x0[j] - x0[l],2) + pow(y4[j] - y4[l],2) + pow(z4[j] - z4[l],2), 3.0/2.0);
            }}}



//K2 | L2
        for(int j = 0; j<4; j++){K2x[j][paso] = K1x[j][paso] + (h/(2*t0))*L1x[j][paso]; K2y[j][paso] = K1y[j][paso] + (h/(2*t0))*L1y[j][paso]; K2z[j][paso] = K1z[j][paso] + (h/(2*t0))*L1z[j][paso]; x1[j] = X[j][paso] + (h/(2*t0))*K1x[j][paso]; y5[j] = Y[j][paso] + (h/(2*t0))*K1y[j][paso]; z5[j] = Z[j][paso] + (h/(2*t0))*K1z[j][paso];}
        
        for(int j = 0; j<4; j++){
            for(int l = 0; l<4; l++){
                if(l != j){
            L2x[j][paso] += -Masas[l]*(x1[j] - x1[l])/pow(pow(x1[j] - x1[l],2) + pow(y5[j] - y5[l],2) + pow(z5[j] - z5[l],2), 3.0/2.0);
            L2y[j][paso] += -Masas[l]*(y5[j] - y5[l])/pow(pow(x1[j] - x1[l],2) + pow(y5[j] - y5[l],2) + pow(z5[j] - z5[l],2), 3.0/2.0);
            L2z[j][paso] += -Masas[l]*(z5[j] - z5[l])/pow(pow(x1[j] - x1[l],2) + pow(y5[j] - y5[l],2) + pow(z5[j] - z5[l],2), 3.0/2.0);
            }}}

//K3 | L3
        for(int j = 0; j<4; j++){K3x[j][paso] = K2x[j][paso] + (h/(2*t0))*L2x[j][paso]; K3y[j][paso] = K2y[j][paso] + (h/(2*t0))*L2y[j][paso]; K3z[j][paso] = K2z[j][paso] + (h/(2*t0))*L2z[j][paso]; x2[j] = X[j][paso] + (h/(2*t0))*K2x[j][paso]; y2[j] = Y[j][paso] + (h/(2*t0))*K2y[j][paso]; z2[j] = Z[j][paso] + (h/(2*t0))*K2z[j][paso];}

        for(int j = 0; j<4; j++){
            for(int l = 0; l<4; l++){
                if(l != j){
            L3x[j][paso] += -Masas[l]*(x2[j] - x2[l])/pow(pow(x2[j] - x2[l],2) + pow(y2[j] - y2[l],2) + pow(z2[j] - z2[l],2), 3.0/2.0);
            L3y[j][paso] += -Masas[l]*(y2[j] - y2[l])/pow(pow(x2[j] - x2[l],2) + pow(y2[j] - y2[l],2) + pow(z2[j] - z2[l],2), 3.0/2.0);
            L3z[j][paso] += -Masas[l]*(z2[j] - z2[l])/pow(pow(x2[j] - x2[l],2) + pow(y2[j] - y2[l],2) + pow(z2[j] - z2[l],2), 3.0/2.0);
            }}}

//K4 | L4
        for(int j = 0; j<4; j++){K4x[j][paso] = K3x[j][paso] + (h/(2*t0))*L3x[j][paso]; K4y[j][paso] = K3y[j][paso] + (h/(2*t0))*L3y[j][paso]; K4z[j][paso] = K3z[j][paso] + (h/(2*t0))*L3z[j][paso]; x3[j] = X[j][paso] + (h/(2*t0))*K3x[j][paso]; y3[j] = Y[j][paso] + (h/(2*t0))*K3y[j][paso]; z3[j] = Z[j][paso] + (h/(2*t0))*K3z[j][paso];}

        for(int j = 0; j<4; j++){
            for(int l = 0; l<4; l++){
                if(l != j){
            L4x[j][paso] += -Masas[l]*(x3[j] - x3[l])/pow(pow(x3[j] - x3[l],2) + pow(y3[j] - y3[l],2) + pow(z3[j] - z3[l],2), 3.0/2.0);
            L4y[j][paso] += -Masas[l]*(y3[j] - y3[l])/pow(pow(x3[j] - x3[l],2) + pow(y3[j] - y3[l],2) + pow(z3[j] - z3[l],2), 3.0/2.0);
            L4z[j][paso] += -Masas[l]*(z3[j] - z3[l])/pow(pow(x3[j] - x3[l],2) + pow(y3[j] - y3[l],2) + pow(z3[j] - z3[l],2), 3.0/2.0);
            }}}
//Final
        for(int j = 0; j<4; j++){
            X[j][paso + 1] = X[j][paso] + (h/t0)*((K1x[j][paso] + 2*K2x[j][paso] + 2*K3x[j][paso] + K4x[j][paso])/6);
            Y[j][paso + 1] = Y[j][paso] + (h/t0)*((K1y[j][paso] + 2*K2y[j][paso] + 2*K3y[j][paso] + K4y[j][paso])/6);
            Z[j][paso + 1] = Z[j][paso] + (h/t0)*((K1z[j][paso] + 2*K2z[j][paso] + 2*K3z[j][paso] + K4z[j][paso])/6);

            vx[j][paso + 1] = vx[j][paso] + (h/t0)*((L1x[j][paso] + 2*L2x[j][paso] + 2*L3x[j][paso] + L4x[j][paso])/6);
            vy[j][paso + 1] = vy[j][paso] + (h/t0)*((L1y[j][paso] + 2*L2y[j][paso] + 2*L3y[j][paso] + L4y[j][paso])/6);
            vz[j][paso + 1] = vz[j][paso] + (h/t0)*((L1z[j][paso] + 2*L2z[j][paso] + 2*L3z[j][paso] + L4z[j][paso])/6);
            
        }
        }
    Sol = fopen("Sol.txt","w");
    Tierra = fopen("Tierra.txt","w");
    Marte = fopen("Marte.txt","w");
    Jupiter = fopen("Jupiter.txt","w");
    for(int q = 0; q<P; q++){
        fprintf(Jupiter, "%lf;%lf;%lf;%lf;%lf;%lf\n", X[3][q], Y[3][q], Z[3][q], Mangx[3][q], Mangy[3][q], Mangz[3][q]);
        fprintf(Marte,   "%lf;%lf;%lf;%lf;%lf;%lf\n", X[2][q], Y[2][q], Z[2][q], Mangx[2][q], Mangy[2][q], Mangz[2][q]);
        fprintf(Tierra,  "%lf;%lf;%lf;%lf;%lf;%lf\n", X[1][q], Y[1][q], Z[1][q], Mangx[1][q], Mangy[1][q], Mangz[1][q]);
        fprintf(Sol,     "%lf;%lf;%lf;%lf;%lf;%lf\n", X[0][q], Y[0][q], Z[0][q], Mangx[0][q], Mangy[0][q], Mangz[0][q]);
    }
    fclose(Sol);
    fclose(Tierra);
    fclose(Marte);
    fclose(Jupiter);

return 0;
}
