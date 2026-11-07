#include "dw4/reflected.h"
struct C { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual int v20();  };
extern "C" {
igVertexData *igVertexArray2__FindVertexData(int, int, int);
extern int DAT_005610b8[];
extern int DAT_005610a8[];
int Gap__Gfx__igVertexArray2__vfunc_25(int arg0, int arg1);
}
/* matching construct: _data is a 4-byte reference field; the casts give the typed views (no layout effect) */
int Gap__Gfx__igVertexArray2__vfunc_25(int arg0, int arg1) {
    igVertexData *h = igVertexArray2__FindVertexData(arg0, 1, arg1);
    if (h != 0) {
        int t = DAT_005610b8[0];
        if (t == ((C *)h->_data)->v20()) {
            return ((igDataList *)h->_data)->_count;
        }
        t = DAT_005610a8[0];
        if (t == ((C *)h->_data)->v20()) {
            return ((igDataList *)h->_data)->_count;
        }
    }
    return 0;
}
