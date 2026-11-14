void igPsx2Media_RpcCompletionHandler(MediaRpcCompletion *c) {
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
        iSyncDCache(DAT_00587360->buffer, DAT_00587360->buffer + 128);
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

void Gap__Core__igPsx2Media__constructFields(igPsx2MediaView *arg0, int extra1) {
    int i;
    int a;
    MediaHandlePool *t;

    Gap__Core__igObject__constructFields((int)arg0, extra1);
    arg0->_headAndTailBuffer = (char *)igObject_MallocAligned((int)arg0, 0x80, 0x40);
    arg0->_commandBuffer = (MediaIoRequest *)igObject_MallocAligned((int)arg0, 0x90, 0x10);
    a = (int)arg0->_headAndTailBuffer;
    SyncDCache(a, a + 0x80);
    t = ((MediaHandlePool *)Memory_AllocateDefaultBuffer(0x10));
    if (t != 0) {
        t->limit = 8;
        t->count = 8;
        t->capacity = 8;
        t->rows = (MediaHandleRow *)Memory_Callocate(t->limit, 0xC);
        t->freeList = (unsigned short *)Memory_Callocate(t->capacity, 2);
        for (i = 0; i < t->count; i++) {
            t->freeList[i] = i;
        }
    }
    arg0->_handlePool = t;
}

void Gap__Core__igPsx2Media__destructFields(igPsx2MediaView *arg0) {
    MediaHandlePool *temp_s0;

    temp_s0 = arg0->_handlePool;
    if (temp_s0 != 0) {
        Memory_FreeBuffer((void *)temp_s0->rows);
        Memory_FreeBuffer((void *)temp_s0->freeList);
        Memory_FreeBufferAliasB(temp_s0);
    }
    arg0->_handlePool = 0;
    ((int *)&DAT_00587360)[0] = 0;
    Gap__Core__igObject__destructFields((int)arg0);
}

void Gap__Core__igPsx2Media__userConstruct(int arg0) {
    Gap__Core__igObject__userConstruct();
    igMedia_SetDefaultMedia(arg0);
}

void igPsx2Media_SetDevicePrefix(int arg0) {
    if (strncasecmp(arg0, &text_cdrom[0], 5) == 0) {
        GPR_00554de0 = 1;
    } else {
        GPR_00554de0 = 0;
    }
    ((int *)&DAT_00587368)[0] = arg0;
}

unsigned short igPsx2Media_AllocateHandle(igPsx2MediaView *self) {
    MediaHandlePool *p;
    unsigned short r;
    self->_sema->wait(1);
    p = self->_handlePool;
    if (p->count == 0) {
        int i;
        p->rows = (MediaHandleRow *)Memory_ReallocateBufferAlias(p->rows, (unsigned int)((p->limit + 4) * 12));
        memset((char *)p->rows + p->limit * 12, 0, 48);
        if (p->capacity < 4) {
            p->freeList = (unsigned short *)Memory_ReallocateBuffer(p->freeList, (unsigned int)8);
            p->capacity = 4;
        }
        i = 0; do { p->freeList[i] = p->limit + i; i++; } while (i < 4);
        p->count = 4;
        p->limit += 4;
    }
    r = p->freeList[p->count - 1];
    p->count = p->count - 1;
    self->_sema->signal();
    return r;
}

void igPsx2Media_FreeHandle(igPsx2MediaView *media, int handle) {
    media->_sema->wait(1);
    MediaHandlePool *pool = media->_handlePool;
    if (handle < pool->limit && handle >= 0) {
        if (pool->count >= pool->capacity) {
            pool->capacity += 8;
            pool->freeList = (unsigned short *)Memory_ReallocateBuffer(pool->freeList, (unsigned int)(pool->capacity * 2));
        }
        pool->freeList[pool->count] = handle;
        pool->count++;
    }
    media->_sema->signal();
}

static inline void appendPath(const char *text, igStringObj *buffer) {
    int length = buffer->_length;
    igStringObj_Insert(buffer, (char *)text, (unsigned int)length, (unsigned int)(strlen(text)));
}

void igPsx2Media_MakeDevicePath(igPsx2MediaView *self, int index, char **path) {
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
            igStringObj_Set((int)self->_conversionString, (int)((*(char * *)&DAT_00587368)));
            if (**path != '\\' && **path != '/') {
                appendPath(DAT_004ffbe8, self->_conversionString);
            }
            appendPath(*path, self->_conversionString);
            end = strlen(*path) + 6;
            for (i = 6; i < end; i++) {
                p = (char *)self->_conversionString->_buffer + i;
                if (*p == '/') {
                    *p = '\\';
                } else {
                    *p = ((int)_toupper(*p));
                }
            }
            appendPath(DAT_004ffbf0, self->_conversionString);
        } else {
            igStringObj_Set((int)self->_conversionString, (int)((*(char * *)&DAT_00587368)));
            appendPath(*path, self->_conversionString);
        }
        text = (char *)self->_conversionString->_buffer;
        text = (text == 0) ? (*(char * *)g_stringObjEmptyText) : text;
    } else if (isDisc && strchr(*path, ';') == 0) {
        igStringObj_Set((int)self->_conversionString, (int)(*path));
        stop = strlen(*path);
        for (j = 6; j < stop; j++) {
            p = (char *)self->_conversionString->_buffer + j;
            if (*p == '/') {
                *p = '\\';
            } else {
                *p = ((int)_toupper(*p));
            }
        }
        appendPath(DAT_004ffbf0, self->_conversionString);
        text = (char *)self->_conversionString->_buffer;
        text = (text == 0) ? (*(char * *)g_stringObjEmptyText) : text;
    } else {
        text = *path;
    }
    {
        row = &self->_handlePool->rows[index];
        if ((*(int *)g_stringPool) == 0) {
            v = ((int)StringPool_Allocate(16));
            if (v != 0) {
                v = ((int)StringPool_Construct((StringPool *)v));
            }
            (*(int *)g_stringPool) = v;
        }
        interned = ((char *)StringPool_Intern((StringPool *)((*(int *)g_stringPool)), (const char *)text));
        if (row->name != 0) {
            int *hdr = (int *)row->name - 2;
            int r = ((int *)row->name)[-1] - 1;
            ((int *)row->name)[-1] = r;
            if (r == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
            }
        }
        row->name = interned;
    }
    igStringObj_Clear(self->_conversionString);
}

/* Opens handle `slot` of the media on the IOP: names it, sends the open command with the mode's
 * sceOpen flags, and keeps the returned descriptor. */
void igPsx2Media_Open(int *result, igPsx2MediaView *media, int slot, int **name, unsigned int mode)
{
    int *command;
    int flags;
    int *header;
    MediaHandleRow *handle;
    int commandSize;
    char *path;
    int fd;
    int n;
    int *word;

    igResult locked = media->_sema->wait(1);
    int *nameRef;
    handle = &media->_handlePool->rows[slot];
    nameRef = *name;
    if (nameRef != 0) {
        nameRef[-1] = nameRef[-1] + 1;
    }
    igPsx2Media_MakeDevicePath(media, slot, (char **)&nameRef);
    if (nameRef != 0) {
        header = nameRef - 2;
        n = nameRef[-1] - 1;
        nameRef[-1] = n;
        if (n == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (int)header);
        }
    }
    handle->mode = mode;
    path = handle->name;
    n = strlen(path) + 5;
    commandSize = (n + 15) & -16;
    command = (int *)((char *)media->_commandBuffer + 16);
    flags = SCE_RDONLY;
    switch (handle->mode) {
    case 0:
    case 4:
    case 8:
        break;
    case 1:
    case 5:
        flags = SCE_TRUNC | SCE_CREAT | SCE_WRONLY;
        break;
    case 2:
    case 6:
        flags = SCE_CREAT | SCE_APPEND | SCE_WRONLY;
        break;
    case 3:
    case 7:
        flags = SCE_CREAT | SCE_RDWR;
        break;
    }
    *command = flags;
    strcpy((char *)(command + 1), path);
    {
        int *reply = (int *)media->_commandBuffer;
        igResult sent;
        igPsx2IopRpcConnection_Call(&sent.v, media->_connection, 2, (int)command, commandSize, (int)reply, 16, 1);
        fd = *reply;
        handle->fd = fd;
    }
    igResult released = media->_sema->signal();
    if (fd < 0) {
        word = (int *)&g_resultFailure;
    } else {
        word = (int *)&g_resultSuccess;
    }
    *result = *word;
}

int igPsx2Media_SendIoRequest(igPsx2MediaView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    int sp4C;
    int temp_a0;
    MediaIoRequest *temp_s1;
    int *p;
    temp_s1 = arg0->_commandBuffer;
    p = &temp_s1->reply;
    temp_s1->fd = ((MediaHandleRow *)((char *)arg0->_handlePool->rows + arg1 * 12))->fd;
    temp_s1->buffer = arg2;
    temp_s1->size = arg3;
    temp_s1->reserved = 0;
    temp_s1->kind = arg5;
    temp_s1->callback = arg4;
    temp_s1->context = arg6;
    temp_s1->extra = arg7;
    SyncDCache(arg2, arg2 + arg3);
    temp_a0 = (int)arg0->_headAndTailBuffer;
    SyncDCache(temp_a0, temp_a0 + 0x80);
    igPsx2IopRpcConnection_Call(&sp4C, arg0->_connection, 6, (int)temp_s1, 0x20, (int)p, 0x10, 1);
    return *p;
}

void igPsx2Media_ReadAsync(igPsx2MediaView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    arg0->_sema->wait(1);
    igPsx2Media_SendIoRequest(arg0, arg1, arg2, arg3, arg4, 3, arg5, 0);
    arg0->_sema->signal();
}

int Gap__Core__igPsx2Media__vfunc_32(void) {
    return 1;
}

