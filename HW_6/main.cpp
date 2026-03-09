#include "list.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv)
{
    int r = 0, task = 0;
    const char* filename = nullptr;
    FILE* fp = nullptr;
    io_status errorstatus = io_status::success;
    double t = 0.;
    if (argc != 3)
        return exitcode(io_status::format);

    if (!(sscanf(argv[1], "%d", &r) == 1))
    {
        return exitcode(io_status::format);
    }
    filename = argv[2];

    fp = fopen(filename, "r");
    if (!fp)
        return exitcode(io_status::opent);

    list l;
    errorstatus = l.read(fp);
    if (errorstatus == io_status::format)
    {
        fclose(fp);
        return exitcode(errorstatus);
    }

    task = taskNum(argv[0]);

    printf("Old List\n");
    l.print(r);

    t = clock();
    switch (task)
    {
    case 1:
        l.bubbleSort();
        break;
    case 2:
        l.selectionSort();
        break;
    case 3:
        l.insertionSort();
        break;
    case 4:
        l.mergeSort();
        break;
    case 5:
        break;
    default:
        break;
    }
    t = clock() / CLOCKS_PER_SEC;
    printf("New List\n");
    l.print(r);
    
    printf("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, l.diff(), t);
    fclose(fp);
    return 0;
}
