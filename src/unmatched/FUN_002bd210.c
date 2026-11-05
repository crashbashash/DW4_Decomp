/* 0x002bd210 - FUN_002bd210. lazily created meta object; typed structs, pointer cached for the release, int length local Verified byte-identical by tools/verify.py. */
typedef struct M { char pad4[4]; int f4; char pad8[10]; short f18; } M;
typedef struct R { char pad12[12]; int f12; } R;
R *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
M *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_00585b20[4];
extern M *DAT_00585b28[4];
extern int DAT_00587040[4];
void FUN_002bd210(void) {
    M *temp_s0;
    M *p;
    int len;

    if (DAT_00585b28[0] == 0) {
        DAT_00585b28[0] = igMetaObject_CreateInstance(DAT_00585b20[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        temp_s0 = DAT_00585b28[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            p = DAT_00585b28[0];
            p->f4 = p->f4 - 1;
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = FUN_002fc250()->f12;
            DAT_00585b28[0]->f18 = len - 1;
            igMetaField_FinalizeDescriptor(DAT_00585b28[0]);
        }
    }
}
