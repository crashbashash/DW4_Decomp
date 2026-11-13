void igVec3fMetaField_SwapBytes(igVec3fMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(FUN_002c4870());
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * (((unsigned int)arg0->_size) >> 2)));
}

void Gap__igVec3fMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    FUN_0018be80(arg2, arg1, 3, 4, 1);
}

void Gap__igVec3fMetaField__vfunc_57(char **out, int unused, float *v)
{
    char buf[1024];
    char *s;
    void *pool;

    sprintf(buf, text_f_f_f, v[0], v[1], v[2]);
    if (buf == 0) {
        s = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = StringPool_Allocate(16);
            if (pool != 0)
                pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        s = (char *)StringPool_Intern(g_stringPool[0], buf);
    }
    *out = s;
}

/* igMetaField slot +0x64 (GetSize): the byte size of one field value. A Vec3f is three 32-bit
 * floats, 12 bytes. The field constructor stores this result as the field's `_size` (+0x14). */
int igVec3fMetaField_GetSize(void) {
    return 0xC;
}

void FUN_0018e470(igVec3fMetaFieldView *self, const float *value)
{
    self->SetDefault(value);
}

/* Override of the igMetaField slot at vtable +0x6c (slot 27): returns 16, one quadword rather than
 * the 12-byte element size. The receiver is not read. */
int Gap__igVec3fMetaField__vfunc_27(void) {
    return 0x10;
}

