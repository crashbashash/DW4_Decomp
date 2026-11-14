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
        headSize = c->request.read.headSize;
        tailSize = c->request.read.tailSize;
        head = c->request.read.head;
        tail = c->request.read.tail;
        memcpy(head, g_igPsx2Media_rpcBuffer->buffer, headSize);
        gap = (4 - (int)head) & 3;
        if (gap != 0) {
            memmove(head + headSize, head + headSize + gap, tail - (head + headSize));
        }
        memcpy(tail, g_igPsx2Media_rpcBuffer->buffer + headSize, tailSize);
        iSyncDCache(g_igPsx2Media_rpcBuffer->buffer, g_igPsx2Media_rpcBuffer->buffer + 128);
        break;
    case 2:
        callback = c->request.wait.callback;
        w = (MediaRpcCompletion *)(int)c;
        thread = w->request.wait.thread;
        if (callback == 0) {
            *w->request.wait.slot = w->request.wait.value;
            iWakeupThread(thread);
        } else {
            callback(thread, w->request.wait.value);
        }
        break;
    }
}

void Gap__Core__igPsx2Media__constructFields(igPsx2MediaView *self, int extra1) {
    int i;
    int buffer;
    MediaHandlePool *pool;

    Gap__Core__igObject__constructFields((int)self, extra1);
    self->_headAndTailBuffer = (char *)igObject_MallocAligned((int)self, 0x80, 0x40);
    self->_commandBuffer = (MediaIoRequest *)igObject_MallocAligned((int)self, 0x90, 0x10);
    buffer = (int)self->_headAndTailBuffer;
    SyncDCache(buffer, buffer + 0x80);
    pool = ((MediaHandlePool *)Memory_AllocateDefaultBuffer(0x10));
    if (pool != 0) {
        pool->limit = 8;
        pool->count = 8;
        pool->capacity = 8;
        pool->rows = (MediaHandleRow *)Memory_Callocate(pool->limit, 0xC);
        pool->freeList = (unsigned short *)Memory_Callocate(pool->capacity, 2);
        for (i = 0; i < pool->count; i++) {
            pool->freeList[i] = i;
        }
    }
    self->_handlePool = pool;
}

void Gap__Core__igPsx2Media__destructFields(igPsx2MediaView *self) {
    MediaHandlePool *pool;

    pool = self->_handlePool;
    if (pool != 0) {
        Memory_FreeBuffer((void *)pool->rows);
        Memory_FreeBuffer((void *)pool->freeList);
        Memory_FreeBufferAliasB(pool);
    }
    self->_handlePool = 0;
    ((int *)&g_igPsx2Media_rpcBuffer)[0] = 0;
    Gap__Core__igObject__destructFields((int)self);
}

void Gap__Core__igPsx2Media__userConstruct(int self) {
    Gap__Core__igObject__userConstruct();
    igMedia_SetDefaultMedia(self);
}

/* Loads the sound and igFileIO IOP modules, binds the file RPC server, hooks the SIF completion
 * handler and picks the host or cdrom device prefix. */
void Gap__Core__igPsx2Media__resetFields(igPsx2MediaView *self, int extra1) {
    Gap__Core__igObject__resetFields((int)self, extra1);
    if (igPsx2_LoadIopModule((char *)text_libsd_irx, 1, 0, 0) != g_resultSuccess) {
        return;
    }
    if (igPsx2_LoadIopModule((char *)text_igFileIO_irx, 2, 0, 0) != g_resultSuccess) {
        return;
    }
    self->_initialized = 1;
    igPsx2IopRpcConnection_Bind(self->_connection, 0x12114);
    igPsx2IopRpcConnection_CallWithData(self->_connection, 19, (int)self->_headAndTailBuffer, 0, 0);
    DIntr();
    sceSifAddCmdHandler(4, (void *)igPsx2Media_RpcCompletionHandler, 0);
    EIntr();
    g_igPsx2Media_rpcBuffer = (MediaRpcShared *)self;
    self->_sema->create();
    if (g_igPsx2_useCdrom[0] == 0) {
        g_igPsx2Media_prefixIsCdrom = 0;
        if (g_igPsx2Media_devicePrefix == 0) {
            g_igPsx2Media_devicePrefix = text_host0;
        }
    } else {
        g_igPsx2Media_prefixIsCdrom = 1;
        g_igPsx2Media_devicePrefix = (int *)text_cdrom0;
    }
}

void igPsx2Media_SetDevicePrefix(int prefix) {
    if (strncasecmp(prefix, &text_cdrom[0], 5) == 0) {
        g_igPsx2Media_prefixIsCdrom = 1;
    } else {
        g_igPsx2Media_prefixIsCdrom = 0;
    }
    ((int *)&g_igPsx2Media_devicePrefix)[0] = prefix;
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
    bool isDisc = g_igPsx2Media_prefixIsCdrom;
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
    int pool;
    if (colon != 0) {
        prefix = colon - *path;
        for (i = 0; i < 5; i++) {
            char **device = &g_igPsx2Media_deviceNames[i];
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
            igStringObj_Set((int)self->_conversionString, (int)((*(char * *)&g_igPsx2Media_devicePrefix)));
            if (**path != '\\' && **path != '/') {
                appendPath(text_backslash, self->_conversionString);
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
            appendPath(text_semicolon_1, self->_conversionString);
        } else {
            igStringObj_Set((int)self->_conversionString, (int)((*(char * *)&g_igPsx2Media_devicePrefix)));
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
        appendPath(text_semicolon_1, self->_conversionString);
        text = (char *)self->_conversionString->_buffer;
        text = (text == 0) ? (*(char * *)g_stringObjEmptyText) : text;
    } else {
        text = *path;
    }
    {
        row = &self->_handlePool->rows[index];
        if ((*(int *)g_stringPool) == 0) {
            pool = ((int)StringPool_Allocate(16));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            (*(int *)g_stringPool) = pool;
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
    strcpy((char *)&command[1], path);
    {
        int *reply = (int *)media->_commandBuffer;
        igResult sent = igPsx2IopRpcConnection_Call(media->_connection, 2, (int)command, commandSize, (int)reply, 16, 1);
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

/* Closes the IOP descriptor of handle `slot`. */
void igPsx2Media_Close(igPsx2MediaView *self, int slot) {
    int reply;
    self->_sema->wait(1);
    igPsx2IopRpcConnection_CallWithData(self->_connection, 3, ((MediaHandleRow *)((char *)self->_handlePool->rows + slot * 12))->fd, &reply, 1);
    self->_sema->signal();
}

/* Writes `size` bytes from `data` to handle `slot`. A buffer that is not 64-byte aligned is staged
 * through the 0x8000-byte write buffer chunk by chunk; returns the bytes written or the IOP's
 * negative error. */
int igPsx2Media_Write(igPsx2MediaView *self, int slot, char *data, int size) {
    int written;
    MediaIoRequest *request;
    int *reply;
    int result;
    int row;
    int left;
    int chunk;
    self->_sema->wait(1);
    request = self->_commandBuffer;
    reply = &request->kind;
    if ((int)data & 0x3F) {
        if (self->_writeBuffer == 0) {
            self->_writeBuffer = (char *)igObject_MallocAligned((int)self, 0x8000, 0x40);
        }
        row = slot * 3 * 4;
        left = size;
        while (left != 0) {
            chunk = 0x8000;
            if (left < 0x8001) {
                chunk = left;
            }
            memcpy(self->_writeBuffer, data, chunk);
            request->fd = ((MediaHandleRow *)((char *)self->_handlePool->rows + row))->fd;
            request->buffer = (int)self->_writeBuffer;
            request->size = chunk;
            request->reserved = 0;
            SyncDCache(self->_writeBuffer, self->_writeBuffer + chunk);
            igPsx2IopRpcConnection_Call(self->_connection, 7, (int)request, 0x10, (int)reply, 0x10, 1);
            written = *reply;
            if (written != chunk) {
                if (written < 0) {
                    self->_sema->signal();
                    return *reply;
                }
                self->_sema->signal();
                return *reply + (size - left);
            }
            left -= chunk;
            data += chunk;
        }
        self->_sema->signal();
        return size;
    }
    request->fd = ((MediaHandleRow *)((char *)self->_handlePool->rows + slot * 12))->fd;
    request->buffer = (int)data;
    request->size = size;
    request->reserved = 0;
    SyncDCache(data, data + size);
    igPsx2IopRpcConnection_Call(self->_connection, 7, (int)request, 0x10, (int)reply, 0x10, 1);
    result = *reply;
    self->_sema->signal();
    return result;
}

int igPsx2Media_SendIoRequest(igPsx2MediaView *self, int handle, int buffer, int size, int callback, int kind, int context, int *extra) {
    int headAndTail;
    MediaIoRequest *request;
    int *p;
    request = self->_commandBuffer;
    p = &request->reply;
    request->fd = ((MediaHandleRow *)((char *)self->_handlePool->rows + handle * 12))->fd;
    request->buffer = buffer;
    request->size = size;
    request->reserved = 0;
    request->kind = kind;
    request->callback = callback;
    request->context = context;
    request->extra = (int)extra;
    SyncDCache(buffer, buffer + size);
    headAndTail = (int)self->_headAndTailBuffer;
    SyncDCache(headAndTail, headAndTail + 0x80);
    igPsx2IopRpcConnection_Call(self->_connection, 6, (int)request, 0x20, (int)p, 0x10, 1);
    return *p;
}

/* Reads `size` bytes of handle `slot` into `buffer`, sleeping until the completion handler wakes
 * this thread; returns the byte count the IOP reported. */
int igPsx2Media_Read(igPsx2MediaView *self, int slot, int buffer, int size) {
    int done;
    self->_sema->wait(1);
    done = 0;
    igPsx2Media_SendIoRequest(self, slot, buffer, size, 0, 3, GetThreadId(), &done);
    self->_sema->signal();
    SleepThread();
    return done;
}

void igPsx2Media_ReadAsync(igPsx2MediaView *self, int handle, int buffer, int size, int callback, int context) {
    self->_sema->wait(1);
    igPsx2Media_SendIoRequest(self, handle, buffer, size, callback, 3, context, 0);
    self->_sema->signal();
}

/* Moves handle `slot`'s file position (lseek `whence`); returns 0 or -1. */
int igPsx2Media_Seek(igPsx2MediaView *self, int slot, int offset, int whence) {
    int *request;
    int *reply;
    int position;
    self->_sema->wait(1);
    request = (int *)self->_commandBuffer;
    reply = request + 4;
    request[0] = ((MediaHandleRow *)((char *)self->_handlePool->rows + slot * 12))->fd;
    request[1] = offset;
    request[2] = whence;
    igPsx2IopRpcConnection_Call(self->_connection, 4, (int)request, 16, (int)reply, 16, 1);
    position = *reply;
    self->_sema->signal();
    return -(position < 0);
}

/* Returns handle `slot`'s file position (an lseek of 0 from the current position). */
int igPsx2Media_Tell(igPsx2MediaView *self, int slot) {
    MediaIoRequest *request;
    self->_sema->wait(1);
    request = self->_commandBuffer;
    request->fd = ((MediaHandleRow *)((char *)self->_handlePool->rows + slot * 12))->fd;
    request->buffer = 0;
    request->size = 1;
    slot = (int)&request->kind;
    igPsx2IopRpcConnection_Call(self->_connection, 4, (int)request, 16, slot, 16, 1);
    slot = *(int *)slot;
    self->_sema->signal();
    return slot;
}

int Gap__Core__igPsx2Media__vfunc_32(void) {
    return 1;
}

