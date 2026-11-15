int igUnsignedLongMetaField_ValueFromString(int self, int value, int text) {
    int consumed;

    consumed = 0;
    sscanf(text, "%ld%n", value, &consumed);
    return consumed;
}

void igUnsignedLongMetaField_ValueToString(int *out, int self, long long *value) {
    struct { int w; int pad[255]; } text;
    int pool;
    int interned;

    sprintf((int *)&text, "%ld", *value);
    if ((int *)&text == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = pool;
        }
        interned = StringPool_Intern((StringPool *)g_stringPool, (const char *)((int *)&text));
    }
    *out = interned;
}

int igUnsignedLongMetaField_GetSize(void) {
    return 8;
}

int **igUnsignedLongMetaField_Construct(int **self, int extra1) {
    igMetaField_Construct((igMetaField *)self);
    *self = &g_igUnsignedLongMetaField_vtable[0];
    if (self != 0) {
        igUnsignedLongMetaField_Init(self);
    }
    return self;
}

int **igUnsignedLongMetaField_Init(int **self) {
    igMetaField_Init((igMetaField *)self);
    *self = &g_igUnsignedLongMetaField_vtable[0];
    return self;
}

int **igUnsignedLongMetaField_CopyConstruct(int **self, int source) {
    igMetaField_CopyConstruct((igMetaField *)self, (igMetaField *)source);
    *self = &g_igUnsignedLongMetaField_vtable[0];
    return self;
}

void igUnsignedLongMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

void igUnsignedLongMetaField_SetDefaultValue(void **field, unsigned long long value) {
    unsigned long long defaultValue = value;
    ((igMetaFieldView *)field)->SetDefault(&defaultValue);
}

/* igUnsignedLongArrayMetaField vtable slot 27 (+0x6c): constant leaf returning 8, the byte size of
 * one unsigned long element (a 64-bit value on this target). The same igMetaField slot is the
 * base's `return -1` and igStructMetaField's `_alignment` accessor. */
int igUnsignedLongMetaField_GetAlignment(igUnsignedLongArrayMetaField *self) {
    return 8;
}

