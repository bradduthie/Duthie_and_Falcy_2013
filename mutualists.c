#include "landscape.h"
#include "array.h"
#include "randpois.h"

int mutualists(double ***SCAPE,int Ma,int **M, int **P,int beta,int deltaM,int X,int flower,int *Sds, int iter){
    FILE *Mv;    
    int i, j, k, n, c, m, rx[2], ry[2], disp, z, q;
    Mv   = fopen("Mv.dat","w");     
    for(i=0; i<Ma; i++){
        disp = randpois(beta);
        j = 0;        
        while(j < disp){
            rx[0] = M[i][0] - deltaM; 
            rx[1] = M[i][0] + deltaM; 
            ry[0] = M[i][1] - deltaM; 
            ry[1] = M[i][1] + deltaM; 
            n = floor((rx[1]-rx[0]+1)*randunif()) - deltaM;
            m = floor((ry[1]-ry[0]+1)*randunif()) - deltaM;        
            z = M[i][0] + n;
            q = M[i][1] + m;
            if(z < 0){
                z = X - abs(n) + z;    
            }
            if(z >= X){
                z = n - (z - X);    
            }
            if(q < 0){
                q = X - abs(m) + q;
            }
            if(q >= X){
                q = m - (q - X);    
            }
            M[i][0] = z;
            M[i][1] = q;
            c = SCAPE[z][q][1]; 
            if(c > 0){
                if(iter == 999){
                    fprintf(Mv,"%d\t%d\n",z,q);
                }
                Sds[2]++;
                for(k=0; k<flower; k++){ /* OR below lets Polls use pollinated flowers */
                    if(P[c][k+2] == 1 || P[c][k+2] == 2){
                        if(randunif() > 0.5){
                            P[c][k+2] = 2;
                        }else{
                            P[c][k+2] = 3;    
                            SCAPE[z][q][0]++;
                        }
                    }
                }    
                /* break; */
            }
            j++;
        }
        if(randunif() > 0.2){
            z = M[i][0];
            q = M[i][1];            
            SCAPE[z][q][0]++;
        }     /* This if loop allows mutualists to survive multiple generations */
    }
    return EXIT_SUCCESS;
}
    
