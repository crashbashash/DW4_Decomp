namespace Gap {
namespace Core {

igMetaField::igMetaField(bool boot) : igObject(boot) {
    _fieldName = 0;
    new (this, 0) igMetaField;
}

/* A fresh field descriptor: every member cleared, the type index -1, persistent, and the comparison
 * selectors 0, 1 and 2. The name is assigned the interned empty string: the shared pool is created
 * on first use, and the previous name (none yet) has its reference dropped. */
igMetaField::igMetaField() {
    int pool;
    void *emptyToken;
    int oldName,refCount;
    int *oldHeader;
    _fieldName=0;
    _offset=0;
    _isRunTime=0;
    _typeIndex=-1;
    _internalIndex=0;
    _size=0;
    _default=0;
    _externalEnumStorage=0;
    if(g_stringPool==0){
        pool=((int)StringPool_Allocate(16));
        if(pool)pool=((int)StringPool_Construct((StringPool *)pool));
        g_stringPool=(StringPool *)pool;
    }
    emptyToken=((char *)StringPool_Intern((StringPool *)g_stringPool, (const char *)0));
    /* Interned strings carry a header in front of the characters: owner chunk at -8, reference
     * count at -4. */
    oldName=_fieldName;
    if(oldName){
        oldHeader=(int *)(oldName-8);
        refCount=*(int *)(oldName-4)-1;
        *(int *)(oldName-4)=refCount;
        if(!refCount)StringChunk_ReleaseHeader((StringChunk *)(*oldHeader), (StringTokenHeader *)oldHeader);
    }
    _fieldName=(int)emptyToken;
    _parentMetaObject=0;
    _invarianceFunction=0;
    _resetMethod=0;
    _shallowCopyMethod=0;
    _deepCopyMethod=0;
    _constructCopyMethod=0;
    _isAlikeExactlyMethod=0;
    _isAlikeDeepMethod=1;
    _isAlikeShallowMethod=2;
    _persistent=1;
}

igMetaField::igMetaField(const igMetaField &other) : igObject(other) {
    int name;
    int refCount;
    int *nameHeader;

    _fieldName = 0;
    _offset = other._offset;
    _isRunTime = other._isRunTime;
    _typeIndex = other._typeIndex;
    _size = other._size;
    _internalIndex = other._internalIndex;
    _externalEnumStorage = other._externalEnumStorage;

    name = other._fieldName;
    if (name) {
        ++*(int *)(name - 4);
    }
    name = _fieldName;
    if (name) {
        nameHeader = (int *)(name - 8);
        refCount = *(int *)(name - 4) - 1;
        *(int *)(name - 4) = refCount;
        if (!refCount) {
            StringChunk_ReleaseHeader((StringChunk *)(*nameHeader), (StringTokenHeader *)nameHeader);
        }
    }
    _fieldName = other._fieldName;

    _parentMetaObject = other._parentMetaObject;
    _invarianceFunction = other._invarianceFunction;
    _resetMethod = other._resetMethod;
    _shallowCopyMethod = other._shallowCopyMethod;
    _deepCopyMethod = other._deepCopyMethod;
    _constructCopyMethod = other._constructCopyMethod;
    _isAlikeExactlyMethod = other._isAlikeExactlyMethod;
    _isAlikeDeepMethod = other._isAlikeDeepMethod;
    _isAlikeShallowMethod = other._isAlikeShallowMethod;
    _persistent = other._persistent;

    _default = (int)malloc(_size);
    memcpy((void *)_default, (void *)other._default, _size);
}

void igMetaField::__bootstrapDestruct() {
    int storage;

    storage = _default;
    if (storage != 0) {
        igObject_FreeStorage((int)(::igMetaField *)this, storage);
    }
    igObject::__bootstrapDestruct();
}

__internalObjectList *igMetaField::getMetaFieldTypes() {
    if ((*(int *)&g_metaFieldList) == 0) {
        (*(int *)&g_metaFieldList) = ((int)InternalObjectList_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
    }
    return g_metaFieldList;
}

int igMetaField::computeRequiredAlignment() {
    return -1;
}

unsigned short igMetaField::computeSize() {
    return 0;
}

/* Interned strings are reference counted in place: the count sits at (string - 4) and the owning
 * StringChunk header at (string - 8); dropping the last reference hands the header back with
 * StringChunk_ReleaseHeader. */
void igMetaField::setBasicProperties(const char *fieldName, igMetaField **externalEnumStorage, int offset, igMetaObject *parentMetaObject) {
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
    setFieldName(&internedName);
    if (internedName != 0) {
        chunkHeader = (int *)((char *)internedName - 8);
        refCount = *(int *)((char *)internedName - 4) - 1;
        *(int *)((char *)internedName - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*chunkHeader), (StringTokenHeader *)chunkHeader);
        }
    }
    _externalEnumStorage = (int)externalEnumStorage;
    _offset = offset;
    _parentMetaObject = (int)parentMetaObject;
    initDefaultMemory();
}

void igMetaField::initDefaultMemory(){
    _size=computeSize();
    if(_default==0)_default=(int)calloc((int)_size, 1);
    else {
        int size=_size;
        if(((int)Memory_GetBufferSize((void *)_default))<size){
            igObject_FreeStorage((int)(::igMetaField *)this, (int)((void *)_default));
            _default=(int)calloc((int)_size, 1);
        }
    }
}

void igMetaField::setDefaultMemory(const void *mem) {
    initDefaultMemory();
    if (mem != 0) {
        memcpy((void *)_default, mem, (int)_size);
    }
}

void igMetaField::setFieldName(void **newName) {
    int *chunkHeader;
    int refCount;
    void *incoming;
    void *previous;

    /* Retain the new name before releasing the old one. */
    incoming = *newName;
    if (incoming != 0) {
        *(int *)((char *)incoming - 4) += 1;
    }
    previous = (void *)_fieldName;
    if (previous != 0) {
        chunkHeader = (int *)((char *)previous - 8);
        refCount = *(int *)((char *)previous - 4) - 1;
        *(int *)((char *)previous - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*chunkHeader), (StringTokenHeader *)chunkHeader);
        }
    }
    _fieldName = (int)*newName;
}

void igMetaField::reset(igObject *src){
    switch(_resetMethod){
    case 0: resetByValue(src); break;
    case 3: resetByNoReset(src); break;
    case 2: resetByReference(src); break;
    }
}

void igMetaField::resetByValue(igObject *src) {
    memcpy((char *)src + _offset, (void *)_default, _size);
}

void igMetaField::resetByReference(igObject *src) {
    memcpy((char *)src + _offset, (void *)_default, _size);
}

/* A reset request leaves the value alone. */
void igMetaField::resetByNoReset(igObject *src) {
}

short igMetaField::getTypeIndex() {
    if (_typeIndex == -1) {
        _typeIndex = getGenericMetaField()->_internalIndex;
    }
    return _typeIndex;
}

igMetaField *igMetaField::_MetaField;

igMetaField *igMetaField::getGenericMetaField() const {
    return _MetaField;
}

void igMetaField::validate(){
    igMetaField *type=getGenericMetaField();
    if(type!=0)_typeIndex=type->_internalIndex;
    else _typeIndex=-1;
    _size=computeSize();
    setDefaultMemory(0);
    if(_externalEnumStorage!=0)*(igMetaField **)_externalEnumStorage=this;
}

/* Rounds size up to a multiple of the field's alignment: (size + a - 1) & ~(a - 1). Reusing the
 * mask local for its complement (m = ~m) orders the temporaries so the nor lands in v0 and the sum
 * in v1. */
int igMetaField::align(int size)
{
    int m = computeRequiredAlignment() - 1;
    int s = size + m;
    m = ~m;
    return m & s;
}

int igMetaField::writeToMemory(const igObject *obj, void *dst, igDirectory *dir, bool endianSwap){
    if(_persistent==0)return 0;
    return (writeRawFieldMemory((const char *)obj+_offset,dst,dir,endianSwap)+3)&~3;
}

int igMetaField::readFromMemoryVersion3(igObject *obj, const void *src, igDirectory *dir, bool endianSwap) {
    int size = readRawFieldMemory((char *)obj + _offset, (const char *)src + 4, dir, endianSwap) + 4;
    return (size + 3) & -4;
}

int igMetaField::readFromMemory(igObject *obj, const void *src, igDirectory *dir, bool endianSwap) {
    return (readRawFieldMemory((char *)obj + _offset, src, dir, endianSwap) + 3) & ~3;
}

int igMetaField::readRawFieldMemory(void *fieldMem, const void *srcMem, igDirectory *dir, bool endianSwap) const {
    memcpy(fieldMem, srcMem, _size);
    if (endianSwap) {
        endianSwapMemory(fieldMem, 1);
    }
    return _size;
}

int igMetaField::writeRawFieldMemory(const void *fieldMem, void *dstMem, igDirectory *dir, bool endianSwap) const {
    memcpy(dstMem, fieldMem, _size);
    if (endianSwap) {
        endianSwapMemory(dstMem, 1);
    }
    return _size;
}

int igMetaField::getIoSize(const igObject *obj) const {
    if (_persistent == 0 || _isRunTime != 0) {
        return 0;
    }
    return (_size + 3) & ~3;
}

void igMetaField::copy(igObject *dst, const igObject *src, int copyMethod) {
    switch (copyMethod) {
    case 0:
        copyByValue(dst, src);
        break;
    case 1:
        copyByReference(dst, src);
        break;
    case 2:
        copyByValueShallow(dst, src);
        break;
    case 3:
        copyByReset(dst, src);
        break;
    case 4:
        copyByNoCopy(dst, src);
        break;
    }
}

void igMetaField::copyShallow(igObject *dst, const igObject *src) {
    copy(dst, src, _shallowCopyMethod);
}

void igMetaField::copyDeep(igObject *dst, const igObject *src) {
    copy(dst, src, _deepCopyMethod);
}
}
}

void igMetaField_ConstructCopy(int a0, int a1, int a2) {
    igMetaField_CopyByTechnique((igMetaFieldView *)a0, a1, a2, ((igMetaField *)a0)->_constructCopyMethod);
}

namespace Gap {
namespace Core {

void igMetaField::copyByValue(igObject *dst, const igObject *src) {
    memcpy((char *)dst + _offset, (const char *)src + _offset, _size);
}

void igMetaField::copyByValueShallow(igObject *dst, const igObject *src) {
    memcpy((char *)dst + _offset, (const char *)src + _offset, _size);
}

void igMetaField::copyByReference(igObject *dst, const igObject *src) {
    memcpy((char *)dst + _offset, (const char *)src + _offset, _size);
}

void igMetaField::copyByReset(igObject *dst, const igObject *src) {
    reset(dst);
}

void igMetaField::copyByNoCopy(igObject *dst, const igObject *src) {
}

int igMetaField::computeTypeSize() {
    return computeSize() & 0xFFFF;
}

igStringRef igMetaField::convertMemoryToString(const void *mem, int num, igDirectory *dir)
{
    int i;
    igStringRef *list;
    int total;
    int cnt;
    char *buf;
    char *p;

    list = (igStringRef *)((char *)malloc(num * 4));
    total = 0;
    cnt = 0;
    for (i = 0; i < num; i++) {
        igStringRef part = getStringFromMemory(mem, dir);
        if (part.p != 0) {
            list[cnt++] = part;
            total += strlen(part.p);
            mem = (const char *)mem + computeTypeSize();
        }
    }
    buf = ((char *)malloc(total + 1));
    p = buf;
    for (i = 0; i < cnt; i++) {
        p += sprintf(p, (const char *)percent_s, list[i].p);
    }
    *p = 0;
    igStringRef result(buf);
    free((void *)list);
    free((void *)buf);
    return result;
}

int igMetaField::convertStringToMemory(const char *val, void *mem, int num, igDirectory *dir) {
    int consumed;
    const char *cursor = val;
    char *element = (char *)mem;
    int i = 0;
    for (; i < num; i++) {
        consumed = setMemoryByString(element, cursor, dir);
        if (consumed != 0) {
            cursor = consumed + cursor;
            element += computeTypeSize();
        } else {
            return 0;
        }
    }
    return cursor - val;
}

int igMetaField::setByString(igObject *obj, const char *val, igDirectory *dir) {
    char *value = (char *)obj + _offset;
    if (value != 0) { return setMemoryByString(value, val, dir); }
    return 0;
}

igStringRef igMetaField::getByString(const igObject *obj, igDirectory *dir)
{
    return getStringFromMemory((const char *)obj + _offset, dir);
}

int igMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir) {
    return strlen(strVal);
}

igStringRef igMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir) {
    return igStringRef((const char *)_fieldName);
}

int igMetaField::addToDirectory(igObject *obj, igDirectory *dir) {
    return -(_persistent == 0);
}

int igMetaField::isAlike(const igObject *obj1, const igObject *obj2, int method) const {
    switch (method) {
    case 0:
        return isAlikeCompareExactly(obj1, obj2);
    case 1:
        return isAlikeCompareDeep(obj1, obj2);
    case 2:
        return isAlikeCompareShallow(obj1, obj2);
    case 3:
        return isAlikeCompareNoCompare(obj1, obj2);
    default:
        return 0;
    }
}

int igMetaField::isAlikeExactly(const igObject *obj1, const igObject *obj2) const {
    return isAlike(obj1, obj2, _isAlikeExactlyMethod);
}

int igMetaField::isAlikeDeep(const igObject *obj1, const igObject *obj2) const {
    return isAlike(obj1, obj2, _isAlikeDeepMethod);
}

int igMetaField::isAlikeShallow(const igObject *obj1, const igObject *obj2) const {
    return isAlike(obj1, obj2, _isAlikeShallowMethod);
}

int igMetaField::isAlikeCompareExactly(const igObject *obj1, const igObject *obj2) const {
    const unsigned char *p1;
    const unsigned char *p2;
    int n;
    int i;
    int offset;
    offset = _offset;
    n = _size;
    p1 = (const unsigned char *)obj1 + offset;
    p2 = (const unsigned char *)obj2 + offset;
    for (i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return 0;
        }
    }
    return 1;
}

int igMetaField::isAlikeCompareDeep(const igObject *obj1, const igObject *obj2) const
{
    return isAlikeCompareExactly(obj1, obj2);
}

int igMetaField::isAlikeCompareShallow(const igObject *obj1, const igObject *obj2) const
{
    return isAlikeCompareExactly(obj1, obj2);
}

int igMetaField::isAlikeCompareNoCompare(const igObject *obj1, const igObject *obj2) const {
    return 1;
}

unsigned char igMetaField::compare(const igObject *obj1, const igObject *obj2) const {
    return (isAlikeExactly(obj1, obj2) != 0) ^ 1;
}

/* A plain field holds no references to visit. */
void igMetaField::traverse(igObject *obj, void *visitFunc, void *traversalData) {
}

void igMetaField::construct(igObject *src)
{
}

void igMetaField::destruct(igObject *src)
{
}

void igMetaField::commission(igObject *src) {
}

void igMetaField::decommission(igObject *src) {
}
}
}

char emptyIndent;

namespace Gap {
namespace Core {

void igMetaField::print(const igObject *src, unsigned int deep, const char *indent) {
    igStringRef text = getStringFromMemory((const char *)src + _offset, 0);
    if (indent == 0) indent = &emptyIndent;
    igReport_Printf("%s%s = %s\n", indent, _fieldName, text.p);
    igReport_Flush();
}

void igMetaField::setFromMemory(igObject *obj, const void *fieldStorage) {
    memcpy((char *)obj + _offset, fieldStorage, _size);
}

void igMetaField::setFromField(igObject *toObject, igMetaField *fromField, igObject *fromObject)
{
    setFromMemory(toObject, (char *)fromObject + fromField->_offset);
}

void igMetaField::endianSwapMemory(void *fieldMem, int nFieldElts) const {
    int size = _size;
    int i;
    int j;
    int half;
    int lo;
    int last;
    unsigned char *a;
    unsigned char *b;
    unsigned char t;
    if (size != 1) {
        for (i = 0, half = size >> 1; i < nFieldElts; i++) {
            lo = i * size;
            last = (i + 1) * size - 1;
            for (j = 0; j < half; j++) {
                a = (unsigned char *)fieldMem + (j + lo);
                b = (unsigned char *)fieldMem + (last - j);
                t = *a;
                *a = *b;
                *b = t;
            }
        }
    }
}

void igMetaField::endianSwap(igObject *obj) const
{
    endianSwapMemory((char *)obj + _offset, 1);
}

void igMetaField::userPostRead() {
    igObject::userPostRead();
    initDefaultMemory();
}

/* Whether constructing a field's value already resets it: a plain field's does not (a reference field
 * answers with its declared `_construct`). */
int igMetaField::constructPerformsReset() const {
    return 0;
}
}
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

static inline igMetaField *cast0(igMetaField *o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Core::igMetaField::getClassMeta()) != 0) { return o; } return 0; }

