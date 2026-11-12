void *beMessengerDelay_Create(void *allocator){beMessengerDelay_EnsureRegistered();return ((void *)igMetaObject_CreateInstance((void *)((int *)g_beMessengerDelay_metaObject)[0],allocator));}

G_358990 *FUN_00358990(void) {
    G_358990 *g = DAT_00588ff0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        beMessengerDelay_EnsureRegistered();
    return DAT_00588ff0[0];
}

int beMessengerDelay_GetVTable(void) {
    union U_3589e0 u;
    int temp_s3;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00536d70[0]);
    u.w[6] = 0;
    u.w[7] = 0;
    u.w[9] = 0;
    u.w[10] = 0;
    temp_s3 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00536d70[0]);
    FUN_00357a90((void **)&u.w[10], -1);
    StringRef_Destruct_00130720(&u.w[9], -1);
    StringRef_Destruct_00130720(&u.w[7], -1);
    StringRef_Destruct_00130720(&u.w[6], -1);
    return temp_s3;
}

void beMessengerDelay_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerDelay_Register);}

void *beMessengerDelay_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerDelay_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerDelay_GetMetaObject,
        beMessengerDelay_className,
        0x30, /* instance size */
        beMessengerDelay_GetVTable,
        beMessengerDelay_InitFields,
        0, /* extra callback item */
        g_beMessengerDelay_callbackList /* callback list */
    );
}

void beMessengerDelay_GetMetaObject(void)
{
    FUN_00358990();
}

void beMessengerDelay_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588ff0)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5dc0[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00358dc0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c5de0[0], &DAT_004c5e00[0], &DAT_004c5e20[0], temp_s2);
}

