void Gap__igPsx2Window__vfunc_26(struct A_148b00 *arg0) {
    int *a1;
    int v1;
    int var_v0;
    struct R_148b00 *p;
    int *old;
    int *s1;

    arg0->f36 = -1;
    p = arg0->f24;
    if (p != 0) {
        p->rc = p->rc - 1;
        if ((p->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(p);
        }
    }
    arg0->f24 = 0;
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
    old = arg0->f32;
    if (old != 0) {
        a1 = old - 2;
        v1 = old[-1] - 1;
        old[-1] = v1;
        if (v1 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->f32 = s1;
    arg0->f40 = 0;
}

int Gap__igPsx2Window__vfunc_39(igPsx2Window *self, igObject *viewContext) {
    igObject *previous;
    if (viewContext != 0) {
        /* The NULL test is repeated around the retain; dropping it changes the bytes. */
        if (viewContext != 0) {
            viewContext->_refCount = viewContext->_refCount + 1;
        }
        previous = (igObject *)(self->_vc);
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(previous);
            }
        }
        self->_vc = (int)(viewContext);
        return 1;
    }
    return 0;
}

void Gap__igPsx2Window__vfunc_25(igPsx2WindowView *self)
{
    self->vfunc_22(self->_winName, self->_width, self->_height);
}

static inline void setWindowName(igPsx2Window *self, const char *name) {
    if (DAT_00586f20[0] == 0) {
        void *pool = (void *)FUN_002eb010(16);
        if (pool != 0) pool = (void *)StringPool_Construct(pool);
        DAT_00586f20[0] = (int)pool;
    }
    const char *interned = (const char *)StringPool_Intern(DAT_00586f20[0], name);
    int *old = (int *)self->_winName;
    if (old != 0) {
        int *header = old - 2;
        int refs = old[-1] - 1;
        old[-1] = refs;
        if (refs == 0) StringChunk_ReleaseHeader(*header, header);
    }
    self->_winName = (int)interned;
}

int Gap__igPsx2Window__vfunc_24(igPsx2Window *self, const char *name, int width, int height) {
    if (name == 0) {
        setWindowName(self, DAT_004d7070);
    } else {
        setWindowName(self, name);
    }
    self->_width = width;
    self->_height = height;
    if (self->_vc != 0) {
        self->_renderDestinationHandle = ((VisualContext *)self->_vc)->currentRenderDestination();
        if (self->_renderDestinationHandle == -1) {
            RenderDestinationDesc desc;
            desc.kind = 1;
            desc.width = width;
            desc.height = height;
            desc.bpp = self->_bpp;
            desc.alpha = self->_alpha;
            desc.bppDepth = self->_bppDepth;
            desc.clearDepth = 0.0f;
            desc.scale = 1.0f;
            self->_renderDestinationHandle = ((VisualContext *)self->_vc)->createRenderDestination(&desc);
        }
        int w;
        int h;
        ((VisualContext *)self->_vc)->getRenderDestinationSize(self->_renderDestinationHandle, &w, &h);
        self->_width = w;
        self->_height = h;
    } else {
        VisualContext *created = FUN_0014a000(igObject_GetAllocator(self));
        if (created != 0) created->_refCount = created->_refCount + 1;
        igRelease((igObject *)self->_vc);
        self->_vc = (int)created;
        VisualContext *vc = (VisualContext *)self->_vc;
        if (vc == 0) {
            printf(DAT_004d7080);
            return 0;
        }
        vc->_refCount = vc->_refCount - 1;
        if ((vc->_refCount & 0x7FFFFF) == 0) igObject_Destroy(vc);
        RenderDestinationDesc desc;
        desc.kind = 1;
        desc.width = width;
        desc.height = height;
        desc.bpp = self->_bpp;
        desc.alpha = self->_alpha;
        desc.bppDepth = self->_bppDepth;
        desc.clearDepth = 0.0f;
        desc.scale = 1.0f;
        self->_renderDestinationHandle = ((VisualContext *)self->_vc)->createRenderDestination(&desc);
    }
    ((VisualContext *)self->_vc)->beginWindow();
    self->_open = 1;
    return 1;
}

void Gap__igPsx2Window__vfunc_27(int *arg0, char *arg1) {
    int *old;
    int *hdr;
    int *s;
    int v;
    if ((arg1 != 0) && (*arg1 != 0)) {
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(0x10);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        s = StringPool_Intern(DAT_00586f20[0], arg1);
        old = (int *)arg0[8];
        if (old != 0) {
            hdr = old - 2;
            v = old[-1] - 1;
            old[-1] = v;
            if (v == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
        arg0[8] = (int)s;
    }
}

int Gap__igPsx2Window__vfunc_34(void *arg0, int dummy1, int arg2, int arg3, int arg4) {
    *(int *)((char *)(arg0) + 8) = arg2;
    *(int *)((char *)(arg0) + 12) = arg3;
    *(int *)((char *)(arg0) + 44) = arg4;
    return 1;
}

void Gap__igPsx2Window__vfunc_35(void *arg0, char *arg1, int *arg2, int *arg3, int *arg4) {
    *arg1 = 1;
    if (arg2 != 0) {
        *arg2 = *(int *)((char *)(arg0) + 8);
    }
    if (arg3 != 0) {
        *arg3 = *(int *)((char *)(arg0) + 12);
    }
    if (arg4 != 0) {
        *arg4 = *(int *)((char *)(arg0) + 44);
    }
}

int Gap__igPsx2Window__vfunc_22(void) {
    return DAT_0055f6c8[0];
}

int Gap__igPsx2Window__vfunc_28(void *arg0) {
    return *(int *)((char *)(arg0) + 32);
}

void Gap__igPsx2Window__vfunc_29(void) {

}

void Gap__igPsx2Window__vfunc_30(void *d0, int *arg1, int *arg2) {
    *arg1 = 0;
    *arg2 = 0;
}

void Gap__igPsx2Window__vfunc_31(void) {

}

void Gap__igPsx2Window__vfunc_32(void *d0, int *arg1, int *arg2) {
    *arg1 = 0x280;
    *arg2 = 0x1C0;
}

void Gap__igPsx2Window__vfunc_36(void) {

}

int Gap__igPsx2Window__vfunc_37(void) {
    return 1;
}

/* IgPsx2Window vtable slot 38, a plain getter that returns the reflected field _vc (the window's
 * visual context reference, igPsx2Window +24). */

int Gap__igPsx2Window__vfunc_38(igPsx2Window *self) {
    return self->_vc;
}

/* igPsx2Window vtable slot 42 (+0xa8): leaf that returns 0 and ignores the window, the PS2
 * backend's "nothing to report" answer for an igWindow virtual (igWindow serialises no fields). */
int Gap__igPsx2Window__vfunc_42(igPsx2Window *self) {
    return 0;
}

void Gap__igPsx2Window__vfunc_33(void *d0, int *arg1, int *arg2) {
    *arg1 = 0x280;
    *arg2 = 0x1C0;
}

void Gap__igPsx2Window__vfunc_40(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}

/* igPsx2Window vtable slot 41 (+0xa4): leaf that returns 0 and ignores the window, the PS2
 * backend's "nothing to report" answer for an igWindow virtual (igWindow serialises no fields). */
int Gap__igPsx2Window__vfunc_41(igPsx2Window *self) {
    return 0;
}

void Gap__igPsx2Window__vfunc_23(void) {

}

/* Reports whether the window is open: returns _open (+40). */

unsigned char Gap__igPsx2Window__vfunc_43(igPsx2Window *self) {
    return self->_open;
}

