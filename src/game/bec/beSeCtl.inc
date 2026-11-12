void FUN_003464f0(int arg0) {
    FUN_003466b0();
    igMetaObject_CreateInstance(*(int *)0x587FE8, arg0);
}

igMetaObject *FUN_00346530(void) {
    if (g_beSeCtl_metaObject[0] == 0) {
        g_beSeCtl_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beSeCtl_metaObject[0];
}

igMetaObject *FUN_00346580(void) {
    igMetaObject *g = g_beSeCtl_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003466b0();
done:
    return g_beSeCtl_metaObject[0];
}

int beSeCtl_GetVTable(void) {
    union U_3465d0 u;
    int temp_s1;
    void **q2;
    S_ref *q3;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    q2 = &u.p[2];
    *q2 = 0;
    q3 = (S_ref *)&u.b[24];
    *(int *)q3 = 0;
    u.w[0] = (int)(&DAT_0053b1f0[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1 = *q2;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void FUN_003466b0(void)
{
    igMetaObject_RunStaticInit(beSeCtl_Register);
}

void *beSeCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSeCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSeCtl_GetMetaObject,
        beSeCtl_className,
        0x24, /* instance size */
        beSeCtl_GetVTable,
        beSeCtl_InitFields,
        0, /* extra callback item */
        g_beSeCtl_callbackList /* callback list */
    );
}

void beSeCtl_GetMetaObject(void)
{
    FUN_00346580();
}

void beSeCtl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSeCtl_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3c00[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003442f0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c3c08[0], &DAT_004c3c10[0], &DAT_004c3c18[0], temp_s2);
}

