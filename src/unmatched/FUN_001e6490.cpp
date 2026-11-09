#include "dw4/igSmartPointer.h"
extern "C" {
void *igMetaObject_FindFieldByName(int, void *);
int FUN_002fe290(int, int);
extern int DAT_004e4aa0[4];
extern void *DAT_00562c60[4];
extern int DAT_00585cc8[4];
}
struct Value : public igVirtualObject { virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int type(); int offset; };
struct Source { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual Value *value(); virtual void select(int); };
struct Sink { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int type(); virtual void d21(); virtual void write(int, int); };
struct FieldDesc { int w0; int w4; int offset; };
struct ValueBinding { char pad[8]; int key; Sink *sink; char pad2[8]; Source *source; };

typedef void (*Notify)(int);
extern "C" int FUN_001e6490(ValueBinding *binding, int selection) {
    igSmartPointer<Value> value(binding->source->value(), kRetainReference);
    int sinkType = binding->sink->type();
    if (((FUN_002fe290(value->type(), sinkType) != 0) ^ 1) != 0) {
        return 0;
    }
    binding->source->select(selection);
    binding->sink->write(binding->key, (int)binding->source + value->offset);
    if (DAT_00562c60[0] == 0) {
        DAT_00562c60[0] = igMetaObject_FindFieldByName(DAT_00585cc8[0], &DAT_004e4aa0[0]);
    }
    Notify notify = *(Notify *)((char *)binding->sink + ((FieldDesc *)DAT_00562c60[0])->offset);
    if (notify != 0) {
        notify(binding->key);
    }
    return 1;
}
