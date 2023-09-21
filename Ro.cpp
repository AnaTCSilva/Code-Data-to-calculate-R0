//Created by Leonardo B. L. Santos - santoslbl@gmail.com
//First version: 27/04/18
//Last update: 28/04/18

/*
Description: Given a model and its parameters, to receive the minimum and the maximum values of each parameter and, given an input value
to calculate the output values distribution, considering
1. an uniform parameter distribution
2. a triangular distribution
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> //for random number

int main (){

 int    i,                //index for each parameter
        j,                //index for sliding in x (input value)
        k,                //index for sliding in par[1]
        l,                //index for sliding in par[2] 
        m,                //index for sliding in par[3]
        o,                //index for sliding in par[4] 
        p,                //index for sliding in par[5]						       
        q,                //index for sliding in par[6]	
        repeat0,          //index for x (input value) frequence
        repeat1,          //index for par[1]'s frequence
        repeat2,          //index for par[2]'s frequenc
        repeat3,          //index for par[3]'s frequence
        repeat4,          //index for par[4]'s frequenc
        repeat5,          //index for par[5]'s frequence
        repeat6;          //index for par[6]'s frequence        
 long int count;
 float  min[161], // 147 +1  
        minx,   
        max[161],
        maxx,    
        guess[161],
        x[161],    
        xmin[161],    
        xmax[161],    
        input,          //input data (doesn't varry) 
        a1,                //a value for par[1]
        a2,                //a value for par[2]
        a3,                //a value for par[3]
        a4,                //a value for par[4]
        a5,                //a value for par[5]		
        a6,                //a value for par[6]			        
        freq0,            //x (input value) frequence
        freq1,            //par[1]'s frequence 
        freq2,            //par[2]'s frequence
        freq3,            //par[3]'s frequence 
        freq4,            //par[4]'s frequence
        freq5,            //par[5]'s frequence 									 
        freq6,            //par[6]'s frequence 		        
        acu1,
        acu2,
        det,
        output;           //output data -> for a statistical a posteriori analysis

 FILE *arq1,              //input file: min, guest, max for each parameter
      *arq2;              //output file: output distribution

 //srand((unsigned) time(NULL));
 //aleat=rand()%101;
  
 printf("ok");

 arq1 = fopen("inputR0.txt","r");    
  for(i=0;i<9;i++){
     fscanf(arq1,"%f %f %f", &xmin[i],&x[i],&xmax[i]);     
  }
    // fscanf(arq1,"%f %f %f",&min[0],&max[0],&guess[0]);     
     fscanf(arq1,"%f %f %f",&min[1],&max[1],&guess[1]);        
     fscanf(arq1,"%f %f %f",&min[2],&max[2],&guess[2]);        
     fscanf(arq1,"%f %f %f",&min[3],&max[3],&guess[3]); 
     fscanf(arq1,"%f %f %f",&min[4],&max[4],&guess[4]); 
     fscanf(arq1,"%f %f %f",&min[5],&max[5],&guess[5]); 
     fscanf(arq1,"%f %f %f",&min[6],&max[6],&guess[6]);      
 fclose(arq1);                   

 //printf("\n\n%f %f %f %f %f %f %f %f %f",min[0],max[0],guest[0], min[1],max[1],guest[1], min[2],max[2],guest[2]);        

 arq2 = fopen("outputR0.txt","w");

/* 
 for(i=0;i<2;i++){
       printf("\nParameter[%d]->",i+1);
       printf("min:");
       scanf("%f",&min[i]);
       printf("max:");
       scanf("%f",&max[i]);
       printf("guess:");
       scanf("%f",&guest[i]);
 }
 */


  for(i=0;i<9;i++){

  xmin[i]/=7;
  xmax[i]/=7;
  x[i]/=7;
 
  count=0;
  acu1=0;
  acu2=0;
  minx=1000;
  maxx=0;

  if(xmin[i]<=0) xmin[i]=0.01; 

  min[0]=xmin[i];
  max[0]=xmax[i];
  guess[0]=x[i];

  minx = sqrt (  (min[0]/(min[1]+min[2]+min[3]) +1) * (min[0]/(min[4]+min[5]) +1) * (min[0]/(min[2]+min[3]) +1) * (min[0]/(min[5]+min[6]) +1)  );
  
  maxx = sqrt (  (max[0]/(max[1]+max[2]+max[3]) +1) * (max[0]/(max[4]+max[5]) +1) * (max[0]/(max[2]+max[3]) +1) * (max[0]/(max[5]+max[6]) +1)  );
     
 det = sqrt (  (guess[0]/(guess[1]+guess[2]+guess[3]) +1) * (guess[0]/(guess[4]+guess[5]) +1) * (guess[0]/(guess[2]+guess[3]) +1) * (guess[0]/(guess[5]+guess[6]) +1)  );


//guess[i] - são os parãmetros entomológicos, para BH, na semana, ou seja, multiplicados por 7

//guess[1] = teta_m x7 = 0.0833 x7 = 0.5831
//guess[2] = mu_m x7= 0.0365 x7 = 0.2555
//guess[3] = c_m x7= 0.0
//guess[4] = teta_h x7= 0.15 x7 = 1,05
//guess[5] = mu_h x7=  4 x 10−5 days−1 x7 = 0.00028
//guess[6] = alpha_h x7 =  0.125 days−1 x7 = 0.875



 //printf("%f %f %f %f %f %f %f %f\n\n", guess[0], guess[1], guess[2], guess[3], guess[4], guess[5], guess[6], output);
 
 for(j=0;j<=9;j++){
       
            input = min[0] +   j*(1.0/10)*(max[0]-min[0]); //uniform distribuition on x (input value)

            freq0 = 10 * (1 - fabs((input-guess[0])/(max[0]-min[0])) );  //a priori parameter distribuition on x (input value)

            //output = a1*input + a2; //model
            output = sqrt (  (input/(guess[1]+guess[2]+guess[3]) +1) * (input/(guess[4]+guess[5]) +1) * (input/(guess[2]+guess[3]) +1) * (input/(guess[5]+guess[6]) +1)  );

            if(output<minx) minx = output;
            if(output>maxx) maxx = output;
          
            //printf("j=%d k=%d freq0=%f freq1=%f output=%f\n", j, k, freq0, freq1, output);

            for(repeat0=0;repeat0<freq0;repeat0++) {
                //fprintf(arq2, "%f %f %f %f %f %f %f %f\n", input, guess[1], guess[2], guess[3], guess[4], guess[5], guess[6], output);
                                                           acu1+=fabs(output-det);
                                                           acu2+=pow(output-det,2);
                                                           count++; 

            }
 }


acu1/=count;
acu2/=count;
acu2=sqrt(acu2);
fprintf(arq2, "%d %f %f %f %f %f %ld\n", i+1, minx, det, maxx, acu1, acu2, count);
} // i

printf("\n\nThat's all folks\n\n");

 fclose(arq2);
 return(0);
    
} //main

