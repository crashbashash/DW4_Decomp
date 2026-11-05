typedef struct T { int word0; int references; char pad[10]; short s18; } T;
typedef struct C { char pad[12]; int cnt; } C;
C *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
T *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_00585d80[4];
extern T *DAT_00585d88[4];
extern int DAT_00587040[4];
void FUN_002bf990(void) {
    T *temp_s0;
    T *p;

    if (DAT_00585d88[0] == 0) {
        DAT_00585d88[0] = igMetaObject_CreateInstance(DAT_00585d80[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        temp_s0 = DAT_00585d88[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            p = DAT_00585d88[0];
            p->references = p->references - 1;
            if (((unsigned long long)(long long)p->references & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            DAT_00585d88[0]->s18 = FUN_002fc250()->cnt - 1;
            igMetaField_FinalizeDescriptor(DAT_00585d88[0]);
        }
    }
}
