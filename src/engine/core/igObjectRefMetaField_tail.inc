void igObjectRefMetaField_ReleaseDefaults(int self) {
    igObjectRefMetaField_SetDefault((igObjectRefMetaField *)self, 0);
    igObject_ReleaseDefaults((igObject *)self);
}

void igObjectRefMetaField_InitDefaults(void **self) {
    igObject_InitDefaults((igObject *)self);
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

void igObjectRefMetaField_SetValue(int self, int object, int value) {
    igObjectRefMetaField_Assign((igObjectRefMetaField *)self, (void *)object, (igObject *)*(int *)value);
}

int igObjectRefMetaField_GetTypeSize(igObjectRefMetaField *) { return 4; }

void igObjectRefMetaField_SetDefault(igObjectRefMetaField *self, igObject *value) {
    igObject **slot;
    igObject *old;

    slot = (igObject **)(self->_default);
    if (value != 0) {
        value->_refCount = (int)((int) (value->_refCount + 1));
    }
    old = (igObject *)(*slot);
    if (old != 0) {
        old->_refCount = (int)((int) (old->_refCount - 1));
        if (((unsigned long long) ((long long) (int) old->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(old);
        }
    }
    *slot = value;
}

int igObjectRefMetaField_ReadRawFieldMem(igObjectRefMetaField *self, igObject **valueSlot, int extra2, int extra3, int extra4) {
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
    if(name&&*name){allocator=Memory_GetAllocatorByName(name);if(!allocator)allocator=((void *)igObject_GetAllocator((igObject *)object));}
    else allocator=((void *)igObject_GetAllocator((igObject *)object));
    igObject *child=(igObject *)igMetaObject_CreateInstance((igMetaObject *)((void *)field->_metaObject), (igMemoryPoolView *)allocator);
    igObjectRefMetaField_Assign(field,object,child);
    if((field->_refCounted||field->_destruct)&&child){--child->_refCount;if(!(child->_refCount&0x7fffff))igObject_Destroy(child);}
}

void igObjectRefMetaField_DestructValue(igObjectRefMetaField *field,void *object){
    if(field->_destruct){igObject *child=*(igObject **)((char *)object+field->_offset);
        if(child){--child->_refCount;if(!(child->_refCount&0x7fffff))igObject_Destroy(child);}}
}

void igObjectRefMetaField_ClearValue(igObjectRefMetaField *field,void *object){
    if(field->_refCounted){igObject *child=*(igObject **)((char *)object+field->_offset);
        if(child){--child->_refCount;if(!(child->_refCount&0x7fffff))igObject_Destroy(child);}}
    igRefMetaField_ClearValue((igMetaField *)field,object);
}

void igObjectRefMetaField_SetToDefault(void *self, int object) {
    int child;

    child = *(int *)(object + ((igObjectRefMetaField *)self)->_offset);
    if (child != 0) {
        igObject_ResetFields((igObjectDispatchView *)child);
    }
}

void igObjectRefMetaField_CopyDefaultToValue(char *self, int object) {
    igObjectRefMetaField_Assign((igObjectRefMetaField *)self, (void *)object, (igObject *)*(int *)((igObjectRefMetaField *)self)->_default);
}

void igObjectRefMetaField_CopyReference(int self, int object, int source) {
    igObjectRefMetaField_Assign((igObjectRefMetaField *)self, (void *)object, (igObject *)*(int *)(source + ((igObjectRefMetaField *)self)->_offset));
}

void igObjectRefMetaField_DeepCopy(igObjectRefMetaField *self, char *dst, char *src) {
    igObjectDispatchView *to;
    igObjectDispatchView *from;
    igObject *copy;

    to = *(igObjectDispatchView **)(dst + self->_offset);
    from = *(igObjectDispatchView **)(src + self->_offset);
    if (to != 0 || from != 0) {
        if (to != 0 && from != 0) {
            from->TrimCapacity();
            igObject_DeepCopy(to, from);
            return;
        }
        if (to == 0) {
            from->TrimCapacity();
            copy = from->CloneViaMetadata(1);
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

void igObjectRefMetaField_ShallowCopy(igObjectRefMetaField *self, int dst, int src) {
    int to;
    igObjectDispatchView *from;
    igObject *copy;
    int off;

    off = self->_offset;
    to = *(int *)(dst + off);
    from = *(igObjectDispatchView **)(src + off);
    if ((to != 0) || (from != 0)) {
        if ((to != 0) && (from != 0)) {
            igObject_ShallowCopy((igObjectDispatchView *)to, (int)from);
            return;
        }
        if (to == 0) {
            copy = (igObject *)from->CloneViaMetadata(0);
            igObjectRefMetaField_Assign((igObjectRefMetaField *)self, (void *)dst, (igObject *)copy);
            if ((self->_destruct == 0) && (copy != 0)) {
                copy->_refCount = copy->_refCount - 1;
                if (((unsigned long long) ((long long)(int)copy->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(copy);
                }
            }
        } else if (from == 0) {
            igObjectRefMetaField_Assign((igObjectRefMetaField *)self, (void *)dst, 0);
        }
    }
}

void igObjectRefMetaField_ResetValue(igObjectRefMetaField *self, int instance) {
    int object;

    object = *(int *)(instance + self->_offset);
    if (object != 0) {
        igObject_ResetFields((igObjectDispatchView *)object);
    }
}

/* Prints `<indent><field> = 0x<value>`, then the referenced object's own fields when `depth` asks
 * for them. */
void igObjectRefMetaField_Print(igObjectRefMetaField *self, char *object, int depth, const char *indent) {
    igReport_Printf("%s%s = 0x%x\n", indent, self->_fieldName, *(int *)(object + self->_offset));
    igReport_Flush();
    if (depth != 0) {
        void **referenced = *(void ***)(object + self->_offset);
        if (referenced != 0) {
            igObject_Print(referenced, depth, (int)indent);
        }
    }
}

void igObjectRefMetaField_ReleaseElements(igObjectRefMetaField *self, int object, int visitor, int context) {
    int child;

    child = *(int *)(object + self->_offset);
    if (child != 0) {
        igObject_VisitFields((igObjectDispatchView *)child, (int (*)(void *, void *, void *))visitor, (void *)context);
    }
}

int igObjectRefMetaField_Compare(igObjectRefMetaField *self, int a, int b) {
    int offset;

    offset = self->_offset;
    return *(int *)(a + offset) - *(int *)(b + offset);
}

int igObjectRefMetaField_IsAlikeExactly(igObjectRefMetaField *self, int objectA, int objectB) {
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

int igObjectRefMetaField_IsAlikeDeep(igObjectRefMetaField *self, int objectA, int objectB) {
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

int igObjectRefMetaField_IsAlikeShallow(igObjectRefMetaField *self, int objectA, int objectB) {
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

void *igObjectRefMetaField_CopyConstruct(igObjectRefMetaField *self, void *source) {
    igRefMetaField_CopyConstruct((igRefMetaField *)self, (igRefMetaField *)source);
    self->_vtable = (int)(&g_igObjectRefMetaField_vtable[0]);
    self->_poolName = 0;
    self->_refCounted = (unsigned char) ((igObjectRefMetaField *)source)->_refCounted;
    self->_metaObject = (int)((int) ((igObjectRefMetaField *)source)->_metaObject);
    return self;
}

void igObjectRefMetaField_Destruct(igObjectRefMetaField *self) {
    igRefMetaField_Destruct((igRefMetaField *)self);
}

void igObjectStringMap_Add(igObjectStringMap *self, const char *name, void *object) {
    igObject *entry;
    igObject *held;

    *(igObject **)&entry = (igObject *)(igNamedObject_Create(((int)igObject_GetAllocator((igObject *)self))));
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

int igObjectStringMap_GetObject(void *self, const char *name) {
    int index;

    index = igObjectStringMap_GetIndexByName((igObjectStringMap *)self, name);
    if (index == -1) {
        return 0;
    }
    return ((int *)((igObjectList *)((igObjectStringMap *)self)->_data)->_data)[index];
}

int igObjectStringMap_GetIndexByName(igObjectStringMap *map, const char *name) {
    igObject *field = ((igObject *)igProperty_FindByName((igObjectList *)map->_names, (igMetaField *)g_propertyNameField, name));
    if (field == 0) {
        return -1;
    }
    FieldList *fields = (FieldList *)map->_names;
    return fields->find(field);
}

int igObjectStringMap_GetCount(void *self) {
    return ((igObjectList *)((igObjectStringMap *)self)->_names)->_count;
}

int igObjectStringMap_GetObjectAt(void *self, int index) {
    return ((int *)((igObjectList *)((igObjectStringMap *)self)->_data)->_data)[index];
}

int *igObjectStringMap_GetNameAt(void *self, int index) {
    int *name;
    igNamedObject *entry;

    entry = (igNamedObject *)((int *)((igObjectList *)((igObjectStringMap *)self)->_names)->_data)[index];
    if (entry == 0) {
        return 0;
    }
    name = (int *)entry->_name;
    if (name != 0) {
        return name;
    }
    return (int *)emptyString;
}

void igObjectStringMap_Clear(igObjectStringMap *o) {
    igObjectList *l = (igObjectList *)o->_names;
    int n = l->_count;
    int i;
    for (i = 0; i < n; i++) {
        igObject *p = ((igObject **)l->_data)[i];
        if (p) {
            p->_refCount = p->_refCount - 1;
            if ((((unsigned long long)(long long)p->_refCount) & 0x7fffffULL) == 0) igObject_Destroy((igObject *)p);
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
            if ((((unsigned long long)(long long)p->_refCount) & 0x7fffffULL) == 0) igObject_Destroy((igObject *)p);
        }
    }
    { int m = l->_count; for (i = 0; i < m; i++) ((igObject **)l->_data)[i] = 0; }
    l->_count = 0;
}

void igObjectStringMap_RemoveAt(igObjectStringMap *self, int index) {
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
    idx = igObjectStringMap_GetCount((void *)self);
    l1 = (igObjectList *)self->_data;
    s4 = 4 * idx;
    s6 = ((igObject **)((char *)l1->_data + s4 - 4))[0];
    if (s6) { s6->_refCount = 1 + (int)s6->_refCount; }
    a4 = 4 * index;
    o = ((igObject **)((char *)l1->_data + a4))[0];
    REL(o)
    if (l1->_count && index >= 0 && index < l1->_count) { ((igObject **)((char *)l1->_data + a4))[0] = s6; }
    l2 = (igObjectList *)self->_data;
    o = ((igObject **)(s4 + (char *)l2->_data - 4))[0];
    REL(o)
    if (l2->_count && idx - 1 >= 0 && idx - 1 < l2->_count) { ((igObject **)((char *)(s4 + (int)(igObject **)l2->_data) - 4))[0] = 0; }
    l3 = (igObjectList *)self->_data;
    c1 = l3->_count - 1;
    o = ((igObject **)(l3->_data + c1 * 4))[0];
    REL(o)
    List_RemoveWordAt((igDataList *)l3, c1);
    ((igObject **)(l3->_data + 4 * l3->_count))[0] = 0;
    l4 = (igObjectList *)self->_names;
    s6b = ((igObject **)(s4 + (char *)l4->_data - 4))[0];
    if (s6b) { s6b->_refCount = 1 + (int)s6b->_refCount; }
    o = ((igObject **)((char *)l4->_data + a4))[0];
    REL(o)
    if (l4->_count && index >= 0 && index < l4->_count) { ((igObject **)(a4 + (char *)l4->_data))[0] = s6b; }
    l5 = (igObjectList *)self->_names;
    o = ((igObject **)((char *)l5->_data + s4 - 4))[0];
    REL(o)
    if (l5->_count && idx - 1 >= 0 && idx - 1 < l5->_count) { ((igObject **)((char *)(s4 + (int)(igObject **)l5->_data) - 4))[0] = 0; }
    l6 = (igObjectList *)self->_names;
    c2 = l6->_count - 1;
    o = ((igObject **)(l6->_data + 4 * c2))[0];
    REL(o)
    List_RemoveWordAt((igDataList *)l6, c2);
    ((igObject **)(l6->_data + l6->_count * 4))[0] = 0;
}

igPsx2FileView *g_reportOutputFile;

void igReport_SetOutputFile(igPsx2FileView *file) {
    igPsx2FileView *p;

    p = g_reportOutputFile;
    if (p != 0) {
        p->_refCount -= 1;
        if ((p->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(p);
        }
    }
    if (file != 0) {
        file->_refCount += 1;
    }
    g_reportOutputFile = file;
}

igPsx2FileView *g_reportErrorFile;

void igReport_SetErrorFile(igPsx2FileView *file) {
    igPsx2FileView *p;
    int rc;
    p = g_reportErrorFile;
    if (p != 0) {
        rc = p->_refCount - 1;
        p->_refCount = rc;
        if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    if (file != 0) {
        file->_refCount = file->_refCount + 1;
    }
    g_reportErrorFile = file;
}

void igReport_Printf(const char *format, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    igReport_VPrintf(format, (int)((char*)__builtin_next_arg(format) - off));
}

unsigned char g_reportOutputEnabled = 1;
unsigned char g_reportEchoToStdout = 1;

void igReport_VPrintf(const char *format, int args) {
    char buffer[4096];
    int length;

    if ((g_reportOutputFile != 0) && (g_reportOutputEnabled != 0)) {
        length = vsnprintf(&buffer[0], 0x1000, format, (char *)args);
        if ((length < 0) || (length >= 0x1000)) {
            buffer[4095] = 0;
            length = 0x1000;
        }
        g_reportOutputFile->Write(&buffer[0], length, 1);
        if (g_reportEchoToStdout != 0) {
            printf((const char *)&percent_s[0], &buffer[0]);
        }
    } else if (g_reportEchoToStdout != 0) {
        vprintf(format, (va_list)args);
    }
}

int igReport_ErrorPrintf(int format, ...) { 
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    return igReport_VErrorPrintf(format, (int)((char*)__builtin_next_arg(format) - off)); }

unsigned char g_reportErrorOutputEnabled = 1;
unsigned char g_reportEchoToStderr = 1;

int igReport_VErrorPrintf(int format, int args) {
    char buf[4096];
    int length;

    if ((g_reportErrorFile != 0) && (g_reportErrorOutputEnabled != 0)) {
        length = vsnprintf(buf, 0x1000, (const char *)format, (char *)args);
        if ((length < 0) || (length >= 0x1000)) {
            buf[4095] = 0;
            length = 0x1000;
        }
        g_reportErrorFile->Write(buf, length, 1);
        if (g_reportEchoToStderr != 0) {
            fprintf(_impure_ptr->_stderr, (const char *)&percent_s[0], buf);
        }
    } else if (g_reportEchoToStderr != 0) {
        vfprintf(_impure_ptr->_stderr, (const char *)format, (va_list)args);
    }
}

void igReport_Flush(void) {
    if (g_reportOutputFile != 0) {
        g_reportOutputFile->Flush();
    }
    fflush(_impure_ptr->_stdout);
}

void igReport_FlushError(void) {
    if (g_reportErrorFile != 0) {
        g_reportErrorFile->Flush();
    }
    fflush(_impure_ptr->_stderr);
}

void igPluginHelper_AddRepository(igPluginHelper *helper, int name, int location, int locationType) {
    int pool;
    char *text;
    igPluginRepository *target;
    char *old;
    igSmartPointer<igPluginRepository> repository(((igPluginRepository *)igPluginRepository_Create(((int)igObject_GetAllocator((igObject *)helper)))));
    igNamedObject_SetName((igNamedObject *)repository.p, (const char *)name);
    target = repository.p;
    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = (StringPool *)pool;
    }
    text = ((char *)StringPool_Intern((StringPool *)g_stringPool, (const char *)location));
    old = (char *)target->_location;
    if (old != 0) {
        int *header = (int *)(old - 8);
        int count = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
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

const char *g_alchemyRootToken = "$(AlchemyRoot)";
const char *g_applicationRootToken = "$(ApplicationRoot)";

/* Add a plugin repository, recording whether its path is under $(AlchemyRoot) (1),
 * $(ApplicationRoot) (2) or neither (0); a recognised root is stripped from the stored location. */
void igPluginHelper_AddRepositoryFromConfig(igPluginHelper *self, int name, const char *path) {
    static const int alchemyRootLength = strlen(g_alchemyRootToken);
    static const int applicationRootLength = strlen(g_applicationRootToken);
    igSmartPointer<igPluginRepository> repository((igPluginRepository *)igPluginRepository_Create((int)igObject_GetAllocator((igObject *)self)));
    igNamedObject_SetName((igNamedObject *)repository.get(), (const char *)name);
    if (strncmp(path, g_alchemyRootToken, alchemyRootLength) == 0) {
        setRepositoryLocation(repository, path, alchemyRootLength);
        repository.get()->_locationType = 1;
    } else if (strncmp(path, g_applicationRootToken, applicationRootLength) == 0) {
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
    if (g_stringPool == 0) {
        int pool = ((int)StringPool_Allocate(16));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = (StringPool *)pool;
    }
    interned = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)((char *)(path + skip)));
    old = repository->_location;
    if (old != 0) {
        header = (int *)(old - 8);
        left = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = left;
        if (left == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
    repository->_location = interned;
}

static inline void setLocation(const igSmartPointer<igPluginRepository> &ref, char *location) {
    igPluginRepository *repository = ref.p;
    int interned, left;
    int old;
    int *header;
    if (g_stringPool == 0) {
        int pool = ((int)StringPool_Allocate(16));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = (StringPool *)pool;
    }
    interned = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)location);
    old = repository->_location;
    if (old != 0) {
        header = (int *)(old - 8);
        left = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = left;
        if (left == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
    repository->_location = interned;
}

