igMetaObject *g_beNDMWStatusInfoRam_metaObject;
igMetaField *g_beNDMWStatusInfoRam_workMetaField;

void *beNDMWStatusInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusInfoRam_EnsureRegistered();
    }
    return g_beNDMWStatusInfoRam_metaObject;
}

int beNDMWStatusInfoRam_GetVTable(void) {
    union U_3b5c00 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p58;
    char *p5C;

    igObject_InitHeader(u.b);
    p58 = &u.b[40];
    *(int *)p58 = 0;
    u.vt = (int)&g_beNDMWStatusInfoRam_vtable[0];
    p5C = &u.b[44];
    *(int *)p5C = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWStatusInfoRam_vtable[0];
    if (p5C != 0) {
        v1 = *(int **)p5C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    u.vt = (int)&g_beBaseInfoRam_vtable[0];
    if (p58 != 0) {
        v1 = *(int **)p58;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWStatusInfoWork_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWStatusInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfoRam_Register);
}

static igMetaObjectCallback g_beNDMWStatusInfoRam_callbackList[] = { beNDMWStatusInfoWork_EnsureRegistered, 0 };

void *beNDMWStatusInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWStatusInfoRam_GetMetaObjectFunction,
        "beNDMWStatusInfoRam",
        0x30, /* instance size */
        beNDMWStatusInfoRam_GetVTable,
        beNDMWStatusInfoRam_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusInfoRam_callbackList /* callback list */
    );
}

void beNDMWStatusInfoRam_GetMetaObjectFunction(void)
{
    beNDMWStatusInfoRam_GetMetaObject();
}

static FieldFactory g_beNDMWStatusInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusInfoRam_fieldTable[] = {
    "_work",
};
static igMetaField **g_beNDMWStatusInfoRam_fieldHandles[] = {
    &g_beNDMWStatusInfoRam_workMetaField,
};
static int g_beNDMWStatusInfoRam_fieldOffsets[] = {
    44,
};

void beNDMWStatusInfoRam_InitFields(void) {
    int base;
    void *work;
    igMetaObject *meta;

    meta = g_beNDMWStatusInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusInfoRam_ctorTable, 1);
    work = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beNDMWStatusInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWStatusInfoRam_fieldTable, g_beNDMWStatusInfoRam_fieldHandles, g_beNDMWStatusInfoRam_fieldOffsets, base);
}

