#include "data.h"
#include "array.h"


void task10(data * a, int n);

void task10(data * a, int n)
{
    int i, j, k, i_1, i_2;

    for(k=1; k<n; k++)
    {
        i=k;
        while (i>0)
        {
            j=(i-1)/2;
            if (a[i]>a[j])
            {
                a[i].swap(a[j]);
            }
            else
            {
                break;
            }
            i=j;
        }
    }

    for(k=n-1; k>0; k--)
    {
        a[0].swap(a[k]);

        i=0;

        while (i<k)
        {
            i_1=2*i+1; 
            i_2=i_1+1;
            if (i_1 >= k)
            {
                break;
            }
            if ((i_2 < k) && (a[i_1]<a[i_2]))
            {
                i_1=i_2;
            }

            if (a[i]<a[i_1])
            {
                a[i].swap(a[i_1]);
                i=i_1;
            }
            else
            {
                break;
            }
        }
    }
}

int data::p = 0;

int main(int argc, char * argv[]) {
  int n, p, s;
  int ret, task;
  char * filename = nullptr;
  data * a = nullptr;
  double t;

  if (argc==4) {
    if (!(sscanf(argv[1], "%d", &n)==1 && sscanf(argv[2], "%d", &p)==1 && sscanf(argv[3], "%d", &s)==1 && s>=1 && s<=4 && n>0 && p>0)) { 
      printf("Usage: n p (s) filename\n");
      return ERROR;
    }
  }
  else if (argc==5) {
    if (!(sscanf(argv[1], "%d", &n)==1 && sscanf(argv[2], "%d", &p)==1 && sscanf(argv[3], "%d", &s)==1 && s==0 && n>0 && p>0)) { 
      printf("Usage: n p (s) filename\n");
      return ERROR;
    }
    filename = argv[5];
  }
  else {
    printf("Usage: n p (s) filename\n");
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
  task10(a, n);
  t = (clock()-t)/CLOCKS_PER_SEC; 
  printf("New array:\n");
  print_array(n, a);
 
  task=10;
  printf("%s : Task = %d Diff = %d Elapsed = %.2f\n",
        argv[0], task, diff(n, a), t);


  delete[] a;
  return 0;
}
