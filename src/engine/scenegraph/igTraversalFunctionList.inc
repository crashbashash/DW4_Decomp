int FUN_0019a6e0(int arg0) {
    igTraversalFunctionList_EnsureRegistered();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igTraversalFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igTraversalFunctionList_metaObject;

igMetaObject *FUN_0019a720(void) {
    if (g_igTraversalFunctionList_metaObject == 0) {
        g_igTraversalFunctionList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTraversalFunctionList_metaObject;
}

igMetaObject *igTraversalFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igTraversalFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTraversalFunctionList_EnsureRegistered();
    return g_igTraversalFunctionList_metaObject;
}

int igTraversalFunctionList_GetVTable(void) {
    struct Obj_19a7c0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTraversalFunctionList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igTraversalFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTraversalFunctionList_Register);
}

CallbackArray *igTraversalFunctionList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTraversalFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igTraversalFunctionList_GetMetaObject,
        "igTraversalFunctionList",
        0x14, /* instance size */
        igTraversalFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTraversalFunctionList_GetMetaObject(void) {
    igTraversalFunctionList_GetMetaObject();
}

ObjectRefWord *FUN_0019a890(ObjectRefWord *self,int delete_storage) {
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

void **FUN_0019a910(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void **FUN_0019a990(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void **FUN_0019aa10(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) operator delete(self);
    }
    return (void **)self;
}

void **FUN_0019aa90(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

O *igSmartPointer_igColorAttr_Destruct(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_0019ab90(ObjectRefWord *self,int delete_storage) {
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

int *FUN_0019ac10(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac20(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac30(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac40(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac50(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac60(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac70(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac80(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac90(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019aca0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019acb0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019acc0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019acd0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int FUN_0019ace0(int a0)
{
    return a0;
}

void *FUN_0019acf0(igGroup *arg0) {
    igObject_InitHeader((igObject *)arg0);
    arg0->_vtable = (int)(&g_igNamedObject_vtable[0]);
    arg0->_name = 0;
    arg0->_vtable = (int)(&g_igNode_vtable[0]);
    arg0->_bound = 0;
    arg0->_parentList = 0;
    arg0->_vtable = (int)(&g_igGroup_vtable[0]);
    arg0->_childList = 0;
    return arg0;
}

