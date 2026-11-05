struct R { int vt; unsigned int rc; char pad[10]; short s18; };
struct M { char pad[12]; int f12; };
void *igMetaObject_CreateInstance();
int Memory_GetAllocatorBySelector();
struct M *FUN_002fc250();
int MetaRefList_AppendRetained();
int igObject_Destroy();
int igMetaField_FinalizeDescriptor();
extern int DAT_00586108[4];
extern struct R * DAT_00586110[4];
extern int DAT_00587040[4];
void FUN_002c3330(void) {
    struct R *temp_s0;
    struct R *g;

    if (DAT_00586110[0] == 0) {
        DAT_00586110[0] = igMetaObject_CreateInstance(DAT_00586108[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        temp_s0 = DAT_00586110[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            g = DAT_00586110[0];
            g->rc = g->rc - 1;
            if ((g->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            DAT_00586110[0]->s18 = FUN_002fc250()->f12 - 1;
            igMetaField_FinalizeDescriptor(DAT_00586110[0]);
        }
    }
}