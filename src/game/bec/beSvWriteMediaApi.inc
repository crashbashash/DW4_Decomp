igMetaObject *g_beSvWriteMediaApi_metaObject;
igMetaField *g_beSvWriteMediaApi_nowGamedataMetaField;
igMetaField *g_beSvWriteMediaApi_saveWorkMetaField;

void beSvWriteMediaApi_Create(int arg0) {
    beSvWriteMediaApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588220, arg0);
}

igMetaObject *beSvWriteMediaApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvWriteMediaApi_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beSvWriteMediaApi_EnsureRegistered();
done:
    return g_beSvWriteMediaApi_metaObject;
}

int beSvWriteMediaApi_GetVTable(void) {
    struct Obj_348ff0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.vt = &g_beSvWriteMediaApi_vtable[0];
    obj.w16 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beSvWriteMediaApi_vtable[0];
    igSmartPointer_beSaveMemoryObj_Destruct((struct Ref **)&obj.w17, (short)(-1));
    FUN_00349080((void **)&obj.w16, (long long)(-1));
    FUN_00348390((struct S_348390 *)&obj, (short)0);
    return t;
}

void **FUN_00349080(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void beSvWriteMediaApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvWriteMediaApi_Register);
}

static igMetaObjectCallback g_beSvWriteMediaApi_callbackList[] = { beSvPlatBaseData_EnsureRegistered, beSaveMemoryObj_EnsureRegistered, 0 };

void *beSvWriteMediaApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvWriteMediaApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvWriteMediaApi_GetMetaObjectFunction,
        "beSvWriteMediaApi",
        0x4c, /* instance size */
        beSvWriteMediaApi_GetVTable,
        beSvWriteMediaApi_InitFields,
        0, /* extra callback item */
        g_beSvWriteMediaApi_callbackList /* callback list */
    );
}

void beSvWriteMediaApi_GetMetaObjectFunction(void)
{
    beSvWriteMediaApi_GetMetaObject();
}

static FieldFactory g_beSvWriteMediaApi_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSvWriteMediaApi_fieldTable[] = {
    "_nowGamedata",
    "_saveWork",
};
static igMetaField **g_beSvWriteMediaApi_fieldHandles[] = {
    &g_beSvWriteMediaApi_nowGamedataMetaField,
    &g_beSvWriteMediaApi_saveWorkMetaField,
};
static int g_beSvWriteMediaApi_fieldOffsets[] = {
    64,
    68,
};

void beSvWriteMediaApi_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)g_beSvWriteMediaApi_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSvWriteMediaApi_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beSvPlatBaseData_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)beSaveMemoryObj_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beSvWriteMediaApi_fieldTable, g_beSvWriteMediaApi_fieldHandles, g_beSvWriteMediaApi_fieldOffsets, temp_s2);
}

