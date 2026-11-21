namespace Gap {
namespace Core {

void igObjectRefMetaField::releaseDefaults()
{
    setDefault(0);
    igObject::releaseDefaults();
}

void igObjectRefMetaField::initDefaults()
{
    igObject::initDefaults();
    setDefaultMemory(0);
}

void igObjectRefMetaField::set(igObject *obj, igObject *val) const
{
    ::igObject *value = (::igObject *)val;
    ::igObject *old = *(::igObject **)((char *)obj + _offset);

    if (_refCounted || _destruct) {
        if (value != 0) {
            value->ref();
        }
        if (old != 0) {
        old->release();
    }
    }
    *(::igObject **)((char *)obj + _offset) = value;
}

void igObjectRefMetaField::setFromMemory(igObject *object, const void *fieldStorage)
{
    set(object, *(igObject *const *)fieldStorage);
}

unsigned short igObjectRefMetaField::computeSize()
{
    return 4;
}

void igObjectRefMetaField::setDefault(igObject *val)
{
    ::igObject **slot;
    ::igObject *old;

    slot = (::igObject **)_default;
    igObject::ref(val);
    old = *slot;
    if (old != 0) {
        old->release();
    }
    *slot = (::igObject *)val;
}

int igObjectRefMetaField::readRawFieldMemory(void *fieldMem, const void *srcMem, igDirectory *dir, bool endianSwap) const
{
    int size;
    ::igObject *object;

    size = igRefMetaField::readRawFieldMemory(fieldMem, srcMem, dir, endianSwap);
    if (_refCounted || _destruct) {
        object = *(::igObject **)fieldMem;
        if (object != 0) {
            object->ref();
        }
    }
    return size;
}

void igObjectRefMetaField::construct(igObject *src)
{
    igMemoryPoolView *pool;
    const char *name;
    ::igObject *child;

    if (!_construct) {
        return;
    }
    name = _poolName.p;
    if ((name != 0) && (*name != 0)) {
        pool = (igMemoryPoolView *)Memory_GetAllocatorByName(name);
        if (pool == 0) {
            pool = src->getMemoryPool();
        }
    } else {
        pool = src->getMemoryPool();
    }
    child = (::igObject *)igMetaObject_CreateInstance((igMetaObject *)_metaObject, pool);
    set(src, (igObject *)child);
    if ((_refCounted || _destruct) && (child != 0)) {
        child->release();
    }
}

void igObjectRefMetaField::destruct(igObject *src)
{
    ::igObject *child;

    if (_destruct) {
        child = *(::igObject **)((char *)src + _offset);
        if (child != 0) {
        child->release();
    }
    }
}

void igObjectRefMetaField::decommission(igObject *src)
{
    ::igObject *child;

    if (_refCounted) {
        child = *(::igObject **)((char *)src + _offset);
        if (child != 0) {
        child->release();
    }
    }
    igRefMetaField::decommission(src);
}

void igObjectRefMetaField::resetByValue(igObject *src)
{
    igObject *child;

    child = *(igObject **)((char *)src + _offset);
    if (child != 0) {
        igObject_ResetFields((igObjectDispatchView *)child);
    }
}

void igObjectRefMetaField::resetByReference(igObject *src)
{
    set(src, *(igObject **)_default);
}

void igObjectRefMetaField::copyByReference(igObject *dst, const igObject *src)
{
    set(dst, *(igObject *const *)((const char *)src + _offset));
}

void igObjectRefMetaField::copyByValue(igObject *dst, const igObject *src)
{
    igObject *to;
    igObject *from;
    ::igObject *copy;

    to = *(igObject **)((char *)dst + _offset);
    from = *(igObject *const *)((const char *)src + _offset);
    if (to != 0 || from != 0) {
        if (to != 0 && from != 0) {
            from->trimCapacity();
            to->copyDeep(from);
            return;
        }
        if (to == 0) {
            from->trimCapacity();
            copy = (::igObject *)from->cloneViaMetadata(1);
            set(dst, (igObject *)copy);
            if (_destruct == 0 && copy != 0) {
                copy->release();
            }
        } else if (from == 0) {
            set(dst, 0);
        }
    }
}

void igObjectRefMetaField::copyByValueShallow(igObject *dst, const igObject *src)
{
    igObject *to;
    igObject *from;
    ::igObject *copy;
    int off;

    off = _offset;
    to = *(igObject **)((char *)dst + off);
    from = *(igObject *const *)((const char *)src + off);
    if ((to != 0) || (from != 0)) {
        if ((to != 0) && (from != 0)) {
            to->copyShallow((int)from);
            return;
        }
        if (to == 0) {
            copy = (::igObject *)from->cloneViaMetadata(0);
            set(dst, (igObject *)copy);
            if ((_destruct == 0) && (copy != 0)) {
                copy->release();
            }
        } else if (from == 0) {
            set(dst, 0);
        }
    }
}

void igObjectRefMetaField::copyByReset(igObject *dst, const igObject *src)
{
    igObject *child;

    child = *(igObject **)((char *)dst + _offset);
    if (child != 0) {
        igObject_ResetFields((igObjectDispatchView *)child);
    }
}

/* Prints `<indent><field> = 0x<value>`, then the referenced object's own fields when `depth` asks
 * for them. */
void igObjectRefMetaField::print(const igObject *src, unsigned int deep, const char *indent)
{
    igObject *referenced;

    igReport_Printf("%s%s = 0x%x\n", indent, getFieldName(), *(int *)((char *)src + _offset));
    igReport_Flush();
    if (deep != 0) {
        referenced = *(igObject **)((char *)src + _offset);
        if (referenced != 0) {
            referenced->printFields(deep, (int)indent);
        }
    }
}

void igObjectRefMetaField::traverse(igObject *obj, void *visitFunc, void *traversalData)
{
    igObject *child;

    child = *(igObject **)((char *)obj + _offset);
    if (child != 0) {
        child->traverseFields((Visitor)visitFunc, traversalData);
    }
}

int igObjectRefMetaField::compare(const igObject *obj1, const igObject *obj2) const
{
    int offset;

    offset = _offset;
    return *(const int *)((const char *)obj1 + offset) - *(const int *)((const char *)obj2 + offset);
}

bool igObjectRefMetaField::isAlikeCompareExactly(const igObject *obj1, const igObject *obj2) const
{
    int fieldOffset;
    igObject *refA;
    igObject *refB;

    fieldOffset = _offset;
    refA = *(igObject **)((char *)obj1 + fieldOffset);
    refB = *(igObject **)((char *)obj2 + fieldOffset);
    if (refA == refB) {
        return 1;
    }
    if ((refA == 0) || (refB == 0)) {
        return 0;
    }
    return refA->isAlikeExactly(refB);
}

bool igObjectRefMetaField::isAlikeCompareDeep(const igObject *obj1, const igObject *obj2) const
{
    int fieldOffset;
    igObject *refA;
    igObject *refB;

    fieldOffset = _offset;
    refA = *(igObject **)((char *)obj1 + fieldOffset);
    refB = *(igObject **)((char *)obj2 + fieldOffset);
    if (refA == refB) {
        return 1;
    }
    if ((refA == 0) || (refB == 0)) {
        return 0;
    }
    return refA->isAlikeDeep(refB);
}

bool igObjectRefMetaField::isAlikeCompareShallow(const igObject *obj1, const igObject *obj2) const
{
    int fieldOffset;
    igObject *refA;
    igObject *refB;

    fieldOffset = _offset;
    refA = *(igObject **)((char *)obj1 + fieldOffset);
    refB = *(igObject **)((char *)obj2 + fieldOffset);
    if (refA == refB) {
        return 1;
    }
    if ((refA == 0) || (refB == 0)) {
        return 0;
    }
    return refA->isAlikeShallow(refB);
}

igObjectRefMetaField::igObjectRefMetaField(bool boot) : igRefMetaField(boot)
{
    new (this, 0) igObjectRefMetaField;
}

igObjectRefMetaField::igObjectRefMetaField()
{
    _refCounted = 1;
    _metaObject = 0;
}

igObjectRefMetaField::igObjectRefMetaField(const igObjectRefMetaField &other) : igRefMetaField(other)
{
    _refCounted = other._refCounted;
    _metaObject = other._metaObject;
}

void igObjectRefMetaField::__bootstrapDestruct()
{
    igRefMetaField::__bootstrapDestruct();
}
}
}



void igObjectStringMap_Add(igObjectStringMap *self, const char *name, void *object) {
    igObject *entry;
    igObject *held;

    *(igObject **)&entry = (igObject *)(igNamedObject_Create(((int)((Gap::Core::igObject *)self)->getMemoryPool())));
    igNamedObject_SetName((igNamedObject *)entry, name);
    ((Gap::Core::igObjectList *)self->_names)->append((Gap::Core::igObject *)entry);
    ((Gap::Core::igObjectList *)self->_data)->append((Gap::Core::igObject *)object);
    held = entry;
    igObject::release(held);
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
    igObject *field = ((igObject *)((Gap::Core::igObjectList *)map->_names)->search((Gap::Core::igStringMetaField *)g_propertyNameField, name));
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
        igObject::release(p);
    }
    { int m = l->_count; for (i = 0; i < m; i++) ((igObject **)l->_data)[i] = 0; }
    l->_count = 0;
    l = (igObjectList *)o->_data;
    n = l->_count;
    for (i = 0; i < n; i++) {
        igObject *p = ((igObject **)l->_data)[i];
        igObject::release(p);
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
    igObject::ref(s6);
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
    igObject::ref(s6b);
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
    igSmartPointer<igPluginRepository> repository(((igPluginRepository *)igPluginRepository_Create(((int)((Gap::Core::igObject *)helper)->getMemoryPool()))));
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
    ((Gap::Core::igObjectList *)helper->_repositoryList)->append((Gap::Core::igObject *)repository.p);
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
    igSmartPointer<igPluginRepository> repository((igPluginRepository *)igPluginRepository_Create((int)((Gap::Core::igObject *)self)->getMemoryPool()));
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
    ((Gap::Core::igObjectList *)self->_repositoryList)->append((Gap::Core::igObject *)repository.get());
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

