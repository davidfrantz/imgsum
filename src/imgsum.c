#include <stdio.h>   // core input and output functions
#include <stdlib.h>  // standard general utilities library

/** Geospatial Data Abstraction Library (GDAL) **/
#include "gdal.h"           // public (C callable) GDAL entry points
#include "cpl_conv.h"


int main( int argc, char *argv[] ){
char *fname = NULL;
GDALDatasetH  fp;
GDALRasterBandH band;
int p, i, j, nx, ny, nc;
double *line = NULL;
double sum, sumline;
double nodata;


  if (argc != 3){ printf("usage: %s image nodata\n\n", argv[0]); exit(1);}

  fname  = argv[1];
  nodata = atof(argv[2]);
  
  GDALAllRegister();
  fp = GDALOpen(fname, GA_ReadOnly);
  if (fp == NULL){ printf("could not open %s\n\n", fname); exit(1);}

  nx  = GDALGetRasterXSize(fp);
  ny  = GDALGetRasterYSize(fp);
  nc = nx*ny;
  
  line = (double*) calloc(nx, sizeof(double));
  if (line == NULL){ printf("unable to allocate memory!\n"); exit(1);}

  band = GDALGetRasterBand(fp, 1);


  sum = 0;

  for (i=0; i<ny; i++){

    if (GDALRasterIO(band, GF_Read, 0, i, nx, 1, 
      line, nx, 1, GDT_Float64, 0, 0) == CE_Failure){
      printf("could not read line %d.\n", i); exit(1);}

    sumline = 0;

    for (j=0; j<nx; j++){

      if (line[j] == nodata) continue;

      sumline += line[j];

    }
    
    sum += sumline;

  }

  GDALClose(fp);

  free((void*)line);
  
  printf("%f\n", sum);

  exit(0);
}
