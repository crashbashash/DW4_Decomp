igMetaObject *igMetaFieldInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaFieldInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaFieldInfo_EnsureRegistered();
    return g_igMetaFieldInfo_metaObject;
}

int igMetaFieldInfo_GetVTable(void) {
    igMetaFieldInfo info;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader((igObject *)&info);
    ps = (char *)&info._name;
    *(int *)ps = 0;
    info._vtable = (int)&g_igNamedObject_vtable[0];
    info._vtable = (int)&g_igMetaFieldInfo_vtable[0];
    s0 = *(int *)((char *)&info + g_objectSystem->vtableProbeOffset);
    info._vtable = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
            }
        }
    }
    return s0;
}

void igMetaFieldInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMetaFieldInfo_Register);
}

CallbackArray *igMetaFieldInfo_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMetaFieldInfo_metaObject,
        Gap::Core::igInfo::arkRegisterInternal,
        (igMetaObjectGetFunction)igInfo_GetPublishedMetaObject,
        igMetaFieldInfo_GetMetaObjectFunction,
        "igMetaFieldInfo",
        0x14,
        igMetaFieldInfo_GetVTable,
        0,
        0,
        0
    );
}

void igMetaFieldInfo_GetMetaObjectFunction(void) {
    igMetaFieldInfo_GetMetaObject();
}

static const char *g_igMetaField_resetTypeNames[] = {
    "kResetByValue", "kResetByValueShallow", "kResetByReference", "kResetByNoReset",
};
static int g_igMetaField_resetTypeValues[] = {
    0, 1, 2, 3,
};

int igMetaField_GetResetTypeMetaEnum(void) {
    if (g_igMetaField_resetTypeMetaEnum == 0) {
        g_igMetaField_resetTypeMetaEnum = ((int)Gap::Core::igMetaEnum::createMetaEnum((char *)"ResetType", g_igMetaField_resetTypeNames, g_igMetaField_resetTypeValues, 4));
    }
    return g_igMetaField_resetTypeMetaEnum;
}

