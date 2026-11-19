igMetaObject *g_igMessageFilter_metaObject;
igMetaField *g_igMessageFilter_msgTypeMetaField;
igMetaField *g_igMessageFilter_receiversMetaField;

int FUN_00231b40(int arg0) {
    igMessageFilter_EnsureRegistered();
    return (int)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x56DAF8), (igMemoryPoolView *)arg0));
}

igMetaObject *igMessageFilter_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageFilter_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMessageFilter_EnsureRegistered();
    return g_igMessageFilter_metaObject;
}

int igMessageFilter_GetVTable(void) {
    union U u;
    int temp_s1;
    S_ref *q2;
    S_ref *q3;

    void *temp_a0;
    void *temp_a0_2;

    igObject_InitHeader((igObject *)u.b);
    q2 = (S_ref *)&u.p[2];
    q3 = (S_ref *)&u.p[3];
    u.w[0] = (int)(&g_igMessageFilter_vtable[0]);
    *(int *)q2 = 0;
    *(int *)q3 = 0;
    temp_s1 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.w[0] = (int)(&g_igMessageFilter_vtable[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q2);
            }
        }
    }
    return temp_s1;
}

void igMessageFilter_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMessageFilter_Register);
}

static igMetaObjectCallback g_igMessageFilter_callbackList[] = { igMetaObject_EnsureRegistered, igMessageReceiverList_EnsureRegistered, 0 };

CallbackArray *igMessageFilter_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessageFilter_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igMessageFilter_GetMetaObjectFunction,
        "igMessageFilter",
        0x10, /* instance size */
        igMessageFilter_GetVTable,
        &igMessageFilter_InitFields,
        0, /* extra callback item */
        g_igMessageFilter_callbackList /* callback list */
    );
}

void igMessageFilter_GetMetaObjectFunction(void) {
    igMessageFilter_GetMetaObject();
}

static FieldFactory g_igMessageFilter_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igMessageFilter_fieldTable[] = {
    "_msgType",
    "_receivers",
};
static igMetaField **g_igMessageFilter_fieldHandles[] = {
    &g_igMessageFilter_msgTypeMetaField,
    &g_igMessageFilter_receiversMetaField,
};
static int g_igMessageFilter_fieldOffsets[] = {
    8,
    12,
};

void igMessageFilter_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igMessageFilter_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igMessageFilter_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)(igMetaObject_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igMessageReceiverList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igMessageFilter_fieldTable, g_igMessageFilter_fieldHandles, g_igMessageFilter_fieldOffsets, temp_s2);
}

