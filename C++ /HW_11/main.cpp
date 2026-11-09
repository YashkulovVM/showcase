#include "student.h"
#include "btree.h"
#include <time.h>

int main(int argc, char** argv)
{
    if(argc != 5)
        return exitcode(io_status::format);

    int maxsize = 0, maxprint = 0, k = 0; 
    char* filename = nullptr;
    int res1 = 0, res2 = 0, res3 = 0, res4 = 0, res5 = 0, res6 = 0;
    double t1 = 0., t2 = 0., t3 = 0., t4 = 0., t5 = 0., t6 = 0.;
    io_status errorstatus = io_status::success;

    if(sscanf(argv[1], "%d", &maxsize) != 1 
    || sscanf(argv[2], "%d", &maxprint) != 1
    || sscanf(argv[3], "%d", &k) != 1)
        return exitcode(io_status::format);
    
    filename = argv[4];
    FILE* fp = fopen(filename, "r");
    if(!fp)
        return exitcode(io_status::opent);
    
    b_tree<student>* BTs = new b_tree<student>(maxsize);
    errorstatus = BTs->read(fp);
    if(errorstatus != io_status::success)
        return exitcode(errorstatus);
    BTs->print(maxprint);
    t1 = clock();
    res1 = BTs->countKNodesCardinality(k);
    t1 = (clock() - t1) / CLOCKS_PER_SEC;
    t2 = clock();
    res2 = BTs->countSmallSTCardinality(k);
    t2 = (clock() - t2) / CLOCKS_PER_SEC;
    t3 = clock();
    res3 = BTs->countShortSTCardinality(k);
    t3 = (clock() - t3) / CLOCKS_PER_SEC;
    t4 = clock();
    res4 = BTs->countSlimSTCardinality(k);
    if(res4 == -1)
        printf("cannot allocate memory for task4\n");
    t4 = (clock() - t4) / CLOCKS_PER_SEC;
    t5 = clock();
    res5 = BTs->countElementsOnLvlK(k);
    t5 = (clock() - t5) / CLOCKS_PER_SEC;
    t6 = clock();
    res6 = BTs->countKBranches(k);
    t6 = (clock() - t6) / CLOCKS_PER_SEC;
    printf("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 1, maxsize, k, res1, t1);
    printf("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 2, maxsize, k, res2, t2);
    printf("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 3, maxsize, k, res3, t3);
    printf("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 4, maxsize, k, res4, t4);
    printf("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 5, maxsize, k, res5, t5);
    printf("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 6, maxsize, k, res6, t6);
    fclose(fp);
    delete BTs;
    return 0;
}
