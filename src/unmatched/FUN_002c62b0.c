void *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
int *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_00586598[4];
extern int *DAT_005865a0[4];
extern int DAT_00587040[4];
void FUN_002c62b0(void) {
    int *s0;
    int *o;
    int count;

    if (DAT_005865a0[0] == 0) {
        DAT_005865a0[0] = igMetaObject_CreateInstance(DAT_00586598[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        s0 = DAT_005865a0[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), s0);
            o = DAT_005865a0[0];
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            count = *(int *)((char *)FUN_002fc250() + 12); /* Read as a whole word first; a direct `short = int - 1` store would be narrowed to an lh. */
            *(short *)((char *)DAT_005865a0[0] + 18) = count - 1;
            igMetaField_FinalizeDescriptor(DAT_005865a0[0]);
        }
    }
}
