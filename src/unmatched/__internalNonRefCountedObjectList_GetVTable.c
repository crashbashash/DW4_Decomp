int ObjectPointerList_Init();
extern void * DAT_00586dc8[4];
int __internalNonRefCountedObjectList_GetVTable(void) {
    int o[4];

    ObjectPointerList_Init(o);
    return *(int *)((char *)o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
