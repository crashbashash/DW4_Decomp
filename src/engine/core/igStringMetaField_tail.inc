namespace Gap {
namespace Core {

void igStringMetaField::releaseDefaults()
{
    setDefault(0);
    igObject::releaseDefaults();
}

/* Post-construction defaults: the root's, then a default slot of its own. */
void igStringMetaField::initDefaults()
{
    igObject::initDefaults();
    setDefaultMemory(0);
}

int igStringMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    igStringRef *string = (igStringRef *)dstMem;

    *string = strVal;
    return strlen(strVal);
}

/* The kit's inline set() is left out of line here (scenegraph's copy is the one retail keeps). */
void igStringMetaField::setFromMemory(igObject *object, const void *fieldStorage)
{
    set(object, *(const char *const *)fieldStorage);
}

igStringRef igStringMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    return *(const igStringRef *)srcMem;
}

/* Value storage size: one pointer. */
unsigned short igStringMetaField::computeSize()
{
    return 4;
}

void igStringMetaField::setDefault(const char *def)
{
    *(igStringRef *)_default = def;
}

int igStringMetaField::getIoSize(const igObject *obj) const
{
    int text;
    int size;
    int len;

    if (_persistent == 0) {
        return 0;
    }
    size = 0;
    text = *(int *)((const char *)obj + _offset);
    size += 4;
    if (text != 0) {
        len = strlen((const char *)text) + 1;
        size += (len + 3) & ~3;
    }
    return size;
}
}
}

/* The pool a temporary buffer for a field of `owner` comes from. */
static inline igMemoryPoolView *temporaryPool(void *owner) {
    igMemoryPoolView *pool = ((Gap::Core::igObject *)owner)->getMemoryPool();
    return g_useOwnerAllocator != 0 ? pool : (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
}

/* The raw form of a string field: a byte count, then the characters padded to a word. */
struct RawStringValue { int size; char text[4]; };

namespace Gap {
namespace Core {

/* Reads a string written by writeRawFieldMemory. Returns the bytes consumed. */
int igStringMetaField::readRawFieldMemory(void *fieldMem, const void *srcMem, igDirectory *dir, bool endianSwap) const
{
    int consumed = 0;
    igStringRef *string = (igStringRef *)fieldMem;
    RawStringValue *raw = (RawStringValue *)srcMem;
    int size = raw->size;
    if (endianSwap) {
        igIntMetaField::getMetaField()->endianSwapMemory(&size, 1);
    }
    consumed += 4;
    if (size > 0) {
        const char *p = raw->text;
        int remaining = size;
        while (remaining && *p) {
            remaining--;
            p++;
        }
        if (remaining != 0) {
            *string = raw->text;
        } else {
            char *copy = (char *)temporaryPool((void *)this)->Allocate(size + 1);
            memcpy(copy, raw->text, size);
            copy[size] = 0;
            *string = copy;
            temporaryPool((void *)this)->Free(copy);
        }
        consumed += size;
    } else {
        *string = (char *)0;
    }
    return consumed;
}

int igStringMetaField::writeRawFieldMemory(const void *fieldMem, void *dstMem, igDirectory *dir, bool endianSwap) const
{
    char *const *v;
    char *cursor;
    int size;
    int len;

    v = (char *const *)fieldMem;
    cursor = (char *)dstMem;
    if (*v != 0) {
        len = strlen(*v) + 1;
        size = (len + 3) & ~3;
        *(int *)cursor = size;
        if (endianSwap) {
            igIntMetaField *d = igIntMetaField::getMetaField();
            d->endianSwapMemory((int *)cursor, 1);
        }
        cursor += 4;
        strcpy(cursor, *v);
        cursor += size;
    } else {
        *(int *)cursor = 0;
        cursor += 4;
    }
    return cursor - (char *)dstMem;
}

/* no-op value hook. */
void igStringMetaField::endianSwapMemory(void *mem, int nElts) const
{
}

/* no-op value hook. */
void igStringMetaField::endianSwap(igObject *obj) const
{
}

void igStringMetaField::resetByValue(igObject *src)
{
    set(src, *(const char **)_default);
}

void igStringMetaField::copyByValue(igObject *dst, const igObject *src)
{
    set(dst, *(const igStringRef *)((const char *)src + _offset));
}

void igStringMetaField::copyByValueShallow(igObject *dst, const igObject *src)
{
    set(dst, *(const igStringRef *)((const char *)src + _offset));
}

/* Null-aware lexical comparison: two nulls compare equal, null sorts before non-null, otherwise
 * strcmp. */
int igStringMetaField::compare(const igObject *obj1, const igObject *obj2) const
{
    int tokenA;
    int tokenB;
    int offset;

    offset = _offset;
    tokenA = *(const int *)((const char *)obj1 + offset);
    tokenB = *(const int *)((const char *)obj2 + offset);
    if (tokenA == 0) {
        return -(tokenB != 0);
    }
    if (tokenB == 0) {
        return 1;
    }
    return strcmp((const char *)tokenA, (const char *)tokenB);
}

void igStringMetaField::construct(igObject *src)
{
}

/* When the field is flagged _destruct, assigns a null token to the object's member, which releases
 * the string it held. */
void igStringMetaField::destruct(igObject *src)
{
    if (_destruct != 0) {
        set(src, igStringRef());
    }
}

bool igStringMetaField::isAlikeCompareExactly(const igObject *obj1, const igObject *obj2) const
{
    int offset = _offset;
    const char *left = *(const char **)((const char *)obj1 + offset);
    const char *right = *(const char **)((const char *)obj2 + offset);

    if (left == right) {
        return true;
    }
    if (!left || !right) {
        return false;
    }
    return !strcmp(left, right);
}

bool igStringMetaField::isAlikeCompareDeep(const igObject *obj1, const igObject *obj2) const
{
    int offset = _offset;
    const char *left = *(const char **)((const char *)obj1 + offset);
    const char *right = *(const char **)((const char *)obj2 + offset);

    if (left == right) {
        return true;
    }
    if (!left || !right) {
        return false;
    }
    return !strcmp(left, right);
}

bool igStringMetaField::isAlikeCompareShallow(const igObject *obj1, const igObject *obj2) const
{
    int offset = _offset;
    const char *left = *(const char **)((const char *)obj1 + offset);
    const char *right = *(const char **)((const char *)obj2 + offset);

    if (left == right) {
        return true;
    }
    if (!left || !right) {
        return false;
    }
    return !strcmp(left, right);
}

igStringMetaField::igStringMetaField(bool boot) : igRefMetaField(boot)
{
    new (this, 0) igStringMetaField;
}

igStringMetaField::igStringMetaField()
{
    _refCounted = 1;
    _shallowCopyMethod = 2;
    _destruct = 1;
}

igStringMetaField::igStringMetaField(const igStringMetaField &other) : igRefMetaField(other)
{
    _refCounted = other._refCounted;
}

void igStringMetaField::__bootstrapDestruct()
{
    igRefMetaField::__bootstrapDestruct();
}
}
}

void igStringObj_SetN(igStringObj *self, int text, int length) {
    char *previous;

    previous = (char *)self->_buffer;
    if ((text == 0) || (length == 0)) {
        self->_buffer = 0;
        self->_length = 0;
    } else {
        self->_buffer = (int)((Gap::Core::igObject *)self)->malloc(length + 1);
        memcpy((char *)self->_buffer, (void *)text, length);
        *(char *)(self->_buffer + length) = 0;
        self->_length = length;
    }
    if (previous != 0) {
        ((Gap::Core::igObject *)self)->free((void *)previous);
    }
}

void igStringObj_Set(igStringObj *self, const char *text) {
    if (text != 0) {
        igStringObj_SetN(self, (int)text, strlen(text));
        return;
    }
    igStringObj_Clear(self);
}

void igStringObj_Clear(igStringObj *self) {
    int buffer;

    buffer = self->_buffer;
    if (buffer != 0) {
        ((Gap::Core::igObject *)self)->free((void *)buffer);
    }
    self->_buffer = 0;
    self->_length = 0;
}

void igStringObj_Insert(igStringObj *self, char *insert, unsigned int at, unsigned int n) {
    unsigned int total;
    char *buf;
    if (n == 0 || insert == 0) { return; }
    if (self->_length == 0) {
        igStringObj_SetN(self, (int)insert, (int)n);
    } else {
    total = n + self->_length;
    buf = (char *)((Gap::Core::igObject *)self)->malloc(total + 1);
    if (at >= self->_length) {
        memcpy(buf, (char *)self->_buffer, self->_length);
        memcpy(buf + self->_length, insert, n);
        buf[total] = 0;
    } else if (at == 0) {
        memcpy(buf, insert, n);
        memcpy(buf + n, (char *)self->_buffer, self->_length + 1);
    } else {
        memcpy(buf, (char *)self->_buffer, at);
        memcpy(buf + at, insert, n);
        memcpy(buf + (at + n), (char *)self->_buffer + at, (self->_length - at) + 1);
    }
    if (self->_buffer != 0) {
        ((Gap::Core::igObject *)self)->free((void *)self->_buffer);
    }
    self->_buffer = (int)buf;
    self->_length = total;
    }
}

void igStringObj_ToLower(igStringObj *self) {
    int buffer;

    buffer = self->_buffer;
    if (buffer != 0) {
        strlwr((char *)buffer);
    }
}

int igStringObj_ToInt(igStringObj *self, int *value) {
    int text;

    text = self->_buffer;
    if (text == 0) {
        text = (*(int *)&g_stringObjEmptyText);
    }
    return sscanf((const char *)text, " %i ", value) == 1;
}

int igStringObj_ToFloat(igStringObj *self, float *value) {
    int text;

    text = self->_buffer;
    if (text == 0) {
        text = (*(int *)&g_stringObjEmptyText);
    }
    return sscanf((const char *)text, " %f ", value) == 1;
}

bool igStringObj_ParseBool(igStringObj *o, char *out) {
    bool r = false;
    if (*igStringObj_Text(o) == 't' || *igStringObj_Text(o) == 'T') {
        *out = 1;
        r = true;
    } else if (*igStringObj_Text(o) == 'f' || *igStringObj_Text(o) == 'F') {
        *out = 0;
        r = true;
    }
    return r;
}

void igStringObj_SetInt(int self, int value, const char *format) {
    igStringObj_Format((igStringObj *)self, format, value);
}

void igStringObj_SetFloat(int string, const char *format, float value) {
    igStringObj_Format((igStringObj *)string, format, value);
}

void igStringObj_SetBool(int self, int value, int upperCase) {
    int *upperText;
    int *lowerText;

    if (upperCase != 0) {
        if (value != 0) {
            upperText = (int *)("TRUE");
        } else {
            upperText = (int *)("FALSE");
        }
        igStringObj_Set((igStringObj *)self, (const char *)upperText);
        return;
    }
    if (value != 0) {
        lowerText = (int *)("true");
    } else {
        lowerText = (int *)("false");
    }
    igStringObj_Set((igStringObj *)self, (const char *)lowerText);
}

int igStringObj_Format(igStringObj *self, const char *format, ...) {
    int usedRegisters = __builtin_args_info(2);
    int offset;
    if (usedRegisters >= 8) offset = 0; else offset = (8 - usedRegisters) * 8;
    return igStringObj_VFormat((int)self, (int)format, (int)((char*)__builtin_next_arg(format) - offset));
}

int igStringObj_VFormat(int self, int format, int args) {
    int buffer[512];
    int length;

    length = vsprintf((char *)buffer, (const char *)format, (va_list)args);
    if (length > 0x7FF) {
        length = -1;
    } else {
        igStringObj_SetN((igStringObj *)self, (int)buffer, length);
    }
    return length;
}

static inline char *pick(char *a, char *d) { if (a == 0) { return d; } return a; }

void igStringObj_KeepExtension(igStringObj *o) {
    int i;
    char *e;
    char *t;
    char *base;
    base = (char *)o->_buffer;
    if (base != 0) {
        i = o->_length - 1;
        e = g_stringObjEmptyText;
        for (; i != 0; i--) {
            if (pick(base, e)[i] == '.') {
                /* read _buffer as a char * word: an int-typed read would be merged with base's load,
                 * and retail loads it again here */
                t = *(char **)&o->_buffer; igStringObj_Set(o, (t == 0 ? e : t) + i);
                return;
            }
            if (pick(base, e)[i] == '/' || pick(base, e)[i] == '\\') break;
        }
        igStringObj_Set(o, e);
    }
}

void igStringObj_RemovePathFilename(igStringObj *p) {
    char *base = (char *)p->_buffer;
    char *q;
    if (base != 0) {
        q = base + p->_length;
        while (q--, base < q) {
            if (*q == 0x5C || *q == 0x2F) {
                *q = 0;
                igStringObj_Set(p, (char *)p->_buffer);
                break;
            }
        }
        if (q == (char *)p->_buffer) {
            igStringObj_Set(p, g_stringObjEmptyText);
        }
    }
}

void igStringObj_StripDirectory(igStringObj *self) {
    char *p;
    unsigned int start;
    start = self->_buffer;
    if (start != 0) {
        p = (char *)(start + self->_length);
        while (--p, start < (unsigned int)p) {
            char c = *p;
            if (c == 0x5C || c == 0x2F) {
                igStringObj_Set(self, p + 1);
                return;
            }
        }
    }
}

int igStringObj_HasFileExtension(igStringObj *self, char *extension) {
    int offset;
    int extensionLength;
    int needsDot;
    char *text;
    unsigned int length;

    text = (char *)self->_buffer;
    length = self->_length;
    if (text == 0) {
        text = g_stringObjEmptyText;
    }
    extensionLength = strlen(extension);
    needsDot = 1;
    if (*extension == 0x2E) {
        needsDot = 0;
    }
    if (length < (unsigned int) (extensionLength + needsDot)) {
        return 0;
    }
    offset = length - extensionLength;
    if (*(text + (offset - needsDot)) != 0x2E) {
        return 0;
    }
    extensionLength = strcasecmp(text + offset, extension);
    return extensionLength == 0;
}

int igStringObj_HasFileExtensionText(char *text, char *extension) {
    unsigned int length = ((unsigned int)strlen(text));
    unsigned int extensionLength = ((unsigned int)strlen(extension));
    int needsDot = 1;
    int offset;
    if (*extension == 0x2E) {
        needsDot = 0;
    }
    if (length < extensionLength + needsDot) {
        return 0;
    }
    offset = length - extensionLength;
    if (text[offset - needsDot] != 0x2E) {
        return 0;
    }
    {
        int result = strcasecmp(text + offset, extension);
        return result == 0;
    }
}

int igStringObj_Erase(igStringObj *self, unsigned int pos, unsigned int len) {
    unsigned int end;
    igStringObj *tmp;
    igStringObj *held;

    if (pos > self->_length - 1 || (end = pos + len) > self->_length) {
        return 0;
    }
    *(igStringObj **)&tmp = (igStringObj *)(igStringObj_Create(((int)((Gap::Core::igObject *)self)->getMemoryPool())));
    igStringObj_Set(tmp, (char *)self->_buffer + end);
    igStringObj_Insert((igStringObj *)tmp, (char *)self->_buffer, 0, pos);
    igStringObj_Set(self, igStringObj_Text(tmp));
    held = tmp;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if (((unsigned long long)((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(held);
        }
    }
    return 1;
}

void igStringObj_Split(igStringObj *src, long long delim, igTDataList<char *> *list) {
    int n = list->_count;
    for (int i = 0; i < n; i++) {
        void **slot = (void **)((char *)list->_data + i * 4);
        if (g_stringPool == 0) {
            int v = ((int)StringPool_Allocate(0x10));
            if (v != 0) v = ((int)StringPool_Construct((StringPool *)v));
            g_stringPool = (StringPool *)v;
        }
        void *ni = ((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)0));
        releaseString((const char *)*slot);
        *slot = ni;
    }
    list->_count = 0;
    if (src->_buffer != 0) {
        char *buf = ((Gap::Core::igObject *)src)->strdup((const char *)src->_buffer);
        for (unsigned i = 0; i < src->_length; i++) {
            if ((char)delim == buf[i]) buf[i] = 0;
        }
        char *p = buf;
        while (p < buf + src->_length) {
            void *s;
            if (p == 0) s = 0;
            else {
                if (g_stringPool == 0) {
                    int v = ((int)StringPool_Allocate(0x10));
                    if (v != 0) v = ((int)StringPool_Construct((StringPool *)v));
                    g_stringPool = (StringPool *)v;
                }
                s = ((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)p));
            }
            void *sp = s;
            StringList_AppendRetained((igStringRefList *)list, (char *const *)&sp);
            releaseString((const char *)sp);
            p += strlen(p) + 1;
        }
        Memory_FreeBuffer(buf);
    }
}

int igStrcasecmp(const char *s1, const char *s2)
{
    return strcasecmp(s1, s2);
}

/* Strips leading and trailing white space (ctype _S) from the string. */
void igStringObj_Trim(igStringObj *self) {
    int n;
    char *copy;
    char *p;
    if (self->_buffer != 0) {
        copy = ((Gap::Core::igObject *)self)->strdup((const char *)self->_buffer);
        n = strlen(copy) - 1;
        while (n >= 0 && (_ctype_[copy[n] + 1] & 8)) {
            copy[n] = 0;
            n -= 1;
        }
        p = copy;
        while (*p != 0 && (_ctype_[*p + 1] & 8)) {
            p += 1;
        }
        igStringObj_Set(self, p);
        Memory_FreeBuffer(copy);
    }
}

int igStringObjList_BinarySearch(igStringObjList *self, int key, int (*cmp)(char *, int)) {
    int lo;
    int hi;
    int mid;
    int c;

    lo = 0;
    hi = self->_count - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        c = cmp(igStringObj_Text(((igStringObj **)self->_data)[mid]), key);
        if (c < 0) {
            lo = mid + 1;
        } else if (c > 0) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (self->_count == 0) {
        return -1;
    }
    if (cmp(igStringObj_Text(((igStringObj **)self->_data)[lo]), key) == 0) {
        return lo;
    }
    return -1;
}

