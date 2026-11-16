igMetaObject *g_beAction2InfoRam_metaObject;
igMetaField *g_beAction2InfoRam_nodeMetaField;
igMetaField *g_beAction2InfoRam_appearanceListMetaField;
igMetaField *g_beAction2InfoRam_actorListMetaField;
igMetaField *g_beAction2InfoRam_workMetaField;

igMetaObject *beAction2InfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beAction2InfoRam_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beAction2InfoRam_EnsureRegistered();
    return g_beAction2InfoRam_metaObject;
}

int beAction2InfoRam_GetVTable(void) {
    union U_36c6d0 u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[40] = 0;
    u.vt = (int)&g_beAction2InfoRam_vtable[0];
    *(int *)&u.b[44] = 0;
    *(int *)&u.b[48] = 0;
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beAction2InfoRam_vtable[0];
    FUN_0036c790((igSmartPointer<igObject> *)(&u.b[56]), (short)(-1));
    FUN_001aa310(&u.b[52], -1);
    FUN_001a7a00(&u.b[48], -1);
    FUN_0034c1b0((void **)(&u.b[44]), (short)(-1));
    FUN_0033e920((S *)u.b, (long long)0);
    return t;
}

igSmartPointer<igObject> *FUN_0036c790(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beAction2InfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2InfoRam_Register);
}

static igMetaObjectCallback g_beAction2InfoRam_callbackList[] = { beModelCtrlNode2_EnsureRegistered, igAppearanceList_EnsureRegistered, igActorList_EnsureRegistered, beAction2InfoWork_EnsureRegistered, 0 };

void *beAction2InfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2InfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beAction2InfoRam_GetMetaObjectFunction,
        "beAction2InfoRam",
        0x3c, /* instance size */
        beAction2InfoRam_GetVTable,
        beAction2InfoRam_InitFields,
        0, /* extra callback item */
        g_beAction2InfoRam_callbackList /* callback list */
    );
}

void beAction2InfoRam_GetMetaObjectFunction(void)
{
    beAction2InfoRam_GetMetaObject();
}

static FieldFactory g_beAction2InfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beAction2InfoRam_fieldTable[] = {
    "_node",
    "_appearanceList",
    "_actorList",
    "_work",
};
static igMetaField **g_beAction2InfoRam_fieldHandles[] = {
    &g_beAction2InfoRam_nodeMetaField,
    &g_beAction2InfoRam_appearanceListMetaField,
    &g_beAction2InfoRam_actorListMetaField,
    &g_beAction2InfoRam_workMetaField,
};
static int g_beAction2InfoRam_fieldOffsets[] = {
    44,
    48,
    52,
    56,
};

void beAction2InfoRam_InitFields(void) {
    void *node;
    void *appearanceList;
    void *actorList;
    void *work;
    void *meta;
    int base;

    meta = (void *)g_beAction2InfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAction2InfoRam_ctorTable, 4);
    node = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)node)->_metaObject = (int)beModelCtrlNode2_GetOrCreateMetaObject();
    appearanceList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)appearanceList)->_metaObject = igAppearanceList_GetOrCreateMetaObject();
    ((igRefMetaField *)appearanceList)->_construct = 1;
    actorList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)actorList)->_metaObject = igActorList_GetOrCreateMetaObject();
    ((igRefMetaField *)actorList)->_construct = 1;
    work = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beAction2InfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beAction2InfoRam_fieldTable, g_beAction2InfoRam_fieldHandles, g_beAction2InfoRam_fieldOffsets, base);
}

