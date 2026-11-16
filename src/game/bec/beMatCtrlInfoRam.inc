igMetaObject *g_beMatCtrlInfoRam_metaObject;
igMetaField *g_beMatCtrlInfoRam_workMetaField;

void *beMatCtrlInfoRam_GetMetaObject(void) {
    bool ok;
    if (g_beMatCtrlInfoRam_metaObject == 0) goto make;
    ok = !!(g_beMatCtrlInfoRam_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beMatCtrlInfoRam_EnsureRegistered();
done:;
    return g_beMatCtrlInfoRam_metaObject;
}

int beMatCtrlInfoRam_GetVTable(void) {
    Obj_359810 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r9 = 0;
    obj.vt = &g_beMatCtrlInfoRam_vtable[0];
    obj.r10 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beMatCtrlInfoRam_vtable[0];
    obj.rel10();
    obj.vt = &g_beBaseInfoRam_vtable[0];
    obj.rel9();
    return r;
}

O *igSmartPointer_beMatCtrlInfoWork_Destruct(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void beMatCtrlInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfoRam_Register);
}

static igMetaObjectCallback g_beMatCtrlInfoRam_callbackList[] = { beMatCtrlInfoWork_EnsureRegistered, 0 };

void *beMatCtrlInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beMatCtrlInfoRam_GetMetaObjectFunction,
        "beMatCtrlInfoRam",
        0x30, /* instance size */
        beMatCtrlInfoRam_GetVTable,
        beMatCtrlInfoRam_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfoRam_callbackList /* callback list */
    );
}

void beMatCtrlInfoRam_GetMetaObjectFunction(void)
{
    beMatCtrlInfoRam_GetMetaObject();
}

static FieldFactory g_beMatCtrlInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrlInfoRam_fieldTable[] = {
    "_work",
};
static igMetaField **g_beMatCtrlInfoRam_fieldHandles[] = {
    &g_beMatCtrlInfoRam_workMetaField,
};
static int g_beMatCtrlInfoRam_fieldOffsets[] = {
    44,
};

void beMatCtrlInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMatCtrlInfoRam_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMatCtrlInfoRam_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beMatCtrlInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beMatCtrlInfoRam_fieldTable, g_beMatCtrlInfoRam_fieldHandles, g_beMatCtrlInfoRam_fieldOffsets, temp_s2);
}

