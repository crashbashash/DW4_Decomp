igMetaObject *g_igTransformRecorder_metaObject;
igMetaField *g_igTransformRecorder_mMetaField;
igMetaField *g_igTransformRecorder_mvmMetaField;

igMetaObject *igTransformRecorder_GetOrCreateMetaObject(void) {
    if (g_igTransformRecorder_metaObject == 0) {
        g_igTransformRecorder_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTransformRecorder_metaObject;
}

igMetaObject *igTransformRecorder_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformRecorder_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTransformRecorder_EnsureRegistered();
    return g_igTransformRecorder_metaObject;
}

int igTransformRecorder_GetVTable(void) { struct Obj_195860 o; int *p = (int *)&o; int t;
 igObject_InitHeader((igObject *)(struct Obj_195860 *)p); o.vt = &g_igTransformRecorder_vtable[0]; o.f8 = 0; o.f12 = 0; o.f16 = 0; o.f28 = 0;
 igMatrix44f_SetIdentity((float *)o.sub1); igMatrix44f_SetIdentity((float *)(p + 24));
 t = *(int *)((char *)&o + *(int *)((char *)g_objectSystem + 916));
 o.vt = &g_igTransformRecorder_vtable[0]; igGroup_Destroy((igGroup *)((struct Obj_195860 *)p), 0); return t; }

void **igSmartPointer_igNodeList_Destruct(void **arg0, short arg1) {
    S_temp_a0_1958f0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_1958f0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

igNode *igNode_Destroy(igNode *self, short deleteFlag) {
    struct Rc *o;
    int *a1;
    int v0;
    if (self != 0) {
        self->_vtable = (int)&g_igNode_vtable[0];
        if (&self->_parentList != 0) {
            o = (struct Rc *)self->_parentList;
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((igObject *)o);
                }
            }
        }
        if (&self->_bound != 0) {
            o = (struct Rc *)self->_bound;
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((igObject *)o);
                }
            }
        }
        if (self != 0) {
            self->_vtable = (int)&g_igNamedObject_vtable[0];
            if (&self->_name != 0) {
                char *p = (char *)self->_name;
                if (p != 0) {
                    a1 = (int *)(p - 8);
                    v0 = *(int *)(p - 4) - 1;
                    *(int *)(p - 4) = v0;
                    if (v0 == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
                    }
                }
            }
        }
        if (deleteFlag > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igGroup *igGroup_Destroy(igGroup *self, short deleteFlag) {
    struct Rc *o;
    int *a1;
    int v0;
    if (self != 0) {
        self->_vtable = (int)&g_igGroup_vtable[0];
        if (&self->_childList != 0) {
            o = (struct Rc *)self->_childList;
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((igObject *)o);
                }
            }
        }
        if (self != 0) {
            self->_vtable = (int)&g_igNode_vtable[0];
            if (&self->_parentList != 0) {
                o = (struct Rc *)self->_parentList;
                if (o != 0) {
                    o->rc = o->rc - 1;
                    if ((o->rc & 0x7FFFFF) == 0) {
                        igObject_Destroy((igObject *)o);
                    }
                }
            }
            if (&self->_bound != 0) {
                o = (struct Rc *)self->_bound;
                if (o != 0) {
                    o->rc = o->rc - 1;
                    if ((o->rc & 0x7FFFFF) == 0) {
                        igObject_Destroy((igObject *)o);
                    }
                }
            }
            if (self != 0) {
                self->_vtable = (int)&g_igNamedObject_vtable[0];
                if (&self->_name != 0) {
                    char *p = (char *)self->_name;
                    if (p != 0) {
                        a1 = (int *)(p - 8);
                        v0 = *(int *)(p - 4) - 1;
                        *(int *)(p - 4) = v0;
                        if (v0 == 0) {
                            StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
                        }
                    }
                }
            }
        }
        if (deleteFlag > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void igTransformRecorder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTransformRecorder_Register);
}

CallbackArray *igTransformRecorder_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTransformRecorder_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igTransformRecorder_GetMetaObject,
        "igTransformRecorder",
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

static FieldFactory g_igTransformRecorder_ctorTable[] = {
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
};
static const char *g_igTransformRecorder_fieldTable[] = {
    "_m",
    "_mvm",
};
static igMetaField **g_igTransformRecorder_fieldHandles[] = {
    &g_igTransformRecorder_mMetaField,
    &g_igTransformRecorder_mvmMetaField,
};
static int g_igTransformRecorder_fieldOffsets[] = {
    32,
    96,
};

void igTransformRecorder_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igTransformRecorder_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igTransformRecorder_ctorTable, 2);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igTransformRecorder_fieldTable, g_igTransformRecorder_fieldHandles, g_igTransformRecorder_fieldOffsets, temp_s1);
}

