void FUN_003c1ca0(int arg0) {
    FUN_003c1de0();
    igMetaObject_CreateInstance(*(int *)0x58B520, arg0);
}

int FUN_003c1ce0(void) {
    if (((int *)DAT_0058b520)[0] == 0) {
        ((int *)DAT_0058b520)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b520)[0];
}

void *beNDMWMdlEBullet_GetReadyMetaObject(void) {
    bool ok;
    if (DAT_0058b520[0] == 0) goto make;
    ok = !!(DAT_0058b520[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003c1de0();
done:;
    return DAT_0058b520[0];
}

int beNDMWMdlEBullet_GetVTable(void) {
    union U_3c1d80 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053e210[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053e210[0];
    FUN_003bf2f0((struct NamedRefObject *)u.b, (long long)0);
    return temp_s0;
}

void FUN_003c1de0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEBullet_Register);
}

void *beNDMWMdlEBullet_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlEBullet_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlEBullet_GetMetaObject,
        beNDMWMdlEBullet_className,
        0x2c, /* instance size */
        beNDMWMdlEBullet_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlEBullet_GetMetaObject(void)
{
    beNDMWMdlEBullet_GetReadyMetaObject();
}

