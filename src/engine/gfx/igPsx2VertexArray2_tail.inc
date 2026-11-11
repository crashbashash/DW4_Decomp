int Gap__Gfx__igPsx2VertexArray2__vfunc_23(igVertexArray2 *array, int primitive, int arg2, Info *info, Disp *display) {
    if (array->_vertexStream == 0) {
        igSmartPointer<Rc_17f2b0> created((Rc_17f2b0 *)FUN_0014adc0(igObject_GetAllocator(array)));
        Rc_17f2b0 *stream = created.p;
        if (stream != 0) stream->_refCount = stream->_refCount + 1;
        Rc_17f2b0 *old = (Rc_17f2b0 *)array->_vertexStream;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        array->_vertexStream = (int)stream;
    }
    igVertexStream *vs = (igVertexStream *)array->_vertexStream;
    if (vs->_isConfigured != 0) return 1;
    igSmartPointer<Rc_17f2b0> format((Rc_17f2b0 *)FUN_0014b180(igObject_GetAllocator(array)));
    FUN_0015f660(array, format);
    if (info != 0 && info->f12 > 1 && !(primitive & 0x2000)) {
        switch (primitive) {
        case 4: primitive = 0x2001; break;
        case 2: primitive = 0x2000; break;
        case 5: primitive = 0x2002; break;
        }
    }
    vs->_primitive = primitive;
    display->v1044(array, 0);
    int result = ((Impl *)vs)->v104(format, arg2, info, display) & 0xFF;
    return result;
}

void Gap__Gfx__igPsx2VertexArray2__vfunc_12(igPsx2VertexArray2View *self)
{
    self->vfunc_22();
}

void Gap__Gfx__igPsx2VertexArray2__vfunc_24(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 20));
    if (temp_a0 != 0) {
        ((DW4VC_108_0 *)(temp_a0))->vX();
    }
}

