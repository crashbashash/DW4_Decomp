igMetaObject *FUN_00143150(void)
{
    igMetaObject *meta = g_igPsx2AudioContext_metaObject[0];
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_001433d0();
end:
    return g_igPsx2AudioContext_metaObject[0];
}

int igPsx2AudioContext_GetVTable(void) {
    union AudioContextProbe u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00524a80[0];
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[48] = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00524a80[0];
    FUN_00143350((void **)&u.b[48], -1);
    FUN_00143350((void **)&u.b[20], -1);
    FUN_001432d0((struct RefCountBits **)&u.b[16], -1);
    FUN_00143250((void **)&u.b[12], -1);
    return t;
}

void **FUN_00143250(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001432d0(struct RefCountBits **self, short flag) {
    struct RefCountBits *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) FUN_00100610(self);
    }
    return (void **)self;
}

void **FUN_00143350(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_001433d0(void)
{
    igMetaObject_RunStaticInit(igPsx2AudioContext_Register);
}

void igPsx2AudioContext_Register(void) {
    AudioLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2AudioContext_metaObject,
        igAudioContext_Register,
        igAudioContext_GetPublishedMetaObject,
        thunk_FUN_00143150,
        igPsx2AudioContext_className,
        sizeof(igPsx2AudioContext),                     /* Instance size. */
        igPsx2AudioContext_GetVTable,
        &igPsx2AudioContext_InitFields,
        0, /* extra callback item */
        g_igPsx2AudioContext_callbackList /* callback list */
    );
}

igMetaObject *FUN_00143460(void) {
    return g_igAudioContext_metaObject[0];
}

void igPsx2AudioContext_InitFields(void) {
    /* matching construct: declaration-order sweep — this order sets the saved registers */
    void *temp_s1;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1_5;
    int temp_s2;
    void *temp_s1_4;
    void *temp_s0;

    temp_s0 = (void *)(g_igPsx2AudioContext_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486d10[0], 0xA);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cfe50();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002b7f80();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00145d40();
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 0);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 2);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 0x30);
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igMemoryRefMetaField *)temp_s1_4)->_memType = igUnsignedIntMetaField_GetDefaultDescriptor();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = FUN_00145d40();
    igMetaObject_NameFields(temp_s0, &DAT_00486d40[0], &DAT_00486d70[0], &DAT_00486da0[0], temp_s2);
    *(int *)((char *)(g_igPsx2AudioContext_metaObject[0]) + 64) = (int)thunk_igAudioContext_GetMetaObject;
}

