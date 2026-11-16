igMetaObject *g_beNDMWStatusCtrlBit_metaObject;
igMetaField *g_beNDMWStatusCtrlBit_playerNoListMetaField;

void beNDMWStatusCtrlBit_Create(int arg0) {
    beNDMWStatusCtrlBit_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrlBit_metaObject, arg0);
}

void *beNDMWStatusCtrlBit_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusCtrlBit_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusCtrlBit_EnsureRegistered();
    }
    return g_beNDMWStatusCtrlBit_metaObject;
}

int beNDMWStatusCtrlBit_GetVTable(void) {
    struct Obj_3b9860 o;
    int r;
    igObject_InitHeader(&o);
    o.f52 = 0;
    o.f56 = 0;
    o.f60 = 0;
    o.f64 = 0;
    o.f68 = 0;
    o.f72 = 0;
    o.f76 = 0;
    o.vt = &g_beNDMWStatusCtrlBit_vtable[0];
    o.f84 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNDMWStatusCtrlBit_vtable[0];
    igSmartPointer_igIntList_Destruct(&o.f84, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void beNDMWStatusCtrlBit_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlBit_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlBit_callbackList[] = { igIntList_EnsureRegistered, 0 };

void *beNDMWStatusCtrlBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlBit_GetMetaObjectFunction,
        "beNDMWStatusCtrlBit",
        0x58, /* instance size */
        beNDMWStatusCtrlBit_GetVTable,
        beNDMWStatusCtrlBit_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlBit_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlBit_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlBit_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlBit_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusCtrlBit_fieldTable[] = {
    "_playerNoList",
};
static igMetaField **g_beNDMWStatusCtrlBit_fieldHandles[] = {
    &g_beNDMWStatusCtrlBit_playerNoListMetaField,
};
static int g_beNDMWStatusCtrlBit_fieldOffsets[] = {
    84,
};

void beNDMWStatusCtrlBit_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWStatusCtrlBit_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWStatusCtrlBit_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWStatusCtrlBit_fieldTable, g_beNDMWStatusCtrlBit_fieldHandles, g_beNDMWStatusCtrlBit_fieldOffsets, temp_s2);
}

