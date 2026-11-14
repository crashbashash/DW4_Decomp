igMetaObject *FUN_0044bce0(void) {
    if (g_igTextElement_metaObject[0] == 0) {
        g_igTextElement_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTextElement_metaObject[0];
}

igMetaObject *igTextElement_GetMetaObject(void)
{
    igMetaObject *g = g_igTextElement_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igTextElement_EnsureRegistered();
    return g_igTextElement_metaObject[0];
}

int igTextElement_GetVTable(void) {
    union U u;

    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[10] = 0;
    u.w[0] = (int)(&DAT_00540c10[0]);
    u.w[11] = 0;
    u.w[12] = 0;
    u.w[13] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00540c10[0]);
    StringRef_Destruct_00130720(&u.w[13], -1);
    FUN_001353b0(&u.w[12], -1);
    FUN_0044bf10((void **)&u.w[11], -1);
    FUN_0044be30((igGeometryElement *)u.b, 0);
    return temp_s2;
}

void *FUN_0044be30(igGeometryElement *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_00541e90[0];
        if (&arg0->_sharableAttrs) {
            p = (igObject *)arg0->_sharableAttrs;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_geometry) {
            p = (igObject *)arg0->_geometry;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_Memory_FreeBuffer(arg0);
        }
    }
    return arg0;
}

void **FUN_0044bf10(void **arg0, long long arg1) {
    char *o;
    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void igTextElement_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextElement_Register);
}

void igTextElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextElement_metaObject,
        igGeometryElement_Register,
        igGeometryElement_GetPublishedMetaObject,
        thunk_igTextElement_GetMetaObject,
        igTextElement_className,
        0x38, /* instance size */
        igTextElement_GetVTable,
        &igTextElement_InitFields,
        0, /* extra callback item */
        g_igTextElement_callbackList /* callback list */
    );
}

void thunk_igTextElement_GetMetaObject(void) {
    igTextElement_GetMetaObject();
}

igMetaObject *FUN_0044c030(void) {
    return g_igGeometryElement_metaObject[0];
}

void igTextElement_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igTextElement_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igTextElement_ctorTable[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_004507f0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00137850();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), &DAT_0051dd88[0]);
    igMetaObject_NameFields(temp_s0, &g_igTextElement_fieldTable[0], &DAT_004cff48[0], &DAT_004cff58[0], temp_s2);
}

void *FUN_0044c110(struct S *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00540e30[0];
        if (&arg0->f8) {
            p = arg0->f8;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_Memory_FreeBuffer(arg0);
        }
    }
    return arg0;
}

igMetaObject *FUN_0044c1b0(void) {
    return g_igGuiComponentModel_metaObject[0];
}

void **FUN_0044c1c0(void **arg0, int arg1) {
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

igMetaObject *FUN_0044c240(void) {
    return g_igGuiComponentAspect_metaObject[0];
}

