int *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
int *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_005865b0[4];
extern int *DAT_005865b8[4];
extern int DAT_00587040[4];
void FUN_002c6620(void) {
    int *s0;
    int *g;

    if (DAT_005865b8[0] == 0) {
        DAT_005865b8[0] = igMetaObject_CreateInstance(DAT_005865b0[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        s0 = DAT_005865b8[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), s0);
            g = DAT_005865b8[0];
            g[1] = g[1] - 1;
            if ((g[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            *(short *)((char *)DAT_005865b8[0] + 18) = (short)(FUN_002fc250()[3] - 1);
            igMetaField_FinalizeDescriptor(DAT_005865b8[0]);
        }
    }
}
