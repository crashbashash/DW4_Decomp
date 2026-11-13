igMetaObject *FUN_00152e80(void) {
    if (g_igPsx2ScissorExt_metaObject[0] == 0) {
        g_igPsx2ScissorExt_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igPsx2ScissorExt_metaObject[0];
}

igMetaObject *igPsx2ScissorExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ScissorExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153000();
    return g_igPsx2ScissorExt_metaObject[0];
}

int igPsx2ScissorExt_GetVTable(void) {
    union U u;
    int temp_s0;
    char *q1;
    char *q2;
    igObject *a;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00530a10[0];
    q1 = &u.b[8];
    *(int *)q1 = 0;
    q2 = &u.b[16];
    *(int *)q2 = 0;
    u.vt = (int)&DAT_00525480[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00530a10[0];
    if (q2 != 0) {
        a = *(igObject **)q2;
        if (a != 0) {
            a->_refCount = (int)((int) ((int)a->_refCount - 1));
            if (((unsigned long long) ((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q1 != 0) {
        a = *(igObject **)q1;
        if (a != 0) {
            a->_refCount = (int)((int) ((int)a->_refCount - 1));
            if (((unsigned long long) ((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return temp_s0;
}

void FUN_00153000(void)
{
    igMetaObject_RunStaticInit(igPsx2ScissorExt_Register);
}

void igPsx2ScissorExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2ScissorExt_metaObject,
        igScissorExt_Register,
        igScissorExt_GetPublishedMetaObject,
        thunk_igPsx2ScissorExt_GetMetaObject,
        igPsx2ScissorExt_className,
        0x2C, /* instance size */
        igPsx2ScissorExt_GetVTable,
        &igPsx2ScissorExt_InitFields,
        0, /* extra callback item */
        g_igPsx2ScissorExt_callbackList /* callback list */
    );
}

igMetaObject *FUN_00153090(void) {
    return g_igScissorExt_metaObject[0];
}

void igPsx2ScissorExt_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igPsx2ScissorExt_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igPsx2ScissorExt_ctorTable[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0x280);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 0x1C0);
    igMetaObject_NameFields(temp_s0, &g_igPsx2ScissorExt_fieldTable[0], &DAT_00489e50[0], &DAT_00489e70[0], temp_s2);
}

