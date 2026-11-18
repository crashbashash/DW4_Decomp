igMetaObject *igShaderData_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igShaderData_EnsureRegistered();
    return g_igShaderData_metaObject;
}

int igShaderData_GetVTable(void) {
    struct Obj_1996b0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igShaderData_vtable[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igShaderData_vtable[0];
    igSmartPointer_igNodeListList_Destruct((struct Ref * *)&obj.w5, -1);
    igSmartPointer_igDataPumpInfo_Destruct((void * *)&obj.w4, -1);
    FUN_0013a800(&obj.w3, -1);
    FUN_0013a800(&obj.w2, -1);
    return t;
}

void igShaderData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igShaderData_Register);
}

static igMetaObjectCallback g_igShaderData_callbackList[] = { igAttrListList_EnsureRegistered, igDataPumpInfo_EnsureRegistered, igNodeListList_EnsureRegistered, 0 };

CallbackArray *igShaderData_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igShaderData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igShaderData_GetMetaObjectFunction,
        "igShaderData",
        0x18, /* instance size */
        igShaderData_GetVTable,
        &igShaderData_InitFields,
        0, /* extra callback item */
        g_igShaderData_callbackList /* callback list */
    );
}

void igShaderData_GetMetaObjectFunction(void) {
    igShaderData_GetMetaObject();
}

static FieldFactory g_igShaderData_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igShaderData_fieldTable[] = {
    "_attrPushLists",
    "_attrPopLists",
    "_dataPumps",
    "_childLists",
};
static igMetaField **g_igShaderData_fieldHandles[] = {
    &g_igShaderData_attrPushListsMetaField,
    &g_igShaderData_attrPopListsMetaField,
    &g_igShaderData_dataPumpsMetaField,
    &g_igShaderData_childListsMetaField,
};
static int g_igShaderData_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void igShaderData_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igShaderData_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igShaderData_ctorTable, 4);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igAttrListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igAttrListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igDataPumpInfo_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igNodeListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igShaderData_fieldTable, g_igShaderData_fieldHandles, g_igShaderData_fieldOffsets, temp_s0);
}

igSmartPointer<igObject> *igSmartPointer_igMatrix44fList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

struct R **igSmartPointer_igModelViewMatrixAttrList_Destruct(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

