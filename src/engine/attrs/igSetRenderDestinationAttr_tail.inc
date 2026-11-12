static inline void setDestination(Attr *self, const igSmartPointer<Destination> &destination) {
    Destination *held = destination.get();
    Destination *previous;
    if (held != 0) {
        held->_refCount = held->_refCount + 1;
    }
    previous = self->f12;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->f12 = held;
}

void Gap__Attrs__igSetRenderDestinationAttr__vfunc_26(Attr *self, int value) {
    if (self->f12 == 0) {
        setDestination(self, igSmartPointer<Destination>((Destination *)FUN_001341b0(igObject_GetAllocator())));
    }
    ((Renderable *)self->f12)->vX(value);
}

void Gap__Attrs__igSetRenderDestinationAttr__vfunc_12(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
    Gap__Core__igObject__vfunc_10(arg0);
}

void Gap__Attrs__igSetRenderDestinationAttr__vfunc_28(igSetRenderDestinationAttr *self) {
    void **renderDestination;

    renderDestination = (void **)(self->_pRDAttr);
    if (renderDestination != 0) {
        ((BoundRenderDestinationVtable *)(renderDestination))->vX();
    }
}

