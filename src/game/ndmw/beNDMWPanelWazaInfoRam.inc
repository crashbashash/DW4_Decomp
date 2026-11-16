igMetaObject *g_beNDMWPanelWazaInfoRam_metaObject;
igMetaField *g_beNDMWPanelWazaInfoRam_workMetaField;

void *beNDMWPanelWazaInfoRam_ResolveMetaObject(void) {
    igMetaObject *meta = g_beNDMWPanelWazaInfoRam_metaObject;
    if (meta) {
        bool t;
        if ((t = (meta->_validity & 4) != 0) != false) goto end;
    }
    beNDMWPanelWazaInfoRam_EnsureRegistered();
end:
    return g_beNDMWPanelWazaInfoRam_metaObject;
}

int beNDMWPanelWazaInfoRam_GetVTable(void) {
    union WazaInfoRamProbe u;
    int temp_s1;
    WazaInfoRamRefHeader * q0;
    WazaInfoRamRefHeader * q1;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q0 = (WazaInfoRamRefHeader *)&u.b[40];
    *(int *)q0 = 0;
    u.vt = (int)(&g_beNDMWPanelWazaInfoRam_vtable[0]);
    q1 = (WazaInfoRamRefHeader *)&u.b[44];
    *(int *)q1 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)(&g_beNDMWPanelWazaInfoRam_vtable[0]);
    if (q1 != 0) {
        q1 = *(WazaInfoRamRefHeader **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    u.vt = (int)(&g_beBaseInfoRam_vtable[0]);
    if (q0 != 0) {
        q0 = *(WazaInfoRamRefHeader **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s1;
}

igSmartPointer<igObject> *beNDMWPanelWazaInfoRam_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beNDMWPanelWazaInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWazaInfoRam_Register);
}

static igMetaObjectCallback g_beNDMWPanelWazaInfoRam_callbackList[] = { beNDMWPanelWazaInfoWork_EnsureRegistered, 0 };

void *beNDMWPanelWazaInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelWazaInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWPanelWazaInfoRam_GetMetaObject,
        "beNDMWPanelWazaInfoRam",
        0x30, /* instance size */
        beNDMWPanelWazaInfoRam_GetVTable,
        beNDMWPanelWazaInfoRam_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelWazaInfoRam_callbackList /* callback list */
    );
}

void beNDMWPanelWazaInfoRam_GetMetaObject(void)
{
    beNDMWPanelWazaInfoRam_ResolveMetaObject();
}

static FieldFactory g_beNDMWPanelWazaInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWPanelWazaInfoRam_fieldTable[] = {
    "_work",
};
static igMetaField **g_beNDMWPanelWazaInfoRam_fieldHandles[] = {
    &g_beNDMWPanelWazaInfoRam_workMetaField,
};
static int g_beNDMWPanelWazaInfoRam_fieldOffsets[] = {
    44,
};

void beNDMWPanelWazaInfoRam_InitFields(void) {
    int base;
    void *work;
    igMetaObject *meta;

    meta = g_beNDMWPanelWazaInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWPanelWazaInfoRam_ctorTable, 1);
    work = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beNDMWPanelWazaInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWPanelWazaInfoRam_fieldTable, g_beNDMWPanelWazaInfoRam_fieldHandles, g_beNDMWPanelWazaInfoRam_fieldOffsets, base);
}

