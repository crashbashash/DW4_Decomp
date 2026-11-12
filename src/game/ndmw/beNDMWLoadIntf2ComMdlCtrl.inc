void beNDMWLoadIntf2ComMdlCtrl_Create(int arg0) {
    FUN_003c7090();
    igMetaObject_CreateInstance(*(int *)0x58BE38, arg0);
}

int FUN_003c6ee0(void) {
    if (((int *)DAT_0058be38)[0] == 0) {
        ((int *)DAT_0058be38)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058be38)[0];
}

void *beNDMWLoadIntf2ComMdlCtrl_GetReadyMetaObject(void) {
    struct G *g = DAT_0058be38[0];
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (exceptions on); `if (ready = ...)` folds it away */
        ready = g->f & 4;
        if (ready != false) goto end;
    }
    FUN_003c7090();
end:
    return DAT_0058be38[0];
}

int beNDMWLoadIntf2ComMdlCtrl_GetVTable(void) {
    struct W_3c6f80 o;
    int r;

    igObject_InitHeader(&o);
    o.vt = DAT_0053c8e0;
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
    o.vt = DAT_0053c8e0;
    FUN_003c7010((ObjectRefWord *)(&o.f[5]), -1);
    FUN_003c7010((ObjectRefWord *)(&o.f[4]), -1);
    FUN_00344030(&o, 0);
    return r;
}

ObjectRefWord *FUN_003c7010(ObjectRefWord *self,int delete_storage) {
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

void FUN_003c7090(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2ComMdlCtrl_Register);
}

void *beNDMWLoadIntf2ComMdlCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2ComMdlCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2ComMdlCtrl_GetMetaObject,
        beNDMWLoadIntf2ComMdlCtrl_className,
        0x28, /* instance size */
        beNDMWLoadIntf2ComMdlCtrl_GetVTable,
        beNDMWLoadIntf2ComMdlCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2ComMdlCtrl_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2ComMdlCtrl_GetMetaObject(void)
{
    beNDMWLoadIntf2ComMdlCtrl_GetReadyMetaObject();
}

void beNDMWLoadIntf2ComMdlCtrl_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(((void * *)DAT_0058be38)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004cbee0[0], 4);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00511b88[0]);
    ((igStringMetaField *)temp_v0_2)->_externalEnumStorage = (int)(&DAT_0058be40[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    ((igStringMetaField *)temp_v0_2)->_refCount = (int)((int) (((igStringMetaField *)temp_v0_2)->_refCount - 1));
    if ((((igStringMetaField *)temp_v0_2)->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = FUN_003c72c0();
    ((igObjectRefMetaField *)temp_s0_2)->_construct = 1;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = FUN_003c72c0();
    ((igObjectRefMetaField *)temp_s0_3)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004cbef0[0], &DAT_004cbf00[0], &DAT_004cbf10[0], temp_s2);
}

