igMetaObject *FUN_0044ff40(void) {
    if (g_igGuiComponent_metaObject[0] == 0) {
        g_igGuiComponent_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igGuiComponent_metaObject[0];
}

igMetaObject *igGuiComponent_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponent_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponent_EnsureRegistered();
    return g_igGuiComponent_metaObject[0];
}

int igGuiComponent_GetVTable(void) {
    struct Obj_44ffe0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541300[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00541300[0];
    FUN_00450370((ObjectRefWord *)&obj.w7, -1);
    FUN_004502f0((void **)&obj.w5, -1);
    FUN_00450270((ObjectRefWord *)&obj.w4, -1);
    FUN_004501f0((void **)&obj.w3, -1);
    return t;
}

O_450090 *FUN_00450090(O_450090 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00541300[0];
        if (&arg0->m28) {
            S1 *t = arg0->m28;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m20) {
            S1 *t = arg0->m20;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m16) {
            S1 *t = arg0->m16;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m12) {
            S1 *t = arg0->m12;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (arg1 > 0) thunk_FUN_002ed460__002ff810(arg0);
    }
    return arg0;
}

void **FUN_004501f0(void **arg0, short arg1) {
    S_temp_a0_4501f0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_4501f0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00450270(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_004502f0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00450370(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void igGuiComponent_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponent_Register);
}

void igGuiComponent_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponent_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igGuiComponent_GetMetaObject,
        igGuiComponent_className,
        0x24, /* instance size */
        igGuiComponent_GetVTable,
        &igGuiComponent_InitFields,
        0, /* extra callback item */
        g_igGuiComponent_callbackList /* callback list */
    );
}

void thunk_igGuiComponent_GetMetaObject(void) {
    igGuiComponent_GetMetaObject();
}

void igGuiComponent_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;

    temp_s1 = (void *)g_igGuiComponent_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d05a0[0], 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0044fa40();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_0044f790();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0044fbb0();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_0044ff40();
    ((igObjectRefMetaField *)temp_s2_4)->_refCounted = 0;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_0044ded0();
    ((igObjectRefMetaField *)temp_s2_5)->_refCounted = 0;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_0044f540();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004d05c0[0], &DAT_004d05e0[0], &DAT_004d0600[0], temp_s0);
}

