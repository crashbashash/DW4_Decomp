void Gap__Core__igObjectRefMetaField__vfunc_12(int arg0) {
    FUN_00303460((igObjectRefMetaField *)arg0, 0);
    Gap__Core__igObject__vfunc_10(arg0);
}

void igObjectRefMetaField_InitDefaults(void **self) {
    Gap__Core__igObject__vfunc_09((int)self);
    ((igMetaFieldView *)self)->SetDefault(0);
}

void igObjectRefMetaField_Assign(igObjectRefMetaField *field,void *object,igObject *value){
    igObject *old=*(igObject **)((char *)object+field->_offset);
    if(field->_refCounted||field->_destruct){
        if(value)++value->_refCount;
        if(old){--old->_refCount;if(!(old->_refCount&0x7fffff))igObject_Destroy(old);}
    }
    *(igObject **)((char *)object+field->_offset)=value;
}

void Gap__Core__igObjectRefMetaField__vfunc_24(int a0, int a1, int a2) {
    igObjectRefMetaField_Assign((igObjectRefMetaField *)a0, (void *)a1, (igObject *)*(int *)((char *)a2 + 0));
}

int igObjectRefMetaField_GetTypeSize(igObjectRefMetaField *) { return 4; }

void FUN_00303460(igObjectRefMetaField *arg0, igObject *arg1) {
    igObject **temp_s0;
    igObject *temp_a0;

    temp_s0 = (igObject **)(arg0->_default);
    if (arg1 != 0) {
        arg1->_refCount = (int)((int) (arg1->_refCount + 1));
    }
    temp_a0 = (igObject *)(*temp_s0);
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)((int) (temp_a0->_refCount - 1));
        if (((unsigned long long) ((long long) (int) temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    *temp_s0 = arg1;
}

int Gap__Core__igObjectRefMetaField__vfunc_51(igObjectRefMetaField *self, igObject **valueSlot, int extra2, int extra3, int extra4) {
    igObject *object;

    igRefMetaField_ReadRawFieldMem((void *)self, (int)valueSlot, (int *)extra2, extra3, extra4);
    if ((self->_refCounted != 0) || (self->_destruct != 0)) {
        object = *valueSlot;
        if (object != 0) {
            object->_refCount = object->_refCount + 1;
        }
    }
}

void igObjectRefMetaField_ConstructValue(igObjectRefMetaField *field,void *object){
    void *allocator;
    if(!field->_construct)return;
    const char *name=(const char *)field->_poolName;
    if(name&&*name){allocator=Memory_GetAllocatorByName((int)name);if(!allocator)allocator=((void *)igObject_GetAllocator((int)object));}
    else allocator=((void *)igObject_GetAllocator((int)object));
    igObject *child=(igObject *)igMetaObject_CreateInstance((igMetaObject *)((void *)field->_metaObject), (igMemoryPoolView *)allocator);
    igObjectRefMetaField_Assign(field,object,child);
    if((field->_refCounted||field->_destruct)&&child){--child->_refCount;if(!(child->_refCount&0x7fffff))igObject_Destroy(child);}
}

void igObjectRefMetaField_DestructValue(igObjectRefMetaField *field,void *object){
    if(field->_destruct){igObject *child=*(igObject **)((char *)object+field->_offset);
        if(child){--child->_refCount;if(!(child->_refCount&0x7fffff))igObject_Destroy(child);}}
}

void Gap__Core__igObjectRefMetaField__vfunc_34(igObjectRefMetaField *field,void *object){
    if(field->_refCounted){igObject *child=*(igObject **)((char *)object+field->_offset);
        if(child){--child->_refCount;if(!(child->_refCount&0x7fffff))igObject_Destroy(child);}}
    igRefMetaField_ClearValue((igMetaField *)field,object);
}

void Gap__Core__igObjectRefMetaField__vfunc_28(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)(arg1 + *(int *)((char *)arg0 + 8));
    if (temp_a0 != 0) {
        igObject_ResetFields((igObjectDispatchView *)temp_a0);
    }
}

void Gap__Core__igObjectRefMetaField__vfunc_30(char *arg0, int arg1) {
    igObjectRefMetaField_Assign((igObjectRefMetaField *)arg0, (void *)arg1, (igObject *)**(int **)(arg0 + 32));
}

void Gap__Core__igObjectRefMetaField__vfunc_37(int arg0, int arg1, int arg2) {
    igObjectRefMetaField_Assign((igObjectRefMetaField *)arg0, (void *)arg1, (igObject *)*(int *)((char *)((arg2 + *(int *)((char *)(arg0) + 8))) + 0));
}

void Gap__Core__igObjectRefMetaField__vfunc_36(igObjectRefMetaField *self, char *dst, char *src) {
    igObjectDispatchView *to;
    igObjectDispatchView *from;
    igObject *copy;

    to = *(igObjectDispatchView **)(dst + self->_offset);
    from = *(igObjectDispatchView **)(src + self->_offset);
    if (to != 0 || from != 0) {
        if (to != 0 && from != 0) {
            from->vfunc_16();
            FUN_003006a0(to, from);
            return;
        }
        if (to == 0) {
            from->vfunc_16();
            copy = from->cloneViaMetadata(1);
            igObjectRefMetaField_Assign(self, dst, copy);
            if (self->_destruct == 0 && copy != 0) {
                copy->_refCount = copy->_refCount - 1;
                if ((copy->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(copy);
                }
            }
        } else if (from == 0) {
            igObjectRefMetaField_Assign(self, dst, 0);
        }
    }
}

void Gap__Core__igObjectRefMetaField__vfunc_38(igObjectRefMetaField *arg0, int arg1, int arg2) {
    int temp_a0;
    igObjectDispatchView *temp_a1;
    igObject *temp_v0;
    int off;

    off = arg0->_offset;
    temp_a0 = *(int *)(arg1 + off);
    temp_a1 = *(igObjectDispatchView **)(arg2 + off);
    if ((temp_a0 != 0) || (temp_a1 != 0)) {
        if ((temp_a0 != 0) && (temp_a1 != 0)) {
            FUN_00300770((igObjectDispatchView *)temp_a0, (int)temp_a1);
            return;
        }
        if (temp_a0 == 0) {
            temp_v0 = (igObject *)temp_a1->cloneViaMetadata(0);
            igObjectRefMetaField_Assign((igObjectRefMetaField *)arg0, (void *)arg1, (igObject *)temp_v0);
            if ((arg0->_destruct == 0) && (temp_v0 != 0)) {
                temp_v0->_refCount = temp_v0->_refCount - 1;
                if (((unsigned long long) ((long long)(int)temp_v0->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_v0);
                }
            }
        } else if (temp_a1 == 0) {
            igObjectRefMetaField_Assign((igObjectRefMetaField *)arg0, (void *)arg1, 0);
        }
    }
}

void Gap__Core__igObjectRefMetaField__vfunc_39(igObjectRefMetaField *self, int instance) {
    int object;

    object = *(int *)(instance + self->_offset);
    if (object != 0) {
        igObject_ResetFields((igObjectDispatchView *)object);
    }
}

/* Prints `<indent><field> = 0x<value>`, then the referenced object's own fields when `depth` asks
 * for them. */
void Gap__Core__igObjectRefMetaField__vfunc_41(igObjectRefMetaField *self, char *object, int depth, const char *indent) {
    FUN_00304430(DAT_004faef0, indent, self->_fieldName, *(int *)(object + self->_offset));
    FUN_00304680();
    if (depth != 0) {
        void **referenced = *(void ***)(object + self->_offset);
        if (referenced != 0) {
            FUN_00300490(referenced, depth, (int)indent);
        }
    }
}

void Gap__Core__igObjectRefMetaField__vfunc_42(igObjectRefMetaField *arg0, int arg1, int arg2, int arg3) {
    int temp_a0;

    temp_a0 = *(int *)(arg1 + arg0->_offset);
    if (temp_a0 != 0) {
        igObject_VisitFields((igObjectDispatchView *)temp_a0, (int (*)(void *, void *, void *))arg2, (void *)arg3);
    }
}

int Gap__Core__igObjectRefMetaField__vfunc_44(igObjectRefMetaField *arg0, int arg1, int arg2) {
    int temp_v0;

    temp_v0 = arg0->_offset;
    return *(int *)(arg1 + temp_v0) - *(int *)(arg2 + temp_v0);
}

int Gap__Core__igObjectRefMetaField__vfunc_45(igObjectRefMetaField *self, int objectA, int objectB) {
    int refA;
    int refB;
    int fieldOffset;

    fieldOffset = self->_offset;
    refA = *(int *)(objectA + fieldOffset);
    refB = *(int *)(objectB + fieldOffset);
    if (refA == refB) {
        return 1;
    }
    if ((refA == 0) || (refB == 0)) {
        return 0;
    }
    return igObject_IsAlikeExactly((void *)refA, (void *)refB);
}

int Gap__Core__igObjectRefMetaField__vfunc_46(igObjectRefMetaField *self, int objectA, int objectB) {
    int refA;
    int refB;
    int fieldOffset;

    fieldOffset = self->_offset;
    refA = *(int *)(objectA + fieldOffset);
    refB = *(int *)(objectB + fieldOffset);
    if (refA == refB) {
        return 1;
    }
    if ((refA == 0) || (refB == 0)) {
        return 0;
    }
    return igObject_IsAlikeDeep((igObjectDispatchView *)refA, (igObjectDispatchView *)refB);
}

int Gap__Core__igObjectRefMetaField__vfunc_47(igObjectRefMetaField *self, int objectA, int objectB) {
    int refA;
    int refB;
    int fieldOffset;

    fieldOffset = self->_offset;
    refA = *(int *)(objectA + fieldOffset);
    refB = *(int *)(objectB + fieldOffset);
    if (refA == refB) {
        return 1;
    }
    if ((refA == 0) || (refB == 0)) {
        return 0;
    }
    return igObject_IsAlikeShallow((igObjectDispatchView *)refA, (igObjectDispatchView *)refB);
}

void *igObjectRefMetaField_Construct(igObjectRefMetaField *self, int extra1) {
    igRefMetaField_Construct((igRefMetaField *)self);
    self->_vtable = (int)g_igObjectRefMetaField_vtable;
    self->_poolName = 0;
    if (self) {
        igObjectRefMetaField_Init(self);
    }
    return self;
}

void *igObjectRefMetaField_Init(igObjectRefMetaField *self) {
    igRefMetaField_Init((igRefMetaField *)self);
    self->_vtable = (int)g_igObjectRefMetaField_vtable;
    self->_poolName = 0;
    self->_refCounted = 1;
    self->_metaObject = 0;
    return self;
}

void *FUN_00303c60(igObjectRefMetaField *arg0, void *arg1) {
    igRefMetaField_CopyConstruct((igRefMetaField *)arg0, (igRefMetaField *)arg1);
    *(int *)((char *)(arg0) + 0) = (int)(&g_igObjectRefMetaField_vtable[0]);
    arg0->_poolName = 0;
    arg0->_refCounted = (unsigned char) *(unsigned char *)((char *)(arg1) + 60);
    arg0->_metaObject = (int)((int) *(int *)((char *)(arg1) + 56));
    return arg0;
}

void Gap__Core__igObjectRefMetaField__vfunc_02(igObjectRefMetaField *self) {
    igRefMetaField_Destruct((igRefMetaField *)self);
}

void FUN_00303cd0(igObjectStringMap *self, int name, void *object) {
    igObject *entry;
    igObject *held;

    *(igObject **)&entry = (igObject *)(FUN_002be270(((int)igObject_GetAllocator((int)self))));
    igNamedObject_SetName((igNamedObject *)entry, name);
    ObjectList_AppendRetained((igObjectList *)self->_names, (igObject *)entry);
    ObjectList_AppendRetained((igObjectList *)self->_data, (igObject *)object);
    held = entry;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if (((unsigned long long)((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(held);
        }
    }
}

int FUN_00303d70(void *arg0, int extra1) {
    int temp_v0;

    temp_v0 = FUN_00303dc0((igObjectStringMap *)arg0, extra1);
    if (temp_v0 == -1) {
        return 0;
    }
    return *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 16) + (temp_v0 * 4));
}

int FUN_00303dc0(igObjectStringMap *map, int name) {
    igObject *field = ((igObject *)igProperty_FindByName((igObjectList *)map->_names, (igMetaField *)g_propertyNameField[0], name));
    if (field == 0) {
        return -1;
    }
    FieldList *fields = (FieldList *)map->_names;
    return fields->find(field);
}

int FUN_00303e50(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 8);
}

int FUN_00303e60(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 16) + (arg1 * 4));
}

int *FUN_00303e80(void *arg0, int arg1) {
    int *temp_v0;
    void *temp_v0_2;

    temp_v0_2 = (void *)(*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 16) + (arg1 * 4)));
    if (temp_v0_2 == 0) {
        return 0;
    }
    temp_v0 = (int *)(*(int *)((char *)(temp_v0_2) + 8));
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return &emptyString[0];
}

void FUN_00303ed0(igObjectStringMap *o) {
    igObjectList *l = (igObjectList *)o->_names;
    int n = l->_count;
    int i;
    for (i = 0; i < n; i++) {
        igObject *p = ((igObject **)l->_data)[i];
        if (p) {
            p->_refCount = p->_refCount - 1;
            if ((((unsigned long long)(long long)p->_refCount) & 0x7fffffULL) == 0) igObject_Destroy((void *)p);
        }
    }
    { int m = l->_count; for (i = 0; i < m; i++) ((igObject **)l->_data)[i] = 0; }
    l->_count = 0;
    l = (igObjectList *)o->_data;
    n = l->_count;
    for (i = 0; i < n; i++) {
        igObject *p = ((igObject **)l->_data)[i];
        if (p) {
            p->_refCount = p->_refCount - 1;
            if ((((unsigned long long)(long long)p->_refCount) & 0x7fffffULL) == 0) igObject_Destroy((void *)p);
        }
    }
    { int m = l->_count; for (i = 0; i < m; i++) ((igObject **)l->_data)[i] = 0; }
    l->_count = 0;
}

void FUN_00304030(igObjectStringMap *arg0, int arg1) {
    /*D*/
    igObject *o;
    igObjectList *l2;
    int c2;
    igObjectList *l6;
    int c1;
    igObjectList *l3;
    int idx;
    igObject *s6b;
    igObject *s6;
    igObjectList *l4;
    igObjectList *l1;
    int s4;
    igObjectList *l5;
    int a4;
    /*E*/
    idx = FUN_00303e50((void *)arg0);
    l1 = (igObjectList *)arg0->_data;
    s4 = 4 * idx;
    s6 = ((igObject **)((char *)l1->_data + s4 - 4))[0];
    if (s6) { s6->_refCount = 1 + (int)s6->_refCount; }
    a4 = 4 * arg1;
    o = ((igObject **)((char *)l1->_data + a4))[0];
    REL(o)
    if (l1->_count && arg1 >= 0 && arg1 < l1->_count) { ((igObject **)((char *)l1->_data + a4))[0] = s6; }
    l2 = (igObjectList *)arg0->_data;
    o = ((igObject **)(s4 + (char *)l2->_data - 4))[0];
    REL(o)
    if (l2->_count && idx - 1 >= 0 && idx - 1 < l2->_count) { ((igObject **)((char *)(s4 + (int)(igObject **)l2->_data) - 4))[0] = 0; }
    l3 = (igObjectList *)arg0->_data;
    c1 = l3->_count - 1;
    o = ((igObject **)(l3->_data + c1 * 4))[0];
    REL(o)
    List_RemoveWordAt((igDataList *)l3, c1);
    ((igObject **)(l3->_data + 4 * l3->_count))[0] = 0;
    l4 = (igObjectList *)arg0->_names;
    s6b = ((igObject **)(s4 + (char *)l4->_data - 4))[0];
    if (s6b) { s6b->_refCount = 1 + (int)s6b->_refCount; }
    o = ((igObject **)((char *)l4->_data + a4))[0];
    REL(o)
    if (l4->_count && arg1 >= 0 && arg1 < l4->_count) { ((igObject **)(a4 + (char *)l4->_data))[0] = s6b; }
    l5 = (igObjectList *)arg0->_names;
    o = ((igObject **)((char *)l5->_data + s4 - 4))[0];
    REL(o)
    if (l5->_count && idx - 1 >= 0 && idx - 1 < l5->_count) { ((igObject **)((char *)(s4 + (int)(igObject **)l5->_data) - 4))[0] = 0; }
    l6 = (igObjectList *)arg0->_names;
    c2 = l6->_count - 1;
    o = ((igObject **)(l6->_data + 4 * c2))[0];
    REL(o)
    List_RemoveWordAt((igDataList *)l6, c2);
    ((igObject **)(l6->_data + l6->_count * 4))[0] = 0;
}

void FUN_00304350(igPsx2FileView *arg0) {
    igPsx2FileView *p;

    p = DAT_005871b0[0];
    if (p != 0) {
        p->_refCount -= 1;
        if ((p->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(p);
        }
    }
    if (arg0 != 0) {
        arg0->_refCount += 1;
    }
    DAT_005871b0[0] = arg0;
}

void FUN_003043c0(igPsx2FileView *arg0) {
    igPsx2FileView *p;
    int rc;
    p = DAT_005871b8[0];
    if (p != 0) {
        rc = p->_refCount - 1;
        p->_refCount = rc;
        if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    if (arg0 != 0) {
        arg0->_refCount = arg0->_refCount + 1;
    }
    DAT_005871b8[0] = arg0;
}

void FUN_00304430(const char *arg0, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    FUN_003044a0(arg0, (int)((char*)__builtin_next_arg(arg0) - off));
}

void FUN_003044a0(const char *arg0, int arg1) {
    char sp10[4096];
    int var_v0;

    if ((DAT_005871b0[0] != 0) && (GPR_00554998 != 0)) {
        var_v0 = vsnprintf(&sp10[0], 0x1000, arg0, arg1);
        if ((var_v0 < 0) || (var_v0 >= 0x1000)) {
            sp10[4095] = 0;
            var_v0 = 0x1000;
        }
        DAT_005871b0[0]->Write(&sp10[0], var_v0, 1);
        if (GPR_0055499c != 0) {
            printf(&DAT_004f95a0[0], &sp10[0]);
        }
    } else if (GPR_0055499c != 0) {
        vprintf(arg0, arg1);
    }
}

int FUN_00304550(int arg0, ...) { 
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    return FUN_003045c0(arg0, (int)((char*)__builtin_next_arg(arg0) - off)); }

int FUN_003045c0(int arg0, int arg1) {
    char buf[4096];
    int var_v0;

    if ((DAT_005871b8[0] != 0) && (GPR_005549a4 != 0)) {
        var_v0 = vsnprintf(buf, 0x1000, arg0, arg1);
        if ((var_v0 < 0) || (var_v0 >= 0x1000)) {
            buf[4095] = 0;
            var_v0 = 0x1000;
        }
        DAT_005871b8[0]->Write(buf, var_v0, 1);
        if (GPR_005549a8 != 0) {
            fprintf(_impure_ptr->_stderr, &DAT_004f95a0[0], buf);
        }
    } else if (GPR_005549a8 != 0) {
        vfprintf(_impure_ptr->_stderr, arg0, arg1);
    }
}

void FUN_00304680(void) {
    if (DAT_005871b0[0] != 0) {
        DAT_005871b0[0]->vfunc_32();
    }
    fflush(_impure_ptr->_stdout);
}

void FUN_003046d0(void) {
    if (DAT_005871b8[0] != 0) {
        DAT_005871b8[0]->vfunc_32();
    }
    fflush(_impure_ptr->_stderr);
}

void FUN_00304720(igPluginHelper *helper, int name, int location, int locationType) {
    int pool;
    char *text;
    igPluginRepository *target;
    char *old;
    igSmartPointer<igPluginRepository> repository(((igPluginRepository *)FUN_002bc930(((int)igObject_GetAllocator((int)helper)))));
    igNamedObject_SetName((igNamedObject *)repository.p, name);
    target = repository.p;
    if (g_stringPool[0] == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool[0] = pool;
    }
    text = ((char *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)location));
    old = (char *)target->_location;
    if (old != 0) {
        int *header = (int *)(old - 8);
        int count = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
        }
    }
    target->_location = (int)text;
    repository.p->_locationType = locationType;
    ObjectList_AppendRetained((igObjectList *)helper->_repositoryList, (igObject *)repository.p);
}

/* Store an interned copy of `location` as the repository's location, releasing the one it held. */
static inline void setRepositoryLocation(const igSmartPointer<igPluginRepository> &repository, const char *location) {
    igPluginRepository *target = repository.p;
    char *text = (char *)StringPool_Intern(InternedStrings::get(), location);
    releaseString((const char *)target->_location);
    target->_location = (int)text;
}

/* The same for the part of `path` past a root prefix of `rootLength` characters. */
static inline void setRepositoryLocation(const igSmartPointer<igPluginRepository> &repository, const char *path, const int &rootLength) {
    igPluginRepository *target = repository.p;
    char *text = (char *)StringPool_Intern(InternedStrings::get(), path + rootLength);
    releaseString((const char *)target->_location);
    target->_location = (int)text;
}

/* Add a plugin repository, recording whether its path is under $(AlchemyRoot) (1),
 * $(ApplicationRoot) (2) or neither (0); a recognised root is stripped from the stored location. */
void FUN_00304840(igPluginHelper *self, int name, const char *path) {
    static int alchemyRootLength = strlen(DAT_004c22c8[0]);
    static int applicationRootLength = strlen(DAT_004c22d0[0]);
    igSmartPointer<igPluginRepository> repository((igPluginRepository *)FUN_002bc930((int)igObject_GetAllocator((int)self)));
    igNamedObject_SetName((igNamedObject *)repository.get(), name);
    if (strncmp(path, DAT_004c22c8[0], alchemyRootLength) == 0) {
        setRepositoryLocation(repository, path, alchemyRootLength);
        repository.get()->_locationType = 1;
    } else if (strncmp(path, DAT_004c22d0[0], applicationRootLength) == 0) {
        setRepositoryLocation(repository, path, applicationRootLength);
        repository.get()->_locationType = 2;
    } else {
        setRepositoryLocation(repository, path);
        repository.get()->_locationType = 0;
    }
    ObjectList_AppendRetained((igObjectList *)self->_repositoryList, (igObject *)repository.get());
}

static inline void setLocation(const igSmartPointer<igPluginRepository> &ref, int path, const int &skip) {
    igPluginRepository *repository = ref.p;
    int interned, left;
    int old;
    int *header;
    if (g_stringPool[0] == 0) {
        int pool = ((int)StringPool_Allocate(16));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool[0] = pool;
    }
    interned = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)((char *)(path + skip)));
    old = repository->_location;
    if (old != 0) {
        header = (int *)(old - 8);
        left = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = left;
        if (left == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
        }
    }
    repository->_location = interned;
}

static inline void setLocation(const igSmartPointer<igPluginRepository> &ref, char *location) {
    igPluginRepository *repository = ref.p;
    int interned, left;
    int old;
    int *header;
    if (g_stringPool[0] == 0) {
        int pool = ((int)StringPool_Allocate(16));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool[0] = pool;
    }
    interned = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)location);
    old = repository->_location;
    if (old != 0) {
        header = (int *)(old - 8);
        left = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = left;
        if (left == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
        }
    }
    repository->_location = interned;
}

