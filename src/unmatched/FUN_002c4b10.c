typedef struct S1 { char pad4[4]; int f4; char pad8[10]; short f12; } S1;
typedef struct L { char pad12[12]; int fc; } L;
L *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
S1 *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_00586388[4];
extern S1 * DAT_00586390[4];
extern int DAT_00587040[4];
void FUN_002c4b10(void) {
    S1 *temp_s0;
    S1 *temp_a0;
    int n;

    if (DAT_00586390[0] == 0) {
        DAT_00586390[0] = igMetaObject_CreateInstance(DAT_00586388[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        temp_s0 = DAT_00586390[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            temp_a0 = DAT_00586390[0];
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
            n = FUN_002fc250()->fc - 1;
            DAT_00586390[0]->f12 = n;
            igMetaField_FinalizeDescriptor(DAT_00586390[0]);
        }
    }
}
