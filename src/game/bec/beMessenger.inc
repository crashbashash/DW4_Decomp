igMetaObject *g_beMessenger_metaObject;
igMetaField *g_beMessenger_argDataMetaField;
igMetaField *g_beMessenger_groupListMetaField;
igMetaField *g_beMessenger_workStackMetaField;
igMetaField *g_beMessenger_delayStackMetaField;
igMetaField *g_beMessenger_pushPopStackMetaField;
igMetaField *g_beMessenger_pushPopCountMetaField;
igMetaField *g_beMessenger_freezeTimeMetaField;
igMetaField *g_beMessenger_isMemoryAssignMetaField;

void beMessenger_CreateInstance(int arg0) {
    FUN_00357d10();
    igMetaObject_CreateInstance(*(int *)0x588F38, arg0);
}

igMetaObject *FUN_00357910(void) {
    if (g_beMessenger_metaObject == 0) {
        g_beMessenger_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMessenger_metaObject;
}

void *FUN_00357960(void) {
    igMetaObject *g = g_beMessenger_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00357d10();
    }
    return g_beMessenger_metaObject;
}

int beMessenger_GetVTable(void) {
    union U_3579b0 u;
    int r;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_0053ab70[0];
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053ab70[0];
    FUN_00357c90((void **)(&u.b[32]), (long long)(-1));
    FUN_00357c10((struct Ref **)(&u.b[28]), (short)(-1));
    FUN_00357b90((void **)(&u.b[24]), (short)(-1));
    FUN_00357b10((void **)(&u.b[20]), -1);
    FUN_00357a90((void **)&u.b[16], -1);
    FUN_00231030(u.b, 0);
    return r;
}

void **FUN_00357a90(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_00357b10(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_00357b90(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_00357c10(struct Ref **self, short flag) {
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

void **FUN_00357c90(void **arg0, long long arg1) {
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

void FUN_00357d10(void)
{
    igMetaObject_RunStaticInit(beMessenger_Register);
}

static igMetaObjectCallback g_beMessenger_callbackList[] = { beMessengerArgData_EnsureRegistered, FUN_00358430, FUN_00357fc0, FUN_003588a0, FUN_00358cd0, 0 };

void *beMessenger_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessenger_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beMessenger_GetMetaObject,
        "beMessenger",
        0x38, /* instance size */
        beMessenger_GetVTable,
        beMessenger_InitFields,
        0, /* extra callback item */
        g_beMessenger_callbackList /* callback list */
    );
}

void beMessenger_GetMetaObject(void)
{
    FUN_00357960();
}

static FieldFactory g_beMessenger_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igLongMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beMessenger_fieldTable[] = {
    "_argData",
    "_groupList",
    "_workStack",
    "_delayStack",
    "_pushPopStack",
    "_pushPopCount",
    "_freezeTime",
    "_isMemoryAssign",
};
static igMetaField **g_beMessenger_fieldHandles[] = {
    &g_beMessenger_argDataMetaField,
    &g_beMessenger_groupListMetaField,
    &g_beMessenger_workStackMetaField,
    &g_beMessenger_delayStackMetaField,
    &g_beMessenger_pushPopStackMetaField,
    &g_beMessenger_pushPopCountMetaField,
    &g_beMessenger_freezeTimeMetaField,
    &g_beMessenger_isMemoryAssignMetaField,
};
static int g_beMessenger_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    48,
};

void beMessenger_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beMessenger_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beMessenger_ctorTable, 8);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_00358dc0();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00358350();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_00357ee0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_003587c0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_00358bf0();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_beMessenger_fieldTable, g_beMessenger_fieldHandles, g_beMessenger_fieldOffsets, temp_s0);
}

