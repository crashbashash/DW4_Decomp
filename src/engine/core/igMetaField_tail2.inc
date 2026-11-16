void *igMetaField_Construct(igMetaField *self) {
    igObject_ConstructHeader((igObject *)self);
    self->_vtable = (int)g_igMetaField_vtable;
    self->_fieldName = 0;
    if (self) {
        igMetaField_Init(self);
    }
    return self;
}

/* igMetaField_Init: reset a freshly constructed field descriptor to its defaults. Every member
 * starts cleared, the type index is -1, and the descriptor is persistent. The name slot is then
 * given the interned empty token: the shared string pool is created on first use, the previous
 * name token (none for a fresh object) has its reference count dropped, and the pool's token
 * replaces it. */
igMetaField *igMetaField_Init(igMetaField *field){
    int pool;
    void *emptyToken;
    int oldName,refCount;
    int *oldHeader;
    igObject_InitHeader((igObject *)field);
    field->_vtable=(int)g_igMetaField_vtable;
    field->_fieldName=0;
    field->_offset=0;
    field->_isRunTime=0;
    field->_typeIndex=-1;
    field->_internalIndex=0;
    field->_size=0;
    field->_default=0;
    field->_externalEnumStorage=0;
    if(g_stringPool==0){
        pool=((int)StringPool_Allocate(16));
        if(pool)pool=((int)StringPool_Construct((StringPool *)pool));
        g_stringPool=(StringPool *)pool;
    }
    emptyToken=((char *)StringPool_Intern((StringPool *)g_stringPool, (const char *)0));
    /* Interned strings carry a header in front of the characters: owner chunk at -8, reference
     * count at -4. */
    oldName=field->_fieldName;
    if(oldName){
        oldHeader=(int *)(oldName-8);
        refCount=*(int *)(oldName-4)-1;
        *(int *)(oldName-4)=refCount;
        if(!refCount)StringChunk_ReleaseHeader((StringChunk *)(*oldHeader), (StringTokenHeader *)oldHeader);
    }
    field->_fieldName=(int)emptyToken;
    field->_parentMetaObject=0;
    field->_invarianceFunction=0;
    field->_resetMethod=0;
    field->_shallowCopyMethod=0;
    field->_deepCopyMethod=0;
    field->_constructCopyMethod=0;
    field->_isAlikeExactlyMethod=0;
    /* Method selector codes: the three comparison kinds default to 0, 1 and 2. */
    field->_isAlikeDeepMethod=1;
    field->_isAlikeShallowMethod=2;
    field->_persistent=1;
    return field;
}

igMetaField *igMetaField_CopyConstruct(igMetaField *dest, igMetaField *source) {
    int name;
    int refCount;
    int *nameHeader;

    igObject_CopyConstructHeader((igObject *)dest, (igObject *)source);
    dest->_vtable = (int)g_igMetaField_vtable;
    dest->_fieldName = 0;
    dest->_offset = source->_offset;
    dest->_isRunTime = source->_isRunTime;
    dest->_typeIndex = source->_typeIndex;
    dest->_size = source->_size;
    dest->_internalIndex = source->_internalIndex;
    dest->_externalEnumStorage = source->_externalEnumStorage;

    name = source->_fieldName;
    if (name) {
        ++*(int *)(name - 4);
    }
    name = dest->_fieldName;
    if (name) {
        nameHeader = (int *)(name - 8);
        refCount = *(int *)(name - 4) - 1;
        *(int *)(name - 4) = refCount;
        if (!refCount) {
            StringChunk_ReleaseHeader((StringChunk *)(*nameHeader), (StringTokenHeader *)nameHeader);
        }
    }
    dest->_fieldName = source->_fieldName;

    dest->_parentMetaObject = source->_parentMetaObject;
    dest->_invarianceFunction = source->_invarianceFunction;
    dest->_resetMethod = source->_resetMethod;
    dest->_shallowCopyMethod = source->_shallowCopyMethod;
    dest->_deepCopyMethod = source->_deepCopyMethod;
    dest->_constructCopyMethod = source->_constructCopyMethod;
    dest->_isAlikeExactlyMethod = source->_isAlikeExactlyMethod;
    dest->_isAlikeDeepMethod = source->_isAlikeDeepMethod;
    dest->_isAlikeShallowMethod = source->_isAlikeShallowMethod;
    dest->_persistent = source->_persistent;

    dest->_default = (int)((char *)igObject_AllocateStorage((igObject *)dest, dest->_size));
    memcpy((void *)dest->_default, (void *)source->_default, dest->_size);
    return dest;
}

void igMetaField_Destruct(igMetaField *self) {
    int storage;

    storage = self->_default;
    if (storage != 0) {
        igObject_FreeStorage((int)self, storage);
    }
    igObject_Destruct((int)self);
}

__internalObjectList *igMetaField_GetMetaFieldList(void) {
    if ((*(int *)&g_metaFieldList) == 0) {
        (*(int *)&g_metaFieldList) = ((int)InternalObjectList_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
    }
    return g_metaFieldList;
}

/* igMetaField slot +0x6c: a constant leaf returning -1. The receiver is not touched,
 * hence no parameters. */
int igMetaField_GetAlignment(void) {
    return -1;
}

int igMetaField_GetSize(void) {
    return 0;
}

/* Interned strings are reference counted in place: the count sits at (string - 4) and the owning
 * StringChunk header at (string - 8); dropping the last reference hands the header back with
 * StringChunk_ReleaseHeader. */
void igMetaField_Configure(igMetaField *self, const char *fieldName, igMetaField **externalEnumStorage, int offset, igMetaObject *parentMetaObject) {
    void *internedName;
    int *chunkHeader;
    int refCount;
    int pool;
    void *name;

    if (fieldName == 0) {
        name = 0;
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        name = ((char *)StringPool_Intern((StringPool *)g_stringPool, fieldName));
    }
    internedName = name;
    igMetaField_SetFieldName(self, &internedName);
    if (internedName != 0) {
        chunkHeader = (int *)((char *)internedName - 8);
        refCount = *(int *)((char *)internedName - 4) - 1;
        *(int *)((char *)internedName - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*chunkHeader), (StringTokenHeader *)chunkHeader);
        }
    }
    self->_externalEnumStorage = (int)externalEnumStorage;
    self->_offset = offset;
    self->_parentMetaObject = (int)parentMetaObject;
    igMetaField_EnsureDefaultStorage(self);
}

void igMetaField_EnsureDefaultStorage(igMetaField *field){
    field->_size=(unsigned short)((igMetaFieldView *)field)->GetSize();
    if(field->_default==0)field->_default=(int)igObject_Callocate((igObject *)field, (int)field->_size, 1);
    else {
        int size=field->_size;
        if(((int)Memory_GetBufferSize((void *)field->_default))<size){
            igObject_FreeStorage((int)field, (int)((void *)field->_default));
            field->_default=(int)igObject_Callocate((igObject *)field, (int)field->_size, 1);
        }
    }
}

void igMetaField_SetDefault(igMetaField *self, int defaultValue) {
    igMetaField_EnsureDefaultStorage(self);
    if (defaultValue != 0) {
        memcpy((void *)self->_default, (void *)defaultValue, (int)self->_size);
    }
}

void igMetaField_SetFieldName(igMetaField *self, void **newName) {
    int *chunkHeader;
    int refCount;
    void *incoming;
    void *previous;

    /* Retain the new name before releasing the old one. */
    incoming = *newName;
    if (incoming != 0) {
        *(int *)((char *)incoming - 4) += 1;
    }
    previous = (void *)self->_fieldName;
    if (previous != 0) {
        chunkHeader = (int *)((char *)previous - 8);
        refCount = *(int *)((char *)previous - 4) - 1;
        *(int *)((char *)previous - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*chunkHeader), (StringTokenHeader *)chunkHeader);
        }
    }
    self->_fieldName = (int)*newName;
}

void igMetaField_Reset(igMetaField *field,void *object){
    switch(field->_resetMethod){
    case 0: ((igMetaFieldView *)field)->SetToDefault((int)object); break;
    case 3: ((igMetaFieldView *)field)->IgnoreReset((int)object); break;
    case 2: ((igMetaFieldView *)field)->CopyDefaultToValue((int)object); break;
    }
}

void igMetaField_SetToDefault(igMetaField *self, int object) {
    memcpy((void *)(object + self->_offset), (void *)self->_default, self->_size);
}

void igMetaField_CopyDefaultToValue(igMetaField *self, int object) {
    memcpy((void *)(object + self->_offset), (void *)self->_default, self->_size);
}

/* igMetaField reset hook, base implementation: an empty function, so a reset request leaves the
 * value alone. */
void igMetaField_IgnoreReset(void) {
}

short igMetaField_GetTypeIndex(igMetaFieldView *self) {
    if (self->_typeIndex == -1) {
        self->_typeIndex = self->GetDescriptor()->_internalIndex;
    }
    return self->_typeIndex;
}

int g_igMetaField_descriptor;

/* Class-handle getter: returns the cached metaobject pointer in the global, the same global the
 * field constructor reads for a field's `_typeIndex`. */
int igMetaField_GetDescriptor(void) {
    return g_igMetaField_descriptor;
}

void igMetaField_FinalizeDescriptor(igMetaField *field){
    void *type=((igMetaFieldView *)field)->GetDescriptor();
    if(type!=0)field->_typeIndex=((igMetaField *)type)->_internalIndex;
    else field->_typeIndex=-1;
    field->_size=(unsigned short)((igMetaFieldView *)field)->GetSize();
    ((igMetaFieldView *)field)->SetDefault(0);
    if(field->_externalEnumStorage!=0)*(int *)field->_externalEnumStorage=(int)field;
}

/* Rounds size up to a multiple of the field's alignment: (size + a - 1) & ~(a - 1). Reusing the
 * mask local for its complement (m = ~m) orders the temporaries so the nor lands in v0 and the sum
 * in v1. */
int igMetaField_AlignSize(void *p, int size)
{
    int m = ((igMetaFieldView *)p)->GetAlignment() - 1;
    int s = size + m;
    m = ~m;
    return m & s;
}

int igMetaField_WritePersistentValue(igMetaField *field,void *object,void *output,void *context,unsigned char swap){
    if(field->_persistent==0)return 0;
    return (((igMetaFieldView *)field)->WriteRawFieldMem((int)((char *)object+field->_offset),(int)output,(int)context,swap)+3)&~3;
}

int igMetaField_ReadFieldMem(igMetaFieldView *field, char *object, char *data, igIGBFile *file, unsigned char endianSwap) {
    int size = field->ReadRawFieldMem((int)object + field->_offset, (int)data + 4, (int)file, endianSwap) + 4;
    return (size + 3) & -4;
}

int igMetaField_ReadRawFieldMemAligned(igMetaFieldView *field, void *object, char *data, void *directory, unsigned char swap) {
    return (field->ReadRawFieldMem((int)object + field->_offset, (int)data, (int)directory, swap) + 3) & ~3;
}

unsigned short igMetaField_ReadRawFieldMem(igMetaFieldView *self, int value, int buffer, int directory, int swapBytes) {
    memcpy((void *)value, (void *)buffer, self->_size);
    if (swapBytes != 0) {
        self->SwapBytes((void *)value, 1);
    }
    return self->_size;
}

unsigned short igMetaField_WriteRawFieldMem(igMetaFieldView *self, int value, int buffer, int directory, int swapBytes) {
    memcpy((void *)buffer, (void *)value, self->_size);
    if (swapBytes != 0) {
        self->SwapBytes((void *)buffer, 1);
    }
    return self->_size;
}

int igMetaField_GetRawFieldMemSize(igMetaField *self) {
    if (self->_persistent == 0 || self->_isRunTime != 0) {
        return 0;
    }
    return (self->_size + 3) & ~3;
}

void igMetaField_CopyByTechnique(igMetaFieldView *self, int destination, int source, int technique) {
    switch (technique) {
    case 0:
        self->DeepCopy(destination, source);
        break;
    case 1:
        self->CopyReference(destination, source);
        break;
    case 2:
        self->ShallowCopy(destination, source);
        break;
    case 3:
        self->ResetValue(destination, source);
        break;
    case 4:
        self->IgnoreCopy(destination, source);
        break;
    }
}

void igMetaField_ShallowCopy(int a0, int a1, int a2) {
    igMetaField_CopyByTechnique((igMetaFieldView *)a0, a1, a2, ((igMetaFieldView *)a0)->_shallowCopyMethod);
}

void igMetaField_DeepCopy(int a0, int a1, int a2) {
    igMetaField_CopyByTechnique((igMetaFieldView *)a0, a1, a2, ((igMetaFieldView *)a0)->_deepCopyMethod);
}

void igMetaField_ConstructCopy(int a0, int a1, int a2) {
    igMetaField_CopyByTechnique((igMetaFieldView *)a0, a1, a2, ((igMetaFieldView *)a0)->_constructCopyMethod);
}

void igMetaField_DeepCopyValue(void *field, int destination, int source) {
    memcpy((void *)(destination + ((igMetaField *)field)->_offset), (void *)(source + ((igMetaField *)field)->_offset), ((igMetaField *)field)->_size);
}

void igMetaField_ShallowCopyValue(igMetaField *self, int destination, int source) {
    memcpy((void *)(destination + self->_offset), (void *)(source + self->_offset), self->_size);
}

void igMetaField_CopyReference(void *field, int destination, int source) {
    memcpy((void *)(destination + ((igMetaField *)field)->_offset), (void *)(source + ((igMetaField *)field)->_offset), ((igMetaField *)field)->_size);
}

void igMetaField_ResetValue(igMetaField *field, void *object) {
    igMetaField_Reset(field, object);
}

void igMetaField_IgnoreCopy(void) {

}

int igMetaField_GetElementSize(void **self) {
    return ((igMetaFieldView *)(self))->GetSize() & 0xFFFF;
}

igStringRef igMetaField_ArrayToString(igMetaFieldView *self, int value, int count, int directory)
{
    int i;
    igStringRef *list;
    int total;
    int cnt;
    char *buf;
    char *p;

    list = (igStringRef *)((char *)igObject_AllocateStorage((igObject *)self, count * 4));
    total = 0;
    cnt = 0;
    for (i = 0; i < count; i++) {
        igStringRef part = self->ValueToString(value, directory);
        if (part.p != 0) {
            list[cnt++] = part;
            total += strlen(part.p);
            value += self->GetElementSize();
        }
    }
    buf = ((char *)igObject_AllocateStorage((igObject *)self, total + 1));
    p = buf;
    for (i = 0; i < cnt; i++) {
        p += sprintf(p, (const char *)percent_s, list[i].p);
    }
    *p = 0;
    igStringRef result(buf);
    igObject_FreeMemory((igObject *)self, (void *)list);
    igObject_FreeMemory((igObject *)self, (void *)buf);
    return result;
}

int igMetaField_ArrayFromString(igMetaFieldView *self, int text, int value, int count, int directory) {
    int consumed;
    int cursor = text;
    int element = value;
    int i = 0;
    for (; i < count; i++) {
        consumed = self->ValueFromString(element, cursor, directory);
        if (consumed != 0) {
            cursor = consumed + cursor;
            element += self->GetElementSize();
        } else {
            return 0;
        }
    }
    return cursor - text;
}

int igMetaField_FromString(igMetaFieldView *field, int object, int text, int directory) {
    int value = object + field->_offset;
    if (value != 0) { return field->ValueFromString(value, text, directory); }
    return 0;
}

igStringRef igMetaField_ToString(igMetaFieldView *self, char *object, int directory)
{
    return self->ValueToString((int)(object + self->_offset), directory);
}

void igMetaField_ValueFromString(int self, int value, int text) {
    strlen((const char *)text);
}

void igMetaField_ValueToString(int *out, void *field) {
    int name;
    int pool;
    int interned;

    name = ((igMetaField *)field)->_fieldName;
    if (name == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)name);
    }
    *out = interned;
}

int igMetaField_Write(igMetaField *self) {
    return -(self->_persistent == 0);
}

int igMetaField_IsAlikeByTechnique(void **self, int left, int right, int technique) {
    switch (technique) {
    case 0:
        return ((igMetaFieldView *)self)->IsAlikeExactly(left, right);
    case 1:
        return ((igMetaFieldView *)self)->IsAlikeDeep(left, right);
    case 2:
        return ((igMetaFieldView *)self)->IsAlikeShallow(left, right);
    case 3:
        return ((igMetaFieldView *)self)->IsAlikeIgnore(left, right);
    default:
        return 0;
    }
}

int igMetaField_IsAlikeExactly(int self, int left, int right) {
    return igMetaField_IsAlikeByTechnique((void **)self, left, right, ((igMetaField *)self)->_isAlikeExactlyMethod);
}

int igMetaField_IsAlikeDeep(int self, int left, int right) {
    return igMetaField_IsAlikeByTechnique((void **)self, left, right, ((igMetaField *)self)->_isAlikeDeepMethod);
}

int igMetaField_IsAlikeShallow(int self, int left, int right) {
    return igMetaField_IsAlikeByTechnique((void **)self, left, right, ((igMetaField *)self)->_isAlikeShallowMethod);
}

int igMetaField_IsAlikeExactlyValue(igMetaField *self, unsigned char *left, unsigned char *right) {
    unsigned char *p1;
    unsigned char *p2;
    int n;
    int i;
    int offset;
    offset = self->_offset;
    n = self->_size;
    p1 = left + offset;
    p2 = right + offset;
    for (i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return 0;
        }
    }
    return 1;
}

int igMetaField_IsAlikeDeepValue(igMetaFieldView *self, const void *left, const void *right)
{
    return self->IsAlikeExactly((int)left, (int)right);
}

int igMetaField_IsAlikeShallowValue(igMetaFieldView *self, const void *left, const void *right)
{
    return self->IsAlikeExactly((int)left, (int)right);
}

int igMetaField_IsAlikeIgnore(void) {
    return 1;
}

unsigned char igMetaField_Compare(int a0, int a1, int a2, int a3) {
    return (igMetaField_IsAlikeExactly(a0, a1, a2) != 0) ^ 1;
}

/* igMetaField slot +0xa8 (ReleaseElements), base implementation: a plain field owns no elements to
 * release. The memory-ref classes override it. */
void igMetaField_ReleaseElements(void) {
}

void igMetaField_ConstructValue(void)
{
}

void igMetaField_DestructValue(void)
{
}

/* igMetaField slot +0x84 (ZeroValue), base implementation: nothing to zero. igRefMetaField
 * overrides it to clear the reference slot at `instance + _offset`. */
void igMetaField_ZeroValue(void) {
}

/* igMetaField slot +0x88 (ClearValue), base implementation: nothing to clear. igRefMetaField
 * overrides it for its reference slot. */
void igMetaField_ClearValue(void) {
}

char emptyIndent;

void igMetaField_Print(void *self, int object, int unused, const char *indent) {
    igStringRef text = ((igMetaFieldView *)self)->ValueToString(object + ((igMetaField *)self)->_offset, 0);
    if (indent == 0) indent = &emptyIndent;
    igReport_Printf("%s%s = %s\n", indent, ((igMetaField *)self)->_fieldName, text.p);
    igReport_Flush();
}

void igMetaField_SetValue(igMetaField *self, int object, int value) {
    memcpy((void *)(object + self->_offset), (void *)value, self->_size);
}

void igMetaField_SetValueFromField(igMetaFieldView *self, void *object, igMetaFieldView *field, char *source)
{
    self->SetValue((int)object, (int)(source + field->_offset));
}

void igMetaField_SwapBytes(igMetaField *self, unsigned char *values, int count) {
    int size = self->_size;
    int i;
    int j;
    int half;
    int lo;
    int last;
    unsigned char *a;
    unsigned char *b;
    unsigned char t;
    if (size != 1) {
        for (i = 0, half = size >> 1; i < count; i++) {
            lo = i * size;
            last = (i + 1) * size - 1;
            for (j = 0; j < half; j++) {
                a = values + (j + lo);
                b = values + (last - j);
                t = *a;
                *a = *b;
                *b = t;
            }
        }
    }
}

void igMetaField_SwapValue(igMetaFieldView *self, char *object)
{
    self->SwapBytes(object + self->_offset, 1);
}

void igMetaField_UserPostRead(int self) {
    igObject_UserPostRead();
    igMetaField_EnsureDefaultStorage((igMetaField *)self);
}

/* igMetaField slot +0xf0 (IsConstruct): whether the field's value is built by the field itself.
 * The base returns 0, so the generic object initialiser constructs a plain field's value;
 * igRefMetaField returns its declared `_construct` (+0x34) instead. */
int igMetaField_IsConstruct(void) {
    return 0;
}

char *g_metaFieldNamePrefix = "__MF_";
char *g_metaFieldScopeSeparator = "::";

int igMetaField_GetMangledName(igMetaField *self, void **pool) {
    int fieldName;
    int prefixLength;
    int withField;
    int withSeparator;
    int className;
    int mangled;
    int result;

    mangled = 0;
    if (self != 0) {
        result = 0;
        if (pool != 0) {
            fieldName = self->_fieldName;
            className = ((igMetaObject *)self->_parentMetaObject)->_name;
            prefixLength = strlen(g_metaFieldNamePrefix);
            withField = prefixLength + strlen((const char *)fieldName);
            withSeparator = strlen(g_metaFieldScopeSeparator);
            withSeparator = withSeparator + withField;
            mangled = strlen((const char *)className);
            mangled = (int)((igMemoryPoolView *)(pool))->Allocate(mangled + withSeparator + 1);
            strcpy((char *)mangled, g_metaFieldNamePrefix);
            strcat((char *)mangled, (const char *)className);
            strcat((char *)mangled, g_metaFieldScopeSeparator);
            strcat((char *)mangled, (const char *)fieldName);
            goto done;
        }
    } else {
done:
        result = mangled;
    }
    return result;
}

static inline igMetaField *cast0(igMetaField *o) { if (o != 0 && igObject_IsKindOf((void *)o, (igMetaObject *)g_igMetaField_metaObject) != 0) { return o; } return 0; }

