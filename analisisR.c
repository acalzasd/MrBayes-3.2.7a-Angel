#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define Lmax 1000000
#define prec 0.001
#define tini 40000
#define ndat 50000
#define w 6

int main()
{ 
    // Nombre archivos
    char nameTemp[100] = "./data-T4-PT/tempIndex.dat";
    char nameRho[100] = "rho.dat";
    char nameDat[100] = "output.txt";

    // Variables
    FILE *input, *output1, *output2;
    int nfilas, ncol, i, j, k, ngen, nchains, nswap;
    double **rho, *f, *prob, *rhoMean, *mean;
    double errorRel, auxRho, auxRho2, auxInt, tauInt;
    char buffer[Lmax];
    char s[2] ="\t";
    char *num;
    char flag; 

    // Calculo Ngen y Nchains
    input=fopen(nameTemp,"r");
    nfilas=0;
    ncol=1;
    do{
        flag=fgetc(input);
        if(flag=='\t' && nfilas==1) ncol++;
        if(flag=='\n') nfilas++;
        if(feof(input)) break;
    } while(1);
    ngen=nfilas;
    nchains=ncol-1;
    fclose(input);

    // Dimensionar
    rho = (double**)calloc(floor(nchains),sizeof(double*));
    for(i=0; i<nchains; i++)
        rho[i] = (double*)calloc(ndat,sizeof(double));
    rhoMean = (double*)calloc(ndat,sizeof(double));
    mean = (double*)calloc(floor(nchains),sizeof(double));
    f = (double*)calloc(ngen,sizeof(double));
    prob = (double*)calloc(floor(nchains),sizeof(double)); 

    // Calculo Rho
    output1 = fopen(nameRho,"w");
    output2 =fopen(nameDat,"w");
    auxRho=0;  
    for (i=0; i<floor(nchains); i++)
        prob[i]=0;
    for(i=0; i<ndat; i++)
        rhoMean[i]=0;
    for (k=2; k<=ncol;k++)
    {
        input=fopen(nameTemp,"r");
        for (j=0; j<ngen; j++)
        {
            fgets (buffer, sizeof(buffer), input);
            num = strtok(buffer, s);
            if(j==0 && k==2) nswap=floor(atof(num));
            i=2;
            while(i<=k) 
            {
                num = strtok(NULL, s);
                i++;
            }
            f[j]=atof(num);
            mean[k-2]+=f[j];
            for (i=0; i<floor(nchains); i++)
                if(floor(f[j])==i) prob[i]+=1;
        }
        mean[k-2]/=ngen;
        fclose(input);
        fprintf(output2,"Cadena n:%d\n",k-1);
        for (i=0; i<floor(nchains); i++)
        {
            prob[i]/=ngen;
            fprintf(output2,"Prob(%d)=%f\n",i,prob[i]);
        }
        for(i=0; i<ndat; i++)
            rho[k-2][i]=0;
        for(i=0; i<ndat; i++)
        {
            for(j=tini; j<(ngen-i); j++)
                rho[k-2][i]+=(f[j]-mean[k-2])*(f[j+i]-mean[k-2]);
            rho[k-2][i]/=(ngen-tini-i);
        }
        auxRho+=rho[k-2][0];
        auxRho2=rho[k-2][0];
        for(i=0; i<ndat; i++)
        {
            rhoMean[i]+=rho[k-2][i];
            rho[k-2][i]/=auxRho2;
        }
    }
    auxRho/=(ncol-1);
    fprintf(output2,"Medias Rho:\n");
    for (i=0; i<floor(nchains); i++)
        fprintf(output2,"Cadena(%d)=%f\n",i,mean[i]);
    fprintf(output1,"#t\trho(t)\n");
    for(i=0; i<ndat; i++)
    {
        rhoMean[i]/=(ncol-1);
        rhoMean[i]/=auxRho;
        fprintf(output1,"%d\t",i*nswap);
        for (j=0; j<floor(nchains); j++)
            fprintf(output1,"%f\t",rho[j][i]);
        fprintf(output1,"%f\n",rhoMean[i]);
    }
    fclose(output1);

    // Calculo del tiempo de autocorrelacion integral
    tauInt=1;
    do{
        auxInt=tauInt;
        tauInt=0;
        for(i=1; i<(w*auxInt); i++)
            tauInt+=rhoMean[i];
        tauInt+=0.5;
        errorRel=fabs(auxInt-tauInt)/fabs(auxInt);
    } while(errorRel>prec);
    fprintf(output2,"Integrated autocorrelation time: %f\n",tauInt*nswap);
    fprintf(output2,"Pasos empleados: %d\n",i);
    fclose(output2);

    return 0;
}