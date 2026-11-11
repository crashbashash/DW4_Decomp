#include "dw4/reflected.h"

class igObjectSlot33 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vfunc_33(int); };

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

class VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void *vX(int); };
struct R { char pad[4]; int f4; };
struct M { char pad[8]; int f8; char pad2[41]; unsigned char f53; };
struct O { int p0; int p1; int f8; int f12; };

extern "C" {
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorByName(const char *);
void *igMetaObject_CreateInstance(void *, void *);
int igObject_ResetFields(int);
int igObject_VisitFields(...);
int igObject_IsAlikeExactly(int, int);
int igObject_IsAlikeDeep(int, int);
int igObject_IsAlikeShallow(int, int);
int Gap__Core__igObject__vfunc_10(...);
void Gap__Core__igObject__vfunc_09(void *);
int igRefMetaField_ReadRawFieldMem(...);
void igRefMetaField_ClearValue(igMetaField *, void *);
void *igRefMetaField_Construct(igRefMetaField *);
void *igRefMetaField_Init(igRefMetaField *);
int igRefMetaField_CopyConstruct(...);
int igRefMetaField_Destruct(...);
void FUN_003006a0(CopyableObject *dst, CopyableObject *src);
int FUN_00300770(...);
int FUN_00300490(...);
int FUN_00304430(...);
int FUN_00304680(...);
extern int DAT_004faef0[4];
extern int g_igObjectRefMetaField_vtable[4];

void FUN_00303460(igObjectRefMetaField *arg0, igObject *arg1);
void igObjectRefMetaField_Assign(igObjectRefMetaField *field, void *object, igObject *value);
void *igObjectRefMetaField_Init(igObjectRefMetaField *);

void Gap__Core__igObjectRefMetaField__vfunc_12(int arg0) {
    FUN_00303460((igObjectRefMetaField *)arg0, 0);
    Gap__Core__igObject__vfunc_10(arg0);
}

void igObjectRefMetaField_InitDefaults(void **self) {
    Gap__Core__igObject__vfunc_09(self);
    ((igObjectSlot33 *)self)->vfunc_33(0);
}

void igObjectRefMetaField_Assign(igObjectRefMetaField *field,void *object,igObject *value){
    igObject *old=*(igObject **)((char *)object+field->_offset);
    if(field->_refCounted||field->_destruct){
        if(value)++value->_refCount;
        if(old){--old->_refCount;if(!(old->_refCount&0x7fffff))igObject_Destroy(old);}
    }
    *(igObject **)((char *)object+field->_offset)=value;
}

void Gap__Core__igObjectRefMetaField__vfunc_24(int a0, int a1, int a2) {
    igObjectRefMetaField_Assign((igObjectRefMetaField *)a0, (void *)a1, (igObject *)*(int *)((char *)a2 + 0));
}

int igObjectRefMetaField_GetTypeSize(igObjectRefMetaField *) { return 4; }

void FUN_00303460(igObjectRefMetaField *arg0, igObject *arg1) {
    igObject **temp_s0;
    igObject *temp_a0;

    temp_s0 = (igObject **)(arg0->_default);
    if (arg1 != 0) {
        arg1->_refCount = (int)((int) (arg1->_refCount + 1));
    }
    temp_a0 = (igObject *)(*temp_s0);
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)((int) (temp_a0->_refCount - 1));
        if (((unsigned long long) ((long long) (int) temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    *temp_s0 = arg1;
}

void Gap__Core__igObjectRefMetaField__vfunc_51(igObjectRefMetaField *self, igObject **valueSlot) {
    igObject *object;

    igRefMetaField_ReadRawFieldMem();
    if ((self->_refCounted != 0) || (self->_destruct != 0)) {
        object = *valueSlot;
        if (object != 0) {
            object->_refCount = object->_refCount + 1;
        }
    }
}

void igObjectRefMetaField_ConstructValue(igObjectRefMetaField *field,void *object){
    void *allocator;
    if(!field->_construct)return;
    const char *name=(const char *)field->_poolName;
    if(name&&*name){allocator=Memory_GetAllocatorByName(name);if(!allocator)allocator=igObject_GetAllocator(object);}
    else allocator=igObject_GetAllocator(object);
    igObject *child=(igObject *)igMetaObject_CreateInstance((void *)field->_metaObject,allocator);
    igObjectRefMetaField_Assign(field,object,child);
    if((field->_refCounted||field->_destruct)&&child){--child->_refCount;if(!(child->_refCount&0x7fffff))igObject_Destroy(child);}
}

void igObjectRefMetaField_DestructValue(igObjectRefMetaField *field,void *object){
    if(field->_destruct){igObject *child=*(igObject **)((char *)object+field->_offset);
        if(child){--child->_refCount;if(!(child->_refCount&0x7fffff))igObject_Destroy(child);}}
}

void Gap__Core__igObjectRefMetaField__vfunc_34(igObjectRefMetaField *field,void *object){
    if(field->_refCounted){igObject *child=*(igObject **)((char *)object+field->_offset);
        if(child){--child->_refCount;if(!(child->_refCount&0x7fffff))igObject_Destroy(child);}}
    igRefMetaField_ClearValue((igMetaField *)field,object);
}

void Gap__Core__igObjectRefMetaField__vfunc_28(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)(arg1 + *(int *)((char *)arg0 + 8));
    if (temp_a0 != 0) {
        igObject_ResetFields(temp_a0);
    }
}

void Gap__Core__igObjectRefMetaField__vfunc_30(char *arg0, int arg1) {
    igObjectRefMetaField_Assign((igObjectRefMetaField *)arg0, (void *)arg1, (igObject *)**(int **)(arg0 + 32));
}

void Gap__Core__igObjectRefMetaField__vfunc_37(int arg0, int arg1, int arg2) {
    igObjectRefMetaField_Assign((igObjectRefMetaField *)arg0, (void *)arg1, (igObject *)*(int *)((char *)((arg2 + *(int *)((char *)(arg0) + 8))) + 0));
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
            igObjectRefMetaField_Assign(self, dst, (igObject *)copy);
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

void Gap__Core__igObjectRefMetaField__vfunc_38(M *arg0, int arg1, int arg2) {
    int temp_a0;
    VC_84_1 *temp_a1;
    R *temp_v0;
    int off;

    off = arg0->f8;
    temp_a0 = *(int *)(arg1 + off);
    temp_a1 = *(VC_84_1 **)(arg2 + off);
    if ((temp_a0 != 0) || (temp_a1 != 0)) {
        if ((temp_a0 != 0) && (temp_a1 != 0)) {
            FUN_00300770(temp_a0, temp_a1);
            return;
        }
        if (temp_a0 == 0) {
            temp_v0 = (R *)temp_a1->vX(0);
            igObjectRefMetaField_Assign((igObjectRefMetaField *)arg0, (void *)arg1, (igObject *)temp_v0);
            if ((arg0->f53 == 0) && (temp_v0 != 0)) {
                temp_v0->f4 = temp_v0->f4 - 1;
                if (((unsigned long long) ((long long) temp_v0->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_v0);
                }
            }
        } else if (temp_a1 == 0) {
            igObjectRefMetaField_Assign((igObjectRefMetaField *)arg0, (void *)arg1, 0);
        }
    }
}

void Gap__Core__igObjectRefMetaField__vfunc_39(igObjectRefMetaField *self, int instance) {
    int object;

    object = *(int *)(instance + self->_offset);
    if (object != 0) {
        igObject_ResetFields(object);
    }
}

void Gap__Core__igObjectRefMetaField__vfunc_41(struct O *arg0, int arg1, int arg2, int arg3) {
    int temp_a0;
    FUN_00304430(&DAT_004faef0[0], arg3, arg0->f12, *(int *)(arg1 + arg0->f8));
    FUN_00304680();
    if (arg2 != 0) {
        temp_a0 = *(int *)(arg1 + arg0->f8);
        if (temp_a0 != 0) {
            FUN_00300490(temp_a0, arg2, arg3);
        }
    }
}

void Gap__Core__igObjectRefMetaField__vfunc_42(igObjectRefMetaField *arg0, int arg1, int arg2, int arg3) {
    int temp_a0;

    temp_a0 = *(int *)(arg1 + arg0->_offset);
    if (temp_a0 != 0) {
        igObject_VisitFields(temp_a0, arg2, arg3);
    }
}

int Gap__Core__igObjectRefMetaField__vfunc_44(igObjectRefMetaField *arg0, int arg1, int arg2) {
    int temp_v0;

    temp_v0 = arg0->_offset;
    return *(int *)(arg1 + temp_v0) - *(int *)(arg2 + temp_v0);
}

int Gap__Core__igObjectRefMetaField__vfunc_45(igObjectRefMetaField *self, int objectA, int objectB) {
    int refA;
    int refB;
    int fieldOffset;

    fieldOffset = self->_offset;
    refA = *(int *)(objectA + fieldOffset);
    refB = *(int *)(objectB + fieldOffset);
    if (refA == refB) {
        return 1;
    }
    if ((refA == 0) || (refB == 0)) {
        return 0;
    }
    return igObject_IsAlikeExactly(refA, refB);
}

int Gap__Core__igObjectRefMetaField__vfunc_46(igObjectRefMetaField *self, int objectA, int objectB) {
    int refA;
    int refB;
    int fieldOffset;

    fieldOffset = self->_offset;
    refA = *(int *)(objectA + fieldOffset);
    refB = *(int *)(objectB + fieldOffset);
    if (refA == refB) {
        return 1;
    }
    if ((refA == 0) || (refB == 0)) {
        return 0;
    }
    return igObject_IsAlikeDeep(refA, refB);
}

int Gap__Core__igObjectRefMetaField__vfunc_47(igObjectRefMetaField *self, int objectA, int objectB) {
    int refA;
    int refB;
    int fieldOffset;

    fieldOffset = self->_offset;
    refA = *(int *)(objectA + fieldOffset);
    refB = *(int *)(objectB + fieldOffset);
    if (refA == refB) {
        return 1;
    }
    if ((refA == 0) || (refB == 0)) {
        return 0;
    }
    return igObject_IsAlikeShallow(refA, refB);
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

void *FUN_00303c60(igObjectRefMetaField *arg0, void *arg1) {
    igRefMetaField_CopyConstruct();
    *(int *)((char *)(arg0) + 0) = (int)(&g_igObjectRefMetaField_vtable[0]);
    arg0->_poolName = 0;
    arg0->_refCounted = (unsigned char) *(unsigned char *)((char *)(arg1) + 60);
    arg0->_metaObject = (int)((int) *(int *)((char *)(arg1) + 56));
    return arg0;
}

void Gap__Core__igObjectRefMetaField__vfunc_02(void) {
    igRefMetaField_Destruct();
}
}
