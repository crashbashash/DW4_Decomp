igMetaObject *g_beNDMWShopCtrlEvolve_metaObject;
igMetaField *g_beNDMWShopCtrlEvolve_shinkaCtrlMetaField;

void beNDMWShopCtrlEvolve_Create(int arg0) {
    FUN_003b8a00();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlEvolve_metaObject, arg0);
}

void *FUN_003b88a0(void) {
    unsigned char b;
    if (g_beNDMWShopCtrlEvolve_metaObject != 0) {
        b = (*(int *)((char *)(g_beNDMWShopCtrlEvolve_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003b8a00();
done:
    return g_beNDMWShopCtrlEvolve_metaObject;
}

int beNDMWShopCtrlEvolve_GetVTable(void) {
    union U_3b88f0 u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&DAT_0053fb40[0];
    p = (int *)&u.b[96];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053fb40[0];
    FUN_003b8980((ObjectRefWord *)p, -1);
    FUN_003b6770((int **)u.b, (long long)0);
    return temp_s0;
}

ObjectRefWord *FUN_003b8980(ObjectRefWord *self,int delete_storage) {
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

void FUN_003b8a00(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlEvolve_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlEvolve_callbackList[] = { FUN_003c9650, 0 };

void *beNDMWShopCtrlEvolve_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlEvolve_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlEvolve_GetMetaObject,
        "beNDMWShopCtrlEvolve",
        0x64, /* instance size */
        beNDMWShopCtrlEvolve_GetVTable,
        beNDMWShopCtrlEvolve_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlEvolve_callbackList /* callback list */
    );
}

void beNDMWShopCtrlEvolve_GetMetaObject(void)
{
    FUN_003b88a0();
}

static FieldFactory g_beNDMWShopCtrlEvolve_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopCtrlEvolve_fieldTable[] = {
    "_shinkaCtrl",
};
static igMetaField **g_beNDMWShopCtrlEvolve_fieldHandles[] = {
    &g_beNDMWShopCtrlEvolve_shinkaCtrlMetaField,
};
static int g_beNDMWShopCtrlEvolve_fieldOffsets[] = {
    96,
};

void beNDMWShopCtrlEvolve_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopCtrlEvolve_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopCtrlEvolve_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c9480();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWShopCtrlEvolve_fieldTable, g_beNDMWShopCtrlEvolve_fieldHandles, g_beNDMWShopCtrlEvolve_fieldOffsets, temp_s2);
}

