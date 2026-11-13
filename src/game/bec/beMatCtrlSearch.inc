igMetaObject *FUN_00359ff0(void) {
    if (g_beMatCtrlSearch_metaObject[0] == 0) {
        g_beMatCtrlSearch_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMatCtrlSearch_metaObject[0];
}

void *FUN_0035a040(void) {
    igMetaObject *g = g_beMatCtrlSearch_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035a120();
    }
    return g_beMatCtrlSearch_metaObject[0];
}

int beMatCtrlSearch_GetVTable(void) {
    struct Obj_35a090 obj;
    char *o;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536aa0[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536aa0[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void FUN_0035a120(void)
{
    igMetaObject_RunStaticInit(beMatCtrlSearch_Register);
}

void *beMatCtrlSearch_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlSearch_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMatCtrlSearch_GetMetaObject,
        beMatCtrlSearch_className,
        0x1c, /* instance size */
        beMatCtrlSearch_GetVTable,
        beMatCtrlSearch_InitFields,
        0, /* extra callback item */
        g_beMatCtrlSearch_callbackList /* callback list */
    );
}

void beMatCtrlSearch_GetMetaObject(void)
{
    FUN_0035a040();
}

void beMatCtrlSearch_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMatCtrlSearch_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beMatCtrlSearch_ctorTable[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00359ff0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_00359e60();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beMatCtrlSearch_fieldTable[0], &DAT_004c60c0[0], &DAT_004c60e0[0], temp_s2);
}

