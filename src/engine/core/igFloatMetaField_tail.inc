int Gap__Core__igFloatMetaField__vfunc_25(void) {
    return 4;
}

void FUN_002e3810(void **arg0, float fparg0) {
    float sp1C;

    sp1C = fparg0;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp1C);
}

int Gap__Core__igFloatMetaField__vfunc_27(void) {
    return 0x10;
}

static inline void *pool() {
    if (((void * *)g_stringPool)[0] == 0) {
        void *o = StringPool_Allocate(0x10);
        if (o != 0) {
            o = ((void *)StringPool_Construct((StringPool *)o));
        }
        ((void * *)g_stringPool)[0] = o;
    }
    return ((void * *)g_stringPool)[0];
}

void FUN_002e3850(igFolderView *self, const char *name) {
    FolderPath h = self->vfunc_23(name);
    char *text = (char *)h.p->_buffer;
    char *v;
    char *old;
    text = (text == 0) ? g_stringObjEmptyText[0] : text;
    v = ((char *)StringPool_Intern((StringPool *)(pool()), (const char *)text));
    old = self->_folderName;
    if (old != 0) {
        int *hdr = (int *)(old - 8);
        int r = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = r;
        if (r == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hdr), (int)hdr);
        }
    }
    self->_folderName = v;
}

