void FUN_0035f100(int arg0) {
    FUN_0035f2b0();
    igMetaObject_CreateInstance(*(int *)0x589478, arg0);
}

igMetaObject *FUN_0035f140(void) {
    if (g_beGeneraterInfoWork_metaObject[0] == 0) {
        g_beGeneraterInfoWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beGeneraterInfoWork_metaObject[0];
}

igMetaObject *FUN_0035f190(void)
{
    igMetaObject *g = g_beGeneraterInfoWork_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0035f2b0();
    return g_beGeneraterInfoWork_metaObject[0];
}

int beGeneraterInfoWork_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *a1;
    int v0;
    S_ref *p0, *p1;

    igObject_InitHeader(u.b);
    p0 = (S_ref *)&u.b[20];
    p1 = (S_ref *)&u.b[28];
    u.vt = (int)&DAT_00536050[0];
    *(int *)p0 = 0;
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00536050[0];
    if (p1 != 0) {
        o = *(char **)p1;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p0 != 0) {
        p0 = *(S_ref **)p0;
        if (p0 != 0) {
            p0->f4 = (int)((int) (p0->f4 - 1));
            if (((unsigned long long) ((long long) p0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p0);
            }
        }
    }
    return t;
}

void FUN_0035f2b0(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfoWork_Register);
}

void *beGeneraterInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beGeneraterInfoWork_GetMetaObject,
        beGeneraterInfoWork_className,
        0x28, /* instance size */
        beGeneraterInfoWork_GetVTable,
        beGeneraterInfoWork_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfoWork_callbackList /* callback list */
    );
}

void beGeneraterInfoWork_GetMetaObject(void)
{
    FUN_0035f190();
}

void beGeneraterInfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beGeneraterInfoWork_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beGeneraterInfoWork_ctorTable[0], 9);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beGeneraterInfoWork_fieldTable[0], &DAT_004c6900[0], &DAT_004c6930[0], temp_s2);
}

