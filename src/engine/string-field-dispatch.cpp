/* Exact field dispatch and shared string comparisons. Virtual declarations
 * project target byte slots and must not be instantiated as objects. */

#include "dw4/reflected.h"
extern "C" int igStrCmp(const char *,const char *);

class FieldResetDispatchView {public: virtual void reserved0(); virtual void reserved1(); virtual void reserved2(); virtual void reserved3(); virtual void reserved4(); virtual void reserved5(); virtual void reserved6(); virtual void reserved7(); virtual void reserved8(); virtual void reserved9(); virtual void reserved10(); virtual void reserved11(); virtual void reserved12(); virtual void reserved13(); virtual void reserved14(); virtual void reserved15(); virtual void reserved16(); virtual void reserved17(); virtual void reserved18(); virtual void reserved19(); virtual void reserved20(); virtual void reserved21(); virtual void reserved22(); virtual void reserved23(); virtual void reserved24(); virtual void reserved25(); virtual void Reset0(void *); virtual void Reset3(void *); virtual void Reset2(void *);};
extern "C" void igMetaField_Reset(igMetaField *field,void *object){
    switch(field->_resetMethod){
    case 0: ((FieldResetDispatchView *)field)->Reset0(object); break;
    case 3: ((FieldResetDispatchView *)field)->Reset3(object); break;
    case 2: ((FieldResetDispatchView *)field)->Reset2(object); break;
    }
}

class FieldWriteDispatchView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int Write(void *,void *,void *,long long); };
extern "C" int igMetaField_WritePersistentValue(igMetaField *field,void *object,void *output,void *context,long long swap){
    if(field->_persistent==0)return 0;
    return (((FieldWriteDispatchView *)field)->Write((char *)object+field->_offset,output,context,swap)+3)&~3;
}

extern "C" bool Gap__Core__igStringArrayMetaField__vfunc_45(igStringMetaField *field,const void *one,const void *two){
    int offset=field->_offset;
    const char *left=*(const char **)((const char *)one+offset);
    const char *right=*(const char **)((const char *)two+offset);
    if(left==right)return true;
    if(!left||!right)return false;
    return !bool(igStrCmp(left,right));
}

extern "C" bool Gap__Core__igStringArrayMetaField__vfunc_46(igStringMetaField *field,const void *one,const void *two){
    int offset=field->_offset;
    const char *left=*(const char **)((const char *)one+offset);
    const char *right=*(const char **)((const char *)two+offset);
    if(left==right)return true;
    if(!left||!right)return false;
    return !bool(igStrCmp(left,right));
}

extern "C" bool Gap__Core__igStringArrayMetaField__vfunc_47(igStringMetaField *field,const void *one,const void *two){
    int offset=field->_offset;
    const char *left=*(const char **)((const char *)one+offset);
    const char *right=*(const char **)((const char *)two+offset);
    if(left==right)return true;
    if(!left||!right)return false;
    return !bool(igStrCmp(left,right));
}
