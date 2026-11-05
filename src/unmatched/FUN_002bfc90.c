typedef struct X { char pad[4]; int f4; char pad2[10]; short f18; } X;
typedef struct Y { char pad[12]; int f12; } Y;
Y *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
X *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_00585de0[4];
extern X *DAT_00585de8[4];
extern int DAT_00587040[4];
void FUN_002bfc90(void) {
    X *temp_s0;
    X *t;
    if (DAT_00585de8[0] == 0) {
        DAT_00585de8[0] = igMetaObject_CreateInstance(DAT_00585de0[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        temp_s0 = DAT_00585de8[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            t = DAT_00585de8[0];
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
            DAT_00585de8[0]->f18 = FUN_002fc250()->f12 - 1;
            igMetaField_FinalizeDescriptor(DAT_00585de8[0]);
        }
    }
}
