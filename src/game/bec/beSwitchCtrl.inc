igMetaObject *g_beSwitchCtrl_metaObject;

void beSwitchCtrl_CreateInstance(int arg0) {
    beSwitchCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587DF8, arg0);
}

igMetaObject *beSwitchCtrl_GetOrCreateMetaObject(void) {
    if (g_beSwitchCtrl_metaObject == 0) {
        g_beSwitchCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSwitchCtrl_metaObject;
}

void *beSwitchCtrl_GetMetaObject(void) {
    igMetaObject *g = g_beSwitchCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSwitchCtrl_EnsureRegistered();
    }
    return g_beSwitchCtrl_metaObject;
}

int beSwitchCtrl_GetVTable(void) {
    union U_343570 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    u.vt = (int)&g_beSwitchCtrl_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void beSwitchCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSwitchCtrl_Register);
}

void *beSwitchCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSwitchCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSwitchCtrl_GetMetaObjectFunction,
        "beSwitchCtrl",
        0x20, /* instance size */
        beSwitchCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSwitchCtrl_GetMetaObjectFunction(void)
{
    beSwitchCtrl_GetMetaObject();
}

igMetaEnum *g_beSwitchCtrl_messageMetaEnum;
static const char *g_beSwitchCtrl_messageNames[] = {
    "GETINFOLIST",
};
static int g_beSwitchCtrl_messageValues[] = {
    0,
};

igMetaEnum *FUN_00343700(void) {
    if (g_beSwitchCtrl_messageMetaEnum == 0) {
        g_beSwitchCtrl_messageMetaEnum = igMetaEnum_Create("Message", g_beSwitchCtrl_messageNames, g_beSwitchCtrl_messageValues, 1);
    }
    return g_beSwitchCtrl_messageMetaEnum;
}

