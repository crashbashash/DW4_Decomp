igMetaObject *igStandardQueue_GetMetaObject(void)
{
    igMetaObject *g = g_igStandardQueue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cf0e0();
    return g_igStandardQueue_metaObject[0];
}

int igStandardQueue_GetVTable(void) {
    union U_2cef90 u;
    int temp_s2;
    char *p2;
    char *p1;
    igObject_InitHeader((ObjectHeader *)u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_0052ddf0[0];
    p1 = &u.b[12];
    *(int *)p1 = 0;
    p2 = &u.b[16];
    *(int *)p2 = 0;
    *(int *)&u.b[20] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&DAT_0052ddf0[0];
    FUN_002ba970((Ref **)&u.b[20], -1);
    FUN_002ba970((Ref **)p2, -1);
    FUN_002ba970((Ref **)p1, -1);
    FUN_002cf040((S_2cf040 *)u.b, 0);
    return temp_s2;
}

void *FUN_002cf040(struct S_2cf040 *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0052ee50[0];
        if (&arg0->f8) {
            p = arg0->f8;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810((int)arg0);
        }
    }
    return arg0;
}

void FUN_002cf0e0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStandardQueue_Register);
}

void igStandardQueue_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStandardQueue_metaObject),
        igQueue_Register,
        igQueue_GetPublishedMetaObject,
        thunk_igStandardQueue_GetMetaObject,
        igStandardQueue_className,
        0x2C, /* instance size */
        igStandardQueue_GetVTable,
        &igStandardQueue_InitFields,
        0, /* extra callback item */
        g_igStandardQueue_callbackList /* callback list */
    );
}

igMetaObject *FUN_002cf170(void) {
    return g_igQueue_metaObject[0];
}

void igStandardQueue_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)(g_igStandardQueue_metaObject[0]);
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&DAT_004c1bf0[0], 8);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002ba690();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_002ba690();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_002ba690();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_0030e9b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3))), 4);
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igMemoryRefMetaField *)temp_s2_4)->_memType = igRawRefMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s2_4)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2_4)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2_4)->_releaseOnReset = 1;
    FUN_0030e9b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7))), 0x2000);
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&DAT_004c1c10[0], (igMetaField ***)&DAT_004c1c30[0], &DAT_004c1c50[0], temp_s0);
    ((igMetaObject *)g_igStandardQueue_metaObject[0])->_writeProxy = (int)thunk_igQueue_GetMetaObject;
}

