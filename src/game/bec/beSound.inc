igMetaObject *g_beSound_metaObject;
igMetaField *g_beSound_criMetaField;
igMetaField *g_beSound_currentBGMMetaField;
igMetaField *g_beSound_playSEsMetaField;

void beSound_CreateInstance(int arg0) {
    beSound_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587EA8, arg0);
}

igMetaObject *beSound_GetOrCreateMetaObject(void) {
    if (g_beSound_metaObject == 0) {
        g_beSound_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSound_metaObject;
}

igMetaObject *beSound_GetMetaObject(void) {
    igMetaObject *g = g_beSound_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beSound_EnsureRegistered();
done:
    return g_beSound_metaObject;
}

int beSound_GetVTable(void) {
    struct W o;
    int *p16;
    int r;
    int *p17;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[5] = 0;
    o.vt = &g_beSound_vtable[0];
    p16 = &o.f[7];
    *p16 = 0;
    p17 = &o.f[8];
    *p17 = 0;
    o.f[9] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beSound_vtable[0];
    FUN_00344440((void **)(&o.f[9]), (short)(-1));
    igStringRef_Destruct(p17, -1);
    FUN_0033de20((void **)p16, (short)(-1));
    FUN_0033f5e0((O_33f5e0 *)&o, (short)0);
    return r;
}

void **FUN_00344440(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void beSound_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSound_Register);
}

static igMetaObjectCallback g_beSound_callbackList[] = { beCri_EnsureRegistered, bePlaySEList_EnsureRegistered, 0 };

void *beSound_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSound_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSound_GetMetaObjectFunction,
        "beSound",
        0x2c, /* instance size */
        beSound_GetVTable,
        beSound_InitFields,
        0, /* extra callback item */
        g_beSound_callbackList /* callback list */
    );
}

void beSound_GetMetaObjectFunction(void)
{
    beSound_GetMetaObject();
}

static FieldFactory g_beSound_ctorTable[] = {
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSound_fieldTable[] = {
    "_cri",
    "_currentBGM",
    "_playSEs",
};
static igMetaField **g_beSound_fieldHandles[] = {
    &g_beSound_criMetaField,
    &g_beSound_currentBGMMetaField,
    &g_beSound_playSEsMetaField,
};
static int g_beSound_fieldOffsets[] = {
    32,
    36,
    40,
};

void beSound_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)g_beSound_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSound_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beCri_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)bePlaySEList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beSound_fieldTable, g_beSound_fieldHandles, g_beSound_fieldOffsets, temp_s2);
}

