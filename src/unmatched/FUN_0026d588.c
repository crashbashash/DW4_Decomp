int FUN_002607e8();
int FUN_00267100();
extern int DAT_004eec50[4];
void FUN_0026d588(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004eec50[0]);
        return;
    }
    FUN_00267100(*(int *)((char *)(arg0) + 4));
}
