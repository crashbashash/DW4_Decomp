igMetaObject *g_beNDMWStageCtl_metaObject;
igMetaField *g_beNDMWStageCtl_resetTrgTimeMetaField;

void beNDMWStageCtl_CreateInstance(int arg0) {
    beNDMWStageCtl_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStageCtl_metaObject, arg0);
}

igMetaObject *beNDMWStageCtl_GetOrCreateMetaObject(void) {
    if (g_beNDMWStageCtl_metaObject == 0) {
        g_beNDMWStageCtl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWStageCtl_metaObject;
}

igMetaObject *beNDMWStageCtl_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStageCtl_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWStageCtl_EnsureRegistered();
    return g_beNDMWStageCtl_metaObject;
}

int beNDMWStageCtl_GetVTable(void) {
    struct F_3bbe80 o;
    int r;
    int *s;
    int *h;
    int c;
    struct T_3bbe80 *a;

    igObject_InitHeader(&o);
    o.vt = g_beBaseInfoManager_vtable;
    o.str = 0;
    o.ref = 0;
    o.vt = g_beNDMWStageCtl_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beBaseInfoManager_vtable;
    if (&o.ref != 0) {
        a = o.ref;
        if (a != 0) {
            a->references = a->references - 1;
            if ((((unsigned long long)((long long)a->references << 0x29)) >> 0x29) == 0) igObject_Destroy(a);
        }
    }
    o.vt = g_igNamedObject_vtable;
    if (&o.str != 0) {
        s = o.str;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
    }
    return r;
}

void beNDMWStageCtl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtl_Register);
}

void *beNDMWStageCtl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStageCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWStageCtl_GetMetaObjectFunction,
        "beNDMWStageCtl",
        0x28, /* instance size */
        beNDMWStageCtl_GetVTable,
        beNDMWStageCtl_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStageCtl_GetMetaObjectFunction(void)
{
    beNDMWStageCtl_GetMetaObject();
}

static FieldFactory g_beNDMWStageCtl_ctorTable[] = {
    igLongMetaField_Create,
};
static const char *g_beNDMWStageCtl_fieldTable[] = {
    "_resetTrgTime",
};
static igMetaField **g_beNDMWStageCtl_fieldHandles[] = {
    &g_beNDMWStageCtl_resetTrgTimeMetaField,
};
static int g_beNDMWStageCtl_fieldOffsets[] = {
    32,
};

void beNDMWStageCtl_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWStageCtl_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWStageCtl_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beNDMWStageCtl_fieldTable, g_beNDMWStageCtl_fieldHandles, g_beNDMWStageCtl_fieldOffsets, temp_s1);
}

