void FUN_0032db00(MediaRpcCompletion *c) {
    int headSize;
    int tailSize;
    char *head;
    char *tail;
    int gap;
    int kind = c->kind;
    MediaRpcCompletion *w;
    void (*callback)(int, int);
    int thread;
    switch (kind) {
    case 1:
        headSize = c->u.read.headSize;
        tailSize = c->u.read.tailSize;
        head = c->u.read.head;
        tail = c->u.read.tail;
        memcpy(head, DAT_00587360->buffer, headSize);
        gap = (4 - (int)head) & 3;
        if (gap != 0) {
            memmove(head + headSize, head + headSize + gap, tail - (head + headSize));
        }
        memcpy(tail, DAT_00587360->buffer + headSize, tailSize);
        FUN_0010b858(DAT_00587360->buffer, DAT_00587360->buffer + 128);
        break;
    case 2:
        callback = c->u.wait.callback;
        w = (MediaRpcCompletion *)(int)c;
        thread = w->u.wait.thread;
        if (callback == 0) {
            *w->u.wait.slot = w->u.wait.value;
            iWakeupThread(thread);
        } else {
            callback(thread, w->u.wait.value);
        }
        break;
    }
}

void Gap__Core__igPsx2Media__vfunc_03(O_32dc10 *arg0, int extra1) {
    int i;
    int a;
    T_32dc10 *t;

    Gap__Core__igObject__vfunc_01((int)arg0, extra1);
    arg0->f8 = FUN_00300db0((int)arg0, 0x80, 0x40);
    arg0->f20 = FUN_00300db0((int)arg0, 0x90, 0x10);
    a = arg0->f8;
    FUN_0010b7d8(a, a + 0x80);
    t = ((T_32dc10 *)Memory_AllocateDefaultBuffer(0x10));
    if (t != 0) {
        t->a0 = 8;
        t->a4 = 8;
        t->a2 = 8;
        t->f12 = ((int)FUN_002ed2e0(t->a0, 0xC));
        t->f8 = (short *)FUN_002ed2e0(t->a2, 2);
        for (i = 0; i < t->a4; i++) {
            t->f8[i] = i;
        }
    }
    arg0->f28 = t;
}

void Gap__Core__igPsx2Media__vfunc_04(S0_32dcf0 *arg0) {
    void *temp_s0;

    temp_s0 = (void *)(arg0->f1C);
    if (temp_s0 != 0) {
        Memory_FreeBuffer((void *)(*(int *)((char *)(temp_s0) + 12)));
        Memory_FreeBuffer((void *)(*(int *)((char *)(temp_s0) + 8)));
        Memory_FreeBufferAliasB(temp_s0);
    }
    arg0->f1C = 0;
    ((int *)&DAT_00587360)[0] = 0;
    Gap__Core__igObject__vfunc_02((int)arg0);
}

void Gap__Core__igPsx2Media__vfunc_09(int arg0) {
    Gap__Core__igObject__vfunc_07();
    FUN_002ebdd0(arg0);
}

void FUN_0032ded0(int arg0) {
    if (strncasecmp(arg0, &DAT_004ffd40[0], 5) == 0) {
        GPR_00554de0 = 1;
    } else {
        GPR_00554de0 = 0;
    }
    ((int *)&DAT_00587368)[0] = arg0;
}

unsigned short Gap__Core__igPsx2Media__vfunc_23(Arg_32df20 *self) {
    Pool_32df20 *p;
    unsigned short r;
    self->r->vf31(1);
    p = self->pool;
    if (p->nfree == 0) {
        int i;
        p->items = (char*)thunk_Memory_ReallocateBuffer(p->items, (unsigned int)((p->count + 4) * 12));
        memset(p->items + p->count * 12, 0, 48);
        if (p->cap < 4) {
            p->ids = (unsigned short*)Memory_ReallocateBuffer(p->ids, (unsigned int)8);
            p->cap = 4;
        }
        i = 0; do { p->ids[i] = p->count + i; i++; } while (i < 4);
        p->nfree = 4;
        p->count += 4;
    }
    r = p->ids[p->nfree - 1];
    p->nfree = p->nfree - 1;
    self->r->vf29();
    return r;
}

void Gap__Core__igPsx2Media__vfunc_24(MediaFields *media, int handle) {
    media->sema->wait(1);
    MediaHandlePool *pool = media->pool;
    if (handle < pool->limit && handle >= 0) {
        if (pool->count >= pool->capacity) {
            pool->capacity += 8;
            pool->freeList = (short *)Memory_ReallocateBuffer(pool->freeList, (unsigned int)(pool->capacity * 2));
        }
        pool->freeList[pool->count] = handle;
        pool->count++;
    }
    media->sema->release();
}

static inline void appendPath(const char *text, MediaPathBuffer *buffer) {
    int length = buffer->length;
    igStringObj_Insert((IniStringView *)buffer, (char *)text, (unsigned int)length, (unsigned int)(strlen(text)));
}

void FUN_0032e130(MediaPathFields *self, int index, char **path) {
    bool usePrefix = true;
    bool isDisc = GPR_00554de0;
    char *colon = strchr(*path, ':');
    char *text;
    int prefix;
    int end;
    int i;
    char *interned;
    int stop;
    char *p;
    MediaHandleRow *row;
    int j;
    int v;
    if (colon != 0) {
        prefix = colon - *path;
        for (i = 0; i < 5; i++) {
            char **device = &DAT_004c2650[i];
            if (prefix == strlen(*device) && strncasecmp(*path, *device, prefix) == 0) {
                if (i < 2) {
                    isDisc = true;
                } else {
                    isDisc = false;
                }
                usePrefix = false;
                break;
            }
        }
    }
    if (usePrefix) {
        if (isDisc) {
            igStringObj_Set((int)self->conversion, (int)((*(char * *)&DAT_00587368)));
            if (**path != '\\' && **path != '/') {
                appendPath(DAT_004ffbe8, self->conversion);
            }
            appendPath(*path, self->conversion);
            end = strlen(*path) + 6;
            for (i = 6; i < end; i++) {
                p = self->conversion->text + i;
                if (*p == '/') {
                    *p = '\\';
                } else {
                    *p = ((int)_toupper(*p));
                }
            }
            appendPath(DAT_004ffbf0, self->conversion);
        } else {
            igStringObj_Set((int)self->conversion, (int)((*(char * *)&DAT_00587368)));
            appendPath(*path, self->conversion);
        }
        text = self->conversion->text;
        text = (text == 0) ? (*(char * *)g_stringObjEmptyText) : text;
    } else if (isDisc && strchr(*path, ';') == 0) {
        igStringObj_Set((int)self->conversion, (int)(*path));
        stop = strlen(*path);
        for (j = 6; j < stop; j++) {
            p = self->conversion->text + j;
            if (*p == '/') {
                *p = '\\';
            } else {
                *p = ((int)_toupper(*p));
            }
        }
        appendPath(DAT_004ffbf0, self->conversion);
        text = self->conversion->text;
        text = (text == 0) ? (*(char * *)g_stringObjEmptyText) : text;
    } else {
        text = *path;
    }
    {
        row = &self->handles->rows[index];
        if ((*(int *)g_stringPool) == 0) {
            v = ((int)StringPool_Allocate(16));
            if (v != 0) {
                v = ((int)StringPool_Construct((struct S_2eadf0 *)v));
            }
            (*(int *)g_stringPool) = v;
        }
        interned = ((char *)StringPool_Intern((StringPool *)((*(int *)g_stringPool)), (const char *)text));
        if (row->name != 0) {
            int *hdr = (int *)row->name - 2;
            int r = ((int *)row->name)[-1] - 1;
            ((int *)row->name)[-1] = r;
            if (r == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hdr), (int)hdr);
            }
        }
        row->name = interned;
    }
    igStringObj_Clear((S0_30b420 *)self->conversion);
}

int FUN_0032e950(struct Z_32e950 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    int sp4C;
    int temp_a0;
    struct T_32e950 *temp_s1;
    int *p;
    temp_s1 = arg0->f20;
    p = &temp_s1->f32;
    temp_s1->f0 = *(int *)(arg0->f28->f12 + arg1 * 12 + 8);
    temp_s1->f4 = arg2;
    temp_s1->f8 = arg3;
    temp_s1->f12 = 0;
    temp_s1->f16 = arg5;
    temp_s1->f20 = arg4;
    temp_s1->f24 = arg6;
    temp_s1->f28 = arg7;
    FUN_0010b7d8(arg2, arg2 + arg3);
    temp_a0 = arg0->f8;
    FUN_0010b7d8(temp_a0, temp_a0 + 0x80);
    FUN_0032d6d0(&sp4C, (Ob_32d6d0 *)arg0->f12, 6, (int)temp_s1, 0x20, (int)p, 0x10, 1);
    return *p;
}

void Gap__Core__igPsx2Media__vfunc_29(C_32eac0 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    arg0->f16->v31(1);
    FUN_0032e950((Z_32e950 *)arg0, arg1, arg2, arg3, arg4, 3, arg5, 0);
    arg0->f16->v29();
}

int Gap__Core__igPsx2Media__vfunc_32(void) {
    return 1;
}

