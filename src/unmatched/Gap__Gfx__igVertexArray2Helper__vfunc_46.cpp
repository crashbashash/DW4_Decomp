#include "dw4/reflected.h"
extern "C" {
void *igVertexArray2__FindVertexData(...);
extern int DAT_00586818[4];
extern int DAT_005610b0[4];
extern int DAT_00561098[4];
/* matching construct: a small sweep of spellings */
void Gap__Gfx__igVertexArray2Helper__vfunc_46(igVertexArray2Helper *helper, int component, int index, unsigned char value);
}
class ByteList {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19();
    virtual int getMeta();
    int _refCount;
    int _count;
    int _capacity;
    int _data;
};
struct VertexData { char pad[12]; ByteList *list; int f16; int f20; int stride; };
struct Byte3 { unsigned char c[3]; Byte3() {} Byte3(const Byte3 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; } Byte3 &operator=(const Byte3 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; return *this; } unsigned char &operator[](int i) { return c[i]; } };
struct Byte4 { unsigned char c[4]; Byte4() {} Byte4(const Byte4 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; c[3] = o.c[3]; } Byte4 &operator=(const Byte4 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; c[3] = o.c[3]; return *this; } unsigned char &operator[](int i) { return c[i]; } };
void Gap__Gfx__igVertexArray2Helper__vfunc_46(igVertexArray2Helper *helper, int component, int index, unsigned char value) {
    VertexData *v;
    int meta;
    ByteList *l;
    v = (VertexData *)igVertexArray2__FindVertexData(helper->_vertexArray, 6, 0);
    meta = DAT_00586818[0];
    if (meta == v->list->getMeta()) {
        int i;
        l = v->list;
        i = component + index * v->stride;
        if (l->_count != 0 && i >= 0 && i < l->_count) {
            ((unsigned char *)l->_data)[i] = value;
        }
    } else {
        meta = DAT_005610b0[0];
        if (meta == v->list->getMeta()) {
            l = v->list;
            Byte3 *q = (Byte3 *)l->_data + index;
            Byte3 t(*q);
            t[component] = value;
            if (l->_count != 0 && index >= 0 && index < l->_count) {
                *q = t;
            }
        } else {
            meta = DAT_00561098[0];
            if (meta == v->list->getMeta()) {
                l = v->list;
                Byte4 *q = (Byte4 *)l->_data + index;
                Byte4 t(*q);
                t[component] = value;
                if (l->_count != 0 && index >= 0 && index < l->_count) {
                    *q = t;
                }
            }
        }
    }
}
