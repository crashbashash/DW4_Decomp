igMetaObject *g_beHitLandDeliv_metaObject;

void beHitLandDeliv_CreateInstance(int allocator) {
    beHitLandDeliv_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589460, allocator);
}

igMetaObject *beHitLandDeliv_GetOrCreateMetaObject(void) {
    if (g_beHitLandDeliv_metaObject == 0) {
        g_beHitLandDeliv_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beHitLandDeliv_metaObject;
}

void *beHitLandDeliv_GetMetaObject(void) {
    igMetaObject *g = g_beHitLandDeliv_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beHitLandDeliv_EnsureRegistered();
    }
    return g_beHitLandDeliv_metaObject;
}

int beHitLandDeliv_GetVTable(void) {
    union U_35ec70 u;
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
    u.vt = (int)&g_beHitLandDeliv_vtable[0];
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

void beHitLandDeliv_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandDeliv_Register);
}

void *beHitLandDeliv_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandDeliv_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beHitLandDeliv_GetMetaObjectFunction,
        "beHitLandDeliv",
        0x20, /* instance size */
        beHitLandDeliv_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beHitLandDeliv_GetMetaObjectFunction(void)
{
    beHitLandDeliv_GetMetaObject();
}

