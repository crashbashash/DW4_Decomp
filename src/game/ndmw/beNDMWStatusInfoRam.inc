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

void **igSmartPointer_beNDMWStatusInfoWork_Destruct(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
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
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWStatusInfoRam_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWStatusInfoRam_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beNDMWStatusInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNDMWStatusInfoRam_fieldTable, g_beNDMWStatusInfoRam_fieldHandles, g_beNDMWStatusInfoRam_fieldOffsets, temp_s2);
}

