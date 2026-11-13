void FUN_002cf900(int arg0) {
    FUN_002cfac0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586CF8), (MemoryPool *)arg0);
}

igMetaObject *igPsx2Media_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Media_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cfac0();
    return g_igPsx2Media_metaObject[0];
}

int igPsx2Media_GetVTable(void) {
    union U_2cf990 u;
    int temp_s2;
    S_ref * q1;
    S_ref * q0;
    S_ref * q2;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader((ObjectHeader *)u.b);
    u.vt = (int)(&DAT_0052da00[0]);
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    q1 = (S_ref *)&u.b[16];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[32];
    *(int *)q2 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)(&DAT_0052da00[0]);
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
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s2;
}

void FUN_002cfac0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2Media_Register);
}

void igPsx2Media_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2Media_metaObject),
        igMedia_Register,
        igMedia_GetPublishedMetaObject,
        thunk_igPsx2Media_GetMetaObject,
        igPsx2Media_className,
        0x28, /* instance size */
        igPsx2Media_GetVTable,
        &igPsx2Media_InitFields,
        0, /* extra callback item */
        g_igPsx2Media_callbackList /* callback list */
    );
}

igMetaObject *FUN_002cfb50(void) {
    return g_igMedia_metaObject[0];
}

void igPsx2Media_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    igRawRefMetaField *t5;
    void *temp_s0;

    temp_s0 = (void *)g_igPsx2Media_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igPsx2Media_ctorTable[0], 8);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((igMemoryRefMetaField *)temp_s2)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s2)->_resetMethod = 3;
    ((igMemoryRefMetaField *)temp_s2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2)->_releaseOnReset = 1;
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002cfe50();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002ba690();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)));
    ((igMemoryRefMetaField *)temp_s2)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s2)->_resetMethod = 3;
    ((igMemoryRefMetaField *)temp_s2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2)->_releaseOnReset = 1;
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)));
    ((igMemoryRefMetaField *)temp_s2)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s2)->_resetMethod = 3;
    ((igMemoryRefMetaField *)temp_s2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2)->_releaseOnReset = 1;
    t5 = (igRawRefMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5));
    t5->_resetMethod = 3;
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002b9540();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igPsx2Media_fieldTable[0], (igMetaField ***)&DAT_004c1d90[0], &DAT_004c1db0[0], temp_s1);
}

