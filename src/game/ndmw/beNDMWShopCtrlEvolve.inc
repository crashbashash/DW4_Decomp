void FUN_003b8860(int arg0) {
    FUN_003b8a00();
    igMetaObject_CreateInstance(*(int *)0x58AE08, arg0);
}

void *FUN_003b88a0(void) {
    unsigned char b;
    if (g_beNDMWShopCtrlEvolve_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beNDMWShopCtrlEvolve_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003b8a00();
done:
    return g_beNDMWShopCtrlEvolve_metaObject[0];
}

int beNDMWShopCtrlEvolve_GetVTable(void) {
    union U_3b88f0 u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&DAT_0053fb40[0];
    p = (int *)&u.b[96];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053fb40[0];
    FUN_003b8980((ObjectRefWord *)p, -1);
    FUN_003b6770((int **)u.b, (long long)0);
    return temp_s0;
}

ObjectRefWord *FUN_003b8980(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void FUN_003b8a00(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlEvolve_Register);
}

void *beNDMWShopCtrlEvolve_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlEvolve_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlEvolve_GetMetaObject,
        beNDMWShopCtrlEvolve_className,
        0x64, /* instance size */
        beNDMWShopCtrlEvolve_GetVTable,
        beNDMWShopCtrlEvolve_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlEvolve_callbackList /* callback list */
    );
}

void beNDMWShopCtrlEvolve_GetMetaObject(void)
{
    FUN_003b88a0();
}

void beNDMWShopCtrlEvolve_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopCtrlEvolve_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9c30[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c9480();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9c38[0], &DAT_004c9c40[0], &DAT_004c9c48[0], temp_s2);
}

