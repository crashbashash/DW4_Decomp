igMetaObject *g_beParticleCtrl2InfoWork_metaObject;
igMetaField *g_beParticleCtrl2InfoWork_positionLockNodeMetaField;
igMetaField *g_beParticleCtrl2InfoWork_positionLockOffsetMetaField;

void beParticleCtrl2InfoWork_Create(int arg0) {
    beParticleCtrl2InfoWork_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5884C8, arg0);
}

igMetaObject *beParticleCtrl2InfoWork_GetOrCreateMetaObject(void) {
    if (g_beParticleCtrl2InfoWork_metaObject == 0) {
        g_beParticleCtrl2InfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beParticleCtrl2InfoWork_metaObject;
}

void *beParticleCtrl2InfoWork_GetMetaObject(void) {
    unsigned char b;
    if (((void * *)&g_beParticleCtrl2InfoWork_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)&g_beParticleCtrl2InfoWork_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beParticleCtrl2InfoWork_EnsureRegistered();
done:
    return ((void * *)&g_beParticleCtrl2InfoWork_metaObject)[0];
}

int beParticleCtrl2InfoWork_GetVTable(void) {
    union U_34c120 u;
    int temp_s0;
    char *ps;
    int *temp_a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beParticleCtrl2InfoWork_vtable[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beParticleCtrl2InfoWork_vtable[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void beParticleCtrl2InfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2InfoWork_Register);
}

static igMetaObjectCallback g_beParticleCtrl2InfoWork_callbackList[] = { beModelCtrlNode2_EnsureRegistered, 0 };

void *beParticleCtrl2InfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beParticleCtrl2InfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beParticleCtrl2InfoWork_GetMetaObjectFunction,
        "beParticleCtrl2InfoWork",
        0x18, /* instance size */
        beParticleCtrl2InfoWork_GetVTable,
        beParticleCtrl2InfoWork_InitFields,
        0, /* extra callback item */
        g_beParticleCtrl2InfoWork_callbackList /* callback list */
    );
}

void beParticleCtrl2InfoWork_GetMetaObjectFunction(void)
{
    beParticleCtrl2InfoWork_GetMetaObject();
}

static FieldFactory g_beParticleCtrl2InfoWork_ctorTable[] = {
    igObjectRefMetaField_Create,
    FUN_00187890,
};
static const char *g_beParticleCtrl2InfoWork_fieldTable[] = {
    "_positionLockNode",
    "_positionLockOffset",
};
static igMetaField **g_beParticleCtrl2InfoWork_fieldHandles[] = {
    &g_beParticleCtrl2InfoWork_positionLockNodeMetaField,
    &g_beParticleCtrl2InfoWork_positionLockOffsetMetaField,
};
static int g_beParticleCtrl2InfoWork_fieldOffsets[] = {
    8,
    12,
};

void beParticleCtrl2InfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beParticleCtrl2InfoWork_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beParticleCtrl2InfoWork_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beModelCtrlNode2_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beParticleCtrl2InfoWork_fieldTable, g_beParticleCtrl2InfoWork_fieldHandles, g_beParticleCtrl2InfoWork_fieldOffsets, temp_s2);
}

