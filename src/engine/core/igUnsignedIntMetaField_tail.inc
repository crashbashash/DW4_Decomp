int igUnsignedIntMetaField_ValueFromString(int self, int value, int text) {
    int consumed;

    consumed = 0;
    sscanf(text, &text_u_n[0], value, &consumed);
    return consumed;
}

void igUnsignedIntMetaField_ValueToString(int *out, void *self, int *value) {
    int buffer[256];
    int pool;
    int interned;

    sprintf(buffer, &percent_ud[0], *value);
    if (buffer == 0) {
        interned = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool[0] = pool;
        }
        interned = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)buffer);
    }
    *out = interned;
}

/* Vtable slot 53 of igNonRefCountedThreadList: a constant leaf returning 4. The list's element
 * type is igUnsignedIntMetaField (slots 50 and 51 hand out that class's metaobject and
 * descriptor), so 4 is read as the element size in bytes. The receiver is not touched, hence no
 * parameters. */
int igUnsignedIntMetaField_GetSize(void) {
    return 4;
}

void *igUnsignedIntMetaField_Construct(igMetaField *self, int extra1) {
    igMetaField_Construct(self);
    self->_vtable = (int)g_igUnsignedIntMetaField_vtable;
    if (self) {
        igUnsignedIntMetaField_Init(self);
    }
    return self;
}

void *igUnsignedIntMetaField_Init(igMetaField *self) {
    igMetaField_Init(self);
    self->_vtable = (int)g_igUnsignedIntMetaField_vtable;
    return self;
}

int **igUnsignedIntMetaField_CopyConstruct(int **self, int source) {
    igMetaField_CopyConstruct((igMetaField *)self, (igMetaField *)source);
    *self = &g_igUnsignedIntMetaField_vtable[0];
    return self;
}

void igUnsignedIntMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

void igUnsignedIntMetaField_SetDefaultValue(void **self, int value) {
    int stored;

    stored = value;
    ((igMetaFieldView *)(self))->SetDefault(&stored);
}

int igUnsignedIntMetaField_GetAlignment(void) {
    return 4;
}

