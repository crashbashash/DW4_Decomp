void * igNamedObject_Create(int arg0) {
    igNamedObject_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585BD8), (igMemoryPoolView *)arg0));
}

igMetaObject *igNamedObject_GetOrCreateMetaObject(void) {
    if (g_igNamedObject_metaObject[0] == 0) {
        g_igNamedObject_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igNamedObject_metaObject[0];
}

igMetaObject *igNamedObject_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igNamedObject_EnsureRegistered();
    return g_igNamedObject_metaObject[0];
}

int igNamedObject_GetVTable(void) {
    igNamedObject object;
    int temp_s0;
    int *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((igObject *)&object);
    ps = &object._name;
    object._vtable = (int)&g_igNamedObject_vtable[0];
    *ps = 0;
    temp_s0 = *(int *)((char *)&object + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    object._vtable = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = (int *)*ps;
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

void igNamedObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNamedObject_Register);
}

void igNamedObject_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNamedObject_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igNamedObject_GetMetaObjectFunction,
        igNamedObject_className,
        0xC, /* instance size */
        igNamedObject_GetVTable,
        &igNamedObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igNamedObject_GetMetaObjectFunction(void) {
    igNamedObject_GetMetaObject();
}

void igNamedObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igNamedObject_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igNamedObject_ctorTable[0], 1);
    igStringMetaField_SetDefaultText((int *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 0);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igNamedObject_fieldTable[0], (igMetaField ***)&DAT_004bfbe8[0], &DAT_004bfbf0[0], temp_s1);
}

