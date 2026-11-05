void InternalObjectList_Init(int *);
extern int *DAT_00586dc8[4];
int __internalObjectList_GetVTable(void) {
    int o[4];
    InternalObjectList_Init(o);
    return *(int *)((char *)o + *(int *)((char *)DAT_00586dc8[0] + 916));
}
