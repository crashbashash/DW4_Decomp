void Gap__Attrs__igRenderListAttr__vfunc_24(void *arg0, int arg1) {
    int temp_v1;

    temp_v1 = *(int *)((char *)(arg0) + 12);
    if (temp_v1 >= 0) {
        Gap__Gfx__igPsx2VisualContext__vfunc_196(arg1, temp_v1);
    }
}

void Gap__Attrs__igRenderListAttr__vfunc_26(void) {

}

void Gap__Attrs__igRenderListAttr__vfunc_12(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
    Gap__Core__igObject__vfunc_10(arg0);
}

void Gap__Attrs__igRenderListAttr__vfunc_28(O_13ffd0 *arg0) {
    V772 *o;
    if (arg0->f12 != -1) {
        arg0->obj->vX(arg0->f12);
    }
    arg0->f12 = -1;
    o = arg0->obj;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->obj = 0;
}

int FUN_00140050(void *arg0) {
    return *(int *)((char *)(arg0) + 104);
}

struct SetRenderDestinationAttrView {
    int _vtable;
    unsigned int _refCount;
    short _cachedAttrIndex;
    short _cachedUnitID;
    RenderDestinationAttrView *_pRDAttr;
};

extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_48(igObject *context, int renderDestination, int *textureIndex);
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_49(igObject *context, int renderDestination, int *textureIndex, int flags);


