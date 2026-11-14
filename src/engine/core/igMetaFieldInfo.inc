igMetaObject *igMetaFieldInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaFieldInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaFieldInfo_EnsureRegistered();
    return g_igMetaFieldInfo_metaObject[0];
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
    s0 = *(int *)((char *)&info + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    info._vtable = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (int)a1);
            }
        }
    }
    return s0;
}

void igMetaFieldInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaFieldInfo_Register);
}

void igMetaFieldInfo_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igMetaFieldInfo_metaObject,
        (igMetaObjectRegisterFunction)igInfo_Register,
        (igMetaObjectGetFunction)igInfo_GetPublishedMetaObject,
        igMetaFieldInfo_GetMetaObjectFunction,
        igMetaFieldInfo_className,
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

int igMetaField_GetResetTypeMetaEnum(void) {
    if (g_igMetaField_resetTypeMetaEnum[0] == 0) {
        g_igMetaField_resetTypeMetaEnum[0] = ((int)igMetaEnum_Create((char *)&text_ResetType[0], (char **)&g_igMetaField_resetTypeNames[0], &g_igMetaField_resetTypeValues[0], 4));
    }
    return g_igMetaField_resetTypeMetaEnum[0];
}

