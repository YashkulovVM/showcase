#include "data.h"
#include "array.h"



int task3(data * a, int n, int m);
int task3(data * a, int n, int m) {
  int i=0, j=n-1;

  while (i<j) {
    while (i<m && a[i]<a[m]) ++i;
    while (j>m && a[j]>a[m]) --j;
    
    if (i<j) {
      a[i].swap(a[j]);
      if (m==i) {
        m=j;
        --i;
        
      }
      else if (m==j) {
        m=i;
        --j;
        
      } 
    }
  }

  return m;
}

int data::p = 0;

int main(int argc, char * argv[]) {
  int m, n, p, s;
  int ret, task;
  char * filename = nullptr;
  data * a = nullptr;
  double t;

  if (argc==5) {
    if (!(sscanf(argv[1], "%d", &m)==1 && sscanf(argv[2], "%d", &n)==1 && sscanf(argv[3], "%d", &p)==1 && sscanf(argv[4], "%d", &s)==1 && 
          s>=1 && s<=4 && n>0 && p>0 && m>=0 && m<n)) { 
      printf("Usage: m n p (s) filename\n");
      return ERROR;
    }
  }
  else if (argc==6) {
    
    if (!(sscanf(argv[1], "%d", &m)==1 && sscanf(argv[2], "%d", &n)==1 && sscanf(argv[3], "%d", &p)==1 && sscanf(argv[4], "%d", &s)==1 &&
          s==0 && n>0 && p>0 && m>=0 && m<n)) { 
      printf("Usage: m n p (s) filename\n");
      return ERROR;
    }
    filename = argv[5];
  }
  else {
    printf("Usage: m n p (s) filename\n");
    return ERROR;
  }

  data::set_p(p);

  a = new data[n];
  if (!a) {
    printf("Not enough memory!\n");
    return ERROR_MEMORY;
  }
  if (filename) {
    ret = initialize_data_array1(n, filename, a);
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
        delete[] a;
        return ERROR;
    }
  }
  else initialize_data_array2(n, s, a);
  
  printf("Array:\n");
  print_array(n, a);
  
  t = clock();
  ret = task3(a, n, m);
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf("New Array:\n");
  print_array(n, a);


  task=3;
  printf("%s : Task = %d Res = %d Elapsed = %.2f\n",
        argv[0], task, ret, t);


  delete[] a;
  return 0;
}
