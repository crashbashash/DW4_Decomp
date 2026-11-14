igMetaObject *igPsx2UserUCodeExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2UserUCodeExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00152d10();
    return g_igPsx2UserUCodeExt_metaObject[0];
}

int igPsx2UserUCodeExt_GetVTable(void) {
    struct Obj_152a80 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w4 = 0;
    obj.vt = &DAT_005252a0[0];
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_005252a0[0];
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
            thunk_Memory_FreeBuffer(arg0);
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
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
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
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00152d10(void)
{
    igMetaObject_RunStaticInit(igPsx2UserUCodeExt_Register);
}

void igPsx2UserUCodeExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2UserUCodeExt_metaObject,
        igUserUCodeExt_Register,
        igUserUCodeExt_GetPublishedMetaObject,
        thunk_igPsx2UserUCodeExt_GetMetaObject,
        igPsx2UserUCodeExt_className,
        0x24, /* instance size */
        igPsx2UserUCodeExt_GetVTable,
        &igPsx2UserUCodeExt_InitFields,
        0, /* extra callback item */
        g_igPsx2UserUCodeExt_callbackList /* callback list */
    );
}

igMetaObject *FUN_00152da0(void) {
    return g_igUserUCodeExt_metaObject[0];
}

void igPsx2UserUCodeExt_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igPsx2UserUCodeExt_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igPsx2UserUCodeExt_ctorTable[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntMetaField_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igRawRefMetaField_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, &g_igPsx2UserUCodeExt_fieldTable[0], &DAT_00489de0[0], &DAT_00489df0[0], temp_s2);
}

