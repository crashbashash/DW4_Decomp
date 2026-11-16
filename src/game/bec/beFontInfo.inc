igMetaObject *g_beFontInfo_metaObject;
igMetaField *g_beFontInfo_unicodeListMetaField;

void *beFontInfo_GetMetaObject(void) {
    igMetaObject *g = g_beFontInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beFontInfo_EnsureRegistered();
    }
    return g_beFontInfo_metaObject;
}

int beFontInfo_GetVTable(void) {
    union U_360ee0 u;
    int temp_s0;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&g_beFontInfo_vtable[0];
    ps = &u.b[28];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beFontInfo_vtable[0];
    FUN_00360f60((ObjectRefWord *)ps, -1);
    FUN_0033ec80((struct S_33ec80 *)u.b, (short)0);
    return temp_s0;
}

ObjectRefWord *FUN_00360f60(ObjectRefWord *self,int delete_storage) {
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

void beFontInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFontInfo_Register);
}

static igMetaObjectCallback g_beFontInfo_callbackList[] = { beUnicodeObjList_EnsureRegistered, 0 };

void *beFontInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFontInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beFontInfo_GetMetaObjectFunction,
        "beFontInfo",
        0x20, /* instance size */
        beFontInfo_GetVTable,
        beFontInfo_InitFields,
        0, /* extra callback item */
        g_beFontInfo_callbackList /* callback list */
    );
}

void beFontInfo_GetMetaObjectFunction(void)
{
    beFontInfo_GetMetaObject();
}

static FieldFactory g_beFontInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beFontInfo_fieldTable[] = {
    "_unicodeList",
};
static igMetaField **g_beFontInfo_fieldHandles[] = {
    &g_beFontInfo_unicodeListMetaField,
};
static int g_beFontInfo_fieldOffsets[] = {
    28,
};

void beFontInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beFontInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beFontInfo_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beUnicodeObjList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beFontInfo_fieldTable, g_beFontInfo_fieldHandles, g_beFontInfo_fieldOffsets, temp_s2);
}

