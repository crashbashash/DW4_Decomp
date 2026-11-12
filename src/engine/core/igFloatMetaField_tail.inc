int Gap__Core__igFloatMetaField__vfunc_25(void) {
    return 4;
}

void FUN_002e3810(void **arg0, float fparg0) {
    float sp1C;

    sp1C = fparg0;
    ((DW4VC_140_1 *)(arg0))->vX((int)(&sp1C));
}

int Gap__Core__igFloatMetaField__vfunc_27(void) {
    return 0x10;
}

static inline void *pool() {
    if (((void * *)g_stringPool)[0] == 0) {
        void *o = FUN_002eb010(0x10);
        if (o != 0) {
            o = ((void *)StringPool_Construct((struct S_2eadf0 *)o));
        }
        ((void * *)g_stringPool)[0] = o;
    }
    return ((void * *)g_stringPool)[0];
}

void FUN_002e3850(Named *self, int key) {
    Holder h = self->Find(key);
    char *text = h.p->text;
    char *v;
    char *old;
    text = (text == 0) ? DAT_004c22f0[0] : text;
    v = ((char *)StringPool_Intern((StringPool *)(pool()), (const char *)text));
    old = self->name;
    if (old != 0) {
        int *hdr = (int *)(old - 8);
        int r = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = r;
        if (r == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hdr), (int)hdr);
        }
    }
    self->name = v;
    IG_OBJECT_RELEASE(h.p);
}

