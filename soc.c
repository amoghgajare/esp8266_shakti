#include <stdio.h>

//signed int setState = 1;    //1 for discharging, -1 for charging
int count = 0;
float current = 1000;            //in millamperes
float voltage;
float crated = 3950; 
int soc1, soc2, soc3, soc4; 
float socInt1 = 90, socInt2 = 100, socInt3 = 80 , socInt4 = 75;             //initial SOC
float socFinal1, socFinal2, socFinal3, socFinal4;     //final SOC

void main(){
for(count = 0; count <50; count++){
socFinal1 = socInt1 - (current/crated);
socInt1 = socFinal1;
printf("%f \n", socFinal1);

socFinal2 = socInt2 -(current/crated);
socInt2 = socFinal2;
printf("%f \n", socFinal2);

socFinal3 = socInt3 - (current/crated);
socInt3 = socFinal3;
printf("%f \n", socFinal3);

socFinal4 = socInt4 - (current/crated);
socInt4 = socFinal4;
printf("%f \n", socFinal4);
}
}
