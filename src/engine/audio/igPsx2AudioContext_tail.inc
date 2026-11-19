void Gap__igPsx2AudioContext__vfunc_23(ContextView *arg0, int arg1) {
    if (arg0->f8 == 0 && arg1 == 1) {
        ((DW4VC_184_0 *)(arg0))->vX();
    }
    arg0->f8 = (unsigned char) (arg1 == 1);
}

void igPsx2AudioContext_InitDefaults(igPsx2AudioContext *self) {
    igMemoryPoolView *allocator = igObject_GetAllocator((igObject *)self);
    g_audioTableOwner.release();
    g_audioTableOwner.p = (igPsx2AudioSourceList *)igPsx2AudioSourceList_Create(allocator);
}

void FUN_00143800(AudioVoiceHandle *h)
{
    ((AudioVoiceTable *)g_audioTableOwner.p)->entries[h->voice].active = 0;
}

int g_pendingIopCallbackValue;
AudioThread *g_streamingSemaphore;

void FUN_00143840(void *arg0) {
    DW4SR4 sp1C;

    g_pendingIopCallbackValue = *(int *)((char *)(arg0) + 12) | 0x20000000;
    sp1C = ((DW4VCSR_128_0 *)(g_streamingSemaphore))->vX();
}

void FUN_00143880(int (*arg0)(int)) {
    DW4SR4 sp2C;

loop_1:
    sp2C = ((DW4VCSR_132_1 *)(g_streamingSemaphore))->vX((int)(1));
    arg0(g_pendingIopCallbackValue);
    goto loop_1;
}

void Gap__igPsx2AudioContext__vfunc_25(igPsx2AudioContext *context) {
    igObject *connection;

    if (context->_connection != 0) {
        igPsx2IopRpcConnection_CallNoData((igPsx2IopRpcConnectionView *)context->_connection, 0x30000, 1);
        connection = (igObject *)context->_connection;
        if (connection != 0) {
            connection->_refCount = connection->_refCount - 1;
            if ((connection->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(connection);
            }
        }
        context->_connection = 0;
    }
    if (context->_batchMemory != 0) {
        igObject_FreeMemory((igObject *)context, (void *)context->_batchMemory);
        context->_batchMemory = 0;
    }
}

void igPsx2AudioContext_ReleaseDefaults(void **arg0) {
    ((DW4VC_100_0 *)(arg0))->vX();
    g_audioTableOwner.clear();
    igObject_ReleaseDefaults((igObject *)arg0);
}
}

extern "C" {
static inline igResult SendRpc(InitRef *conn, int command, int send, int sendSize, int reply, int replySize, int wait) {
    return igPsx2IopRpcConnection_Call((igPsx2IopRpcConnectionView *)conn, command, (void *)send, sendSize, (void *)reply, replySize, wait);
}

static inline igResult CallRpc(InitRef *conn, int command, unsigned int value, int *reply, int noWait) {
    return igPsx2IopRpcConnection_CallWithData((igPsx2IopRpcConnectionView *)conn, command, value, reply, noWait);
}

void Gap__igPsx2AudioContext__vfunc_24(int *arg0, struct InitContext *arg1) {
    struct InitRef *o;
    int s0; int *buf; int n; struct VoiceList *l;
    if (sceSifSearchModuleByName("Intrinsic_Sound_Module") < 0) {
        if (igPsx2_LoadIopModule("igAudio.irx", 2, 0, 0) != g_resultSuccess) {
            *arg0 = g_resultFailure.v;
            return;
        }
    }
    s0 = (int)igObject_GetAllocator((igObject *)arg1);
    o = arg1->conn;
    if (o != 0) {
        o->rc = o->rc - 1;
        if (((unsigned long long)((long long)o->rc << 41) >> 41) == 0)
            igObject_Destroy((igObject *)o);
    }
    arg1->conn = (struct InitRef *)igPsx2IopRpcConnection_Create(s0);
    igPsx2IopRpcConnection_Bind((igPsx2IopRpcConnectionView *)arg1->conn, 0x12111);
    s0 = (int)igObject_MallocAligned((igObject *)arg1, 0x10, (unsigned short)0x10);
    buf = (int *)s0;
    buf[0] = arg1->f24;
    buf[1] = arg1->f32;
    buf[2] = arg1->f36;
    n = arg1->f32 + arg1->f36;
    if (n >= ((struct VoiceList *)g_audioTableOwner.p)->count) List_Reserve((igDataList *)(((struct VoiceList *)g_audioTableOwner.p)), n, 0x24);
    n = arg1->f32 + arg1->f36;
    l = ((struct VoiceList *)g_audioTableOwner.p);
    if (n >= 0) {
        if (n <= l->cap) l->count = n;
        else List_Resize(l, n, 0x24);
    }
    n = ((struct VoiceList *)g_audioTableOwner.p)->count;
    if (n != 0) memset((void *)((struct VoiceList *)g_audioTableOwner.p)->data, 0, n * 0x24);
    SendRpc(arg1->conn, 0x20000, s0, 0x10, 0, 0, 0);
    igObject_FreeMemory((igObject *)arg1, (void *)s0);
    CallRpc(arg1->conn, 0x40000, 0x3FFF3FFFu, 0, 0);
    CallRpc(arg1->conn, 0x40001, 0x3FFF3FFF, 0, 0);
    arg1->f40 = (int)igObject_MallocAligned((igObject *)arg1, 0x2000, (unsigned short)0x10);
    DIntr();
    sceSifAddCmdHandler((unsigned int)3, (void (*)(void *, void *))FUN_00143800, (void *)0);
    EIntr();
    *arg0 = g_resultSuccess.v;
}
}

extern "C" {
void Gap__igPsx2AudioContext__vfunc_61(void *arg0, int arg1, int arg2) {
    ((struct VoiceTable61 *)g_audioTableOwner.p)->e[arg1].a4 = arg2;
    ((struct VoiceTable61 *)g_audioTableOwner.p)->e[arg1].b4 = 1;
}

int Gap__igPsx2AudioContext__vfunc_28(void) {
    int cnt;
    struct VoiceSlotTable *t;
    int i;
    struct VoiceSlot *e;
    t = ((struct VoiceSlotTable *)g_audioTableOwner.p);
    cnt = t->cnt;
    i = 0;
    for (; i < cnt; i++) {
        if (!t->items[i].used) {
            break;
        }
    }
    if (i == cnt) {
        return -1;
    }
    e = &t->items[i];
    memset(e, 0, 0x24);
    e->used = 1;
    e->f24 = 1.0f;
    e->f16 = 1.0f;
    e->f20 = 1.0f;
    e->f4 = 0x4000;
    e->f12 = 0x10000;
    e->f32 = -1;
    return i;
}

void Gap__igPsx2AudioContext__vfunc_29(int *arg0, void *arg1, int arg2) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    void *temp_s0;
    int temp_a3;
    int temp_a0;

    temp_a0 = *(int *)((char *)(g_audioTableOwner.p) + 16);
    temp_s0 = (void *)(temp_a0 + (arg2 * 0x24));
    temp_a3 = *(int *)((char *)(temp_s0) + 32);
    if (temp_a3 >= 0) {
        *(int *)((char *)((temp_a0 + (temp_a3 * 0x24))) + 32) = -1;
    }
    igPsx2IopRpcConnection_CallNoData((igPsx2IopRpcConnectionView *)(*(int *)((char *)(arg1) + 12)), arg2 | 0x90000, 0);
    ((VoiceUsedFlag *)temp_s0)->b0 = 0;
    *arg0 = g_resultSuccess.v;
}

/* matching construct: a small sweep of spellings */
void Gap__igPsx2AudioContext__vfunc_30(void *self, int index, struct PlayRequest *req) {
    struct Voice *v = &((struct VoiceTable *)g_audioTableOwner.p)->items[index];
    if (req->channels > 1) {
        v->stereo = 1;
    }
    switch (req->mode) {
    case 1:
        v->paused = 1;
        v->loop = 1;
        break;
    case 2:
        v->loop = 1;
        v->playing = 1;
        break;
    case 3:
        v->seek = 1;
        v->paused = 1;
        break;
    case 4:
        v->seek = 1;
        v->position = (unsigned int)floor(req->start);
        v->playing = 1;
        break;
    case 0:
        return;
    default:
        return;
    }
    v->dirty = 1;
}

void Gap__igPsx2AudioContext__vfunc_47(int *a0, UploadContext *a1, int a2, int a3, int a4, int a5, int a6) {
    FUN_00144030(a0, a1, a2, a3, a4, a5, 1, a6, 1);
}

void Gap__igPsx2AudioContext__vfunc_31(int *a0, UploadContext *a1, int a2, int a3, int a4, int a5) {
    FUN_00144030(a0, a1, a2, a3, a4, a5, 0, 0, 1);
}

void FUN_00144030(int *arg0, UploadContext *arg1, int arg2, int arg3, int arg4, int arg5, unsigned char arg6, int arg7, unsigned char arg8) {
    unsigned char k;
    int v;
    int *p;
    unsigned char s3;
    int *q;
    UploadEntry *e;

    s3 = arg6;
    if (arg3 & 0xF) {
        *arg0 = g_resultFailure.v;
        return;
    }
    e = (UploadEntry *)((char *)((UploadTable *)g_audioTableOwner.p)->tab + arg2 * 36);
    if (e->c0) {
        *arg0 = g_resultFailure.v;
        return;
    }
    p = (int *)(igObject_MallocAligned((igObject *)arg1, 16, (unsigned short)16));
    q = (int *)(igObject_MallocAligned((igObject *)arg1, 16, (unsigned short)16));
    if (e->b2) {
        k = 4;
    } else if (e->b3) {
        k = 2;
    } else {
        k = 24;
    }
    if (e->b7) {
        k |= 0x10;
    }
    p[0] = (e->f4 << 8) | (k & 0xFF);
    p[1] = arg5;
    p[2] = arg4;
    p[3] = arg3 & 0xDFFFFFFF;
    SyncDCache((void *)arg3, (void *)(arg3 + arg5));
    if (s3) {
        igPsx2IopRpcConnection_Call((igPsx2IopRpcConnectionView *)arg1->h, arg2 | 0x70000, p, 16, 0, 0, 0);
        if (arg8 != 0) {
            *q = 2;
        } else {
            *q = 1;
        }
    } else {
        igPsx2IopRpcConnection_Call((igPsx2IopRpcConnectionView *)arg1->h, arg2 | 0x70000, p, 16, q, 16, 0);
    }
    igObject_FreeMemory((igObject *)arg1, (void *)p);
    e->c4 = 1;
    v = *q;
    if (v != -1) {
        if (v == 2) {
            e->b2 = 1;
            if (e->f0 != 0) {
                igPsx2IopRpcConnection_CallWithData((igPsx2IopRpcConnectionView *)arg1->h, arg2 | 0x240000, e->f0, 0, 0);
            }
        } else {
            e->b3 = 1;
        }
        igObject_FreeMemory((igObject *)arg1, (void *)q);
        *arg0 = g_resultSuccess.v;
    } else {
        igObject_FreeMemory((igObject *)arg1, (void *)q);
        *arg0 = g_resultFailure.v;
    }
}

void Gap__igPsx2AudioContext__vfunc_48(int *arg0, void *arg1, int arg2, int arg3) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots in declaration order, the reverse of the 2001 default */
    int sp2C;

    igPsx2IopRpcConnection_CallWithData((igPsx2IopRpcConnectionView *)(*(int *)((char *)(arg1) + 12)), arg2 | 0x80000, arg3, &sp2C, 1);
    if (sp2C == 2) {
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

int Gap__igPsx2AudioContext__vfunc_51(igPsx2AudioContext *self) {
    int replyBuffer;
    igMemoryPoolView *allocator;

    allocator = igObject_GetAllocator((igObject *)self);
    replyBuffer = ((AllocatorAllocateSlot *)(allocator))->Allocate((int)(0x20), (int)(0x10));
    igPsx2IopRpcConnection_Call((igPsx2IopRpcConnectionView *)self->_connection, 0x10000, 0, 0, (void *)replyBuffer, 0x20, 0);
    return replyBuffer;
}

void Gap__igPsx2AudioContext__vfunc_52(igPsx2AudioContext *arg0, int *arg1, int *arg2, int *arg3, int *arg4) {
    int a[4];
    igPsx2IopRpcConnection_Call((igPsx2IopRpcConnectionView *)arg0->_connection, 0xE0000, 0, 0, a, 0x20, 0);
    if (arg1 != 0) {
        *arg1 = a[0];
    }
    if (arg2 != 0) {
        *arg2 = a[1];
    }
    if (arg3 != 0) {
        *arg3 = a[2];
    }
    if (arg4 != 0) {
        *arg4 = a[3];
    }
}

void Gap__igPsx2AudioContext__vfunc_34(int *arg0, void *arg1, int arg2, float fparg0) {
    int temp_s2;
    void *temp_a2;
    void *g;

    g = g_audioTableOwner.p;
    temp_a2 = (void *)(*(int *)((char *)(g) + 16) + (arg2 * 0x24));
    *(float *)((char *)(temp_a2) + 24) = fparg0;
    if (*(unsigned char *)((char *)(arg1) + 8) != 0) {
        temp_s2 = *(int *)((char *)(arg1) + 12);
        igPsx2IopRpcConnection_CallWithData((igPsx2IopRpcConnectionView *)temp_s2, arg2 | 0x270000, FUN_00145960(arg1, temp_a2), 0, 0);
    } else {
        ((B11 *)temp_a2)->f = 1;
    }
    *arg0 = g_resultSuccess.v;
}
}

extern "C" {
igResult Gap__igPsx2AudioContext__vfunc_35(char *arg1, int arg2, float fparg0) {
    VoiceFlags35 *e;
    int s2;

    e = ((VoiceTable35 *)g_audioTableOwner.p)->arr + arg2;
    if (fparg0 == 0.0f) {
        e->g16 = 1.0f;
        e->g20 = 1.0f;
    } else if (fparg0 < 0.0f) {
        e->g16 = 1.0f;
        e->g20 = 1.0f + fparg0;
    } else {
        e->g20 = 1.0f;
        e->g16 = 1.0f - fparg0;
    }
    if (*(unsigned char *)(arg1 + 8) != 0) {
        s2 = *(int *)(arg1 + 12);
        igPsx2IopRpcConnection_CallWithData((igPsx2IopRpcConnectionView *)s2, arg2 | 0x270000, FUN_00145960(arg1, e), 0, 0);
    } else {
        e->b0 = 1;
    }
    return g_resultSuccess;
}
}

extern "C" {
void Gap__igPsx2AudioContext__vfunc_36(int *arg0, ContextView *arg1, int arg2, float arg3) {
    VoiceFlags40 *e;
    int whole;
    int packed;

    e = &((VoiceTable40 *)g_audioTableOwner.p)->arr[arg2];
    if (e->a3) {
        *arg0 = g_resultFailure.v;
        return;
    }
    whole = (int)floor(arg3);
    arg3 = arg3 - (float)floor(arg3);
    packed = (whole << 16) | (int)((double)0xffff * arg3);
    e->f12 = packed;
    if (arg1->f8 != 0) {
        igPsx2IopRpcConnection_CallWithData((igPsx2IopRpcConnectionView *)arg1->f12, arg2 | 0x250000, packed, 0, 0);
    } else {
        e->c1 = 1;
    }
    *arg0 = g_resultSuccess.v;
}

void Gap__igPsx2AudioContext__vfunc_42(int arg0, int arg1, unsigned char arg2) {
    VoiceFlags42 *p;
    p = (VoiceFlags42 *)(*(int *)((char *)(g_audioTableOwner.p) + 16) + arg1 * 0x24);
    if ((p->b3 != arg2) && ((p->b1 == 0) || (p->b4 != 0))) {
        p->b3 = arg2;
        p->b4 = 1;
    }
}

void Gap__igPsx2AudioContext__vfunc_49(igPsx2AudioContext *arg0, int arg1, int arg2) {
    *(int *)((char *)((*(int *)((char *)(g_audioTableOwner.p) + 16) + (arg1 * 0x24))) + 32) = arg2;
    *(int *)((char *)((*(int *)((char *)(g_audioTableOwner.p) + 16) + (arg2 * 0x24))) + 32) = arg1;
    igPsx2IopRpcConnection_CallWithData((igPsx2IopRpcConnectionView *)arg0->_connection, arg1 | 0x2B0000, arg2, 0, 1);
}

void Gap__igPsx2AudioContext__vfunc_41(ContextView *arg0, int arg1) {
    int temp_s2;
    VoiceFlags41 *temp_s0;

    temp_s0 = &((VoiceTable41 *)g_audioTableOwner.p)->arr[arg1];
    if (arg0->f8 == 0) {
        temp_s0->f11 = 1;
        return;
    }
    temp_s2 = arg0->f12;
    igPsx2IopRpcConnection_CallWithData((igPsx2IopRpcConnectionView *)temp_s2, arg1 | 0xD0000, FUN_00145a10(arg0, temp_s0), 0, 1);
    temp_s0->f9 = 0 & 1;
}

void Gap__igPsx2AudioContext__vfunc_40(ContextView *arg0, int arg1) {
    int sp40[5];
    VoiceFlags40 *e;
    VoiceFlags40 *e2;
    int idx;

    e = &((VoiceTable40 *)g_audioTableOwner.p)->arr[arg1];
    if (e->a5 == 0 || e->b6 != 0) {
        e->a5 = 1;
        e->b6 = 0 & 1;
        idx = e->next;
        if (idx >= 0) {
            e2 = &((VoiceTable40 *)g_audioTableOwner.p)->arr[idx];
            e2->a5 = 1;
            e2->b6 = 0 & 1;
        }
        if (arg0->f8 == 0) {
            e->c3 = 1;
            return;
        }
        sp40[0] = FUN_00145960(arg0, e);
        sp40[1] = e->f12;
        if (e->b4 != 0) {
            sp40[2] = FUN_00145a10(arg0, e);
            igPsx2IopRpcConnection_Call((igPsx2IopRpcConnectionView *)arg0->f12, arg1 | 0x200000, sp40, 0x10, 0, 0, 0);
            e->b4 = 0 & 1;
            return;
        }
        igPsx2IopRpcConnection_Call((igPsx2IopRpcConnectionView *)arg0->f12, arg1 | 0x2a0000, sp40, 0x10, 0, 0, 0);
    }
}

void Gap__igPsx2AudioContext__vfunc_43(ContextView *arg0, int arg1) {
    VoiceFlags43 *e;
    VoiceFlags43 *e2;
    int idx;

    e = &((VoiceTable43 *)g_audioTableOwner.p)->arr[arg1];
    e->f8 = 0 & 1;
    idx = e->next;
    if (idx >= 0) {
        e2 = &((VoiceTable43 *)g_audioTableOwner.p)->arr[idx];
        e2->f8 = 0 & 1;
    }
    if (arg0->f8 != 0) {
        igPsx2IopRpcConnection_CallNoData((igPsx2IopRpcConnectionView *)arg0->f12, arg1 | 0x210000, 0);
        return;
    }
    e->f11 = 1;
}

void Gap__igPsx2AudioContext__vfunc_50(ContextView *arg0, int arg1) {
    VoiceFlags40 *e;
    VoiceFlags40 *e2;
    int idx;

    e = &((VoiceTable40 *)g_audioTableOwner.p)->arr[arg1];
    /* matching construct: spelling sweep — the redundant !e->a5 test keeps retail's second branch on the same flag */
    if (!(e->a5 || (!e->a5 && e->c3))) {
        return;
    }
    e->b6 = 1;
    idx = e->next;
    if (idx >= 0) {
        e2 = &((VoiceTable40 *)g_audioTableOwner.p)->arr[idx];
        e2->b6 = 1;
    }
    if (arg0->f8 != 0) {
        igPsx2IopRpcConnection_CallNoData((igPsx2IopRpcConnectionView *)arg0->f12, arg1 | 0x2d0000, 0);
    } else {
        e->c5 = 1;
    }
}

void Gap__igPsx2AudioContext__vfunc_53(int unusedReceiver, int entryIndex, int value) {
    if (!(value & 0x3F)) {
        ((AudioTableEntry *)(((AudioTableOwner *)g_audioTableOwner.p)->entries + entryIndex * 0x24))->word1 = value & ~0x3F;
    }
}

void Gap__igPsx2AudioContext__vfunc_54(igPsx2AudioContext *arg0, int arg1) {
    ThreadRef *s0;
    ThreadRef *a0;
    AudioThread *p;
    if (arg0->_streamingThread == 0) {
        p = (AudioThread *)igSemaphore_Create(0);
        g_streamingSemaphore = p;
        p->a92();
        g_streamingSemaphore->a132((void *)1);
        s0 = (ThreadRef *)(igThread_Create(0));
        if (s0 != 0) {
            s0->references = s0->references + 1;
        }
        a0 = (ThreadRef *)arg0->_streamingThread;
        if (a0 != 0) {
            --a0->references;
            if (((unsigned long long)(long long)a0->references & 0x7fffffULL) == 0) {
                igObject_Destroy((igObject *)a0);
            }
        }
        arg0->_streamingThread = (int)s0;
        ((AudioThread *)arg0->_streamingThread)->a132((void *)&FUN_00143880);
        ((AudioThread *)arg0->_streamingThread)->a140(arg1);
        ((AudioThread *)arg0->_streamingThread)->a120();
        DIntr();
        sceSifAddCmdHandler((unsigned int)0, (void (*)(void *, void *))&FUN_00143840, (void *)&g_pendingIopCallbackValue);
        EIntr();
    }
}
