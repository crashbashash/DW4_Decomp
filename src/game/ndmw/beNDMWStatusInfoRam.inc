void *FUN_003b5bb0(void) {
    igMetaObject *g = g_beNDMWStatusInfoRam_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b5d70();
    }
    return g_beNDMWStatusInfoRam_metaObject[0];
}

int beNDMWStatusInfoRam_GetVTable(void) {
    union U_3b5c00 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p58;
    char *p5C;

    igObject_InitHeader(u.b);
    p58 = &u.b[40];
    *(int *)p58 = 0;
    u.vt = (int)&DAT_0053db60[0];
    p5C = &u.b[44];
    *(int *)p5C = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053db60[0];
    if (p5C != 0) {
        v1 = *(int **)p5C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    u.vt = (int)&DAT_00539e90[0];
    if (p58 != 0) {
        v1 = *(int **)p58;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void **FUN_003b5cf0(struct Ref **self, short flag) {
    struct Ref *p;
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

void FUN_003b5d70(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfoRam_Register);
}

void *beNDMWStatusInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWStatusInfoRam_GetMetaObject,
        beNDMWStatusInfoRam_className,
        0x30, /* instance size */
        beNDMWStatusInfoRam_GetVTable,
        beNDMWStatusInfoRam_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusInfoRam_callbackList /* callback list */
    );
}

void beNDMWStatusInfoRam_GetMetaObject(void)
{
    FUN_003b5bb0();
}

void beNDMWStatusInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStatusInfoRam_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9840[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003b5f00();
    igMetaObject_NameFields(temp_s0, &DAT_004c9848[0], &DAT_004c9850[0], &DAT_004c9858[0], temp_s2);
}

