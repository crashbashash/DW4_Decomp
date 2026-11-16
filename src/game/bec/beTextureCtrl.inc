igMetaObject *g_beTextureCtrl_metaObject;
igMetaField *g_beTextureCtrl_isFirstTimeMetaField;
igMetaField *g_beTextureCtrl_workMetaField;

void beTextureCtrl_CreateInstance(int arg0) {
    beTextureCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587CB8, arg0);
}

igMetaObject *beTextureCtrl_GetOrCreateMetaObject(void) {
    if (g_beTextureCtrl_metaObject == 0) {
        g_beTextureCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beTextureCtrl_metaObject;
}

void *beTextureCtrl_GetMetaObject(void) {
    igMetaObject *g = g_beTextureCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beTextureCtrl_EnsureRegistered();
    }
    return g_beTextureCtrl_metaObject;
}

int beTextureCtrl_GetVTable(void) {
    Obj_3423f0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[5] = 0;
    o.vt = &g_beTextureCtrl_vtable[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beTextureCtrl_vtable[0];
    FUN_00342460((void **)&o.s, (short)(-1));
    FUN_0033f5e0((O_33f5e0 *)&o, (short)0);
    return r;
}

void **FUN_00342460(void **arg0, short arg1) {
    S_temp_a0_342460 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_342460 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void beTextureCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTextureCtrl_Register);
}

static igMetaObjectCallback g_beTextureCtrl_callbackList[] = { beTextureCtrlWork_EnsureRegistered, 0 };

void *beTextureCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTextureCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beTextureCtrl_GetMetaObjectFunction,
        "beTextureCtrl",
        0x28, /* instance size */
        beTextureCtrl_GetVTable,
        beTextureCtrl_InitFields,
        0, /* extra callback item */
        g_beTextureCtrl_callbackList /* callback list */
    );
}

void beTextureCtrl_GetMetaObjectFunction(void)
{
    beTextureCtrl_GetMetaObject();
}

static FieldFactory g_beTextureCtrl_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beTextureCtrl_fieldTable[] = {
    "_isFirstTime",
    "_work",
};
static igMetaField **g_beTextureCtrl_fieldHandles[] = {
    &g_beTextureCtrl_isFirstTimeMetaField,
    &g_beTextureCtrl_workMetaField,
};
static int g_beTextureCtrl_fieldOffsets[] = {
    32,
    36,
};

void beTextureCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beTextureCtrl_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beTextureCtrl_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beTextureCtrlWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beTextureCtrl_fieldTable, g_beTextureCtrl_fieldHandles, g_beTextureCtrl_fieldOffsets, temp_s2);
}

