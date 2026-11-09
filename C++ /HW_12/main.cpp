#include "RBTree.h"
#include "student.h"
#include <time.h>

int main(int argc, char** argv)
{
	double t1 = 0., t2 = 0., t3 = 0., t4 = 0., t5 = 0.;
	char * filename = nullptr;
	int res1 = 0, res2 = 0, res3 = 0, res4 = 0, res5 = 0.;
	int maxprint = 0, k = 0;
	io_status errorstatus = io_status::success;	
	if(argc != 4 || sscanf(argv[1], "%d", &maxprint) != 1
	|| sscanf(argv[2], "%d", &k) != 1)
	{
		return exitcode(io_status::format);
	}
	filename = argv[3];
	FILE* fp = fopen(filename, "r");
	if(!fp)
	{
		return exitcode(io_status::opent);
	}
	rb_tree<student> *RBTs = new rb_tree<student>;
	errorstatus = RBTs->read(fp);
	if(errorstatus != io_status:: success)
	{
		fclose(fp);
		return exitcode(errorstatus);
	}
	printf("Tree:\n");
	RBTs->print(maxprint);
    t1 = clock();
    res1 = RBTs->countSmallSTCardinality(k);
    t1 = (clock() - t1) / CLOCKS_PER_SEC;
    t2 = clock();
    res2 = RBTs->countShortSTCardinality(k);
    t2 = (clock() - t2) / CLOCKS_PER_SEC;
    t3 = clock();
    res3 = RBTs->countSlimSTCardinality(k);
    if(res3 == -1)
        printf("cannot allocate memory for task3\n");
    t3 = (clock() - t3) / CLOCKS_PER_SEC;
    t4 = clock();
    res4 = RBTs->countElementsOnLvlK(k);
    t4 = (clock() - t4) / CLOCKS_PER_SEC;
    t5 = clock();
    res5 = RBTs->countKBranches(k);
    t5 = (clock() - t5) / CLOCKS_PER_SEC;
    printf("%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 1, k, res1, t1);
    printf("%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 2, k, res2, t2);
    printf("%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 3, k, res3, t3);
    printf("%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 4, k, res4, t4);
    printf("%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 5, k, res5, t5);
    fclose(fp);
    delete RBTs;
    return 0;
}
