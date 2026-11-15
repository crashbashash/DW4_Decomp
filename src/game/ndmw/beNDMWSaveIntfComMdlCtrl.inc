igMetaObject *g_beNDMWSaveIntfComMdlCtrl_metaObject;
int g_beNDMWSaveIntfComMdlCtrl_nameExternalEnumStorage;
igMetaField *g_beNDMWSaveIntfComMdlCtrl_messengerMetaField;
igMetaField *g_beNDMWSaveIntfComMdlCtrl_openDataListMetaField;
igMetaField *g_beNDMWSaveIntfComMdlCtrl_closeDataListMetaField;
igMetaField *g_beNDMWSaveIntfComMdlCtrl_posMetaField;

igMetaObject *FUN_003bc1f0(void) {
    if (g_beNDMWSaveIntfComMdlCtrl_metaObject == 0 || !isValid(g_beNDMWSaveIntfComMdlCtrl_metaObject)) FUN_003bc350();
    return g_beNDMWSaveIntfComMdlCtrl_metaObject;
}

int beNDMWSaveIntfComMdlCtrl_GetVTable(void) {
    struct Obj_3bc240 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0053d900[0];
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053d900[0];
    FUN_003bc2d0((ObjectRefWord *)&obj.w6, -1);
    FUN_003bc2d0((ObjectRefWord *)&obj.w5, -1);
    FUN_00344030(&obj, 0);
    return t;
}

ObjectRefWord *FUN_003bc2d0(ObjectRefWord *self,int delete_storage) {
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

void FUN_003bc350(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfComMdlCtrl_Register);
}

static igMetaObjectCallback g_beNDMWSaveIntfComMdlCtrl_callbackList[] = { FUN_00357d10, FUN_003bc660, 0 };

void *beNDMWSaveIntfComMdlCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveIntfComMdlCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWSaveIntfComMdlCtrl_GetMetaObject,
        "beNDMWSaveIntfComMdlCtrl",
        0x28, /* instance size */
        beNDMWSaveIntfComMdlCtrl_GetVTable,
        beNDMWSaveIntfComMdlCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWSaveIntfComMdlCtrl_callbackList /* callback list */
    );
}

void beNDMWSaveIntfComMdlCtrl_GetMetaObject(void)
{
    FUN_003bc1f0();
}

static FieldFactory g_beNDMWSaveIntfComMdlCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    FUN_00187890,
};
static const char *g_beNDMWSaveIntfComMdlCtrl_fieldTable[] = {
    "_messenger",
    "_openDataList",
    "_closeDataList",
    "_pos",
};
static igMetaField **g_beNDMWSaveIntfComMdlCtrl_fieldHandles[] = {
    &g_beNDMWSaveIntfComMdlCtrl_messengerMetaField,
    &g_beNDMWSaveIntfComMdlCtrl_openDataListMetaField,
    &g_beNDMWSaveIntfComMdlCtrl_closeDataListMetaField,
    &g_beNDMWSaveIntfComMdlCtrl_posMetaField,
};
static int g_beNDMWSaveIntfComMdlCtrl_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beNDMWSaveIntfComMdlCtrl_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    igMetaObject *temp_s1;
    igStringMetaField *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (igMetaObject *)(g_beNDMWSaveIntfComMdlCtrl_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWSaveIntfComMdlCtrl_ctorTable, 4);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "COMMDLCTRL");
    temp_v0_2->_externalEnumStorage = (int)(&g_beNDMWSaveIntfComMdlCtrl_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = (int)FUN_003bc580();
    ((igObjectRefMetaField *)temp_s0_2)->_construct = 1;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = (int)FUN_003bc580();
    ((igObjectRefMetaField *)temp_s0_3)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWSaveIntfComMdlCtrl_fieldTable, g_beNDMWSaveIntfComMdlCtrl_fieldHandles, g_beNDMWSaveIntfComMdlCtrl_fieldOffsets, temp_s2);
}

