igMetaObject *g_beNDMWLoadIntf2ComMdlCtrl_metaObject;
int g_beNDMWLoadIntf2ComMdlCtrl_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2ComMdlCtrl_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2ComMdlCtrl_openDataListMetaField;
igMetaField *g_beNDMWLoadIntf2ComMdlCtrl_closeDataListMetaField;
igMetaField *g_beNDMWLoadIntf2ComMdlCtrl_posMetaField;

void beNDMWLoadIntf2ComMdlCtrl_Create(int arg0) {
    beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2ComMdlCtrl_metaObject, arg0);
}

igMetaObject *beNDMWLoadIntf2ComMdlCtrl_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadIntf2ComMdlCtrl_metaObject == 0) {
        g_beNDMWLoadIntf2ComMdlCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadIntf2ComMdlCtrl_metaObject;
}

void *beNDMWLoadIntf2ComMdlCtrl_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2ComMdlCtrl_metaObject;
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (exceptions on); `if (ready = ...)` folds it away */
        ready = g->_validity & 4;
        if (ready != false) goto end;
    }
    beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered();
end:
    return g_beNDMWLoadIntf2ComMdlCtrl_metaObject;
}

int beNDMWLoadIntf2ComMdlCtrl_GetVTable(void) {
    struct W_3c6f80 o;
    int r;

    igObject_InitHeader(&o);
    o.vt = g_beNDMWLoadIntf2ComMdlCtrl_vtable;
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beNDMWLoadIntf2ComMdlCtrl_vtable;
    FUN_003c7010((ObjectRefWord *)(&o.f[5]), -1);
    FUN_003c7010((ObjectRefWord *)(&o.f[4]), -1);
    FUN_00344030(&o, 0);
    return r;
}

ObjectRefWord *FUN_003c7010(ObjectRefWord *self,int delete_storage) {
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

void beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2ComMdlCtrl_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2ComMdlCtrl_callbackList[] = { beMessenger_EnsureRegistered, beLoadIntf2ComMdlDataList_EnsureRegistered, 0 };

void *beNDMWLoadIntf2ComMdlCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2ComMdlCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2ComMdlCtrl_GetMetaObject,
        "beNDMWLoadIntf2ComMdlCtrl",
        0x28, /* instance size */
        beNDMWLoadIntf2ComMdlCtrl_GetVTable,
        beNDMWLoadIntf2ComMdlCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2ComMdlCtrl_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2ComMdlCtrl_GetMetaObject(void)
{
    beNDMWLoadIntf2ComMdlCtrl_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2ComMdlCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    FUN_00187890,
};
static const char *g_beNDMWLoadIntf2ComMdlCtrl_fieldTable[] = {
    "_messenger",
    "_openDataList",
    "_closeDataList",
    "_pos",
};
static igMetaField **g_beNDMWLoadIntf2ComMdlCtrl_fieldHandles[] = {
    &g_beNDMWLoadIntf2ComMdlCtrl_messengerMetaField,
    &g_beNDMWLoadIntf2ComMdlCtrl_openDataListMetaField,
    &g_beNDMWLoadIntf2ComMdlCtrl_closeDataListMetaField,
    &g_beNDMWLoadIntf2ComMdlCtrl_posMetaField,
};
static int g_beNDMWLoadIntf2ComMdlCtrl_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beNDMWLoadIntf2ComMdlCtrl_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s1;
    void *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWLoadIntf2ComMdlCtrl_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2ComMdlCtrl_ctorTable, 4);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "COMMDLCTRL");
    ((igStringMetaField *)temp_v0_2)->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2ComMdlCtrl_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    ((igStringMetaField *)temp_v0_2)->_refCount = (int)((int) (((igStringMetaField *)temp_v0_2)->_refCount - 1));
    if ((((igStringMetaField *)temp_v0_2)->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = (int)beLoadIntf2ComMdlDataList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0_2)->_construct = 1;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = (int)beLoadIntf2ComMdlDataList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0_3)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2ComMdlCtrl_fieldTable, g_beNDMWLoadIntf2ComMdlCtrl_fieldHandles, g_beNDMWLoadIntf2ComMdlCtrl_fieldOffsets, temp_s2);
}

