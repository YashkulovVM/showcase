#include "tree.h"
#include "list.h"
#include <time.h>


int list::m = 0;
int list::r = 0;
int main(int argc, char** argv)
{
    int new_r = 0, new_m = 0;
    int ret1 = 0, ret2 = 0, ret3 = 0, ret4 = 0, ret5 = 0;
    double t1 = 0., t2 = 0., t3 = 0., t4 = 0., t5 = 0.;
    const char* filename = nullptr;
    FILE* fp = nullptr;
    io_status errorstatus = io_status::success;
    if (argc != 4)
        return exitcode(io_status::format);

    if (!(sscanf(argv[1], "%d", &new_r) == 1 && sscanf(argv[3], "%d", &new_m) == 1))
    {
        return exitcode(io_status::format);
    }
    list::set_r(new_r);
    list::set_m(new_m);
    filename = argv[2];

    //tree<student>
    fp = fopen(filename, "r");
    if (!fp)
        return exitcode(io_status::opent);


    tree<student>* Ts = new tree<student>;
    errorstatus = Ts->read(fp);
    if(errorstatus != io_status::success)
        {
            fclose(fp);
            return exitcode(errorstatus);
        }
    printf("tree of students:\n");
    Ts->print(stdout, new_r);


    t1 = clock();
    ret1 = Ts->countLeavesTotalCardinality();
    t1 = (clock() - t1) / CLOCKS_PER_SEC;
    t2 = clock();
    ret2 = Ts->countLongBranchCardinality();
    t2 = (clock() - t2) / CLOCKS_PER_SEC;
    t3 = clock();
    ret3 = Ts->countMaxLevelCardinality();
    t3 = (clock() - t3) / CLOCKS_PER_SEC;
    t4 = clock();
    ret4 = Ts->countMaxLRDiff();
    t4 = (clock() - t4) / CLOCKS_PER_SEC;
    t5 = clock();
    ret5 = Ts->countParentsWithOneChild();
    t5 = (clock() - t5) / CLOCKS_PER_SEC; 
    printf("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 1, new_m, ret1, t1);
    printf("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 2, new_m, ret2, t2);
    printf("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 3, new_m, ret3, t3);
    printf("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 4, new_m, ret4, t4);
    printf("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 5, new_m, ret5, t5);

    fclose(fp);
    delete Ts;

    //tree<list>
    fp = fopen(filename, "r");
    tree<list>* Tl = new tree<list>;
    errorstatus = Tl->read(fp);
    if(errorstatus != io_status::success)
        {
            fclose(fp);
            return exitcode(errorstatus);
        }
    printf("tree of lists:\n");
    Tl->print(stdout, new_r);

    t1 = clock();
    ret1 = Tl->countLeavesTotalCardinality();
    t1 = (clock() - t1) / CLOCKS_PER_SEC;
    t2 = clock();
    ret2 = Tl->countLongBranchCardinality();
    t2 = (clock() - t2) / CLOCKS_PER_SEC;
    t3 = clock();
    ret3 = Tl->countMaxLevelCardinality();
    t3 = (clock() - t3) / CLOCKS_PER_SEC;
    t4 = clock();
    ret4 = Tl->countMaxLRDiff();
    t4 = (clock() - t4) / CLOCKS_PER_SEC;
    t5 = clock();
    ret5 = Tl->countParentsWithOneChild();
    t5 = (clock() - t5) / CLOCKS_PER_SEC;
    printf("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 1, new_m, ret1, t1);
    printf("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 2, new_m, ret2, t2);
    printf("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 3, new_m, ret3, t3);
    printf("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 4, new_m, ret4, t4);
    printf("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 5, new_m, ret5, t5);

    fclose(fp);
    delete Tl;

    return 0;
}