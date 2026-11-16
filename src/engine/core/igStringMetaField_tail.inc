void igStringMetaField_ReleaseDefaults(int self) {
    igStringMetaField_SetDefaultText((int *)self, 0);
    igObject_ReleaseDefaults((igObject *)self);
}

/* Post-construction defaults; same two steps. */
void igStringMetaField_InitDefaults(void **self) {
    igObject_InitDefaults((igObject *)self);
    ((igMetaFieldView *)self)->SetDefault(0);
}

void igStringMetaField_ValueFromString(int self, int objectBase, int text) {
    int *header;
    int refCount;
    int pool;
    void *previous;
    void **slot;
    void *interned;

    slot = (void **)objectBase;
    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = (StringPool *)pool;
    }
    interned = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)text)));
    previous = (void *)(*slot);
    if (previous != 0) {
        header = (int *)((char *)previous - 8);
        refCount = *(int *)((char *)(previous) - 4) - 1;
        *(int *)((char *)(previous) - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
    *slot = interned;
    strlen((const char *)text);
}

/* Interns the text behind *textCell (null stays null), stores the token via
 * igStringMetaField_AssignRetainedToken, then drops the temporary reference. The shared pool is
 * created on first use. */
void igStringMetaField_AssignText(igStringMetaField *self, int object, int *textCell) {
    void *token;
    StringTokenHeader *header;
    int text;
    int count;
    int pool;
    void *interned;

    text = *textCell;
    if (text == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = ((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)text));
    }
    token = interned;
    igStringMetaField_AssignRetainedToken(self, object, &token);
    if (token != 0) {
        header = (StringTokenHeader *)token - 1;
        count = header->refCount - 1;
        header->refCount = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)header->owner, (StringTokenHeader *)header);
        }
    }
}

/* Output-first retained copy: *output = *sourceCell, taking one more reference on the token. */
void igStringMetaField_ValueToString(void **output, void *field, void **sourceCell) {
    void *token;
    StringTokenHeader *header;

    *output = *sourceCell;
    token = *output;
    if (token != 0) {
        header = (StringTokenHeader *)token - 1;
        header->refCount = header->refCount + 1;
    }
}

/* Value storage size: one pointer. */
int igStringMetaField_GetTypeSize(void) {
    return 4;
}

void igStringMetaField_SetDefaultText(int *self, int text) {
    int *header;
    int refCount;
    int pool;
    void **slot;
    void *previous;
    void *interned;

    slot = (void **)self[8];
    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = (StringPool *)pool;
    }
    interned = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)text)));
    previous = (void *)(*slot);
    if (previous != 0) {
        header = (int *)((char *)previous - 8);
        refCount = *(int *)((char *)(previous) - 4) - 1;
        *(int *)((char *)(previous) - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
    *slot = interned;
}

int igStringMetaField_GetRawFieldMemSize(igStringMetaField *self, int object) {
    int text;
    int size;
    int len;

    if (self->_persistent == 0) {
        return 0;
    }
    size = 0;
    text = *(int *)(object + self->_offset);
    size += 4;
    if (text != 0) {
        len = strlen((const char *)text) + 1;
        size += (len + 3) & ~3;
    }
    return size;
}

/* The pool a temporary buffer for a field of `owner` comes from. */
static inline igMemoryPoolView *temporaryPool(void *owner) {
    igMemoryPoolView *pool = igObject_GetAllocator((igObject *)owner);
    return g_useOwnerAllocator != 0 ? pool : (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
}

/* The raw form of a string field: a byte count, then the characters padded to a word. */
struct RawStringValue { int size; char text[4]; };

/* Reads a string written by igStringMetaField_WriteRawValue. Returns the bytes consumed. */
int igStringMetaField_ReadRawValue(void *self, void *value, void *source, int directory, int swap) {
    int consumed = 0;
    igStringRef *string = (igStringRef *)value;
    RawStringValue *raw = (RawStringValue *)source;
    int size = raw->size;
    if (swap != 0) {
        ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(&size, 1);
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
            char *copy = (char *)temporaryPool(self)->Allocate(size + 1);
            memcpy(copy, raw->text, size);
            copy[size] = 0;
            *string = copy;
            temporaryPool(self)->Free(copy);
        }
        consumed += size;
    } else {
        *string = (char *)0;
    }
    return consumed;
}

int igStringMetaField_WriteRawValue(void *self, void *value, void *dst, int a3, int swap) {
 char **v; char *cursor; int size; int len;
 v = (char **)value;
 cursor = (char *)dst;
 if (*v != 0) {
  len = strlen(*v) + 1;
  size = (len + 3) & ~3;
  *(int *)cursor = size;
  if (swap != 0) {
   igMetaFieldView *d = (igMetaFieldView *)igIntMetaField_GetDefaultDescriptor();
   d->SwapBytes((int *)cursor, 1);
  }
  cursor += 4;
  strcpy(cursor, *v);
  cursor += size;
 } else {
  *(int *)cursor = 0;
  cursor += 4;
 }
 return cursor - (char *)dst;
}

/* no-op value hook. */
void igStringMetaField_SwapValue(void) {

}

/* no-op value hook. */
void igStringArrayMetaField_SwapValue(void) {

}

void igStringMetaField_ResetValue(int *self, int object) {
    char *token;
    char *interned;
    int *header;
    int refCount;
    int defaultText = *(int *)self[8];
    int pool;
    if (defaultText == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(16));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = ((char *)StringPool_Intern((StringPool *)g_stringPool, (const char *)defaultText));
    }
    token = interned;
    igStringMetaField_AssignRetainedToken(self, object, &token);
    if (token != 0) {
        header = (int *)(token - 8);
        refCount = header[1] - 1;
        header[1] = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
}

void igStringMetaField_CopyValue(igStringMetaField *self, int destination, int source) {
    void *token;
    int *header;
    int refCount;

    token = (void *)(*(int *)(source + self->_offset));
    if (token != 0) {
        *(int *)((char *)(token) - 4) = (int)((int) (*(int *)((char *)(token) - 4) + 1));
    }
    igStringMetaField_AssignRetainedToken(self, destination, &token);
    if (token != 0) {
        header = (int *)((char *)token - 8);
        refCount = *(int *)((char *)(token) - 4) - 1;
        *(int *)((char *)(token) - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
}

void igStringMetaField_ShallowCopy(igStringArrayMetaField *self, int destination, int source) {
    void *token;
    int *header;
    int refCount;
    token = (void *)(*(int *)(source + self->_offset));
    if (token != 0) {
        *(int *)((char *)(token) - 4) = (int)((int) (*(int *)((char *)(token) - 4) + 1));
    }
    igStringMetaField_AssignRetainedToken(self, destination, &token);
    if (token != 0) {
        header = (int *)((char *)token - 8);
        refCount = *(int *)((char *)(token) - 4) - 1;
        *(int *)((char *)(token) - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
}

/* Null-aware lexical comparison: two nulls compare equal, null sorts before non-null, otherwise
 * strcmp. */
int igStringMetaField_Compare(igStringArrayMetaField *self, int objectA, int objectB) {
    int tokenA;
    int tokenB;
    int offset;

    offset = self->_offset;
    tokenA = *(int *)(objectA + offset);
    tokenB = *(int *)(objectB + offset);
    if (tokenA == 0) {
        return -(tokenB != 0);
    }
    if (tokenB == 0) {
        return 1;
    }
    return strcmp((const char *)tokenA, (const char *)tokenB);
}

void igStringMetaField_ConstructValue(void) {

}

/* When the field is flagged _destruct, assigns a null token to the object's member, which releases
 * the string it held. */
void igStringMetaField_DestructValue(igStringMetaField *self, int object) {
    void *token;
    StringTokenHeader *header;
    int count;
    if (self->_destruct != 0) {
        token = 0;
        igStringMetaField_AssignRetainedToken(self, object, &token);
        if (token != 0) {
            header = (StringTokenHeader *)token - 1;
            count = header->refCount - 1;
            header->refCount = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)header->owner, (StringTokenHeader *)header);
            }
        }
    }
}

bool igStringMetaField_IsAlikeExactly(igStringMetaField *field,const void *one,const void *two){
    int offset=field->_offset;
    const char *left=*(const char **)((const char *)one+offset);
    const char *right=*(const char **)((const char *)two+offset);
    if(left==right)return true;
    if(!left||!right)return false;
    return !bool(strcmp(left,right));
}

bool igStringMetaField_IsAlikeDeep(igStringMetaField *field,const void *one,const void *two){
    int offset=field->_offset;
    const char *left=*(const char **)((const char *)one+offset);
    const char *right=*(const char **)((const char *)two+offset);
    if(left==right)return true;
    if(!left||!right)return false;
    return !bool(strcmp(left,right));
}

bool igStringMetaField_IsAlikeShallow(igStringMetaField *field,const void *one,const void *two){
    int offset=field->_offset;
    const char *left=*(const char **)((const char *)one+offset);
    const char *right=*(const char **)((const char *)two+offset);
    if(left==right)return true;
    if(!left||!right)return false;
    return !bool(strcmp(left,right));
}

void *igStringMetaField_Construct(igStringMetaField *self, int extra1) {
    igRefMetaField_Construct((igRefMetaField *)self);
    self->_vtable = (int)g_igStringMetaField_vtable;
    if (self) {
        igStringMetaField_Init(self);
    }
    return self;
}

void *igStringMetaField_Init(igStringMetaField *self) {
    igRefMetaField_Init((igRefMetaField *)self);
    self->_vtable = (int)g_igStringMetaField_vtable;
    self->_refCounted = 1;
    self->_shallowCopyMethod = 2;
    self->_destruct = 1;
    return self;
}

void *igStringMetaField_CopyConstruct(void *object, void *other) {
    igStringMetaField *self = (igStringMetaField *)object;
    igStringMetaField *source = (igStringMetaField *)other;
    igRefMetaField_CopyConstruct((igRefMetaField *)object, (igRefMetaField *)other);
    self->_vtable = (int)(&g_igStringMetaField_vtable[0]);
    self->_refCounted = source->_refCounted;
    return object;
}

void igStringMetaField_Destruct(igStringMetaField *self) {
    igRefMetaField_Destruct((igRefMetaField *)self);
}

void igStringObj_SetN(igStringObj *self, int text, int length) {
    char *previous;

    previous = (char *)self->_buffer;
    if ((text == 0) || (length == 0)) {
        self->_buffer = 0;
        self->_length = 0;
    } else {
        self->_buffer = (int)igObject_AllocateStorage((igObject *)self, length + 1);
        memcpy((char *)self->_buffer, (void *)text, length);
        *(char *)(self->_buffer + length) = 0;
        self->_length = length;
    }
    if (previous != 0) {
        igObject_FreeMemory((igObject *)self, (void *)previous);
    }
}

void igStringObj_Set(int self, int text) {
    if (text != 0) {
        igStringObj_SetN((igStringObj *)self, text, strlen((const char *)text));
        return;
    }
    igStringObj_Clear((igStringObj *)self);
}

int igStringObj_Clear(igStringObj *self) {
    int buffer;

    buffer = self->_buffer;
    if (buffer != 0) {
        igObject_FreeMemory((igObject *)self, (void *)buffer);
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
    buf = (char *)igObject_AllocateStorage((igObject *)self, total + 1);
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
        igObject_FreeMemory((igObject *)self, (void *)self->_buffer);
    }
    self->_buffer = (int)buf;
    self->_length = total;
    }
}

void igStringObj_ToLower(igStringObj *self) {
    int buffer;

    buffer = self->_buffer;
    if (buffer != 0) {
        strlwr(buffer);
    }
}

int igStringObj_ToInt(void *object, int value) {
    igStringObj *self = (igStringObj *)object;
    int text;

    text = self->_buffer;
    if (text == 0) {
        text = (*(int *)&g_stringObjEmptyText);
    }
    return sscanf((const char *)text, " %i ", value) == 1;
}

int igStringObj_ToFloat(void *object, int value) {
    igStringObj *self = (igStringObj *)object;
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

void igStringObj_SetInt(int self, int value, int format) {
    igStringObj_Format((igStringObj *)self, (const char *)format, value);
}

void igStringObj_SetFloat(int string, void *format, float value) {
    igStringObj_Format((igStringObj *)string, (const char *)format, value);
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
        igStringObj_Set(self, (int)upperText);
        return;
    }
    if (value != 0) {
        lowerText = (int *)("true");
    } else {
        lowerText = (int *)("false");
    }
    igStringObj_Set(self, (int)lowerText);
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
                t = *(char **)&o->_buffer; igStringObj_Set((int)o, (int)((t == 0 ? e : t) + i));
                return;
            }
            if (pick(base, e)[i] == '/' || pick(base, e)[i] == '\\') break;
        }
        igStringObj_Set((int)o, (int)e);
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
                igStringObj_Set((int)p, (int)(char *)p->_buffer);
                break;
            }
        }
        if (q == (char *)p->_buffer) {
            igStringObj_Set((int)p, (*(int *)&g_stringObjEmptyText));
        }
    }
}

void igStringObj_StripDirectory(int *self) {
    char *p;
    unsigned int start;
    start = self[2];
    if (start != 0) {
        p = (char *)(start + self[3]);
        while (--p, start < (unsigned int)p) {
            char c = *p;
            if (c == 0x5C || c == 0x2F) {
                igStringObj_Set((int)self, (int)(p + 1));
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
    *(igStringObj **)&tmp = (igStringObj *)(igStringObj_Create(((int)igObject_GetAllocator((igObject *)self))));
    igStringObj_Set((int)tmp, (int)((char *)self->_buffer + end));
    igStringObj_Insert((igStringObj *)tmp, (char *)self->_buffer, 0, pos);
    igStringObj_Set((int)self, (int)(igStringObj_Text(tmp)));
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
        char *buf = igObject_DuplicateString(src, (const char *)src->_buffer);
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
            StringList_AppendRetained(list, &sp);
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
        copy = igObject_DuplicateString(self, (const char *)self->_buffer);
        n = strlen(copy) - 1;
        while (n >= 0 && (_ctype_[copy[n] + 1] & 8)) {
            copy[n] = 0;
            n -= 1;
        }
        p = copy;
        while (*p != 0 && (_ctype_[*p + 1] & 8)) {
            p += 1;
        }
        igStringObj_Set((int)self, (int)p);
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

