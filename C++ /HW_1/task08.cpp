#include "data.h"
#include "array.h"


void task8(data * a, data * c, int n);

void task8(data * a, data * b, int n)
{
    int num_of_merge=1;
    int l;
    int i, j, p, k;
    int final_l;
    int last_len_final;
    int normal;
    int top_i;
    int top_j;

    for(l=1; l<n; l*=2)
    {
        final_l=2*l;
        last_len_final=n%(final_l);
        normal=n-last_len_final;

        if (num_of_merge%2==1)
        {
            for(k=0; k<normal; k+=final_l)
            {
                top_i=k+l;
                top_j=k+final_l;
                for(p=k, i=k, j=top_i; p<top_j; p++)
                {
                    if (i<top_i && j<top_j)
                    {
                        if (a[i]<a[j])
                        {
                            b[p]=a[i];
                            i++;
                        }
                        else
                        {
                            b[p]=a[j];
                            j++;
                        }
                    }
                    else if(i>=top_i && j<top_j)
                    {
                        b[p]=a[j];
                        j++;
                    }
                    else if(i<top_i && j>=top_j)
                    {
                        b[p]=a[i];
                        i++;
                    }
                }
            }

            if (last_len_final!=0)
            {
                top_i=normal+l;
                top_j=n;
                for(k=normal, i=normal, j=top_i; k<n; k++)
                {
                    if (i<top_i && j<top_j)
                    {
                        if (a[i]<a[j])
                        {
                            b[k]=a[i];
                            i++;
                        }
                        else
                        {
                            b[k]=a[j];
                            j++;
                        }
                    }
                    else if(i>=top_i && j<top_j)
                    {
                        b[k]=a[j];
                        j++;
                    }
                    else if(i<top_i && j>=top_j)
                    {
                        b[k]=a[i];
                        i++;
                    }
                }
            }
        }
        else
        {
            for(k=0; k<normal; k+=final_l)
            {
                top_i=k+l;
                top_j=k+final_l;
                for(p=k, i=k, j=top_i; p<top_j; p++)
                {
                    if (i<top_i && j<top_j)
                    {
                        if (b[i]<b[j])
                        {
                            a[p]=b[i];
                            i++;
                        }
                        else
                        {
                            a[p]=b[j];
                            j++;
                        }
                    }
                    else if(i>=top_i && j<top_j)
                    {
                        a[p]=b[j];
                        j++;
                    }
                    else if(i<top_i && j>=top_j)
                    {
                        a[p]=b[i];
                        i++;
                    }
                }
            }

            if (last_len_final!=0)
            {
                top_i=normal+l;
                top_j=n;
                for(k=normal, i=normal, j=top_i; k<n; k++)
                {
                    if (i<top_i && j<top_j)
                    {
                        if ((b[i]<b[j]))
                        {
                            a[k]=b[i];
                            i++;
                        }
                        else
                        {
                            a[k]=b[j];
                            j++;
                        }
                    }
                    else if(i>=top_i && j<top_j)
                    {
                        a[k]=b[j];
                        j++;
                    }
                    else if(i<top_i && j>=top_j)
                    {
                        a[k]=b[i];
                        i++;
                    }
                }
            }
        }
        num_of_merge++;
    }

    if (num_of_merge%2==0)
    {
        for(i=0; i<n; i++)
        {
            a[i]=b[i];
        }
    }

}



/*void merge(data * a, int n, data * b, int m, data * c);
void merge(data * a, int n, data * b, int m, data * c) {
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
  for ( ; i<n; ++i ) c[i+j] = a[i];
  for ( ; i<m; ++j ) c[i+j] = b[j];
}*/
/*
void task8(data * a, data * c, int n) {
  int i=0;  // i is num of merged elements;
  int size, r;
  int r_new = n%2;
  data * ptr1 = a;
  data * ptr2 = c;
  
  for (size=1, r=n%size; size+r < n; size*=2, std::swap(ptr1, ptr2)) {
    r = n%size;
    r_new = n % (2*size);

    printf("size = %d r = %d r_new = %d\n", size, r, r_new);
    printf("ptr1:\n");
    print_array(n, ptr1);
    printf("ptr2:\n");
    print_array(n, ptr2);
    
    r = n%size;
    r_new = n % (2*size);
    for (i=0; i+r_new<n; i+=2*size) {
      merge(ptr1+i, size, ptr1+i+size, size, ptr2+i);  
    }
    if (r<r_new) merge(ptr1+i, size, ptr1+i+size, r, ptr2+i);
    else {
      for ( ; i<n; ++i) ptr2[i]=ptr1[i];
    }
  }

    printf("size = %d r = %d r_new = %d\n", size, r, r_new);
    printf("ptr1:\n");
    print_array(n, ptr1);
    printf("ptr2:\n");
    print_array(n, ptr2);
    printf("size = %d, i = %d, r_new = %d*****\n", size, i, r_new);
    size/=2;
  merge(ptr1, size, ptr1+i, r, ptr2); 

    printf("size = %d r = %d r_new = %d\n", size, r, r_new);
    printf("ptr1:\n");
    print_array(n, ptr1);
    printf("ptr2:\n");
    print_array(n, ptr2);
  for (i=0; i<n; ++i) ptr1[i]=ptr2[i];

}
*/


int data::p = 0;

int main(int argc, char * argv[]) {
  int n, p, s;
  int ret, task;
  char * filename = nullptr;
  data * a = nullptr;
  data * c = nullptr;
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
  
  c = new data[n];
  if (!c) {
    printf("Not enough memory for extra array!\n");
    delete[] a;
    return ERROR_MEMORY;
  }

  t = clock();
  task8(a, c, n);
  t = (clock()-t)/CLOCKS_PER_SEC; 
  printf("New array:\n");
  print_array(n, a);
 
  task=8;
  printf("%s : Task = %d Diff = %d Elapsed = %.2f\n",
        argv[0], task, diff(n, a), t);


  delete[] a;
  delete[] c;
  return 0;
}
