igMetaObject *g_igCameraMode_metaObject;
igMetaField *g_igCameraMode_cameraPathMetaField;
igMetaField *g_igCameraMode_cameraMetaField;

igCameraMode *igCameraMode_Create(int allocator) {
    igCameraMode_EnsureRegistered();
    return (igCameraMode *)igMetaObject_CreateInstance(g_igCameraMode_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igCameraMode_GetMetaObject(void) {
    igMetaObject *g = g_igCameraMode_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        igCameraMode_EnsureRegistered();
    return g_igCameraMode_metaObject;
}

int igCameraMode_GetVTable(void) {
    union U_45ccd0 u;
    int temp_s1;
    S_ref *q1;
    S_ref *q2;
    
    
    igObject_InitHeader((igObject *)u.b);
    u.w[0] = (int)(&g_igViewMode_vtable[0]);
    igMatrix44f_SetIdentity((float *)&u.w[3]);
    u.w[0] = (int)(&g_igCameraMode_vtable[0]);
    q1 = (S_ref *)&u.b[76];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[80];
    *(int *)q2 = 0;
    temp_s1 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.w[0] = (int)(&g_igCameraMode_vtable[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q2);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q1);
            }
        }
    }
    return temp_s1;
}

void igCameraMode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCameraMode_Register);
}

static igMetaObjectCallback g_igCameraMode_callbackList[] = { Gap::Sg::igGraphPath::arkRegister, Gap::Sg::igCamera::arkRegister, 0 };

CallbackArray *igCameraMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCameraMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        igCameraMode_GetMetaObjectFunction,
        "igCameraMode",
        0x54, /* instance size */
        igCameraMode_GetVTable,
        &igCameraMode_InitFields,
        0, /* extra callback item */
        g_igCameraMode_callbackList /* callback list */
    );
}

void igCameraMode_GetMetaObjectFunction(void) {
    igCameraMode_GetMetaObject();
}

static FieldFactory g_igCameraMode_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igCameraMode_fieldTable[] = {
    "_cameraPath",
    "_camera",
};
static igMetaField **g_igCameraMode_fieldHandles[] = {
    &g_igCameraMode_cameraPathMetaField,
    &g_igCameraMode_cameraMetaField,
};
static int g_igCameraMode_fieldOffsets[] = {
    76,
    80,
};

void igCameraMode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = g_igCameraMode_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igCameraMode_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)(Gap::Sg::igGraphPath::getClassTypeLazy());
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)(Gap::Sg::igCamera::getClassTypeLazy());
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCameraMode_fieldTable, g_igCameraMode_fieldHandles, g_igCameraMode_fieldOffsets, temp_s2);
}

