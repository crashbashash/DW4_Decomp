void *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
int *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_00585908[4];
extern int *DAT_00585910[4];
extern int DAT_00587040[4];
void FUN_002b9b90(void) {
    int *s0;
    int *o;

    if (DAT_00585910[0] == 0) {
        DAT_00585910[0] = igMetaObject_CreateInstance(DAT_00585908[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        s0 = DAT_00585910[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), s0);
            o = DAT_00585910[0];
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            *(short *)((char *)DAT_00585910[0] + 18) = *(int *)((char *)FUN_002fc250() + 12) - 1;
            igMetaField_FinalizeDescriptor(DAT_00585910[0]);
        }
    }
}
