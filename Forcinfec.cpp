//Created by Leonardo B. L. Santos - santoslbl@gmail.com
//First version: 28/04/18
//Last update: 28/04/18

/*
Description: Given a series of values x (new cases), determine R0 using the approach presented in:
Favier et al. (2006). Early determination of the reproductive number for vector-borne diseases the case of dengue in Brazil. Tropical Medicine and International Health, v. II, p. 332–340
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (){

 int    m=52,             //total number of points (epidemiological weeks)
        n,                //number of points for the least squares estimation 
        i;                //index for each number

 float  newcases[8321],   //520 + 1      
        acucases[8321],
        x[8321], 
        y[8321],    
        xmed,         //average for x  
        ymed,         //average for y
        Sxx, Sxy, Syy, R2, ttable, min, max, QME, t, reject,
        b1;           //output data: a -> y = ax + b

 FILE *arq1,              //input file: min, guest, max for each parameter
      *arq2;              //output file: output distribution

 //srand((unsigned) time(NULL));
 //aleat=rand()%101;


//for(n=3;n<=m;n++){
 
arq1 = fopen("in.txt","r");
 
int vezes, VEZES=9; //VEZES = number of different samples
 
for(i=0;i<(m*VEZES);i++){   
    fscanf(arq1,"%f",&newcases[i]);
    acucases[i]=0;  
}
	  
for(vezes=0;vezes<VEZES;vezes++){ 
 
 float b=0;
 int ja=0, tam=0;
 n=1;
 for(i=(m*vezes);i<(m*vezes+m);i++){   
	 if(ja==0 && newcases[i]<b) {
	 	n=tam;
	 	ja=1;
	 }  
     tam++;
     b=newcases[i]; 
     //printf("i= %d, n= %d\n", i, n);    
 }
 
 if(ja==0) n=m;
 




//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 if(n<3) n=3;
 //n=3;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!






 //printf("vezes= %d %d\n", vezes+1, n);    

 xmed=0;
 ymed=0;

 float a=0;
 //for(i=0;i<n;i++){   
 for(i=(m*vezes);i<(m*vezes+n);i++){   //not  for(i=(m*vezes);i<(m*vezes+m);i++){  -> we must to trade m by n
     acucases[i]=a+newcases[i];
     a=acucases[i];
     x[i]=acucases[i];  
     y[i]=newcases[i];
     xmed+=x[i];
     ymed+=y[i];
     printf("%d %f %f %f %f\n", i,newcases[i],acucases[i],x[i],y[i]);
 } 
 // fclose(arq1);                   

 xmed/=n;
 ymed/=n;

 arq2 = fopen("outputFI.txt","a");

 Sxx=0;
 Sxy=0;
 Syy=0;

 for(i=(m*vezes);i<(m*vezes+n);i++){  //m - número de semanas
       Sxy+=( (x[i]-xmed)*(y[i]-ymed) );
       Sxx+=pow(x[i]-xmed, 2);
       Syy+=pow(y[i]-ymed, 2); 	
 }
 b1 = Sxy/Sxx;//slope
 
 R2 = pow(Sxy,2)/(Sxx*Syy); 
 //r = sqrt(R2);  ??? -?
 QME = (Syy-b1*Sxy)/(n-2); //criterio de tirada de pontos
 t = b1 / sqrt(QME/Sxx);
 //pvalue = 2*t;


 if(n==3) ttable=3.182;//erro
 if(n==4) ttable=2.776;
 if(n==5) ttable=2.571; 
 if(n==6) ttable=2.447;
 if(n==7) ttable=2.365;
 if(n==8) ttable=2.306;
 if(n==9) ttable=2.262;
 if(n==10) ttable=2.228;
 if(n==11) ttable=2.201;
 if(n==13) ttable=2.179;
 if(n==14) ttable=2.16;
 if(n==15) ttable=2.145;
 if(n==16) ttable=2.131;

 reject=0;
 if(fabs(t)>ttable) reject=1;

 min = b1 - ttable*sqrt(QME/Sxx);
 max = b1 + ttable*sqrt(QME/Sxx);
 
// if(fabs(t)>ttable) reject=1;
// if (min <0) reject=0;
 printf("vezes= %d %d %f \n", vezes+1, n, min);    
// printf("vezes= %f     ", sqrt(QME/Sxx));    


 fprintf(arq2, "%d %f %f %f %f %f %d\n", vezes+1, min, b1, max, reject, R2, n);
 
 fclose(arq2);

} //vezes
fclose(arq1);                   

printf("\n\nThat's all folks\n\n");

return(0);

} //main

