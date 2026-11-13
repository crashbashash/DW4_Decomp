void Gap__Core__igStringMetaField__vfunc_12(int arg0) {
    igStringMetaField_SetDefaultText((int *)arg0, 0);
    Gap__Core__igObject__vfunc_10(arg0);
}

/* Post-construction defaults; same two steps. */
void igStringMetaField_InitDefaults(void **self) {
    Gap__Core__igObject__vfunc_09((int)self);
    ((igObjectSlot33 *)self)->vfunc_33(0);
}

void Gap__Core__igStringMetaField__vfunc_56(int arg0, int a1, int arg2) {
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
            var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
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
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
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
    StringTokenHeader_30a910 *header;
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
                pool = ((int)StringPool_Construct((S_2eadf0 *)pool));
            }
            g_stringPool[0] = pool;
        }
        interned = ((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)text));
    }
    token = interned;
    igStringMetaField_AssignRetainedToken(self, object, &token);
    if (token != 0) {
        header = (StringTokenHeader_30a910 *)token - 1;
        count = header->refCount - 1;
        header->refCount = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)header->owner, (int)header);
        }
    }
}

/* Output-first retained copy: *output = *sourceCell, taking one more reference on the token. */
void Gap__Core__igStringMetaField__vfunc_57(void **output, void *field, void **sourceCell) {
    void *token;
    StringTokenHeader_30a910 *header;

    *output = *sourceCell;
    token = *output;
    if (token != 0) {
        header = (StringTokenHeader_30a910 *)token - 1;
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
            var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
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
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    *temp_s1 = temp_s0;
}

int Gap__Core__igStringMetaField__vfunc_49(S_30aab0 *arg0, int arg1) {
    int temp_a0;
    int var_s0;
    int len;

    if (arg0->f26 == 0) {
        return 0;
    }
    var_s0 = 0;
    temp_a0 = *(int *)(arg1 + arg0->f8);
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
   Desc *d = (Desc *)FUN_002c3090();
   d->vSwap((int *)cursor, 1);
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
void Gap__Core__igStringMetaField__vfunc_53(void) {

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
                p = ((int)StringPool_Construct((S_2eadf0 *)p));
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
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*h), (int)h);
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
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
}

void Gap__Core__igStringMetaField__vfunc_38(igStringArrayMetaField *arg0, int arg1, int arg2) {
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
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
}

/* Null-aware lexical comparison: two nulls compare equal, null sorts before non-null, otherwise
 * strcmp. */
int Gap__Core__igStringMetaField__vfunc_44(igStringArrayMetaField *self, int objectA, int objectB) {
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
    StringTokenHeader_30a910 *header;
    int count;
    if (self->_destruct != 0) {
        token = 0;
        igStringMetaField_AssignRetainedToken(self, object, &token);
        if (token != 0) {
            header = (StringTokenHeader_30a910 *)token - 1;
            count = header->refCount - 1;
            header->refCount = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)header->owner, (int)header);
            }
        }
    }
}

bool Gap__Core__igStringMetaField__vfunc_45(igStringMetaField *field,const void *one,const void *two){
    int offset=field->_offset;
    const char *left=*(const char **)((const char *)one+offset);
    const char *right=*(const char **)((const char *)two+offset);
    if(left==right)return true;
    if(!left||!right)return false;
    return !bool(strcmp(left,right));
}

bool Gap__Core__igStringMetaField__vfunc_46(igStringMetaField *field,const void *one,const void *two){
    int offset=field->_offset;
    const char *left=*(const char **)((const char *)one+offset);
    const char *right=*(const char **)((const char *)two+offset);
    if(left==right)return true;
    if(!left||!right)return false;
    return !bool(strcmp(left,right));
}

bool Gap__Core__igStringMetaField__vfunc_47(igStringMetaField *field,const void *one,const void *two){
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

void *FUN_0030b2c0(void *arg0, void *arg1) {
    igRefMetaField_CopyConstruct((igRefMetaField *)arg0, (igRefMetaField *)arg1);
    *(int *)((char *)(arg0) + 0) = (int)(&g_igStringMetaField_vtable[0]);
    *(unsigned char *)((char *)(arg0) + 56) = (unsigned char) *(unsigned char *)((char *)(arg1) + 56);
    return arg0;
}

void Gap__Core__igStringMetaField__vfunc_02(void) {
    igRefMetaField_Destruct();
}

void FUN_0030b320(struct S_30b320 *arg0, int arg1, int arg2) {
    char *temp_s0;

    temp_s0 = arg0->f8;
    if ((arg1 == 0) || (arg2 == 0)) {
        arg0->f8 = 0;
        arg0->f12 = 0;
    } else {
        arg0->f8 = (char *)igObject_AllocateStorage((int)arg0, arg2 + 1);
        memcpy(arg0->f8, arg1, arg2);
        arg0->f8[arg2] = 0;
        arg0->f12 = arg2;
    }
    if (temp_s0 != 0) {
        FUN_00300f50((int)arg0, (int)temp_s0);
    }
}

void igStringObj_Set(int arg0, int arg1) {
    if (arg1 != 0) {
        FUN_0030b320((struct S_30b320 *)arg0, arg1, strlen(arg1));
        return;
    }
    igStringObj_Clear((S0_30b420 *)arg0);
}

int igStringObj_Clear(S0_30b420 *arg0) {
    int temp_a1;

    temp_a1 = arg0->f8;
    if (temp_a1 != 0) {
        FUN_00300f50((int)arg0, temp_a1);
    }
    arg0->f8 = 0;
    arg0->fC = 0;
}

void igStringObj_Insert(IniStringView *self, char *insert, unsigned int at, unsigned int n) {
    unsigned int total;
    char *buf;
    if (n == 0 || insert == 0) { return; }
    if (self->length == 0) {
        FUN_0030b320((struct S_30b320 *)self, (int)insert, (int)n);
    } else {
    total = n + self->length;
    buf = FUN_00300d70(self, total + 1);
    if (at >= self->length) {
        memcpy(buf, self->text, self->length);
        memcpy(buf + self->length, insert, n);
        buf[total] = 0;
    } else if (at == 0) {
        memcpy(buf, insert, n);
        memcpy(buf + n, self->text, self->length + 1);
    } else {
        memcpy(buf, self->text, at);
        memcpy(buf + at, insert, n);
        memcpy(buf + (at + n), self->text + at, (self->length - at) + 1);
    }
    if (self->text != 0) {
        FUN_00300f50((int)self, (int)self->text);
    }
    self->text = buf;
    self->length = total;
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

bool FUN_0030b670(O_30b670 *o, char *out) {
    bool r = false;
    if (*o->Str() == 't' || *o->Str() == 'T') {
        *out = 1;
        r = true;
    } else if (*o->Str() == 'f' || *o->Str() == 'F') {
        *out = 0;
        r = true;
    }
    return r;
}

void FUN_0030b720(int arg0, int arg1, int arg2) {
    FUN_0030b7e0(arg0, arg2, arg1);
}

void FUN_0030b770(int arg0, int arg1, int arg2) {
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

int FUN_0030b7e0(int arg0, int arg1, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    return FUN_0030b840(arg0, arg1, (int)((char*)__builtin_next_arg(arg1) - off));
}

int FUN_0030b840(int arg0, int extra1, int extra2) {
    int buf[512];
    int var_s0;

    var_s0 = vsprintf(buf);
    if (var_s0 > 0x7FF) {
        var_s0 = -1;
    } else {
        FUN_0030b320((S_30b320 *)arg0, (int)buf, var_s0);
    }
    return var_s0;
}

static inline char *pick(char *a, char *d) { if (a == 0) { return d; } return a; }

void igStringObj_KeepExtension(O_30b8a0 *o) {
    int i;
    char *e;
    char *t;
    char *base;
    base = o->s;
    if (base != 0) {
        i = o->len - 1;
        e = g_stringObjEmptyText[0];
        for (; i != 0; i--) {
            if (pick(base, e)[i] == '.') {
                t = ((O_30b8a0 *)o)->s; igStringObj_Set((int)o, (int)((t == 0 ? e : t) + i));
                return;
            }
            if (pick(base, e)[i] == '/' || pick(base, e)[i] == '\\') break;
        }
        igStringObj_Set((int)o, (int)e);
    }
}

void FUN_0030b980(struct P_30b980 *p) {
    char *base = p->path;
    char *q;
    if (base != 0) {
        q = base + p->len;
        while (q--, base < q) {
            if (*q == 0x5C || *q == 0x2F) {
                *q = 0;
                igStringObj_Set((int)p, (int)p->path);
                break;
            }
        }
        if (q == p->path) {
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

int FUN_0030ba90(void *arg0, char *arg1) {
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

int FUN_0030bb40(char *arg0, char *arg1) {
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

static inline char *text_30bbf0(Str_30bbf0 *s) { char *t = s->text_30bbf0; if (t == 0) { return g_stringObjEmptyText[0]; } return t; }

int igStringObj_Erase(Str_30bbf0 *self, unsigned int pos, unsigned int len) {
    unsigned int end;
    Str_30bbf0 *tmp;
    Str_30bbf0 *held;

    if (pos > self->length - 1 || (end = pos + len) > self->length) {
        return 0;
    }
    *(Str_30bbf0 **)&tmp = (Str_30bbf0 *)(igStringObj_Create(((int)igObject_GetAllocator((int)self))));
    igStringObj_Set((int)tmp, (int)(self->text_30bbf0 + end));
    igStringObj_Insert((IniStringView *)tmp, self->text_30bbf0, 0, pos);
    igStringObj_Set((int)self, (int)(text_30bbf0(tmp)));
    held = tmp;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(held);
        }
    }
    return 1;
}

void FUN_0030bce0(SrcStr *src, long long delim, List_30bce0 *list) {
    int n = list->count;
    for (int i = 0; i < n; i++) {
        void **slot = (void **)((char *)list->items + i * 4);
        if (g_stringPool[0] == 0) {
            int v = ((int)StringPool_Allocate(0x10));
            if (v != 0) v = ((int)StringPool_Construct((S_2eadf0 *)v));
            g_stringPool[0] = v;
        }
        void *ni = ((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)0));
        Rel_30bce0::go(*slot);
        *slot = ni;
    }
    list->count = 0;
    if (src->f8 != 0) {
        char *buf = ((char *)igObject_DuplicateString((int)src, src->f8));
        for (unsigned i = 0; i < (unsigned)src->f12; i++) {
            if ((char)delim == buf[i]) buf[i] = 0;
        }
        char *p = buf;
        while (p < buf + src->f12) {
            void *s;
            if (p == 0) s = 0;
            else {
                if (g_stringPool[0] == 0) {
                    int v = ((int)StringPool_Allocate(0x10));
                    if (v != 0) v = ((int)StringPool_Construct((S_2eadf0 *)v));
                    g_stringPool[0] = v;
                }
                s = ((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)p));
            }
            void *sp = s;
            StringList_AppendRetained(list, &sp);
            Rel_30bce0::go(sp);
            p += strlen(p) + 1;
        }
        Memory_FreeBuffer(buf);
    }
}

int thunk_strcasecmp(const char *s1, const char *s2)
{
    return strcasecmp(s1, s2);
}

static inline char *text_30bfa0(ShortStr_30bfa0 *s) { char *t = s->text_30bfa0; if (t == 0) { return g_stringObjEmptyText[0]; } return t; }

int FUN_0030bfa0(L_30bfa0 *self, int key, int (*cmp)(char *, int)) {
    int lo;
    int hi;
    int mid;
    int c;

    lo = 0;
    hi = self->count - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        c = cmp(text_30bfa0(self->data[mid]), key);
        if (c < 0) {
            lo = mid + 1;
        } else if (c > 0) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (self->count == 0) {
        return -1;
    }
    if (cmp(text_30bfa0(self->data[lo]), key) == 0) {
        return lo;
    }
    return -1;
}

