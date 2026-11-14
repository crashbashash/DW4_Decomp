igMetaObject *FUN_0019ea00(void) {
    if (g_igInterpretedShaderData_metaObject[0] == 0) {
        g_igInterpretedShaderData_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igInterpretedShaderData_metaObject[0];
}

igMetaObject *igInterpretedShaderData_GetMetaObject(void)
{
    igMetaObject *g = g_igInterpretedShaderData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019ebc0();
    return g_igInterpretedShaderData_metaObject[0];
}

int igInterpretedShaderData_GetVTable(void) {
    struct Obj_19eaa0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.vt = &DAT_0052a8e0[0];
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052a8e0[0];
    FUN_0014dd40(&obj.w7, -1);
    FUN_0019eb40((ObjectRefWord *)&obj.w6, -1);
    FUN_00194790((int * *)&obj, 0);
    return t;
}

ObjectRefWord *FUN_0019eb40(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_0019ebc0(void)
{
    igMetaObject_RunStaticInit(igInterpretedShaderData_Register);
}

void igInterpretedShaderData_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igInterpretedShaderData_metaObject),
        igTransientShaderData_Register,
        igTransientShaderData_GetPublishedMetaObject,
        thunk_igInterpretedShaderData_GetMetaObject,
        igInterpretedShaderData_className,
        0x20, /* instance size */
        igInterpretedShaderData_GetVTable,
        &igInterpretedShaderData_InitFields,
        0, /* extra callback item */
        g_igInterpretedShaderData_callbackList /* callback list */
    );
}

void thunk_igInterpretedShaderData_GetMetaObject(void) {
    igInterpretedShaderData_GetMetaObject();
}

int FUN_0019ec60(void) {
    return ((int *)g_igTransientShaderData_metaObject)[0];
}

void igInterpretedShaderData_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igInterpretedShaderData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igInterpretedShaderData_ctorTable[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00199170();
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igObjectStringMap_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igInterpretedShaderData_fieldTable[0], &DAT_0048bef0[0], &DAT_0048bef8[0], temp_s2);
}

