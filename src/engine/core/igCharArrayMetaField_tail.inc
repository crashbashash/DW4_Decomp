void Gap__Core__igCharArrayMetaField__vfunc_52(igCharArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)FUN_002cc2c0()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

/* IgCharArrayMetaField virtual getter 25. Returns the array's storage size in bytes as 16 bits:
 * `_num` elements of one byte each, so it is `_num` itself (compare
 * igEnumArrayMetaField::vfunc_25, which scales by 4). */

unsigned short Gap__Core__igCharArrayMetaField__vfunc_25(igCharArrayMetaField *self) {
    return self->_num;
}

void FUN_002d4c20(void *arg0, int arg1, char arg2) {
    ((igMetaFieldView *)(((char *)(arg0) + 0)))->SetDefault(0);
    *(char *)(*(int *)((char *)(arg0) + 32) + arg1) = arg2;
}

