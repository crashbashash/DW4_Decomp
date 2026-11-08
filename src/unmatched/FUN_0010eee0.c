typedef struct {
    int count;
    int max_count;
    int init_count;
    int wait_threads;
    unsigned int attr;
    unsigned int option;
} SemaParam;

int CreateSema(SemaParam *param);
extern int D_00481f04;

void FUN_0010eee0(void)
{
    SemaParam param;
    if (D_00481f04 == -1) {
        param.init_count = 1;
        param.max_count = 1;
        param.option = 0;
        D_00481f04 = CreateSema(&param);
    }
}
