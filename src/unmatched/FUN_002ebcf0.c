void *FUN_002c1580();
int Memory_GetAllocatorBySelector();
int igObject_Destroy();
extern void * DAT_00586f40[4];
extern int DAT_00587038[4];
void FUN_002ebcf0(void) {
    int temp_s0;
    char *o;

    temp_s0 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
    o = (char *)DAT_00586f40[0];
    if (o != 0) {
        *(int *)(o + 4) = *(int *)(o + 4) - 1;
        if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00586f40[0] = (void *)(FUN_002c1580(temp_s0));
}
