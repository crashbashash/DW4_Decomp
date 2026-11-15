unsigned short igStructMetaField_GetSize(void *self) {
    return ((igMetaField *)self)->_size;
}

void igStructMetaField_ValueFromString(int self, int value, int text) {
    strlen(text);
}

void igStructMetaField_ValueToString(int *result, void *self) {
    int name;
    int pool;
    int interned;

    name = ((igMetaField *)self)->_fieldName;
    if (name == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = pool;
        }
        interned = StringPool_Intern((StringPool *)g_stringPool, (const char *)name);
    }
    *result = interned;
}

/* Accessor: returns the field's byte alignment (`_alignment`, igIntMetaField, +52). */
int igStructMetaField_GetAlignment(igStructMetaField *self) {
    return self->_alignment;
}

void igStructMetaField_ConstructValue(igStructMetaField *self, int instance) {
    int (*constructor)(int);

    constructor = (int (*)(int))(self->_cppConstructor);
    if (constructor != 0) {
        constructor(instance + self->_offset);
        return;
    }
    igMetaField_ConstructValue();
}

void igStructMetaField_DestructValue(igStructMetaField *self, int instance) {
    int (*destructor)(int);

    destructor = (int (*)(int))(self->_cppDestructor);
    if (destructor != 0) {
        destructor(instance + self->_offset);
        return;
    }
    igMetaField_DestructValue();
}

void igStructMetaField_SetToDefault(igStructMetaField *self, int instance) {
    if (self->_cppConstructor != 0) {
        ((int (*)(...))self->_cppDestructor)(instance + self->_offset);
        ((int (*)(...))self->_cppConstructor)(instance + self->_offset);
        return;
    }
    igMetaField_SetToDefault((igMetaField *)self, instance);
}

void igStructMetaField_CopyDefaultToValue(igMetaFieldView *self, void *object)
{
    self->SetToDefault((int)object);
}

/* Predicate: true when the struct field metadata has a C++ constructor hook (`_cppConstructor`,
 * igRawRefMetaField, +56) set. */
int igStructMetaField_IsConstruct(igStructMetaField *self) {
    return self->_cppConstructor != 0;
}

void igSymbolTable_SetCapacity(int table, int capacity)
{
    ((igSymbolTable *)table)->_capacity = capacity;
}

