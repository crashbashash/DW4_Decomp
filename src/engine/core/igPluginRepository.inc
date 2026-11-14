int igPluginRepository_GetLocationTypeMetaEnum(void) {
    if (DAT_00585ae8[0] == 0) {
        DAT_00585ae8[0] = ((int)igMetaEnum_Create((char *)&LOCATION_TYPE[0], (char **)&DAT_004bfa38[0], &DAT_004bfa48[0], 3));
    }
    return DAT_00585ae8[0];
}

int igPluginRepository_Create(int arg0) {
    igPluginRepository_EnsureRegistered();
    return igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585AF0), (igMemoryPoolView *)arg0);
}

igMetaObject *igPluginRepository_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginRepository_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPluginRepository_EnsureRegistered();
    return g_igPluginRepository_metaObject[0];
}

int igPluginRepository_GetVTable(void) {
    igPluginRepository repository;
    int temp_s0;
    int *q0;
    int *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((igObject *)&repository);
    q1 = &repository._name;
    *(int *)q1 = 0;
    repository._vtable = (int)&DAT_00532de0[0];
    q0 = &repository._location;
    *(int *)q0 = 0;
    temp_s0 = *(int *)((char *)&repository + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    repository._vtable = (int)&DAT_00532de0[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    repository._vtable = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igPluginRepository_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPluginRepository_Register);
}

void igPluginRepository_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPluginRepository_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igPluginRepository_GetMetaObjectFunction,
        igPluginRepository_className,
        0x14, /* instance size */
        igPluginRepository_GetVTable,
        &igPluginRepository_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igPluginRepository_GetMetaObjectFunction(void) {
    igPluginRepository_GetMetaObject();
}

void igPluginRepository_InitFields(void) {
    igMetaObject *meta = g_igPluginRepository_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igPluginRepository_ctorTable, 2);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 1));
    *(int *)((char *)field + 52) = (int)igPluginRepository_GetLocationTypeMetaEnum;
    igMetaObject_NameFields(meta, (const char **)g_igPluginRepository_fieldTable, (igMetaField ***)DAT_004bfa68, (int *)DAT_004bfa70, base);
}

