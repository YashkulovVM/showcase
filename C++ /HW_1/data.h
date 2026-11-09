#ifndef data_H
#define data_H
#include "makros.h"
class data {
  private:
    int m = M;
    double a[M] = {0};
    static int p;
  public:
    data () = default;
    ~data () = default;
    
    int get_m () const { return m; }
    const double * get_a () { return a; }
    static int get_p () { return p; }
    static void set_p (int q) {
      p = q; 
    }

    // Copy constructor
    data (const data &x) = default;
    // Assignement operator
    data& operator= (const data&) = default;
    
    // Comparison operators
    bool operator< (const data& x) const
    { return m < x.m; }
    bool operator> (const data& x) const
    { return m > x.m; }
    
    // Print data in a line (not more than p): m a[0] a[1] ... a[m-1]
    void print (FILE * fp = stdout)  {
      int length = data::get_p()<m ? data::get_p() : m;
      int i;

      fprintf(fp, "%d", m);
      for (i=0; i<length; ++i) {
        fprintf(stdout, " %lf", a[i]);
      }
      fputc('\n', fp);
    }

    // Read data from the line: m a[0] a[1] ... a[m-1]
    int read (FILE *fp = stdin) {
      int i;
      double x = 0;

      if (!fscanf(fp, "%d", &m)) return ERROR_READ;
      if (m>M) {
        for (i=0; i<M; ++i) {
          if (fscanf(fp, "%lf", &a[i])!=1) return ERROR_READ;
        }
        for ( ; i<m; ++i) {
          if (fscanf(fp, "%lf", &x)!=1) return ERROR_READ;
        }
      }
      else {
        for (i=0; i<m; ++i) {
          if (!fscanf(fp, "%lf", &a[i])) return ERROR_READ;
        }
      }
      return SUCCESS;
    }
    // Init data by formulae with number s
    
void init (int s) {
      //int i;
      m=s;
      //for (i=0; i<m; ++i) a[i]=0;
    }

    void swap(data& b) {
      std::swap(a, b.a);
      std::swap(m, b.m);
    }
};


/* if define after declarations - CE bcs of default arguments
void data::print (FILE * fp = stdout) {
  int length = data::get_p()<m ? data::get_p() : m;
  int i;

  fprintf(fp, "%d", m);
  for (i=0; i<length; ++i) {
    fprintf(stdout, " %lf", a[i]);
  }

  fputc('\n', fp);
}
int data::read(FILE * fp = stdin) {

  int i;

  if (!fscanf(fp, "%d", &m)) return ERROR_READ;

  if (m>M) m = M;

  for (i=0; i<m; ++i) {
    if (!fscanf(fp, "%lf", &a[i])) return ERROR_READ;
  }
  return SUCCESS;
}
*/

#endif // data
