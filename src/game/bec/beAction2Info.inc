igMetaObject *g_beAction2Info_metaObject;
igMetaField *g_beAction2Info_switchMetaField;
igMetaField *g_beAction2Info_animationDatabaseMetaField;
igMetaField *g_beAction2Info_dataListMetaField;

igMetaObject *beAction2Info_GetMetaObject(void) {
    if (g_beAction2Info_metaObject == 0 || !isValid(g_beAction2Info_metaObject)) beAction2Info_EnsureRegistered();
    return g_beAction2Info_metaObject;
}

int beAction2Info_GetVTable(void) {
    struct W o;
    int *p16;
    int r;
    int *p17;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    o.vt = &g_beAction2Info_vtable[0];
    p16 = &o.f[6];
    *p16 = 0;
    p17 = &o.f[7];
    *p17 = 0;
    o.f[8] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beAction2Info_vtable[0];
    FUN_0036cc00((ObjectRefWord *)(&o.f[8]), -1);
    FUN_001aa390(p17, -1);
    FUN_00343260((ObjectRefWord *)p16, -1);
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

ObjectRefWord *FUN_0036cc00(ObjectRefWord *self,int delete_storage) {
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

void beAction2Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2Info_Register);
}

static igMetaObjectCallback g_beAction2Info_callbackList[] = { igSwitch_EnsureRegistered, igAnimationDatabase_EnsureRegistered, beAction2DataList_EnsureRegistered, 0 };

void *beAction2Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beAction2Info_GetMetaObjectFunction,
        "beAction2Info",
        0x28, /* instance size */
        beAction2Info_GetVTable,
        beAction2Info_InitFields,
        0, /* extra callback item */
        g_beAction2Info_callbackList /* callback list */
    );
}

void beAction2Info_GetMetaObjectFunction(void)
{
    beAction2Info_GetMetaObject();
}

static FieldFactory g_beAction2Info_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beAction2Info_fieldTable[] = {
    "_switch",
    "_animationDatabase",
    "_dataList",
};
static igMetaField **g_beAction2Info_fieldHandles[] = {
    &g_beAction2Info_switchMetaField,
    &g_beAction2Info_animationDatabaseMetaField,
    &g_beAction2Info_dataListMetaField,
};
static int g_beAction2Info_fieldOffsets[] = {
    28,
    32,
    36,
};

void beAction2Info_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beAction2Info_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beAction2Info_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igSwitch_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igAnimationDatabase_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)beAction2DataList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beAction2Info_fieldTable, g_beAction2Info_fieldHandles, g_beAction2Info_fieldOffsets, temp_s2);
}

