char *FUN_001405a0(char *arg0) {
    char *p;
    char c;

    if (arg0 == 0) {
        return 0;
    }
    p = arg0 + strlen(arg0);
    for (; arg0 < p; p--) {
        c = p[-1];
        if (c == 0x5C || c == 0x2F) {
            break;
        }
    }
    return p;
}

static inline void retain(Image *o) { if (o != 0) { o->_refCount = o->_refCount + 1; } }

static inline unsigned magFilter(const TextureAttr *a) { return a->magFilter; }

static inline unsigned minFilter(const TextureAttr *a) { return a->minFilter; }

static inline unsigned wrapS(const TextureAttr *a) { return a->wrapS; }

static inline unsigned wrapT(const TextureAttr *a) { return a->wrapT; }

int Gap__Attrs__igTextureAttr__vfunc_37(TextureAttr *attr, int unused, Allocator *allocator) {
    char text[8204];
    if (allocator == 0) {
        allocator = (Allocator *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault[0]);
    }
    igSmartPointer<Image> image((Image *)FUN_00140c00(attr, 0), kRetainReference);
    int *name = &NO_IMAGE[0];
    if (image.p != 0) {
        if (image.p->name != 0) {
            name = (int *)FUN_001405a0((char *)image.p->name);
        }
    }
    sprintf(text, &text_s_d_d_d_d_d_d_d_d[0], name, attr->bColor, magFilter(attr), minFilter(attr), wrapS(attr), wrapT(attr), (long long)attr->mipmapMode, (long long)attr->source, (long long)attr->paging);
    int copy = allocator->allocate(strlen(text) + 1);
    strcpy(copy, text);
    return copy;
}

int Gap__Attrs__igTextureAttr__vfunc_38(Arg *arg0, int arg1) {
    int sp206C;
    int sp2068;
    int sp2064;
    int sp2060;
    int sp205C;
    int sp2058;
    int sp2054;
    int sp2050;
    char sp50[8192];
    int *var_a1;
    int *var_s1;

    if (sscanf(arg1, &text_s_d_d_d_d_d_d_d_d[0], sp50, &sp206C, &sp2068, &sp2064, &sp2060, &sp205C, &sp2058, &sp2054, &sp2050) != 9) {
        return 0;
    }
    var_s1 = (int *)(&NO_IMAGE[0]);
    var_a1 = (int *)(&NO_IMAGE[0]);
    if (FUN_00140c00(arg0, 0) != 0) {
        if (((T_140740 *)FUN_00140c00(arg0, 0))->f88 != 0) {
            var_s1 = (int *)(FUN_001405a0((char *)((T_140740 *)FUN_00140c00(arg0, 0))->f88));
        }
        var_a1 = (int *)(var_s1);
    }
    if (strcmp(sp50, var_a1) == 0) {
        if (sp206C == arg0->f16) {
            if ((sp2068 == arg0->f20) && (sp2064 == arg0->f24) && (sp2060 == arg0->f28) && (sp205C == arg0->f32) && (sp2058 == arg0->f40) && (sp2054 == arg0->f44) && (sp2050 == arg0->f52)) {
                return 1;
            }
        }
    }
    return 0;
}

void Gap__Attrs__igTextureAttr__vfunc_26(void) {

}

void Gap__Attrs__igTextureAttr__vfunc_17(S0 *arg0) {
    if (arg0->f3C == 0) {
        arg0->f3C = 1;
    }
    FUN_0013b820(arg0);
}

void FUN_00140ad0(T_140ad0 *arg0, int *arg1, int arg2) {
    L_140ad0 *s1;
    int s0;
    int n;
    int *a0;
    int v1;
    int *a0b;
    if (arg2 == 0) {
        if (arg1 != 0) {
            arg1[1] = arg1[1] + 1;
        }
        a0 = arg0->f48;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->f48 = arg1;
        return;
    }
    if (arg0->f64->n == 0) {
        ObjectList_ResizeRetained(arg0->f64, arg0->f60 - 1);
    }
    s1 = arg0->f64;
    if (arg1 != 0) {
        arg1[1] = arg1[1] + 1;
    }
    s0 = arg2 * 4;
    a0b = *(int **)((char *)s1->d + s0 - 4);
    if (a0b != 0) {
        a0b[1] = a0b[1] - 1;
        if ((a0b[1] & 0x7FFFFF) == 0) {
            igObject_Destroy(a0b);
        }
    }
    n = s1->n;
    v1 = arg2 - 1;
    if (n != 0 && v1 >= 0 && v1 < n) {
        *(int **)(s0 + (int)s1->d - 4) = arg1;
    }
}

int FUN_00140c00(void *arg0, int arg1) {
    if (arg1 == 0) {
        return *(int *)((char *)(arg0) + 48);
    }
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 64)) + 16) + (arg1 * 4))) - 4);
}

void Gap__Attrs__igTextureAttr__vfunc_12(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
    igObject_ReleaseDefaults(arg0);
}

void Gap__Attrs__igTextureAttr__vfunc_28(S_140c70 *arg0) {
    int temp_a1;
    R_140c70 *t;

    temp_a1 = arg0->f36;
    if (temp_a1 != -1) {
        if (arg0->f12 != 0) {
            arg0->f12->vX(temp_a1);
        }
    }
    arg0->f36 = -1;
    t = arg0->f12;
    if (t != 0) {
        t->refs = t->refs - 1;
        if ((t->refs & 0x7fffff) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f12 = 0;
}

