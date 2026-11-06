int FUN_002b9500();
int Memory_GetAllocatorBySelector();
extern int DAT_00530608[4];
extern int DAT_00587048[4];
void *FUN_002dc180(void *arg0) {
    *(int *)((char *)(arg0) + 8) = (int)(&DAT_00530608[0]);
    *(int *)((char *)(arg0) + 0) = FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0]));
    *(int *)((char *)(arg0) + 4) = FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0]));
    return arg0;
}
