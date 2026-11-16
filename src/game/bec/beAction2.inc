igMetaObject *g_beAction2_metaObject;

void beAction2_CreateInstance(int allocator) {
    beAction2_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58A028, allocator);
}

igMetaObject *beAction2_GetOrCreateMetaObject(void) {
    if (g_beAction2_metaObject == 0) {
        g_beAction2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beAction2_metaObject;
}

void *beAction2_GetMetaObject(void) {
    igMetaObject *g = g_beAction2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beAction2_EnsureRegistered();
    }
    return g_beAction2_metaObject;
}

int beAction2_GetVTable(void) {
    union U_36de10 u;
    int temp_s0;
    igObject *q0;
    int temp_v0;
    int *temp_a1;
    int *temp_v1;
    char *q1;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
    q0 = (igObject *)&u.b[24];
    *(int *)q0 = 0;
    u.vt = (int)&g_beAction2_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)q0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q0->_refCount << 0x29) >> 0x29) == 0) {
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

void beAction2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2_Register);
}

void *beAction2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beAction2_GetMetaObjectFunction,
        "beAction2",
        0x20, /* instance size */
        beAction2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2_GetMetaObjectFunction(void)
{
    beAction2_GetMetaObject();
}

