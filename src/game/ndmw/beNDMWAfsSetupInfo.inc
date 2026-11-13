void *beNDMWAfsSetupInfo_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWAfsSetupInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003ca690();
    }
    return g_beNDMWAfsSetupInfo_metaObject[0];
}

int beNDMWAfsSetupInfo_GetVTable(void) {
    struct W_3ca580 o;
    int r;
    igObject_InitHeader(&o);
    o.vt = DAT_0053c470;
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053c470;
    FUN_003ca610((ObjectRefWord_3ca610 *)(&o.f[5]), -1);
    FUN_00333760(&o.f[4], -1);
    FUN_00131b20(&o, 0);
    return r;
}

ObjectRefWord_3ca610 *FUN_003ca610(ObjectRefWord_3ca610 *self,int delete_storage) {
    if(self) {
        ObjectRefTarget_3ca610 *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_003ca690(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupInfo_Register);
}

void *beNDMWAfsSetupInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWAfsSetupInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beNDMWAfsSetupInfo_GetMetaObject,
        beNDMWAfsSetupInfo_className,
        0x1c, /* instance size */
        beNDMWAfsSetupInfo_GetVTable,
        beNDMWAfsSetupInfo_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsSetupInfo_callbackList /* callback list */
    );
}

void beNDMWAfsSetupInfo_GetMetaObject(void)
{
    beNDMWAfsSetupInfo_ResolveMetaObject();
}

void beNDMWAfsSetupInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWAfsSetupInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc5b0[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00334610();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_003ca800();
    igMetaObject_NameFields(temp_s0, &DAT_004cc5b8[0], &DAT_004cc5c0[0], &DAT_004cc5c8[0], temp_s2);
}

