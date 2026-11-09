#include "data.h"
#include "array.h"



int task1(data * ar, int n, data& x);
int task1(data * ar, int n, data& x) {
  int top=n, bottom=0, s;

  while (bottom!=top) {
    s = (bottom + top)/2;
    if (ar[s]<x) bottom=s+1;
    else top=s;
  }

  return bottom;
}

int data::p = 0;

int main(int argc, char * argv[]) {
  char * x_file = nullptr;
  int n, p, s;
  int ret, task;
  char * filename = nullptr;
  FILE * fp1 = nullptr;
  data x;
  data * ar = nullptr;
  double t;

  if (argc==5) {
    x_file = argv[1];
    if (!(sscanf(argv[2], "%d", &n)==1 && sscanf(argv[3], "%d", &p)==1 && sscanf(argv[4], "%d", &s)==1 && s>=1 && s<=4 && n>0 && p>0)) { 
      printf("Usage: x n p (s) filename\n");
      return ERROR;
    }
  }
  else if (argc==6) {
    x_file = argv[1];
    if (!(sscanf(argv[2], "%d", &n)==1 && sscanf(argv[3], "%d", &p)==1 && sscanf(argv[4], "%d", &s)==1 && s==0 && n>0 && p>0)) { 
      printf("Usage: x n p (s) filename\n");
      return ERROR;
    }
    filename = argv[5];
  }
  else {
    printf("Usage: x n p (s) filename\n");
    return ERROR;
  }

  data::set_p(p);

  fp1 = fopen(x_file, "r");
  if (!fp1) {
    printf("Cannot open %s!\n", x_file);
    return ERROR_OPEN;
  } 
  ret=x.read(fp1);
  if (ret!=SUCCESS) {
    switch(ret) {
      case ERROR_READ:
        printf("Cannot read %s\n", x_file);
        break;
      default:
        printf("Unknown error %d\n", ret);
      }
    fclose(fp1);
    return ERROR;
  }
  fclose(fp1);

  ar = new data[n];
  if (!ar) {
    printf("Not enough memory!\n");
    return ERROR_MEMORY;
  }
  if (filename) {
    ret = initialize_data_array1(n, filename, ar);
      if (ret!=SUCCESS) {
        switch(ret) {
          case ERROR_OPEN:
            printf("Cannot open %s\n", filename);
            break;
          case ERROR_READ:
            printf("Cannot read %s\n", filename);
            break;
          default:
            printf("Unknown error %d\n", ret);
        }
        delete[] ar;
        return ERROR;
    }
  }
  else initialize_data_array2(n, s, ar);
  
  printf("X:\n");
  x.print();
  printf("Array:\n");
  print_array(n, ar);
  
  t = clock();
  ret = task1(ar, n, x);
  t = (clock()-t)/CLOCKS_PER_SEC;
  task=1;
  printf("%s : Task = %d Res = %d Elapsed = %.2f\n",
        argv[0], task, ret, t);


  delete[] ar;
  return 0;
}
