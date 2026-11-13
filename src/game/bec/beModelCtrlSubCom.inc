igMetaObject *FUN_0034f210(void) {
    if (g_beModelCtrlSubCom_metaObject[0] == 0) {
        g_beModelCtrlSubCom_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlSubCom_metaObject[0];
}

igMetaObject *FUN_0034f260(void) {
    igMetaObject *g = g_beModelCtrlSubCom_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0034f340();
    return g_beModelCtrlSubCom_metaObject[0];
}

int beModelCtrlSubCom_GetVTable(void) {
    struct Obj_34f2b0 o;
    struct R *t;
    int r;
    igObject_InitHeader(&o);
    o.vt = &DAT_00537fe0[0];
    o.p = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00537fe0[0];
    if (&o.p != 0) {
        t = o.p;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}

void FUN_0034f340(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSubCom_Register);
}

void *beModelCtrlSubCom_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlSubCom_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlSubCom_GetMetaObject,
        beModelCtrlSubCom_className,
        0xc, /* instance size */
        beModelCtrlSubCom_GetVTable,
        beModelCtrlSubCom_InitFields,
        0, /* extra callback item */
        g_beModelCtrlSubCom_callbackList /* callback list */
    );
}

void beModelCtrlSubCom_GetMetaObject(void)
{
    FUN_0034f260();
}

void beModelCtrlSubCom_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlSubCom_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beModelCtrlSubCom_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beModelCtrlSubCom_fieldTable[0], &DAT_004c4bd0[0], &DAT_004c4bd8[0], temp_s2);
}

