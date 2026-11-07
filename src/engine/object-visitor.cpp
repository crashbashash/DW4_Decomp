/* Callback-driven object and field traversal; the virtual types project observed ABI slots. */
#include "dw4/reflected.h"
class VisitorObjectView {public:
virtual void o0();
virtual void o1();
virtual void o2();
virtual void o3();
virtual void o4();
virtual void o5();
virtual void o6();
virtual void o7();
virtual void o8();
virtual void o9();
virtual void o10();
virtual void o11();
virtual void o12();
virtual void o13();
virtual void o14();
virtual void o15();
virtual void Prepare();virtual void o76();virtual void o80();virtual void o84();virtual igMetaObject *Meta();};
typedef int (*Visitor)(void *,void *,void *);
class VisitorFieldView {public:
virtual void f0();
virtual void f1();
virtual void f2();
virtual void f3();
virtual void f4();
virtual void f5();
virtual void f6();
virtual void f7();
virtual void f8();
virtual void f9();
virtual void f10();
virtual void f11();
virtual void f12();
virtual void f13();
virtual void f14();
virtual void f15();
virtual void f16();
virtual void f17();
virtual void f18();
virtual void f19();
virtual void f20();
virtual void f21();
virtual void f22();
virtual void f23();
virtual void f24();
virtual void f25();
virtual void f26();
virtual void f27();
virtual void f28();
virtual void f29();
virtual void f30();
virtual void f31();
virtual void f32();
virtual void f33();
virtual void f34();
virtual void f35();
virtual void f36();
virtual void f37();
virtual void f38();
virtual void f39();
virtual void Visit(void *,Visitor,void *);};
struct FieldVector {int vt,refs;VisitorFieldView **data;int count;};
extern "C" int igMetaObject_GetFieldCount(igMetaObject *);
extern "C" int g_igObject_metaObject[4];
extern "C" void igObject_VisitFields(VisitorObjectView *object,Visitor callback,void *context){
    FieldVector *fields;
    int count;
    int i;
    VisitorFieldView *field;
    if(callback(object,0,context)==1)return;
    object->Prepare();
    fields=(FieldVector *)object->Meta()->_metaFields;
    count=fields->count;
    for(i=igMetaObject_GetFieldCount((igMetaObject *)g_igObject_metaObject[0]);i<count;++i){
        field=fields->data[i];
        if(callback(object,field,context)!=1)field->Visit(object,callback,context);
    }
}
