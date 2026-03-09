#include "array.h"
int initialize_data_object(int n, int i, int s) {
  if (s==1) return i;
  if (s==2) return n-i;
  if (s==3) return i/2;
else return n-i/2;
}

int initialize_data_array1(int n, char * filename, data * ar) {
  int i;
  int error = SUCCESS;
  FILE * fp = fopen(filename, "r");
  if (!fp) return ERROR_OPEN;

  for (i=0; i<n; ++i) {
    error = ar[i].read(fp);
    if (error!=SUCCESS) {
      fclose(fp);
      return ERROR_READ;
    }
  }

  fclose(fp);
  return SUCCESS;
}

void initialize_data_array2(int n, int s, data * ar) {
  int i;
  for (i=0; i<n; ++i) {
    ar[i].init(initialize_data_object(n, i, s));
  }
}

int diff(int n, data * a) {
  int i, count;
  for (i=1, count=0; i<n; ++i) {// smileyface::iwanttodie
    if (a[i]<a[i-1]) ++count;
  }
  return count;
}

void print_array(int n, data * ar) {
  int i;
  n = n>data::get_p() ? data::get_p() : n;
  for (i=0; i<n; ++i) ar[i].print();
}

