int igUnsignedShortMetaField_ValueFromString(int self, int value, int text) {
    int consumed;

    consumed = 0;
    sscanf(text, "%hd%n", value, &consumed);
    return consumed;
}

void igUnsignedShortMetaField_ValueToString(int *out, int self, unsigned short *value) {
    char buffer[1024];
    int pool;
    int interned;

    sprintf(buffer, "%hd", *value);
    if (buffer == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = pool;
        }
        interned = StringPool_Intern((StringPool *)g_stringPool, (const char *)buffer);
    }
    *out = interned;
}

int igUnsignedShortMetaField_GetSize(void) {
    return 2;
}

void igUnsignedShortMetaField_SetDefaultValue(void **self, short value) {
    short stored;

    stored = value;
    ((igMetaFieldView *)(self))->SetDefault(&stored);
}

int **igUnsignedShortMetaField_Construct(int **self, int flags) {
    igMetaField_Construct((igMetaField *)self);
    *self = &g_igUnsignedShortMetaField_vtable[0];
    if (self != 0) {
        igUnsignedShortMetaField_Init(self);
    }
    return self;
}

int **igUnsignedShortMetaField_Init(int **self) {
    igMetaField_Init((igMetaField *)self);
    *self = &g_igUnsignedShortMetaField_vtable[0];
    return self;
}

int **igUnsignedShortMetaField_CopyConstruct(int **self, int source) {
    igMetaField_CopyConstruct((igMetaField *)self, (igMetaField *)source);
    *self = &g_igUnsignedShortMetaField_vtable[0];
    return self;
}

void igUnsignedShortMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

/* igUnsignedShortArrayMetaField vtable slot 27 (+0x6c): constant leaf returning 2, the byte size
 * of one unsigned short element. The same igMetaField slot is the base's `return -1` and
 * igStructMetaField's `_alignment` accessor. */
int igUnsignedShortMetaField_GetAlignment(igUnsignedShortArrayMetaField *self) {
    return 2;
}

