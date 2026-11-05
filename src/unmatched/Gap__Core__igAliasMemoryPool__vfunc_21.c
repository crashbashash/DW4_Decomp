int igAliasMemoryPool_EnsureRegistered(void);
int igObject_CloneViaMetadata(int, int);
void *FUN_002f0040(int, int, void *);
void *Memory_GetDefaultAllocator(void);
void *igAliasMemoryPool_CopyConstruct(void *, int);
extern unsigned char * DAT_00586dc8[4];
void *Gap__Core__igAliasMemoryPool__vfunc_21(int arg0, int arg1) {
    void *p;
    if (*DAT_00586dc8[0] != 0) {
        igAliasMemoryPool_EnsureRegistered();
        return (void *)igObject_CloneViaMetadata(arg0, arg1);
    }
    p = FUN_002f0040(0xB8, 0, Memory_GetDefaultAllocator());
    if (p != 0) {
        p = igAliasMemoryPool_CopyConstruct(p, arg0);
    }
    return p;
}
