#include "list2.h"

#include <stdio.h>
#include <time.h>

int main(int argc, char** argv)
{
    int r = 0, k = 0, task = 0, len1 = 0, len2 = 0;
    const char* filename = nullptr;
    FILE* fp = nullptr;
    io_status errorstatus = io_status::success;
    double t = 0.;
    if (argc != 4)
        return exitcode(io_status::format);

    if (!(sscanf(argv[1], "%d", &r) == 1
       && sscanf(argv[3], "%d", &k) == 1))
    {
        return exitcode(io_status::format);
    }
    filename = argv[2];

    fp = fopen(filename, "r");
    if (!fp)
        return exitcode(io_status::opent);

    list2 list;
    errorstatus = list.read(fp);
    if (errorstatus == io_status::format)
    {
        fclose(fp);
        return exitcode(errorstatus);
    }

    task = taskNum(argv[0]);

    len1 = list.get_length();

    printf("Old List\n");
    list.print(r);

    t = clock();
    switch (task)
    {
    case 1:
        list.shift(k);
        break;
    case 2:
        list.solveProblem2(k);
        break;
    case 3:
        list.solveProblem3(k);
        break;
    case 4:
    case 5:
        list.solveProblem5(k);
        break;
    case 6:
        list.solveProblem6(k);
        break;
    case 7:
        list.solveProblem7(k);
        break;
    case 8:
    default:
        break;
    }
    t = clock() / CLOCKS_PER_SEC;

    printf("New List\n");
    list.print(r);

    len2 = list.get_length();

    printf("%s : Task = %d Len Old = %u Len New = %u Elapsed = %.2f\n", argv[0], task, len1, len2, t);
    fclose(fp);
    return 0;
}
