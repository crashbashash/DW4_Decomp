void igRenderListAttr_apply(igRenderListAttr *self, igPsx2VisualContext *arg1) {
    int temp_v1;

    temp_v1 = self->_handle;
    if (temp_v1 >= 0) {
        igPsx2VisualContext_ExecuteRenderList(arg1, temp_v1);
    }
}

void igRenderListAttr_SynchronizeDefault(void) {

}

void igRenderListAttr_ReleaseDefaults(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
    igObject_ReleaseDefaults((igObject *)arg0);
}

void igRenderListAttr_Reset(O_13ffd0 *arg0) {
    V772 *o;
    if (arg0->f12 != -1) {
        arg0->obj->vX(arg0->f12);
    }
    arg0->f12 = -1;
    o = arg0->obj;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
            igObject_Destroy((igObject *)o);
        }
    }
    arg0->obj = 0;
}

int igVisualContext_GetScissorType(void *arg0) {
    return *(int *)((char *)(arg0) + 104);
}

struct SetRenderDestinationAttrView {
    int _vtable;
    unsigned int _refCount;
    short _cachedAttrIndex;
    short _cachedUnitID;
    RenderDestinationAttrView *_pRDAttr;
};



