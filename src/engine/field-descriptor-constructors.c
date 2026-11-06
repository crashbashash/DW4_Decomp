/* Constructor / initializer chains of the reflection field descriptors (igMetaField and its Int,
 * UnsignedInt, Ref, ObjectRef and String subclasses; finding #880). Every class has two entry
 * points. <Class>_Construct builds the base part, stamps the class vtable and, when the object
 * exists, runs <Class>_Init. <Class>_Init runs the base Init, stamps the vtable again (so a
 * subclass vtable is replaced by the more derived one) and sets that class's field defaults.
 * Reflected members are proven offsets; the leading vtable word is an explicit ABI projection. */
#include "dw4/reflected.h"
void *igObject_ConstructHeader(void *);
igMetaField *igMetaField_Init(igMetaField *);
void *igMetaField_Construct(igMetaField *);
void *igRefMetaField_Construct(igRefMetaField *);
void *igRefMetaField_Init(igRefMetaField *);
void *igIntMetaField_Init(igMetaField *);
void *igObjectRefMetaField_Init(igObjectRefMetaField *);
void *igStringMetaField_Init(igStringMetaField *);
void *igUnsignedIntMetaField_Init(igMetaField *self);
/* class vtables, named after the <Class>_Init that stamps each one */
extern int g_igMetaField_vtable[4];
extern int g_igRefMetaField_vtable[4];
extern int g_igIntMetaField_vtable[4];
extern int g_igObjectRefMetaField_vtable[4];
extern int g_igStringMetaField_vtable[4];
extern int g_igUnsignedIntMetaField_vtable[4];

void *igIntMetaField_Construct(igMetaField *self) {
    igMetaField_Construct(self);
    self->_vtable = (int)g_igIntMetaField_vtable;
    if (self) {
        igIntMetaField_Init(self);
    }
    return self;
}

void *igIntMetaField_Init(igMetaField *self) {
    igMetaField_Init(self);
    self->_vtable = (int)g_igIntMetaField_vtable;
    return self;
}

void *igMetaField_Construct(igMetaField *self) {
    igObject_ConstructHeader(self);
    self->_vtable = (int)g_igMetaField_vtable;
    self->_fieldName = 0;
    if (self) {
        igMetaField_Init(self);
    }
    return self;
}

void *igObjectRefMetaField_Construct(igObjectRefMetaField *self) {
    igRefMetaField_Construct((igRefMetaField *)self);
    self->_vtable = (int)g_igObjectRefMetaField_vtable;
    self->_poolName = 0;
    if (self) {
        igObjectRefMetaField_Init(self);
    }
    return self;
}

void *igObjectRefMetaField_Init(igObjectRefMetaField *self) {
    igRefMetaField_Init((igRefMetaField *)self);
    self->_vtable = (int)g_igObjectRefMetaField_vtable;
    self->_poolName = 0;
    self->_refCounted = 1;
    self->_metaObject = 0;
    return self;
}

void *igRefMetaField_Construct(igRefMetaField *self) {
    igMetaField_Construct((igMetaField *)self);
    self->_vtable = (int)g_igRefMetaField_vtable;
    if (self) {
        igRefMetaField_Init(self);
    }
    return self;
}

void *igRefMetaField_Init(igRefMetaField *self) {
    igMetaField_Init((igMetaField *)self);
    self->_vtable = (int)g_igRefMetaField_vtable;
    self->_construct = 0;
    self->_destruct = 0;
    return self;
}

void *igStringMetaField_Construct(igStringMetaField *self) {
    igRefMetaField_Construct((igRefMetaField *)self);
    self->_vtable = (int)g_igStringMetaField_vtable;
    if (self) {
        igStringMetaField_Init(self);
    }
    return self;
}

void *igStringMetaField_Init(igStringMetaField *self) {
    igRefMetaField_Init((igRefMetaField *)self);
    self->_vtable = (int)g_igStringMetaField_vtable;
    self->_refCounted = 1;
    self->_shallowCopyMethod = 2;
    self->_destruct = 1;
    return self;
}

void *igUnsignedIntMetaField_Construct(igMetaField *self) {
    igMetaField_Construct(self);
    self->_vtable = (int)g_igUnsignedIntMetaField_vtable;
    if (self) {
        igUnsignedIntMetaField_Init(self);
    }
    return self;
}

void *igUnsignedIntMetaField_Init(igMetaField *self) {
    igMetaField_Init(self);
    self->_vtable = (int)g_igUnsignedIntMetaField_vtable;
    return self;
}
