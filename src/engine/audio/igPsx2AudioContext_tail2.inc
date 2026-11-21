int Gap__igPsx2AudioContext__vfunc_55(void **self, int value) {
    return (int)((Gap::Core::igObject *)self)->mallocAligned(value, ((DW4VC_132_0 *)(self))->vX()) | 0x20000000;
}

int Gap__igPsx2AudioContext__vfunc_33(igPsx2AudioContext *self) {
    return 0x10;
}

void Gap__igPsx2AudioContext__vfunc_56(int arg0, int arg1) {
    ((Gap::Core::igObject *)arg0)->free((void *)((arg1 & 0xDFFFFFFF)));
}

void Gap__igPsx2AudioContext__vfunc_57(int arg0, int arg1) {
    ((struct VoiceTable57 *)g_audioTableOwner.p)->arr[arg1].bitA = 1;
    ((struct VoiceTable57 *)g_audioTableOwner.p)->arr[arg1].bitE = 1;
}

void Gap__igPsx2AudioContext__vfunc_58(int arg0, int arg1) {
    ((struct VoiceTable58 *)g_audioTableOwner.p)->arr[arg1].b1 = 1;
    ((struct VoiceTable58 *)g_audioTableOwner.p)->arr[arg1].b4 = 1;
}

void Gap__igPsx2AudioContext__vfunc_59(void *arg0, int arg1, int arg2) {
    ((struct VoiceTable61 *)g_audioTableOwner.p)->e[arg1].b2 = arg2;
    ((struct VoiceTable61 *)g_audioTableOwner.p)->e[arg1].b4 = 1;
    ((struct VoiceTable61 *)g_audioTableOwner.p)->e[arg1].b5 = 1;
}

void Gap__igPsx2AudioContext__vfunc_60(int arg0, int arg1, int arg2, int arg3) {
    int temp_v1;

    temp_v1 = arg1 * 0x24;
    ((VoiceFlags42 *)(*(int *)((char *)(g_audioTableOwner.p) + 16) + temp_v1))->b2 = arg2;
    ((VoiceFlags42 *)(*(int *)((char *)(g_audioTableOwner.p) + 16) + temp_v1))->v = arg3;
    ((VoiceFlags42 *)(*(int *)((char *)(g_audioTableOwner.p) + 16) + temp_v1))->b5 = 1;
    ((VoiceFlags42 *)(*(int *)((char *)(g_audioTableOwner.p) + 16) + temp_v1))->b4 = 1;
}

void Gap__igPsx2AudioContext__vfunc_37(int *arg0, void *arg1, int arg2, int arg3) {
    VoiceFlags37 *p;
    p = (VoiceFlags37 *)(*(int *)((char *)(g_audioTableOwner.p) + 16) + (arg2 * 0x24));
    if (p->b1 != 0) {
        *arg0 = g_resultSuccess.v;
        return;
    }
    if (*(unsigned char *)((char *)arg1 + 8) != 0) {
        igPsx2IopRpcConnection_CallWithData((igPsx2IopRpcConnectionView *)(*(int *)((char *)(arg1) + 12)), arg2 | 0x260000, arg3, 0, 0);
    } else {
        *(int *)((char *)p + 28) = arg3;
        p->c2 = 1;
    }
    *arg0 = g_resultSuccess.v;
}

void Gap__igPsx2AudioContext__vfunc_44(igPsx2AudioContext *self) {
}

void Gap__igPsx2AudioContext__vfunc_45(igPsx2AudioContextView *self)
{
    self->vfunc_44();
}

/* A voice's pending changes (byte 11) as the flush reads them, and the fields they send. */
struct VoiceChanges {
    unsigned char used : 1;
    unsigned char flags8 : 4;
    unsigned char streamed : 1;
    unsigned char flags8b : 2;
    unsigned char flags9 : 4;
    unsigned char dirty : 1;
    unsigned char flags9b : 3;
    unsigned char pad10;
    union {
        unsigned char pending;
        struct {
            unsigned char volumeChanged : 1;
            unsigned char pitchChanged : 1;
            unsigned char panChanged : 1;
            unsigned char playChanged : 1;
            unsigned char sourceChanged : 1;
            unsigned char stopChanged : 1;
            unsigned char changes2 : 2;
        } changed;
    };
};
struct VoiceView {
    unsigned int position;
    int f4;
    VoiceChanges state;
    int pitch;
    char pad16[12];
    int pan;
    char pad32[4];
};
struct CommandBuffer { char pad[40]; int *commands; int offset; };

/* Sends every voice's pending changes to the IOP as one batch of 16-byte commands. */
void Gap__igPsx2AudioContext__vfunc_46(igPsx2AudioContext *self) {
    if (self->_immediateMode) return;
    CommandBuffer *buffer = (CommandBuffer *)self;
    int sent = 0;
    int *command = buffer->commands + buffer->offset;
    int count = ((igPsx2AudioSourceList *)g_audioTableOwner.p)->_count;
    for (int i = 0; i < count; i++) {
        VoiceView *v = &((VoiceView *)((igPsx2AudioSourceList *)g_audioTableOwner.p)->_data)[i];
        if (!v->state.used) continue;
        if (v->state.pending == 0) continue;
        if (v->state.changed.sourceChanged) {
            command[0] = i | 0xD0000;
            command[1] = FUN_00145a10(self, v);
            v->state.changed.sourceChanged = 0;
            v->state.dirty = 0;
            sent++;
            command += 4;
        }
        if (v->state.changed.pitchChanged) {
            sent++;
            command[0] = i | 0x250000;
            command[1] = v->pitch;
            command += 4;
        }
        if (v->state.changed.volumeChanged) {
            command[0] = i | 0x270000;
            command[1] = FUN_00145960(self, v);
            sent++;
            command += 4;
        }
        if (v->state.changed.panChanged) {
            sent++;
            command[0] = i | 0x260000;
            command[1] = v->pan;
            command += 4;
        }
        if (v->state.changed.stopChanged) {
            sent++;
            command[0] = i | 0x2D0000;
            command += 4;
        }
        if (v->state.changed.playChanged) {
            if (v->state.streamed) {
                command[1] = FUN_00145960(self, v);
                command[2] = v->pitch;
                if (v->state.dirty) {
                    command[0] = i | 0x200000;
                    command[3] = FUN_00145a10(self, v);
                    v->state.dirty = 0;
                } else {
                    command[0] = i | 0x2A0000;
                }
                sent++;
                command += 4;
            } else {
                sent++;
                command[0] = i | 0x210000;
                command += 4;
            }
        }
        v->state.pending = 0;
    }
    if (sent <= 256 && sent != 0) {
        igPsx2IopRpcConnection_Call((igPsx2IopRpcConnectionView *)self->_connection, 0x50000, buffer->commands + buffer->offset, sent * 16, 0, 0, 0);
        buffer->offset = 1024 - buffer->offset;
    }
}

int Gap__igPsx2AudioContext__vfunc_38(igPsx2AudioContext *arg0, int arg1) {
    int sp1C;

    igPsx2IopRpcConnection_CallWithData((igPsx2IopRpcConnectionView *)arg0->_connection, arg1 | 0xB0000, 0, &sp1C, 0);
    return sp1C;
}

int Gap__igPsx2AudioContext__vfunc_39(void *arg0, int arg1) {
    return ((unsigned long long) ((long long) *(unsigned char *)((char *)((*(int *)((char *)(g_audioTableOwner.p) + 16) + (arg1 * 0x24))) + 8) << 0x3A) >> 0x3F) != 0;
}

unsigned FUN_00145960(void *context, void *voice) {
    struct VoiceGain *arg1 = (struct VoiceGain *)voice;
    int k = 0x3FFF;
    float s = (float)k * arg1->f24;
    unsigned x = (unsigned)(s * arg1->f16);
    unsigned y = (unsigned)(s * arg1->f20);
    return (x << 16) | y;
}

int FUN_00145a10(void *arg0, void *voice) {
    VoiceState *a = (VoiceState *)voice;
    VoiceStateWord u;
    u.r.d0 = a->a6;
    u.r.d1 = a->a1;
    u.r.d2 = a->b3;
    u.r.d3 = a->a4;
    u.r.d4 = a->b0;
    u.r.d5 = a->b1;
    u.r.d6 = a->b5;
    u.r.d7 = a->b2;
    u.r.e = a->c;
    return u.i;
}

igMetaObject *igPsx2AudioContext_GetMeta(void)
{
    return g_igPsx2AudioContext_metaObject;
}

void Gap__igPsx2AudioContext__vfunc_26(igPsx2AudioContext *self, igObject *window) {
    igObject *previousWindow;
    igObject::ref(window);
    previousWindow = (igObject *)(self->_window);
    igObject::release(previousWindow);
    self->_window = (int)window;
}

int Gap__igPsx2AudioContext__vfunc_27(igPsx2AudioContext *self) {
    return self->_window;
}

