igMetaObject *igPsx2DecalExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2DecalExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001542b0();
    return g_igPsx2DecalExt_metaObject[0];
}

int igPsx2DecalExt_GetVTable(void) {
    union U_1541d0 u;
    int temp_s1;
    S_ref *q1;
    S_ref *q2;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00530a10[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[16];
    *(int *)q2 = 0;
    u.w[0] = (int)(&DAT_005256f0[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00530a10[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s1;
}

void FUN_001542b0(void)
{
    igMetaObject_RunStaticInit(igPsx2DecalExt_Register);
}

void igPsx2DecalExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2DecalExt_metaObject,
        igDecalExt_Register,
        igDecalExt_GetPublishedMetaObject,
        thunk_igPsx2DecalExt_GetMetaObject,
        igPsx2DecalExt_className,
        0x20, /* instance size */
        igPsx2DecalExt_GetVTable,
        &igPsx2DecalExt_InitFields,
        0, /* extra callback item */
        g_igPsx2DecalExt_callbackList /* callback list */
    );
}

int FUN_00154340(void) {
    return (int)DAT_0055fea8[0];
}

void igPsx2DecalExt_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005605f8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048a0b8[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048a0c0[0], &DAT_0048a0c8[0], &DAT_0048a0d0[0], temp_s2);
}

