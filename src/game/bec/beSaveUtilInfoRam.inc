igMetaObject *FUN_00346810(void) {
    if (g_beSaveUtilInfoRam_metaObject[0] == 0 || !isValid(g_beSaveUtilInfoRam_metaObject[0])) FUN_00346950();
    return g_beSaveUtilInfoRam_metaObject[0];
}

int beSaveUtilInfoRam_GetVTable(void) {
    struct Obj_346860 obj;
    igObject *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj.w10 = 0;
    obj.vt = &DAT_00538e10[0];
    obj.w12 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00538e10[0];
    if (&obj.w12 != 0) {
        o = (igObject *)obj.w12;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    obj.vt = &DAT_00539e90[0];
    if (&obj.w10 != 0) {
        o = (igObject *)obj.w10;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void FUN_00346950(void)
{
    igMetaObject_RunStaticInit(beSaveUtilInfoRam_Register);
}

void *beSaveUtilInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveUtilInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beSaveUtilInfoRam_GetMetaObject,
        beSaveUtilInfoRam_className,
        0x34, /* instance size */
        beSaveUtilInfoRam_GetVTable,
        beSaveUtilInfoRam_InitFields,
        0, /* extra callback item */
        g_beSaveUtilInfoRam_callbackList /* callback list */
    );
}

void beSaveUtilInfoRam_GetMetaObject(void)
{
    FUN_00346810();
}

void beSaveUtilInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSaveUtilInfoRam_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beSaveUtilInfoRam_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0034b0d0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beSaveUtilInfoRam_fieldTable[0], &DAT_004c3c38[0], &DAT_004c3c40[0], temp_s2);
}

