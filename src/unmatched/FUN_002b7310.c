typedef struct T { int w0; int refs; short s8[4]; } T;
typedef struct LST { char pad[12]; int count; } LST;
LST *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
T *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_00585748[4];
extern T * DAT_00585750[4];
extern int DAT_00587040[4];
void FUN_002b7310(void) {
    T *temp_s0;
    T *p;

    if (DAT_00585750[0] == 0) {
        DAT_00585750[0] = igMetaObject_CreateInstance(DAT_00585748[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        temp_s0 = DAT_00585750[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            p = DAT_00585750[0];
            p->refs = p->refs - 1;
            if (((unsigned long long) ((long long) p->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            *(short *)((char *)(DAT_00585750[0]) + 18) = (short) (FUN_002fc250()->count - 1);
            igMetaField_FinalizeDescriptor(DAT_00585750[0]);
        }
    }
}
