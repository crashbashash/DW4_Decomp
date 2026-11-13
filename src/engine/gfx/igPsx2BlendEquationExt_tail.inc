igMetaObject *igPsx2BlendEquationExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2BlendEquationExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00154710();
    return g_igPsx2BlendEquationExt_metaObject[0];
}

int igPsx2BlendEquationExt_GetVTable(void) {
    union U_154630 u;
    int temp_s1;
    S_ref *q1;
    S_ref *q2;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00530a10[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[16];
    *(int *)q2 = 0;
    u.w[0] = (int)(&DAT_00525770[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
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

void FUN_00154710(void)
{
    igMetaObject_RunStaticInit(igPsx2BlendEquationExt_Register);
}

void igPsx2BlendEquationExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2BlendEquationExt_metaObject,
        igBlendEquationExt_Register,
        igBlendEquationExt_GetPublishedMetaObject,
        thunk_igPsx2BlendEquationExt_GetMetaObject,
        igPsx2BlendEquationExt_className,
        0x30, /* instance size */
        igPsx2BlendEquationExt_GetVTable,
        &igPsx2BlendEquationExt_InitFields,
        0, /* extra callback item */
        g_igPsx2BlendEquationExt_callbackList /* callback list */
    );
}

igMetaObject *FUN_001547a0(void) {
    return g_igBlendEquationExt_metaObject[0];
}

void igPsx2BlendEquationExt_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igPsx2BlendEquationExt_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igPsx2BlendEquationExt_ctorTable[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    FUN_002d4e40(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), -0x80);
    igMetaObject_NameFields(temp_s0, &g_igPsx2BlendEquationExt_fieldTable[0], &DAT_0048a140[0], &DAT_0048a160[0], temp_s2);
}

