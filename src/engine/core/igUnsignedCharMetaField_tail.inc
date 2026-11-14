int igUnsignedCharMetaField_ValueFromString(void *self, char *value, int text) {
    int consumed;
    int parsed;

    consumed = 0;
    parsed = 0;
    sscanf(text, &text_u_n[0], &parsed, &consumed);
    *value = (char) parsed;
    return consumed;
}

void igUnsignedCharMetaField_ValueToString(int *result, int self, unsigned char *value) {
    int text[256];
    int pool;
    int interned;
    sprintf(text, &percent_u[0], *value);
    if (text == 0) {
        interned = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool[0] = pool;
        }
        interned = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)text);
    }
    *result = interned;
}

/* igMetaField slot +0x64 (GetSize): the byte size of one field value. An unsigned char is a single
 * byte. The field constructor stores this result as the field's `_size` (+0x14). */
int igUnsignedCharMetaField_GetSize(void) {
    return 1;
}

void igUnsignedCharMetaField_SetDefaultValue(void **self, char value) {
    char defaultValue;

    defaultValue = value;
    ((igMetaFieldView *)(self))->SetDefault(&defaultValue);
}

int igUnsignedCharMetaField_GetAlignment(void) {
    return 1;
}

