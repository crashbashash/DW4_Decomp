int igIntMetaField_ValueFromString(int self, int value, int text) {
    int consumed;

    consumed = 0;
    sscanf(text, &percent_d_percent_n[0], value, &consumed);
    return consumed;
}

void igIntMetaField_ValueToString(int *result, int self, int *value) {
    int buffer[256];
    int pool;
    int interned;

    sprintf(&buffer[0], &percent_d_7[0], *value);
    if (&buffer[0] == 0) {
        interned = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool[0] = pool;
        }
        interned = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&buffer[0]);
    }
    *result = interned;
}

int igIntMetaField_GetSize(void) {
    return 4;
}

void *igIntMetaField_Construct(igMetaField *self, int extra1) {
    igMetaField_Construct(self);
    self->_vtable = (int)g_igIntMetaField_vtable;
    if (self) {
        igIntMetaField_Init(self);
    }
    return self;
}

void *igIntMetaField_Init(igMetaField *self) {
    igMetaField_Init(self);
    self->_vtable = (int)g_igIntMetaField_vtable;
    return self;
}

int **igIntMetaField_CopyConstruct(int **self, int source) {
    igMetaField_CopyConstruct((igMetaField *)self, (igMetaField *)source);
    *self = &g_igIntMetaField_vtable[0];
    return self;
}

void igIntMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

void igIntMetaField_SetDefault(void **self, int value) {
    int defaultValue;

    defaultValue = value;
    ((igMetaFieldView *)(self))->SetDefault(&defaultValue);
}

int igIntMetaField_GetAlignment(void) {
    return 4;
}

