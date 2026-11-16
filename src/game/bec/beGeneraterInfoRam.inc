igMetaObject *g_beGeneraterInfoRam_metaObject;
igMetaField *g_beGeneraterInfoRam_workMetaField;

igMetaObject *beGeneraterInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterInfoRam_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beGeneraterInfoRam_EnsureRegistered();
    return g_beGeneraterInfoRam_metaObject;
}

int beGeneraterInfoRam_GetVTable(void) {
    Obj_35f460 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m40 = 0;
    obj.vt = &g_beGeneraterInfoRam_vtable[0];
    obj.m44 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beGeneraterInfoRam_vtable[0];
    obj.rel44();
    obj.vt = &g_beBaseInfoRam_vtable[0];
    obj.rel40();
    return r;
}

void **FUN_0035f550(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void beGeneraterInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfoRam_Register);
}

static igMetaObjectCallback g_beGeneraterInfoRam_callbackList[] = { beGeneraterInfoWork_EnsureRegistered, 0 };

void *beGeneraterInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beGeneraterInfoRam_GetMetaObjectFunction,
        "beGeneraterInfoRam",
        0x30, /* instance size */
        beGeneraterInfoRam_GetVTable,
        beGeneraterInfoRam_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfoRam_callbackList /* callback list */
    );
}

void beGeneraterInfoRam_GetMetaObjectFunction(void)
{
    beGeneraterInfoRam_GetMetaObject();
}

static FieldFactory g_beGeneraterInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beGeneraterInfoRam_fieldTable[] = {
    "_work",
};
static igMetaField **g_beGeneraterInfoRam_fieldHandles[] = {
    &g_beGeneraterInfoRam_workMetaField,
};
static int g_beGeneraterInfoRam_fieldOffsets[] = {
    44,
};

void beGeneraterInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beGeneraterInfoRam_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beGeneraterInfoRam_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beGeneraterInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beGeneraterInfoRam_fieldTable, g_beGeneraterInfoRam_fieldHandles, g_beGeneraterInfoRam_fieldOffsets, temp_s2);
}

