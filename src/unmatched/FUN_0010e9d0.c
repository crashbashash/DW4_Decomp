typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; unsigned int option; } SemaParam;
int FUN_0010aee0(SemaParam *);
extern int DAT_00481f08;
extern int DAT_00481f0c;
void FUN_0010e9d0(void) {
    SemaParam p;
    if (DAT_00481f08 == -1) {
        p.option = 0;
        p.init_count = 1;
        p.max_count = 1;
        DAT_00481f08 = FUN_0010aee0(&p);
        DAT_00481f0c = FUN_0010aee0(&p);
    }
}
