igMetaObject *igPsx2UserUCodeExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2UserUCodeExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2UserUCodeExt_EnsureRegistered();
    return g_igPsx2UserUCodeExt_metaObject;
}

int igPsx2UserUCodeExt_GetVTable(void) {
    struct Obj_152a80 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.w4 = 0;
    obj.vt = &g_igPsx2UserUCodeExt_vtable[0];
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igPsx2UserUCodeExt_vtable[0];
    FUN_00152c90((void **)&obj.w7, -1);
    FUN_00152c10((ObjectRefWord *)&obj.w6, -1);
    FUN_00152b10((S_152b10 *)&obj, 0);
    return t;
}

void *FUN_00152b10(struct S_152b10 *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00526b70[0];
        if (arg0 != 0) {
            arg0->f0 = &DAT_00527020[0];
            if (arg0 != 0) {
                arg0->f0 = &DAT_00530a10[0];
                if (&arg0->f10) {
                    p = (igObject *)arg0->f10;
                    if (p != 0) {
                        rc = (int)p->_refCount - 1;
                        p->_refCount = rc;
                        if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                            igObject_Destroy(p);
                        }
                    }
                }
                if (&arg0->f8) {
                    p = (igObject *)arg0->f8;
                    if (p != 0) {
                        rc = (int)p->_refCount - 1;
                        p->_refCount = rc;
                        if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                            igObject_Destroy(p);
                        }
                    }
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00152c10(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void **FUN_00152c90(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)r);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void igPsx2UserUCodeExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2UserUCodeExt_Register);
}

static igMetaObjectCallback g_igPsx2UserUCodeExt_callbackList[] = { igPsx2VisualContext_EnsureRegistered, Gap::Core::igIntMetaField::arkRegister, Gap::Core::igRawRefMetaField::arkRegister, 0 };

CallbackArray *igPsx2UserUCodeExt_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2UserUCodeExt_metaObject,
        igUserUCodeExt_Register,
        igUserUCodeExt_GetPublishedMetaObject,
        igPsx2UserUCodeExt_GetMetaObjectFunction,
        "igPsx2UserUCodeExt",
        0x24, /* instance size */
        igPsx2UserUCodeExt_GetVTable,
        &igPsx2UserUCodeExt_InitFields,
        0, /* extra callback item */
        g_igPsx2UserUCodeExt_callbackList /* callback list */
    );
}

igMetaObject *FUN_00152da0(void) {
    return g_igUserUCodeExt_metaObject;
}

static FieldFactory g_igPsx2UserUCodeExt_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igPsx2UserUCodeExt_fieldTable[] = {
    "_context",
    "_currentDListHandle",
    "_pDLists",
    "_bCompiling",
};
static igMetaField **g_igPsx2UserUCodeExt_fieldHandles[] = {
    &g_igPsx2UserUCodeExt_contextMetaField,
    &g_igPsx2UserUCodeExt_currentDListHandleMetaField,
    &g_igPsx2UserUCodeExt_pDListsMetaField,
    &g_igPsx2UserUCodeExt_bCompilingMetaField,
};
static int g_igPsx2UserUCodeExt_fieldOffsets[] = {
    20,
    24,
    28,
    32,
};

void igPsx2UserUCodeExt_InitFields(void) {
    int fieldStart;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igPsx2UserUCodeExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2UserUCodeExt_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igPsx2VisualContext_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)Gap::Core::igIntMetaField::getClassTypeLazy();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)Gap::Core::igRawRefMetaField::getClassTypeLazy();
    igMetaObject_NameFields(meta, g_igPsx2UserUCodeExt_fieldTable, g_igPsx2UserUCodeExt_fieldHandles, g_igPsx2UserUCodeExt_fieldOffsets, fieldStart);
}

