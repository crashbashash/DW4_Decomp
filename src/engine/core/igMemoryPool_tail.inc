int **igMemoryPool_Initialize(int **arg0) {
    igObject_InitHeader((igObject *)arg0);
    *arg0 = &DAT_0052f620[0];
    return arg0;
}

int **FUN_002effb0(int **arg0) {
    igObject_ConstructHeader((igObject *)arg0);
    *arg0 = &DAT_0052f620[0];
    return arg0;
}

igMemoryPool *igMemoryPool_CopyConstruct(igMemoryPool *self, igMemoryPool *source) {
    igObject_CopyConstructHeader((igObject *)self, (igObject *)source);
    self->_vtable = (int)&DAT_0052f620[0];
    return self;
}
