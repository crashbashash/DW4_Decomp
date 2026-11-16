igMetaObject *g_beFont_metaObject;
igMetaField *g_beFont_rootMetaField;
igMetaField *g_beFont_fontsMetaField;
igMetaField *g_beFont_fontIdxMetaField;
igMetaField *g_beFont_gaPairListMetaField;
igMetaField *g_beFont_lineFeedListMetaField;
igMetaField *g_beFont_alignListMetaField;
igMetaField *g_beFont_convertDataMetaField;
igMetaField *g_beFont_condition00MetaField;
igMetaField *g_beFont_condition01MetaField;
igMetaField *g_beFont_historyMetaField;

void beFont_CreateInstance(int arg0) {
    beFont_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589678, arg0);
}

igMetaObject *beFont_GetOrCreateMetaObject(void) {
    if (g_beFont_metaObject == 0) {
        g_beFont_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beFont_metaObject;
}

void *beFont_GetMetaObject(void) {
    igMetaObject *g = g_beFont_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beFont_EnsureRegistered();
    }
    return g_beFont_metaObject;
}

int beFont_GetVTable(void) {
    struct Obj_361f30 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &g_beFont_vtable[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beFont_vtable[0];
    igStringRef_Destruct(&obj.w16, -1);
    igStringRef_Destruct(&obj.w15, -1);
    igSmartPointer_igStringObj_Destruct(&obj.w14, -1);
    FUN_001354b0(&obj.w13, -1);
    igSmartPointer_igIntList_Destruct(&obj.w12, -1);
    FUN_003620f0((void **)&obj.w11, (short)(-1));
    FUN_00362070((ObjectRefWord *)&obj.w9, -1);
    FUN_001d97f0(&obj.w8, -1);
    FUN_0033f5e0((O_33f5e0 *)&obj, (short)0);
    return t;
}

ObjectRefWord *FUN_00362070(ObjectRefWord *self,int delete_storage) {
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

void **FUN_003620f0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void beFont_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFont_Register);
}

static igMetaObjectCallback g_beFont_callbackList[] = { igAttrSet_EnsureRegistered, beFontImageList_EnsureRegistered, beFontGeomAttrPairList_EnsureRegistered, igIntList_EnsureRegistered, igFloatList_EnsureRegistered, igStringObj_EnsureRegistered, 0 };

void *beFont_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFont_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beFont_GetMetaObjectFunction,
        "beFont",
        0x48, /* instance size */
        beFont_GetVTable,
        beFont_InitFields,
        0, /* extra callback item */
        g_beFont_callbackList /* callback list */
    );
}

void beFont_GetMetaObjectFunction(void)
{
    beFont_GetMetaObject();
}

static FieldFactory g_beFont_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beFont_fieldTable[] = {
    "_root",
    "_fonts",
    "_fontIdx",
    "_gaPairList",
    "_lineFeedList",
    "_alignList",
    "_convertData",
    "_condition00",
    "_condition01",
    "_history",
};
static igMetaField **g_beFont_fieldHandles[] = {
    &g_beFont_rootMetaField,
    &g_beFont_fontsMetaField,
    &g_beFont_fontIdxMetaField,
    &g_beFont_gaPairListMetaField,
    &g_beFont_lineFeedListMetaField,
    &g_beFont_alignListMetaField,
    &g_beFont_convertDataMetaField,
    &g_beFont_condition00MetaField,
    &g_beFont_condition01MetaField,
    &g_beFont_historyMetaField,
};
static int g_beFont_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
};

void beFont_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beFont_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beFont_ctorTable, 0xA);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igAttrSet_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)beFontImageList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)beFontGeomAttrPairList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_beFont_fieldTable, g_beFont_fieldHandles, g_beFont_fieldOffsets, temp_s0);
}

