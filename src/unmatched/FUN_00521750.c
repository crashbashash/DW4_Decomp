int __register_global_object();
extern int DAT_0058c660[4];
extern void * DAT_0058c670[4];
int FUN_001d6560();

void FUN_00521750(void) {
    DAT_0058c670[0] = (void *)(0);
    if (DAT_0058c670[0] != 0) {
        *(int *)((char *)(DAT_0058c670[0]) + 4) = (int)((int) (*(int *)((char *)(DAT_0058c670[0]) + 4) + 1));
    }
    __register_global_object(&DAT_0058c670[0], &FUN_001d6560, &DAT_0058c660[0]);
}
