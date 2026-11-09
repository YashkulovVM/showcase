#include "2tree.h"
#include "stdio.h"
#include <time.h>

int main(int argc, char** argv)
{
    unsigned int r = 0, k = 0;
    const char* filename = nullptr;
    FILE* fp = nullptr;
    io_status errorstatus = io_status::success;
    unsigned int ret1 = 0, ret2 = 0, ret3 = 0, ret5 = 0;
    unsigned int ret4 = 0;
    double t4 = 0.;
    double t1 = 0., t2 = 0., t3 = 0., t5 = 0.;
    if (argc != 4)
        return exitcode(io_status::format);

    if (!(sscanf(argv[1], "%u", &r) == 1 && sscanf(argv[3], "%u", &k) == 1))
    {
        return exitcode(io_status::format);
    }
    filename = argv[2];

    fp = fopen(filename, "r");
    if (!fp)
        return exitcode(io_status::opent);

    tree T;
    errorstatus = T.read(fp);
    if (errorstatus == io_status::format)
    {
        fclose(fp);
        return exitcode(errorstatus);
    }

    printf("Tree:\n");
    T.print(r);

    t1 = clock();
    ret1 = T.countSmallBranches(k);
    t1 = (clock() - t1) / CLOCKS_PER_SEC;
    t2 = clock();
    ret2 = T.countElementsOfSmallBranches(k);
    t2 = (clock() - t2) / CLOCKS_PER_SEC;
    t3 = clock();
    ret3 = T.countShortSubtrees(k);
    t3 = (clock() - t3) / CLOCKS_PER_SEC;
    t4 = clock();
    ret4 = T.countSlimSubtrees(k);
    if(ret4 == static_cast<unsigned int>(-1))
        printf("cannot allocate memory for task4\n");
    t4 = (clock() - t4)/CLOCKS_PER_SEC;
    t5 = clock();
    ret5 = T.countNumberOfElementsOnLvl(k);
    if(ret5 == static_cast<unsigned int>(-1))
        printf("cannot allocate memory for task4\n");
    t5 = (clock() - t5) / CLOCKS_PER_SEC;
    
    printf("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 1, k, ret1, t1);
    printf("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 2, k, ret2, t2);
    printf("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 3, k, ret3, t3);
    printf("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 4, k, ret4, t4);
    printf("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 5, k, ret5, t5);
    fclose(fp);
    return 0;
}