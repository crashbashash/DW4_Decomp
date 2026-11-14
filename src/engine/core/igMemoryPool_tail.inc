int **igMemoryPool_Initialize(int **self) {
    igObject_InitHeader((igObject *)self);
    *self = &g_igMemoryPool_vtable[0];
    return self;
}

int **igMemoryPool_Construct(int **self) {
    igObject_ConstructHeader((igObject *)self);
    *self = &g_igMemoryPool_vtable[0];
    return self;
}

igMemoryPool *igMemoryPool_CopyConstruct(igMemoryPool *self, igMemoryPool *source) {
    igObject_CopyConstructHeader((igObject *)self, (igObject *)source);
    self->_vtable = (int)&g_igMemoryPool_vtable[0];
    return self;
}
