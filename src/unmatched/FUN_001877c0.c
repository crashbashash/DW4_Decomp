typedef struct R { char pad4[4]; int f4; char pad8[10]; short f18; } R;
typedef struct Q { char pad12[12]; int f12; } Q;
Q *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
R *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_00560f48[4];
extern R * DAT_00560f50[4];
extern int DAT_00587040[4];
void FUN_001877c0(void) {
    R *temp_s0;
    R *o;
    int t;

    if (DAT_00560f50[0] == 0) {
        DAT_00560f50[0] = igMetaObject_CreateInstance(DAT_00560f48[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        temp_s0 = DAT_00560f50[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            o = DAT_00560f50[0];
            o->f4 = o->f4 - 1;
            if ((o->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = FUN_002fc250()->f12 - 1;
            DAT_00560f50[0]->f18 = t;
            igMetaField_FinalizeDescriptor(DAT_00560f50[0]);
        }
    }
}
