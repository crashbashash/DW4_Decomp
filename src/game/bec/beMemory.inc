igMetaObject *FUN_003591e0(void) {
    if (g_beMemory_metaObject[0] == 0) {
        g_beMemory_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beMemory_metaObject[0];
}

void *FUN_00359230(void) {
    igMetaObject *g = g_beMemory_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00359310();
    }
    return g_beMemory_metaObject[0];
}

int beMemory_GetVTable(void) {
    union U u;
    int temp_s0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_igNamedObject_vtable[0];
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_0053c1e0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
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

void FUN_00359310(void)
{
    igMetaObject_RunStaticInit(beMemory_Register);
}

void *beMemory_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMemory_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beMemory_GetMetaObject,
        beMemory_className,
        0x24, /* instance size */
        beMemory_GetVTable,
        beMemory_InitFields,
        0, /* extra callback item */
        g_beMemory_callbackList /* callback list */
    );
}

void beMemory_GetMetaObject(void)
{
    FUN_00359230();
}

void beMemory_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMemory_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beMemory_ctorTable[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00357910();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &g_beMemory_fieldTable[0], &DAT_004c5f90[0], &DAT_004c5fb0[0], temp_s2);
}

