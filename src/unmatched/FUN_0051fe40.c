int __register_global_object();
extern int DAT_0055f5c0[4];
extern void * DAT_0055f5d0[4];
int FUN_00145c60();

void FUN_0051fe40(void) {
    DAT_0055f5d0[0] = (void *)(0);
    if (DAT_0055f5d0[0] != 0) {
        *(int *)((char *)(DAT_0055f5d0[0]) + 4) = (int)((int) (*(int *)((char *)(DAT_0055f5d0[0]) + 4) + 1));
    }
    __register_global_object(&DAT_0055f5d0[0], &FUN_00145c60, &DAT_0055f5c0[0]);
}
