igMetaObject *g_igFileInfo_metaObject;
igMetaField *g_igFileInfo_externalEntryListMetaField;
igMetaField *g_igFileInfo_infoListMetaField;
igMetaField *g_igFileInfo_fileInfoListMetaField;
igMetaField *g_igFileInfo_cachedFileMetaField;

igMetaObject *FUN_00228e60(void) {
    if (g_igFileInfo_metaObject == 0) {
        g_igFileInfo_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igFileInfo_metaObject;
}

igMetaObject *igFileInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igFileInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002290c0();
    return g_igFileInfo_metaObject;
}

int igFileInfo_GetVTable(void) {
    struct Obj_8 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.w[1] = 0;
    obj.vt = &g_igFileInfo_vtable[0];
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igFileInfo_vtable[0];
    FUN_00229040((R **)&obj.w[5], -1);
    FUN_00228fc0((ObjectRefWord *)&obj.w[4], -1);
    igSmartPointer_igInfoList_Destruct(&obj.w[3], -1);
    igSmartPointer_igDirectory_Destruct(&obj.w[2], -1);
    igNamedObject_Destroy(&obj, 0);
    return r;
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_00228fc0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

struct R **FUN_00229040(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_002290c0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igFileInfo_Register);
}

static igMetaObjectCallback g_igFileInfo_callbackList[] = { igDirectory_EnsureRegistered, igInfoList_EnsureRegistered, FUN_00228dd0, igIGBFile_EnsureRegistered, 0 };

CallbackArray *igFileInfo_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFileInfo_metaObject,
        igNamedObject_Register,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        thunk_igFileInfo_GetMetaObject,
        "igFileInfo",
        0x1C, /* instance size */
        igFileInfo_GetVTable,
        &igFileInfo_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igFileInfo_callbackList /* callback list */
    );
}

void thunk_igFileInfo_GetMetaObject(void) {
    igFileInfo_GetMetaObject();
}

static FieldFactory g_igFileInfo_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igFileInfo_fieldTable[] = {
    "_externalEntryList",
    "_infoList",
    "_fileInfoList",
    "_cachedFile",
};
static igMetaField **g_igFileInfo_fieldHandles[] = {
    &g_igFileInfo_externalEntryListMetaField,
    &g_igFileInfo_infoListMetaField,
    &g_igFileInfo_fileInfoListMetaField,
    &g_igFileInfo_cachedFileMetaField,
};
static int g_igFileInfo_fieldOffsets[] = {
    12,
    16,
    20,
    24,
};

void igFileInfo_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    igMetaObject *temp_s1;

    temp_s1 = g_igFileInfo_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igFileInfo_ctorTable, 4);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igDirectory_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_00228cf0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igIGBFile_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_igFileInfo_fieldTable, g_igFileInfo_fieldHandles, g_igFileInfo_fieldOffsets, temp_s0);
}

int *FUN_00229260(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igStringRef_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

