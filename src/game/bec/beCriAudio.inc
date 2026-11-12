igMetaObject *FUN_003671a0(void) {
    if (g_beCriAudio_metaObject[0] == 0) {
        g_beCriAudio_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beCriAudio_metaObject[0];
}

void *FUN_003671f0(void) {
    unsigned char b;
    if (((void * *)g_beCriAudio_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)g_beCriAudio_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00367320();
done:
    return ((void * *)g_beCriAudio_metaObject)[0];
}

int beCriAudio_GetVTable(void) {
    union U_367240 u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q38;
    void **q3c;

    igObject_InitHeader(u.b);
    q38 = &u.p[2];
    q3c = &u.p[3];
    u.w[0] = (int)(&DAT_00534e30[0]);
    *q38 = 0;
    *q3c = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00534e30[0]);
    if (q3c != 0) {
        a = (struct Rc *)*q3c;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q38 != 0) {
        a = (struct Rc *)*q38;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return t;
}

void FUN_00367320(void)
{
    igMetaObject_RunStaticInit(beCriAudio_Register);
}

void *beCriAudio_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriAudio_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriAudio_GetMetaObject,
        beCriAudio_className,
        0x18, /* instance size */
        beCriAudio_GetVTable,
        beCriAudio_InitFields,
        0, /* extra callback item */
        g_beCriAudio_callbackList /* callback list */
    );
}

void beCriAudio_GetMetaObject(void)
{
    FUN_003671f0();
}

void beCriAudio_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCriAudio_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c75c0[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00335130();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_003674d0();
    igMetaObject_NameFields(temp_s0, &DAT_004c75d0[0], &DAT_004c75e0[0], &DAT_004c75f0[0], temp_s2);
}

