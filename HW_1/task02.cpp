#include "data.h"
#include "array.h"


void task2(data * a, int n, data * b, int m, data * c);
void task2(data * a, int n, data * b, int m, data * c) {
  int i, j;

  for (i=0, j=0; i<n && j<m; ) {
    if (a[i]<b[j]) {
      c[i+j] = a[i];
      ++i;
    }
    else {
      c[i+j] = b[j];
      ++j;
    }
  }
  if (i<n) {
    for ( ; i<n; ++i)
      c[j+i] = a[i];
  }
  else if (j<m) {
    for ( ; j<m; ++j) 
      c[j+i] = b[j];
  } 
}


int data::p = 0;

int main(int argc, char * argv[]) {
  int n, pa, sa, m, pb, sb;
  int ret, task;
  char * namea = nullptr;
  char * nameb = nullptr;

  data * a = nullptr;
  data * b = nullptr;
  data * c = nullptr;
  double t;

  if (!(argc==7 || argc==8 || argc==9))
    {
        printf("Wrong usage;\n");
        return 1;
    }
  if (argc==7)
  {
	  if (!(sscanf(argv[1],"%d", &n)==1 && sscanf(argv[2],"%d", &pa)==1 && sscanf(argv[3],"%d", &sa)==1 && sscanf(argv[4],"%d", &m)==1 &&
	 	  sscanf(argv[5],"%d", &pb)==1 && sscanf(argv[6],"%d", &sb)==1 && n>0 && m>0 && pa>0 && pb>0 && sa>=1 && sa<=4 && sb>=1 && sb<=4))
	  {
	      printf("Usage: n p_a s_a m p_b s_b\n");
	      return 7;
	  }
  }
  else if (argc==8)
  {
  	if (!(sscanf(argv[1],"%d", &n)==1 && sscanf(argv[2],"%d", &pa)==1 && sscanf(argv[3],"%d", &sa)==1 && n>0 && pa>0 && sa>=0 && sa<=4))
  	{
  	    printf("Usage: n p_a s_a ...\n");
  	    return 8;
  	}
	if (sa==0)
	{
	    namea=argv[4];
	    if (!(sscanf(argv[5],"%d", &m)==1 && sscanf(argv[6],"%d", &pb)==1 && sscanf(argv[7],"%d", &sb)==1 && m>0 && pb>0 && sb>=1 && sb<=4))
	    {
	    	printf("Usage: n p_a s_a filename_a m p_b s_b\n");
		    return 8;
	    }
	}
	else
	{
	    if (!(sscanf(argv[4],"%d", &m)==1 && sscanf(argv[5],"%d", &pb)==1 && sscanf(argv[6],"%d", &sb)==1 && m>0 && pb>0 && sb==0))
	    {
		   printf("Usage: n p_a s_a m p_b s_b filename_b\n");
		    return 8;
	    }
	    nameb=argv[7];
	}
	
}
  else if (argc==9)
  {
	  namea=argv[4];
	  nameb=argv[8];

	  if (!(sscanf(argv[1],"%d", &n)==1 && sscanf(argv[2],"%d", &pa)==1 && sscanf(argv[3],"%d", &sa)==1 && sscanf(argv[5],"%d", &m)==1 && 
		    sscanf(argv[6],"%d", &pb)==1 && sscanf(argv[7],"%d", &sb)==1 && n>0 && m>0 && pa>0 && pb>0 && sa==0 && sb==0))
	  {
	      printf("Usage: n p_a s_a filename_a m p_b s_b filename_b\n");
	      return 10;
	  }
  }

  a = new data[n];
  if (!a) {
    printf("Not enough memory for a!\n");
    return ERROR_MEMORY;
  }
  if (namea) {
    ret = initialize_data_array1(n, namea, a);
    if (ret!=SUCCESS) {
         switch(ret) {
          case ERROR_OPEN:
            printf("Cannot open %s\n", namea);
            break;
          case ERROR_READ:
            printf("Cannot read %s\n", namea);
            break;
          default:
            printf("Unknown error %d\n", ret);
        }
        delete[] a;
        return ERROR;

    }
  }
  else initialize_data_array2(n, sa, a);

  b = new data[m];
  if (!b) {
    printf("Not enough memory for b!\n");
    delete[] a;
    return ERROR_MEMORY;
  }
  if (nameb) {
    ret = initialize_data_array1(m, nameb, b);
    if (ret!=SUCCESS) {
         switch(ret) {
          case ERROR_OPEN:
            printf("Cannot open %s\n", nameb);
            break;
          case ERROR_READ:
            printf("Cannot read %s\n", nameb);
            break;
          default:
            printf("Unknown error %d\n", ret);
        }
        delete[] b;
        delete[] a;
        return ERROR;

    }
  }
  else initialize_data_array2(m, sb, b);

  printf("Array A:\n");
  data::set_p(pa);
  print_array(n, a);
  printf("Array B:\n");
  data::set_p(pb);
  print_array(m, b);

  c = new data[n+m];
  if (!c) {
    printf("Not enough memory for c!\n");
    delete[] a;
    delete[] b;
    return ERROR_MEMORY;
  }

  t = clock();
  task2(a, n, b, m, c);
  t = (clock()-t)/CLOCKS_PER_SEC;

  printf("Array C:\n");
  data::set_p(pa+pb);
  print_array(m+n, c);

  task=2;
  printf("%s : Task = %d Diff = %d Elapsed = %.2f\n",
        argv[0], task, diff(n+m, c), t);


  delete[] a;
  delete[] b;
  delete[] c;
  return 0;
}
