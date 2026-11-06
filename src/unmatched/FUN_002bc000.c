typedef struct Q { char pad4[4]; int f4; char pad12[10]; short f18; } Q;
typedef struct R { char pad[12]; int f12; } R;
R *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
Q *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_00585a90[4];
extern Q * DAT_00585a98[4];
extern int DAT_00587040[4];
void FUN_002bc000(void) {
    Q *temp_s0;
    Q *p;

    if (DAT_00585a98[0] == 0) {
        DAT_00585a98[0] = igMetaObject_CreateInstance(DAT_00585a90[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        temp_s0 = DAT_00585a98[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            p = DAT_00585a98[0];
            p->f4 -= 1;
            if ((p->f4 & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
            DAT_00585a98[0]->f18 = FUN_002fc250()->f12 - 1;
            igMetaField_FinalizeDescriptor(DAT_00585a98[0]);
        }
    }
}
