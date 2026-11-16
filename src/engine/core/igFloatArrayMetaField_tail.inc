/* Storage size in bytes of the field's array: `_num` elements of 4 bytes (float), truncated to the
 * 16-bit size the meta field system uses. */

int igFloatArrayMetaField_GetSize(igFloatArrayMetaField *self) {
    return (self->_num * 4) & 0xFFFF;
}

void igFloatArrayMetaField_SwapBytes(igFloatArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)igFloatMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

int igFloatMetaField_ValueFromString(int self, int value, int text) {
    int consumed;

    consumed = 0;
    sscanf((const char *)text, "%f%n", value, &consumed);
    return consumed;
}

void igFloatMetaField_ValueToString(int *result, int self, float *value) {
    char text[1024];
    int pool;
    int interned;

    sprintf(text, "%f", fptodp(*value));
    if (text == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)text);
    }
    *result = interned;
}

