igMetaObject *g_igHotKeyBinding_metaObject;
igMetaField *g_igHotKeyBinding_keyMetaField;
igMetaField *g_igHotKeyBinding_buttonMetaField;
igMetaField *g_igHotKeyBinding_actionMetaField;

int FUN_0044dc20(int arg0) {
    igHotKeyBinding_RunStaticInit();
    return igMetaObject_CreateInstance((int)g_igHotKeyBinding_metaObject, arg0);
}

igMetaObject *igHotKeyBinding_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyBinding_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyBinding_RunStaticInit();
    return g_igHotKeyBinding_metaObject;
}

int igHotKeyBinding_GetVTable(void) {
    struct Obj_44dcb0 o;
    struct R *t;
    int r;
    igObject_InitHeader(&o);
    o.vt = &DAT_00541b70[0];
    o.p = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00541b70[0];
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

void igHotKeyBinding_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyBinding_Register);
}

static igMetaObjectCallback g_igHotKeyBinding_callbackList[] = { igAction_RunStaticInit, 0 };

void igHotKeyBinding_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igHotKeyBinding_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igHotKeyBinding_GetMetaObject,
        "igHotKeyBinding",
        0x14, /* instance size */
        igHotKeyBinding_GetVTable,
        &igHotKeyBinding_InitFields,
        0, /* extra callback item */
        g_igHotKeyBinding_callbackList /* callback list */
    );
}

void thunk_igHotKeyBinding_GetMetaObject(void) {
    igHotKeyBinding_GetMetaObject();
}

static FieldFactory g_igHotKeyBinding_ctorTable[] = {
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igHotKeyBinding_fieldTable[] = {
    "_key",
    "_button",
    "_action",
};
static igMetaField **g_igHotKeyBinding_fieldHandles[] = {
    &g_igHotKeyBinding_keyMetaField,
    &g_igHotKeyBinding_buttonMetaField,
    &g_igHotKeyBinding_actionMetaField,
};
static int g_igHotKeyBinding_fieldOffsets[] = {
    8,
    12,
    16,
};
static int g_igHotKeyBinding_keyDefault;
static int g_igHotKeyBinding_buttonDefault = 0x20;

void igHotKeyBinding_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igHotKeyBinding_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igHotKeyBinding_ctorTable, 3);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    igEnumMetaField_SetDefaultValue(temp_v0, &g_igHotKeyBinding_keyDefault);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_00145eb0);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    igEnumMetaField_SetDefaultValue(temp_v0_2, &g_igHotKeyBinding_buttonDefault);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(FUN_00146850);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00453250();
    igMetaObject_NameFields(temp_s0, g_igHotKeyBinding_fieldTable, g_igHotKeyBinding_fieldHandles, g_igHotKeyBinding_fieldOffsets, temp_s2);
}

