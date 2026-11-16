igMetaObject *g_beDBManager_metaObject;

void beDBManager_CreateInstance(int allocator) {
    beDBManager_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589958, allocator);
}

igMetaObject *beDBManager_GetOrCreateMetaObject(void) {
    if (g_beDBManager_metaObject == 0) {
        g_beDBManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beDBManager_metaObject;
}

igMetaObject *beDBManager_GetMetaObject(void) {
    igMetaObject *g = g_beDBManager_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beDBManager_EnsureRegistered();
    return g_beDBManager_metaObject;
}

int beDBManager_GetVTable(void) {
    union U_3661b0 u;
    int temp_s0;
    igObject *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
    q0 = (igObject *)&u.b[24];
    *(int *)q0 = 0;
    u.vt = (int)&g_beDBManager_vtable[0];
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

void beDBManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDBManager_Register);
}

void *beDBManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDBManager_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beDBManager_GetMetaObjectFunction,
        "beDBManager",
        0x20, /* instance size */
        beDBManager_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDBManager_GetMetaObjectFunction(void)
{
    beDBManager_GetMetaObject();
}

