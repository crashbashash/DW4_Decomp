igMetaObject *FUN_001957c0(void) {
    if (g_igTransformRecorder_metaObject[0] == 0) {
        g_igTransformRecorder_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTransformRecorder_metaObject[0];
}

igMetaObject *igTransformRecorder_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformRecorder_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00195c00();
    return g_igTransformRecorder_metaObject[0];
}

int igTransformRecorder_GetVTable(void) { struct Obj_195860 o; int *p = (int *)&o; int t;
 igObject_InitHeader((struct Obj_195860 *)p); o.vt = &DAT_0052b7d0[0]; o.f8 = 0; o.f12 = 0; o.f16 = 0; o.f28 = 0;
 igMatrix44f_SetIdentity(o.sub1); igMatrix44f_SetIdentity(p + 24);
 t = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
 o.vt = &DAT_0052b7d0[0]; FUN_00195a90((struct T_195a90 *)((struct Obj_195860 *)p), 0); return t; }

void **FUN_001958f0(void **arg0, short arg1) {
    S_temp_a0_1958f0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_1958f0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void *FUN_00195970(struct T_195970 *arg0, long long arg1) {
    struct Rc *o;
    int *a1;
    int v0;
    if (arg0 != 0) {
        arg0->vt = &DAT_00528a90[0];
        if (&arg0->f16 != 0) {
            o = arg0->f16;
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((void *)o);
                }
            }
        }
        if (&arg0->f12 != 0) {
            o = arg0->f12;
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((void *)o);
                }
            }
        }
        if (arg0 != 0) {
            arg0->vt = &g_igNamedObject_vtable[0];
            if (&arg0->f8 != 0) {
                char *p = arg0->f8;
                if (p != 0) {
                    a1 = (int *)(p - 8);
                    v0 = *(int *)(p - 4) - 1;
                    *(int *)(p - 4) = v0;
                    if (v0 == 0) {
                        StringChunk_ReleaseHeader(*a1, a1);
                    }
                }
            }
        }
        if ((short)arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void *FUN_00195a90(struct T_195a90 *arg0, long long arg1) {
    struct Rc *o;
    int *a1;
    int v0;
    if (arg0 != 0) {
        arg0->vt = &DAT_00528dd0[0];
        if (&arg0->f28 != 0) {
            o = arg0->f28;
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((void *)o);
                }
            }
        }
        if (arg0 != 0) {
            arg0->vt = &DAT_00528a90[0];
            if (&arg0->f16 != 0) {
                o = arg0->f16;
                if (o != 0) {
                    o->rc = o->rc - 1;
                    if ((o->rc & 0x7FFFFF) == 0) {
                        igObject_Destroy((void *)o);
                    }
                }
            }
            if (&arg0->f12 != 0) {
                o = arg0->f12;
                if (o != 0) {
                    o->rc = o->rc - 1;
                    if ((o->rc & 0x7FFFFF) == 0) {
                        igObject_Destroy((void *)o);
                    }
                }
            }
            if (arg0 != 0) {
                arg0->vt = &g_igNamedObject_vtable[0];
                if (&arg0->f8 != 0) {
                    char *p = arg0->f8;
                    if (p != 0) {
                        a1 = (int *)(p - 8);
                        v0 = *(int *)(p - 4) - 1;
                        *(int *)(p - 4) = v0;
                        if (v0 == 0) {
                            StringChunk_ReleaseHeader(*a1, a1);
                        }
                    }
                }
            }
        }
        if ((short)arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void FUN_00195c00(void)
{
    igMetaObject_RunStaticInit(igTransformRecorder_Register);
}

void igTransformRecorder_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igTransformRecorder_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igTransformRecorder_GetMetaObject,
        igTransformRecorder_className,
        0xA0, /* instance size */
        igTransformRecorder_GetVTable,
        &igTransformRecorder_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTransformRecorder_GetMetaObject(void) {
    igTransformRecorder_GetMetaObject();
}

void igTransformRecorder_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igTransformRecorder_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igTransformRecorder_ctorTable[0], 2);
    igMetaObject_NameFields(temp_s0, &g_igTransformRecorder_fieldTable[0], &DAT_0048b150[0], &DAT_0048b158[0], temp_s1);
}

