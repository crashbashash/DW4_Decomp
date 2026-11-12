igMetaObject *FUN_00137fb0(void) {
    if (g_igDisplayListAttr_metaObject[0] == 0) {
        g_igDisplayListAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igDisplayListAttr_metaObject[0];
}

igMetaObject *igDisplayListAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igDisplayListAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00138160();
    return g_igDisplayListAttr_metaObject[0];
}

int igDisplayListAttr_GetVTable(void) {
    struct Obj_138050 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523ba0[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00523ba0[0];
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

void **FUN_001380e0(void **arg0, short arg1) {
    S_temp_a0_1380e0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_1380e0 *)((void *)(*arg0));
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00138160(void)
{
    igMetaObject_RunStaticInit(igDisplayListAttr_Register);
}

void igDisplayListAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDisplayListAttr_metaObject,
        igAttr_Register,
        igAttr_GetPublishedMetaObject,
        thunk_igDisplayListAttr_GetMetaObject,
        igDisplayListAttr_className,
        0x10, /* instance size */
        igDisplayListAttr_GetVTable,
        &igDisplayListAttr_InitFields,
        0, /* extra callback item */
        g_igDisplayListAttr_callbackList /* callback list */
    );
}

void thunk_igDisplayListAttr_GetMetaObject(void) {
    igDisplayListAttr_GetMetaObject();
}

void igDisplayListAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igDisplayListAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486708[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0013ad40();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00486710[0], &DAT_00486718[0], &DAT_00486720[0], temp_s2);
}

