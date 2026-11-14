void igCharArrayMetaField_SwapBytes(igCharArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)igCharMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

/* IgCharArrayMetaField virtual getter 25. Returns the array's storage size in bytes as 16 bits:
 * `_num` elements of one byte each, so it is `_num` itself (compare
 * igEnumArrayMetaField::vfunc_25, which scales by 4). */

unsigned short igCharArrayMetaField_GetSize(igCharArrayMetaField *self) {
    return self->_num;
}

void igCharArrayMetaField_SetDefaultElement(void *arg0, int arg1, char arg2) {
    ((igMetaFieldView *)(((char *)(arg0) + 0)))->SetDefault(0);
    *(char *)(*(int *)((char *)(arg0) + 32) + arg1) = arg2;
}

