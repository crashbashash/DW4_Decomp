void igStringMetaField_ReleaseDefaults(int arg0) {
    igStringMetaField_SetDefaultText((int *)arg0, 0);
    igObject_ReleaseDefaults(arg0);
}

/* Post-construction defaults; same two steps. */
void igStringMetaField_InitDefaults(void **self) {
    igObject_InitDefaults((int)self);
    ((igMetaFieldView *)self)->SetDefault(0);
}

void igStringMetaField_ValueFromString(int arg0, int a1, int arg2) {
    int *temp_a1;
    int temp_v0;
    int var_v0;
    void *temp_v1;
    void **arg1;
    void *temp_s0;

    arg1 = (void **)a1;
    if (g_stringPool[0] == 0) {
        var_v0 = ((int)StringPool_Allocate(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg2)));
    temp_v1 = (void *)(*arg1);
    if (temp_v1 != 0) {
        temp_a1 = (int *)((char *)temp_v1 - 8);
        temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
        *(int *)((char *)(temp_v1) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
        }
    }
    *arg1 = temp_s0;
    strlen(arg2);
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
        if (g_stringPool[0] == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool[0] = pool;
        }
        interned = ((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)text));
    }
    token = interned;
    igStringMetaField_AssignRetainedToken(self, object, &token);
    if (token != 0) {
        header = (StringTokenHeader *)token - 1;
        count = header->refCount - 1;
        header->refCount = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)header->owner, (int)header);
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

void igStringMetaField_SetDefaultText(int *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    void **temp_s1;
    void *temp_a0;
    void *temp_s0;

    temp_s1 = (void **)arg0[8];
    if (g_stringPool[0] == 0) {
        var_v0 = ((int)StringPool_Allocate(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg1)));
    temp_a0 = (void *)(*temp_s1);
    if (temp_a0 != 0) {
        temp_a1 = (int *)((char *)temp_a0 - 8);
        temp_v1 = *(int *)((char *)(temp_a0) - 4) - 1;
        *(int *)((char *)(temp_a0) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
        }
    }
    *temp_s1 = temp_s0;
}

int igStringMetaField_GetRawFieldMemSize(igStringMetaField *arg0, int arg1) {
    int temp_a0;
    int var_s0;
    int len;

    if (arg0->_persistent == 0) {
        return 0;
    }
    var_s0 = 0;
    temp_a0 = *(int *)(arg1 + arg0->_offset);
    var_s0 += 4;
    if (temp_a0 != 0) {
        len = strlen(temp_a0) + 1;
        var_s0 += (len + 3) & ~3;
    }
    return var_s0;
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
   igMetaFieldView *d = (igMetaFieldView *)FUN_002c3090();
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

void igStringMetaField_ResetValue(int *arg0, int arg1) {
    char *tok;
    char *t;
    int *h;
    int v;
    int s0 = *(int *)arg0[8];
    int p;
    if (s0 == 0) {
        t = 0;
    } else {
        if (g_stringPool[0] == 0) {
            p = ((int)StringPool_Allocate(16));
            if (p != 0) {
                p = ((int)StringPool_Construct((StringPool *)p));
            }
            g_stringPool[0] = p;
        }
        t = ((char *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)s0));
    }
    tok = t;
    igStringMetaField_AssignRetainedToken(arg0, arg1, &tok);
    if (tok != 0) {
        h = (int *)(tok - 8);
        v = h[1] - 1;
        h[1] = v;
        if (v == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
        }
    }
}

void igStringMetaField_CopyValue(igStringMetaField *arg0, int arg1, int arg2) {
    void *sp1C;
    int *temp_a1;
    int temp_v1;

    sp1C = (void *)(*(int *)(arg2 + arg0->_offset));
    if (sp1C != 0) {
        *(int *)((char *)(sp1C) - 4) = (int)((int) (*(int *)((char *)(sp1C) - 4) + 1));
    }
    igStringMetaField_AssignRetainedToken(arg0, arg1, &sp1C);
    if (sp1C != 0) {
        temp_a1 = (int *)((char *)sp1C - 8);
        temp_v1 = *(int *)((char *)(sp1C) - 4) - 1;
        *(int *)((char *)(sp1C) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
        }
    }
}

void igStringMetaField_ShallowCopy(igStringArrayMetaField *arg0, int arg1, int arg2) {
    void *sp1C;
    int *temp_a1;
    int temp_v1;
    sp1C = (void *)(*(int *)(arg2 + arg0->_offset));
    if (sp1C != 0) {
        *(int *)((char *)(sp1C) - 4) = (int)((int) (*(int *)((char *)(sp1C) - 4) + 1));
    }
    igStringMetaField_AssignRetainedToken(arg0, arg1, &sp1C);
    if (sp1C != 0) {
        temp_a1 = (int *)((char *)sp1C - 8);
        temp_v1 = *(int *)((char *)(sp1C) - 4) - 1;
        *(int *)((char *)(sp1C) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
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
    return strcmp(tokenA, tokenB);
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
                StringChunk_ReleaseHeader((StringChunk *)header->owner, (int)header);
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

void *igStringMetaField_CopyConstruct(void *arg0, void *arg1) {
    igRefMetaField_CopyConstruct((igRefMetaField *)arg0, (igRefMetaField *)arg1);
    *(int *)((char *)(arg0) + 0) = (int)(&g_igStringMetaField_vtable[0]);
    *(unsigned char *)((char *)(arg0) + 56) = (unsigned char) *(unsigned char *)((char *)(arg1) + 56);
    return arg0;
}

void igStringMetaField_Destruct(igStringMetaField *self) {
    igRefMetaField_Destruct((igRefMetaField *)self);
}

void igStringObj_SetN(igStringObj *arg0, int arg1, int arg2) {
    char *temp_s0;

    temp_s0 = (char *)arg0->_buffer;
    if ((arg1 == 0) || (arg2 == 0)) {
        arg0->_buffer = 0;
        arg0->_length = 0;
    } else {
        arg0->_buffer = (int)igObject_AllocateStorage((int)arg0, arg2 + 1);
        memcpy((char *)arg0->_buffer, arg1, arg2);
        *(char *)(arg0->_buffer + arg2) = 0;
        arg0->_length = arg2;
    }
    if (temp_s0 != 0) {
        igObject_FreeMemory((int)arg0, (int)temp_s0);
    }
}

void igStringObj_Set(int arg0, int arg1) {
    if (arg1 != 0) {
        igStringObj_SetN((igStringObj *)arg0, arg1, strlen(arg1));
        return;
    }
    igStringObj_Clear((igStringObj *)arg0);
}

int igStringObj_Clear(igStringObj *arg0) {
    int temp_a1;

    temp_a1 = arg0->_buffer;
    if (temp_a1 != 0) {
        igObject_FreeMemory((int)arg0, temp_a1);
    }
    arg0->_buffer = 0;
    arg0->_length = 0;
}

void igStringObj_Insert(igStringObj *self, char *insert, unsigned int at, unsigned int n) {
    unsigned int total;
    char *buf;
    if (n == 0 || insert == 0) { return; }
    if (self->_length == 0) {
        igStringObj_SetN(self, (int)insert, (int)n);
    } else {
    total = n + self->_length;
    buf = FUN_00300d70(self, total + 1);
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
        igObject_FreeMemory((int)self, self->_buffer);
    }
    self->_buffer = (int)buf;
    self->_length = total;
    }
}

void igStringObj_ToLower(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 8);
    if (temp_a0 != 0) {
        strlwr(temp_a0);
    }
}

int igStringObj_ToInt(void *arg0, int arg1) {
    int var_a0;

    var_a0 = *(int *)((char *)(arg0) + 8);
    if (var_a0 == 0) {
        var_a0 = ((int *)g_stringObjEmptyText)[0];
    }
    return sscanf(var_a0, &DAT_004f9730[0], arg1) == 1;
}

int igStringObj_ToFloat(void *arg0, int arg1) {
    int var_a0;

    var_a0 = *(int *)((char *)(arg0) + 8);
    if (var_a0 == 0) {
        var_a0 = ((int *)g_stringObjEmptyText)[0];
    }
    return sscanf(var_a0, &DAT_004f9738[0], arg1) == 1;
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

void igStringObj_SetInt(int arg0, int arg1, int arg2) {
    igStringObj_Format(arg0, arg2, arg1);
}

void igStringObj_SetFloat(int string, void *format, float value) {
    igStringObj_Format(string, (int)format, value);
}

void igStringObj_SetBool(int arg0, int arg1, int arg2) {
    int *var_a1;
    int *var_a1_2;

    if (arg2 != 0) {
        if (arg1 != 0) {
            var_a1 = (int *)(&TRUE[0]);
        } else {
            var_a1 = (int *)(&FALSE[0]);
        }
        igStringObj_Set(arg0, (int)var_a1);
        return;
    }
    if (arg1 != 0) {
        var_a1_2 = (int *)(&text_true_2[0]);
    } else {
        var_a1_2 = (int *)(&text_false_2[0]);
    }
    igStringObj_Set(arg0, (int)var_a1_2);
}

int igStringObj_Format(int arg0, int arg1, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    return igStringObj_VFormat(arg0, arg1, (int)((char*)__builtin_next_arg(arg1) - off));
}

int igStringObj_VFormat(int arg0, int extra1, int extra2) {
    int buf[512];
    int var_s0;

    var_s0 = vsprintf(buf);
    if (var_s0 > 0x7FF) {
        var_s0 = -1;
    } else {
        igStringObj_SetN((igStringObj *)arg0, (int)buf, var_s0);
    }
    return var_s0;
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
        e = g_stringObjEmptyText[0];
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
            igStringObj_Set((int)p, ((int *)g_stringObjEmptyText)[0]);
        }
    }
}

void igStringObj_StripDirectory(int *arg0) {
    char *p;
    unsigned int a3;
    a3 = arg0[2];
    if (a3 != 0) {
        p = (char *)(a3 + arg0[3]);
        while (--p, a3 < (unsigned int)p) {
            char c = *p;
            if (c == 0x5C || c == 0x2F) {
                igStringObj_Set((int)arg0, (int)(p + 1));
                return;
            }
        }
    }
}

int igStringObj_HasFileExtension(void *arg0, char *arg1) {
    int temp_a0;
    int temp_v0;
    int var_a1;
    char *var_s0;
    unsigned int temp_s2;

    var_s0 = *(char **)((char *)(arg0) + 8);
    temp_s2 = *(int *)((char *)(arg0) + 12);
    if (var_s0 == 0) {
        var_s0 = (char *)DAT_004C22F0[0];
    }
    temp_v0 = strlen(arg1);
    var_a1 = 1;
    if (*arg1 == 0x2E) {
        var_a1 = 0;
    }
    if (temp_s2 < (unsigned int) (temp_v0 + var_a1)) {
        return 0;
    }
    temp_a0 = temp_s2 - temp_v0;
    if (*(var_s0 + (temp_a0 - var_a1)) != 0x2E) {
        return 0;
    }
    temp_v0 = strcasecmp(var_s0 + temp_a0, arg1);
    return temp_v0 == 0;
}

int igStringObj_HasFileExtensionText(char *arg0, char *arg1) {
    unsigned int len = ((unsigned int)strlen(arg0));
    unsigned int slen = ((unsigned int)strlen(arg1));
    int dot = 1;
    int off;
    if (*arg1 == 0x2E) {
        dot = 0;
    }
    if (len < slen + dot) {
        return 0;
    }
    off = len - slen;
    if (arg0[off - dot] != 0x2E) {
        return 0;
    }
    {
        int r = strcasecmp(arg0 + off, arg1);
        return r == 0;
    }
}


int igStringObj_Erase(igStringObj *self, unsigned int pos, unsigned int len) {
    unsigned int end;
    igStringObj *tmp;
    igStringObj *held;

    if (pos > self->_length - 1 || (end = pos + len) > self->_length) {
        return 0;
    }
    *(igStringObj **)&tmp = (igStringObj *)(igStringObj_Create(((int)igObject_GetAllocator((int)self))));
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
        if (g_stringPool[0] == 0) {
            int v = ((int)StringPool_Allocate(0x10));
            if (v != 0) v = ((int)StringPool_Construct((StringPool *)v));
            g_stringPool[0] = v;
        }
        void *ni = ((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)0));
        releaseString((const char *)*slot);
        *slot = ni;
    }
    list->_count = 0;
    if (src->_buffer != 0) {
        char *buf = ((char *)igObject_DuplicateString((int)src, src->_buffer));
        for (unsigned i = 0; i < src->_length; i++) {
            if ((char)delim == buf[i]) buf[i] = 0;
        }
        char *p = buf;
        while (p < buf + src->_length) {
            void *s;
            if (p == 0) s = 0;
            else {
                if (g_stringPool[0] == 0) {
                    int v = ((int)StringPool_Allocate(0x10));
                    if (v != 0) v = ((int)StringPool_Construct((StringPool *)v));
                    g_stringPool[0] = v;
                }
                s = ((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)p));
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

