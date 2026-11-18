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

void igSetRenderDestinationAttr_SynchronizeDefault(Attr *self, int value) {
    if (self->f12 == 0) {
        setDestination(self, igSmartPointer<Destination>((Destination *)igRenderDestinationAttr_Create(igObject_GetAllocator((igObject *)self))));
    }
    ((Renderable *)self->f12)->vX(value);
}

void igSetRenderDestinationAttr_ReleaseDefaults(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
    igObject_ReleaseDefaults((igObject *)arg0);
}

void igSetRenderDestinationAttr_Reset(igSetRenderDestinationAttr *self) {
    void **renderDestination;

    renderDestination = (void **)(self->_pRDAttr);
    if (renderDestination != 0) {
        ((BoundRenderDestinationVtable *)(renderDestination))->vX();
    }
}

