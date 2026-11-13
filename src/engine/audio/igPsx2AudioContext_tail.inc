void Gap__igPsx2AudioContext__vfunc_23(ContextView *arg0, int arg1) {
    if (arg0->f8 == 0 && arg1 == 1) {
        ((DW4VC_184_0 *)(arg0))->vX();
    }
    arg0->f8 = (unsigned char) (arg1 == 1);
}

void Gap__igPsx2AudioContext__vfunc_11(void) {
    int allocator = igObject_GetAllocator();
    g_audioTableOwner.release();
    g_audioTableOwner.p = (igPsx2AudioSourceList *)FUN_001435c0(allocator);
}

void FUN_00143800(AudioVoiceHandle *h)
{
    ((AudioVoiceTable *)g_audioTableOwner.p)->entries[h->voice].active = 0;
}

void FUN_00143840(void *arg0) {
    DW4SR4 sp1C;

    DAT_0055f5b0[0] = *(int *)((char *)(arg0) + 12) | 0x20000000;
    sp1C = ((DW4VCSR_128_0 *)(DAT_0055f5b8[0]))->vX();
}

void FUN_00143880(int (*arg0)(int)) {
    DW4SR4 sp2C;

loop_1:
    sp2C = ((DW4VCSR_132_1 *)(DAT_0055f5b8[0]))->vX((int)(1));
    arg0(DAT_0055f5b0[0]);
    goto loop_1;
}

void Gap__igPsx2AudioContext__vfunc_25(igPsx2AudioContext *context) {
    igObject *connection;
    int result;

    if (context->_connection != 0) {
        FUN_0032d9b0(&result, (igObject *)context->_connection, 0x30000, 1);
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
        FUN_00300f50(context, context->_batchMemory);
        context->_batchMemory = 0;
    }
}

void Gap__igPsx2AudioContext__vfunc_12(void **arg0) {
    ((DW4VC_100_0 *)(arg0))->vX();
    g_audioTableOwner.clear();
    Gap__Core__igObject__vfunc_10(arg0);
}
}

extern "C" {
static inline RpcStatus SendRpc(InitRef *conn, int command, int send, int sendSize, int reply, int replySize, int callback) {
    RpcStatus status;
    FUN_0032d6d0(&status, conn, command, send, sendSize, reply, replySize, callback);
    return status;
}

static inline RpcStatus CallRpc(InitRef *conn, int command, unsigned int value, int a, int b) {
    RpcStatus status;
    FUN_0032d850(&status, conn, command, value, a, b);
    return status;
}

void Gap__igPsx2AudioContext__vfunc_24(int *arg0, struct InitContext *arg1) {
    struct InitRef *o;
    int s0; int *buf; int n; struct VoiceList *l;
    if (sceSifSearchModuleByName(text_Intrinsic_Sound_Module) < 0) {
        if (igPsx2_LoadIopModule(text_igAudio_irx, 2, 0, 0) != *(RpcStatus *)g_statusSucceeded) {
            *arg0 = g_allocatorFailureStatus[0];
            return;
        }
    }
    s0 = FUN_00301000(arg1);
    o = arg1->conn;
    if (o != 0) {
        o->rc = o->rc - 1;
        if (((unsigned long long)((long long)o->rc << 41) >> 41) == 0)
            igObject_Destroy(o);
    }
    arg1->conn = (struct InitRef *)FUN_002cfe10(s0);
    FUN_0032d640(arg1->conn, 0x12111);
    s0 = (int)FUN_00300db0(arg1, 0x10, 0x10);
    buf = (int *)s0;
    buf[0] = arg1->f24;
    buf[1] = arg1->f32;
    buf[2] = arg1->f36;
    n = arg1->f32 + arg1->f36;
    if (n >= ((struct VoiceList *)g_audioTableOwner.p)->count) List_Reserve(((struct VoiceList *)g_audioTableOwner.p), n, 0x24);
    n = arg1->f32 + arg1->f36;
    l = ((struct VoiceList *)g_audioTableOwner.p);
    if (n >= 0) {
        if (n <= l->cap) l->count = n;
        else List_Resize(l, n, 0x24);
    }
    n = ((struct VoiceList *)g_audioTableOwner.p)->count;
    if (n != 0) memset((void *)((struct VoiceList *)g_audioTableOwner.p)->data, 0, n * 0x24);
    SendRpc(arg1->conn, 0x20000, s0, 0x10, 0, 0, 0);
    FUN_00300f50(arg1, s0);
    CallRpc(arg1->conn, 0x40000, 0x3FFF3FFFu, 0, 0);
    CallRpc(arg1->conn, 0x40001, 0x3FFF3FFF, 0, 0);
    arg1->f40 = (int)FUN_00300db0(arg1, 0x2000, 0x10);
    DIntr();
    sceSifAddCmdHandler(3, FUN_00143800, 0);
    EIntr();
    *arg0 = g_statusSucceeded[0];
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
    int sp3C;

    temp_a0 = *(int *)((char *)(g_audioTableOwner.p) + 16);
    temp_s0 = (void *)(temp_a0 + (arg2 * 0x24));
    temp_a3 = *(int *)((char *)(temp_s0) + 32);
    if (temp_a3 >= 0) {
        *(int *)((char *)((temp_a0 + (temp_a3 * 0x24))) + 32) = -1;
    }
    FUN_0032d9b0(&sp3C, *(int *)((char *)(arg1) + 12), arg2 | 0x90000, 0);
    ((VoiceUsedFlag *)temp_s0)->b0 = 0;
    *arg0 = g_statusSucceeded[0];
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
    int spAC;
    int *p;
    unsigned char s3;
    int *q;
    int spA8;
    UploadEntry *e;
    int spA4;

    s3 = arg6;
    if (arg3 & 0xF) {
        *arg0 = g_allocatorFailureStatus[0];
        return;
    }
    e = (UploadEntry *)((char *)((UploadTable *)g_audioTableOwner.p)->tab + arg2 * 36);
    if (e->c0) {
        *arg0 = g_allocatorFailureStatus[0];
        return;
    }
    p = FUN_00300db0(arg1, 16, 16);
    q = FUN_00300db0(arg1, 16, 16);
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
    SyncDCache(arg3, arg3 + arg5);
    if (s3) {
        FUN_0032d6d0(&spAC, arg1->h, arg2 | 0x70000, p, 16, 0, 0, 0);
        if (arg8 != 0) {
            *q = 2;
        } else {
            *q = 1;
        }
    } else {
        FUN_0032d6d0(&spA8, arg1->h, arg2 | 0x70000, p, 16, q, 16, 0);
    }
    FUN_00300f50(arg1, p);
    e->c4 = 1;
    v = *q;
    if (v != -1) {
        if (v == 2) {
            e->b2 = 1;
            if (e->f0 != 0) {
                FUN_0032d850(&spA4, arg1->h, arg2 | 0x240000, e->f0, 0, 0);
            }
        } else {
            e->b3 = 1;
        }
        FUN_00300f50(arg1, q);
        *arg0 = g_statusSucceeded[0];
    } else {
        FUN_00300f50(arg1, q);
        *arg0 = g_allocatorFailureStatus[0];
    }
}

void Gap__igPsx2AudioContext__vfunc_48(int *arg0, void *arg1, int arg2, int arg3) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots in declaration order, the reverse of the 2001 default */
    int sp2C;
    int sp28;

    FUN_0032d850(&sp28, *(int *)((char *)(arg1) + 12), arg2 | 0x80000, arg3, &sp2C, 1);
    if (sp2C == 2) {
        *arg0 = g_statusSucceeded[0];
    } else {
        *arg0 = g_allocatorFailureStatus[0];
    }
}

int Gap__igPsx2AudioContext__vfunc_51(igPsx2AudioContext *self) {
    int rpcStatus;
    int replyBuffer;
    void **allocator;

    allocator = (void **)(igObject_GetAllocator());
    replyBuffer = ((AllocatorAllocateSlot *)(allocator))->Allocate((int)(0x20), (int)(0x10));
    FUN_0032d6d0(&rpcStatus, self->_connection, 0x10000, 0, 0, replyBuffer, 0x20, 0);
    return replyBuffer;
}

void Gap__igPsx2AudioContext__vfunc_52(igPsx2AudioContext *arg0, int *arg1, int *arg2, int *arg3, int *arg4) {
    int a[4];
    int r;
    FUN_0032d6d0(&r, arg0->_connection, 0xE0000, 0, 0, a, 0x20, 0);
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
    int sp4C;
    int temp_s2;
    void *temp_a2;
    void *g;

    g = g_audioTableOwner.p;
    temp_a2 = (void *)(*(int *)((char *)(g) + 16) + (arg2 * 0x24));
    *(float *)((char *)(temp_a2) + 24) = fparg0;
    if (*(unsigned char *)((char *)(arg1) + 8) != 0) {
        temp_s2 = *(int *)((char *)(arg1) + 12);
        FUN_0032d850(&sp4C, temp_s2, arg2 | 0x270000, FUN_00145960(arg1, temp_a2), 0, 0);
    } else {
        ((B11 *)temp_a2)->f = 1;
    }
    *arg0 = g_statusSucceeded[0];
}
}

extern "C" {
PanResult Gap__igPsx2AudioContext__vfunc_35(char *arg1, int arg2, float fparg0) {
    PanResult status;
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
        FUN_0032d850(&status, s2, arg2 | 0x270000, FUN_00145960(arg1, e), 0, 0);
    } else {
        e->b0 = 1;
    }
    return PanResult(g_statusSucceeded[0]);
}
}

extern "C" {
void Gap__igPsx2AudioContext__vfunc_36(int *arg0, ContextView *arg1, int arg2, float arg3) {
    int sp8C;
    VoiceFlags40 *e;
    int whole;
    int packed;

    e = &((VoiceTable40 *)g_audioTableOwner.p)->arr[arg2];
    if (e->a3) {
        *arg0 = g_allocatorFailureStatus[0];
        return;
    }
    whole = (int)floor(arg3);
    arg3 = arg3 - (float)floor(arg3);
    packed = (whole << 16) | (int)((double)0xffff * arg3);
    e->f12 = packed;
    if (arg1->f8 != 0) {
        FUN_0032d850(&sp8C, arg1->f12, arg2 | 0x250000, packed, 0, 0);
    } else {
        e->c1 = 1;
    }
    *arg0 = g_statusSucceeded[0];
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
    int sp1C;
    *(int *)((char *)((*(int *)((char *)(g_audioTableOwner.p) + 16) + (arg1 * 0x24))) + 32) = arg2;
    *(int *)((char *)((*(int *)((char *)(g_audioTableOwner.p) + 16) + (arg2 * 0x24))) + 32) = arg1;
    FUN_0032d850(&sp1C, arg0->_connection, arg1 | 0x2B0000, arg2, 0, 1);
}

void Gap__igPsx2AudioContext__vfunc_41(ContextView *arg0, int arg1) {
    int sp4C;
    int temp_s2;
    VoiceFlags41 *temp_s0;

    temp_s0 = &((VoiceTable41 *)g_audioTableOwner.p)->arr[arg1];
    if (arg0->f8 == 0) {
        temp_s0->f11 = 1;
        return;
    }
    temp_s2 = arg0->f12;
    FUN_0032d850(&sp4C, temp_s2, arg1 | 0xD0000, FUN_00145a10(arg0, temp_s0), 0, 1);
    temp_s0->f9 = 0 & 1;
}

void Gap__igPsx2AudioContext__vfunc_40(ContextView *arg0, int arg1) {
    int sp40[5];
    int sp5C; /* matching construct: declaration order — the two status words are declared high slot first so the unit compiler (combat build) assigns sp+0x5c/sp+0x58 as retail does */
    int sp58;
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
            FUN_0032d6d0(&sp5C, arg0->f12, arg1 | 0x200000, sp40, 0x10, 0, 0, 0);
            e->b4 = 0 & 1;
            return;
        }
        FUN_0032d6d0(&sp58, arg0->f12, arg1 | 0x2a0000, sp40, 0x10, 0, 0, 0);
    }
}

void Gap__igPsx2AudioContext__vfunc_43(ContextView *arg0, int arg1) {
    int sp1C;
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
        FUN_0032d9b0(&sp1C, arg0->f12, arg1 | 0x210000, 0);
        return;
    }
    e->f11 = 1;
}

void Gap__igPsx2AudioContext__vfunc_50(ContextView *arg0, int arg1) {
    int sp1C;
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
        FUN_0032d9b0(&sp1C, arg0->f12, arg1 | 0x2d0000, 0);
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
        p = (AudioThread *)FUN_002ba650(0);
        DAT_0055f5b8[0] = p;
        p->a92();
        DAT_0055f5b8[0]->a132((void *)1);
        s0 = FUN_002b7f40(0);
        if (s0 != 0) {
            s0->references = s0->references + 1;
        }
        a0 = (ThreadRef *)arg0->_streamingThread;
        if (a0 != 0) {
            --a0->references;
            if (((unsigned long long)(long long)a0->references & 0x7fffffULL) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->_streamingThread = (int)s0;
        ((AudioThread *)arg0->_streamingThread)->a132((void *)&FUN_00143880);
        ((AudioThread *)arg0->_streamingThread)->a140(arg1);
        ((AudioThread *)arg0->_streamingThread)->a120();
        DIntr();
        sceSifAddCmdHandler(0, &FUN_00143840, &DAT_0055f5b0[0]);
        EIntr();
    }
}
