int igDoubleMetaField_ValueFromString(int self, int value, int text) {
    int consumed;

    consumed = 0;
    sscanf(text, "%lg%n", value, &consumed);
    return consumed;
}

void igDoubleMetaField_ValueToString(int *out, int self, long long *value) {
    int buffer[256];
    int pool;
    int interned;

    sprintf(buffer, "%g", *value);
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

int igDoubleMetaField_GetSize(void) {
    return 8;
}

void igDoubleMetaField_SetDefaultDouble(void **field, long long value) {
    long long defaultValue;

    defaultValue = value;
    ((igMetaFieldView *)(field))->SetDefault(&defaultValue);
}

int igDoubleMetaField_GetAlignment(void) {
    return 8;
}

