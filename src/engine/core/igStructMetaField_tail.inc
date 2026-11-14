unsigned short Gap__Core__igStructMetaField__vfunc_25(void *arg0) {
    return *(int *)((char *)(arg0) + 20);
}

void Gap__Core__igStructMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    strlen(arg2);
}

void Gap__Core__igStructMetaField__vfunc_57(int *arg0, void *arg1) {
    int temp_s0;
    int var_v0;
    int var_v1;

    temp_s0 = *(int *)((char *)(arg1) + 12);
    if (temp_s0 == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)temp_s0);
    }
    *arg0 = var_v1;
}

/* Accessor: returns the field's byte alignment (`_alignment`, igIntMetaField, +52). */
int Gap__Core__igStructMetaField__vfunc_27(igStructMetaField *self) {
    return self->_alignment;
}

void Gap__Core__igStructMetaField__vfunc_31(igStructMetaField *self, int instance) {
    int (*constructor)(int);

    constructor = (int (*)(int))(self->_cppConstructor);
    if (constructor != 0) {
        constructor(instance + self->_offset);
        return;
    }
    igMetaField_ConstructValue();
}

void Gap__Core__igStructMetaField__vfunc_32(igStructMetaField *self, int instance) {
    int (*destructor)(int);

    destructor = (int (*)(int))(self->_cppDestructor);
    if (destructor != 0) {
        destructor(instance + self->_offset);
        return;
    }
    igMetaField_DestructValue();
}

void Gap__Core__igStructMetaField__vfunc_28(igStructMetaField *self, int instance) {
    if (self->_cppConstructor != 0) {
        ((int (*)(...))self->_cppDestructor)(instance + self->_offset);
        ((int (*)(...))self->_cppConstructor)(instance + self->_offset);
        return;
    }
    igMetaField_SetToDefault((DefaultCopyField *)self, instance);
}

void Gap__Core__igStructMetaField__vfunc_30(igStructMetaFieldView *self, void *object)
{
    self->SetToDefault(object);
}

/* Predicate: true when the struct field metadata has a C++ constructor hook (`_cppConstructor`,
 * igRawRefMetaField, +56) set. */
int Gap__Core__igStructMetaField__vfunc_60(igStructMetaField *self) {
    return self->_cppConstructor != 0;
}

void FUN_0030da00(int a0, int a1)
{
    *(int *)((char *)a0 + 8) = a1;
}

