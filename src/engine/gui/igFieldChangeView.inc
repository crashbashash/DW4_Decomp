int FUN_00450de0(int arg0) {
    igFieldChangeView_EnsureRegistered();
    return igMetaObject_CreateInstance(*(int *)0x58C550, arg0);
}

igMetaObject *igFieldChangeView_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldChangeView_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldChangeView_EnsureRegistered();
    return g_igFieldChangeView_metaObject[0];
}

int igFieldChangeView_GetVTable(void) {
    struct Obj_450e70 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541360[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00541360[0];
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

void igFieldChangeView_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldChangeView_Register);
}

void igFieldChangeView_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFieldChangeView_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igFieldChangeView_GetMetaObject,
        igFieldChangeView_className,
        0x14, /* instance size */
        igFieldChangeView_GetVTable,
        &igFieldChangeView_InitFields,
        0, /* extra callback item */
        g_igFieldChangeView_callbackList /* callback list */
    );
}

void thunk_igFieldChangeView_GetMetaObject(void) {
    igFieldChangeView_GetMetaObject();
}

void igFieldChangeView_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFieldChangeView_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igFieldChangeView_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00450a00();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002beca0();
    igMetaObject_NameFields(temp_s0, &g_igFieldChangeView_fieldTable[0], &DAT_004d0710[0], &DAT_004d0718[0], temp_s2);
}

