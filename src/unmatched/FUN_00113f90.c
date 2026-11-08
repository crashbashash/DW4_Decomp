typedef struct {
    int count;
    int max_count;
    int init_count;
    int wait_threads;
    unsigned int attr;
    unsigned int option;
} SemaParam;

int CreateSema(SemaParam *param);
extern int D_00482590;
extern int D_00482594;

void FUN_00113f90(void)
{
    SemaParam first;
    SemaParam second;
    first.max_count = 1;
    first.init_count = 1;
    second.max_count = 1;
    second.init_count = 1;
    D_00482590 = CreateSema(&first);
    D_00482594 = CreateSema(&second);
}
