int Gap__igPsx2AudioContext__vfunc_55(void **self, int value) {
    return (int)FUN_00300db0(self, value, ((DW4VC_132_0 *)(self))->vX()) | 0x20000000;
}

int Gap__igPsx2AudioContext__vfunc_33(igPsx2AudioContext *self) {
    return 0x10;
}

void Gap__igPsx2AudioContext__vfunc_56(int arg0, int arg1) {
    FUN_00300f50(arg0, (arg1 & 0xDFFFFFFF));
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
    int sp;
    VoiceFlags37 *p;
    p = (VoiceFlags37 *)(*(int *)((char *)(g_audioTableOwner.p) + 16) + (arg2 * 0x24));
    if (p->b1 != 0) {
        *arg0 = g_statusSucceeded[0];
        return;
    }
    if (*(unsigned char *)((char *)arg1 + 8) != 0) {
        FUN_0032d850(&sp, *(int *)((char *)(arg1) + 12), arg2 | 0x260000, arg3, 0, 0);
    } else {
        *(int *)((char *)p + 28) = arg3;
        p->c2 = 1;
    }
    *arg0 = g_statusSucceeded[0];
}

void Gap__igPsx2AudioContext__vfunc_44(igPsx2AudioContext *self) {
}

void Gap__igPsx2AudioContext__vfunc_45(igPsx2AudioContextView *self)
{
    self->vfunc_44();
}

int Gap__igPsx2AudioContext__vfunc_38(igPsx2AudioContext *arg0, int arg1) {
    int sp1C;
    int sp18;

    FUN_0032d850(&sp18, arg0->_connection, arg1 | 0xB0000, 0, &sp1C, 0);
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

igMetaObject *Gap__igPsx2AudioContext__vfunc_22(void)
{
    return g_igPsx2AudioContext_metaObject[0];
}

void Gap__igPsx2AudioContext__vfunc_26(igPsx2AudioContext *self, igObject *window) {
    igObject *previousWindow;
    if (window != 0) {
        window->_refCount = window->_refCount + 1;
    }
    previousWindow = (igObject *)(self->_window);
    if (previousWindow != 0) {
        previousWindow->_refCount = previousWindow->_refCount - 1;
        if ((previousWindow->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousWindow);
        }
    }
    self->_window = (int)window;
}

int Gap__igPsx2AudioContext__vfunc_27(igPsx2AudioContext *self) {
    return self->_window;
}

