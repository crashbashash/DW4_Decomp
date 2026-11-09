#include "dw4/reflected.h"
class CopyableObject {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15();
    virtual void prepareCopy();
    virtual void s17(); virtual void s18();
    virtual CopyableObject *duplicate(int deep);
    unsigned int _refCount;
};
extern "C" {
void FUN_003006a0(CopyableObject *dst, CopyableObject *src);
void igObjectRefMetaField_Assign(igObjectRefMetaField *field, void *object, CopyableObject *value);
void igObject_Destroy(void *object);
void Gap__Core__igObjectRefMetaField__vfunc_36(igObjectRefMetaField *self, char *dst, char *src);
}
void Gap__Core__igObjectRefMetaField__vfunc_36(igObjectRefMetaField *self, char *dst, char *src) {
    CopyableObject *to;
    CopyableObject *from;
    CopyableObject *copy;

    to = *(CopyableObject **)(dst + self->_offset);
    from = *(CopyableObject **)(src + self->_offset);
    if (to != 0 || from != 0) {
        if (to != 0 && from != 0) {
            from->prepareCopy();
            FUN_003006a0(to, from);
            return;
        }
        if (to == 0) {
            from->prepareCopy();
            copy = from->duplicate(1);
            igObjectRefMetaField_Assign(self, dst, copy);
            if (self->_destruct == 0 && copy != 0) {
                copy->_refCount = copy->_refCount - 1;
                if ((copy->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(copy);
                }
            }
        } else if (from == 0) {
            igObjectRefMetaField_Assign(self, dst, 0);
        }
    }
}
