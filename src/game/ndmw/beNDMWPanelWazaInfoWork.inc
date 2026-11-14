void FUN_003bdb10(int arg0) {
    FUN_003bdf00();
    igMetaObject_CreateInstance(*(int *)0x58B200, arg0);
}

igMetaObject *FUN_003bdb50(void) {
    if (g_beNDMWPanelWazaInfoWork_metaObject[0] == 0) {
        g_beNDMWPanelWazaInfoWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWPanelWazaInfoWork_metaObject[0];
}

igMetaObject *beNDMWPanelWazaInfoWork_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWPanelWazaInfoWork_metaObject[0] != 0) {
        ready = (g_beNDMWPanelWazaInfoWork_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003bdf00();
done:
    return g_beNDMWPanelWazaInfoWork_metaObject[0];
}

int beNDMWPanelWazaInfoWork_GetVTable(void) {
    struct Obj_3bdbf0 obj;
    int temp_s5;

    igObject_InitHeader(&obj);
    obj.vt = (&DAT_0053d5d0[0]);
    obj.f10 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.f20 = 0;
    obj.f24 = 0;
    obj.f28 = 0;
    obj.f2C = 0;
    temp_s5 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_0053d5d0[0]);
    ObjectRef_Destruct_00150eb0(&obj.f2C, -1);
    ObjectRef_Destruct_001c6460(&obj.f28, -1);
    FUN_003bde80((struct Ref **)&obj.f24, (short)(-1));
    StringRef_Destruct_00130720(&obj.f20, -1);
    FUN_003bde00((void **)&obj.f18, (short)(-1));
    FUN_003bdd80((void **)&obj.f14, -1);
    FUN_003bdd00((ObjectRefWord *)&obj.f10, -1);
    return temp_s5;
}

ObjectRefWord *FUN_003bdd00(ObjectRefWord *self,int delete_storage) {
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

void **FUN_003bdd80(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_003bde00(void **arg0, short arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_003bde80(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void FUN_003bdf00(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWazaInfoWork_Register);
}

void *beNDMWPanelWazaInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        ((igMetaObject_3bdf20 * *)g_beNDMWPanelWazaInfoWork_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWPanelWazaInfoWork_GetMetaObject,
        beNDMWPanelWazaInfoWork_className,
        0x30, /* instance size */
        beNDMWPanelWazaInfoWork_GetVTable,
        beNDMWPanelWazaInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelWazaInfoWork_callbackList /* callback list */
    );
}

void beNDMWPanelWazaInfoWork_GetMetaObject(void)
{
    beNDMWPanelWazaInfoWork_ResolveMetaObject();
}

void beNDMWPanelWazaInfoWork_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beNDMWPanelWazaInfoWork_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beNDMWPanelWazaInfoWork_ctorTable[0], 0xB);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_003be8e0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_003be5a0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_003be0f0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_003bfcc0();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &g_beNDMWPanelWazaInfoWork_fieldTable[0], &DAT_004ca500[0], &DAT_004ca530[0], temp_s0);
}

