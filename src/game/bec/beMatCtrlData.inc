igMetaObject *g_beMatCtrlData_metaObject;
igMetaField *g_beMatCtrlData_chkBoxMetaField;

void *beMatCtrlData_GetMetaObject(void) {
    igMetaObject *g = g_beMatCtrlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMatCtrlData_EnsureRegistered();
    }
    return g_beMatCtrlData_metaObject;
}

int beMatCtrlData_GetVTable(void) {
    union U_35a480 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_beMatCtrlData_vtable[0];
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beMatCtrlData_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void beMatCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlData_Register);
}

static igMetaObjectCallback g_beMatCtrlData_callbackList[] = { igAABox_EnsureRegistered, 0 };

void *beMatCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMatCtrlData_GetMetaObjectFunction,
        "beMatCtrlData",
        0x10, /* instance size */
        beMatCtrlData_GetVTable,
        beMatCtrlData_InitFields,
        0, /* extra callback item */
        g_beMatCtrlData_callbackList /* callback list */
    );
}

void beMatCtrlData_GetMetaObjectFunction(void)
{
    beMatCtrlData_GetMetaObject();
}

static FieldFactory g_beMatCtrlData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrlData_fieldTable[] = {
    "_chkBox",
};
static igMetaField **g_beMatCtrlData_fieldHandles[] = {
    &g_beMatCtrlData_chkBoxMetaField,
};
static int g_beMatCtrlData_fieldOffsets[] = {
    12,
};

void beMatCtrlData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMatCtrlData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMatCtrlData_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igAABox_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beMatCtrlData_fieldTable, g_beMatCtrlData_fieldHandles, g_beMatCtrlData_fieldOffsets, temp_s2);
}

igMetaEnum *g_beMatCtrlData_messageMetaEnum;
static const char *g_beMatCtrlData_messageNames[] = {
    "SHOWMAT", "HIDEMAT", "SHOW_LUACALL", "HIDE_LUACALL",
    "PAUSE", "RESTART",
};
static int g_beMatCtrlData_messageValues[] = {
    0, 1, 2, 3, 4, 5,
};

igMetaEnum *beMatCtrl_GetMessageEnum(void) {
    if (g_beMatCtrlData_messageMetaEnum == 0) {
        g_beMatCtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beMatCtrlData_messageNames, g_beMatCtrlData_messageValues, 6);
    }
    return g_beMatCtrlData_messageMetaEnum;
}

