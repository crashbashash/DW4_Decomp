igMetaObject *g_beNDMWStatusCtrlFolder_metaObject;
igMetaField *g_beNDMWStatusCtrlFolder_folderMenuMetaField;

void beNDMWStatusCtrlFolder_Create(int arg0) {
    beNDMWStatusCtrlFolder_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrlFolder_metaObject, arg0);
}

igMetaObject *beNDMWStatusCtrlFolder_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusCtrlFolder_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWStatusCtrlFolder_EnsureRegistered();
done:
    return g_beNDMWStatusCtrlFolder_metaObject;
}

int beNDMWStatusCtrlFolder_GetVTable(void) {
    struct W_3ba0c0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = g_beNDMWStatusCtrlFolder_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beNDMWStatusCtrlFolder_vtable;
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void beNDMWStatusCtrlFolder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlFolder_Register);
}

void *beNDMWStatusCtrlFolder_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlFolder_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlFolder_GetMetaObjectFunction,
        "beNDMWStatusCtrlFolder",
        0x58, /* instance size */
        beNDMWStatusCtrlFolder_GetVTable,
        beNDMWStatusCtrlFolder_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusCtrlFolder_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlFolder_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlFolder_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWStatusCtrlFolder_fieldTable[] = {
    "_folderMenu",
};
static igMetaField **g_beNDMWStatusCtrlFolder_fieldHandles[] = {
    &g_beNDMWStatusCtrlFolder_folderMenuMetaField,
};
static int g_beNDMWStatusCtrlFolder_fieldOffsets[] = {
    84,
};

void beNDMWStatusCtrlFolder_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWStatusCtrlFolder_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWStatusCtrlFolder_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beNDMWStatusCtrlFolder_fieldTable, g_beNDMWStatusCtrlFolder_fieldHandles, g_beNDMWStatusCtrlFolder_fieldOffsets, temp_s1);
}

