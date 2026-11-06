int FUN_002ed5a0();
int Memory_GetAllocatorBySelector();
int StringChunk_ReleaseHeader();
int FUN_0032c240();
extern int DAT_00587048[4];
extern int DAT_00587330[4];
int FUN_0032c110(int arg0) {
    void *sp2C;
    int *temp_a1;
    int temp_s0;
    int temp_v0;

    FUN_0032c240(&sp2C, DAT_00587330[0], arg0);
    temp_s0 = FUN_002ed5a0(sp2C, Memory_GetAllocatorBySelector(DAT_00587048[0]));
    if (sp2C != 0) {
        temp_a1 = (int *)((char *)sp2C - 8);
        temp_v0 = *(int *)((char *)(sp2C) - 4) - 1;
        *(int *)((char *)(sp2C) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    return temp_s0;
}
