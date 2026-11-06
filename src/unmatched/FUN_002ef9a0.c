int FUN_002c0a00(int);
int Memory_GetAllocatorBySelector(int);

void FUN_002ef9a0(void) {
    *(int *)0x586F48 = FUN_002c0a00(Memory_GetAllocatorBySelector(*(int *)0x587038));
}
