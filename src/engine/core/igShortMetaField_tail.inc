int igShortMetaField_ValueFromString(int self, int value, int text) {
    int consumed;

    consumed = 0;
    sscanf(text, "%hd%n", value, &consumed);
    return consumed;
}

void igShortMetaField_ValueToString(int *out, int self, short *value) {
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

int **igShortMetaField_Construct(int **self, int source) {
    igMetaField_Construct((igMetaField *)self);
    *self = &g_igShortMetaField_vtable[0];
    if (self != 0) {
        igShortMetaField_Init(self);
    }
    return self;
}

int **igShortMetaField_Init(int **self) {
    igMetaField_Init((igMetaField *)self);
    *self = &g_igShortMetaField_vtable[0];
    return self;
}

int **igShortMetaField_CopyConstruct(int **self, int source) {
    igMetaField_CopyConstruct((igMetaField *)self, (igMetaField *)source);
    *self = &g_igShortMetaField_vtable[0];
    return self;
}

void igShortMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

/* igRegistryValueList vtable slot 53 (+0xd4): constant leaf returning 2. */
int igShortMetaField_GetSize(igRegistryValueList *self) {
    return 2;
}

void igShortMetaField_SetDefault(void **self, short value) {
    short defaultValue;

    defaultValue = value;
    ((igMetaFieldView *)(self))->SetDefault(&defaultValue);
}

int igShortMetaField_GetAlignment(void) {
    return 2;
}

