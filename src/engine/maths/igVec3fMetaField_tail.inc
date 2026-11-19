void igVec3fMetaField_SwapBytes(igVec3fMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(igFloatMetaField_GetDefaultDescriptor());
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * (((unsigned int)arg0->_size) >> 2)));
}

void igVec3fMetaField_ValueFromString(int arg0, int arg1, int arg2) {
    FUN_0018be80((const char *)arg2, (void *)arg1, 3, 4, 1);
}

void igVec3fMetaField_ValueToString(char **out, int unused, float *v)
{
    char buf[1024];
    char *s;
    void *pool;

    sprintf(buf, "%f,%f,%f", v[0], v[1], v[2]);
    if (buf == 0) {
        s = 0;
    } else {
        if (g_stringPool == 0) {
            pool = StringPool_Allocate(16);
            if (pool != 0)
                pool = StringPool_Construct((StringPool *)pool);
            g_stringPool = (StringPool *)pool;
        }
        s = (char *)StringPool_Intern(g_stringPool, buf);
    }
    *out = s;
}

/* igMetaField slot +0x64 (GetSize): the byte size of one field value. A Vec3f is three 32-bit
 * floats, 12 bytes. The field constructor stores this result as the field's `_size` (+0x14). */
int igVec3fMetaField_GetSize(void) {
    return 0xC;
}

void igVec3fMetaField_SetDefault(igMetaField *self, const float *value)
{
    ((igVec3fMetaFieldView *)self)->SetDefault(value);
}

/* Override of the igMetaField slot at vtable +0x6c (slot 27): returns 16, one quadword rather than
 * the 12-byte element size. The receiver is not read. */
int igVec3fMetaField_GetAlignment(void) {
    return 0x10;
}

