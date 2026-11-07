void *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
void *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_0056d9d8[4];
extern void * DAT_0056d9e0[4];
extern int DAT_00587040[4];
void FUN_002284a0(void) {
    void *temp_s0;

    if (DAT_0056d9e0[0] == 0) {
        DAT_0056d9e0[0] = (void *)(igMetaObject_CreateInstance(DAT_0056d9d8[0], Memory_GetAllocatorBySelector(DAT_00587040[0])));
        temp_s0 = (void *)(DAT_0056d9e0[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            {
                void *held = (void *)DAT_0056d9e0[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_0056d9e0[0]) + 18) = (short) (*(int *)((char *)(FUN_002fc250()) + 12) - 1);
            igMetaField_FinalizeDescriptor(DAT_0056d9e0[0]);
        }
    }
}
