#include "dw4/reflected.h"
extern "C" {
int FUN_0026ce40(int, int);
int FUN_0026cf70(int);
int FUN_00295468(int);
int igObject_IsKindOf(void *, int);
extern int DAT_00587760[4];
int Gap__igCriMovieCodec__vfunc_26(void *arg0, igMovieInfo *arg1, int arg2) {
    void *obj;
    igCriMovieData *r;
    obj = (void *)arg1->_userdata;
    if (obj != 0 && igObject_IsKindOf(obj, DAT_00587760[0]) != 0) {
        r = (igCriMovieData *)obj;
    } else {
        r = 0;
    }
    if (r != 0) {
        int *p;
        arg1->_state = arg2;
        if (arg1->_type == 2) {
            if (FUN_0026cf70(r->_adxt) == 0) {
                FUN_0026ce40(r->_adxt, 1);
            }
        } else if (FUN_00295468(r->_mwply) == 0) {
            p = (int *)r->_mwply;
            ((int (*)(int *, int))*(int *)(*p + 40))(p, 1);
        }
        return 1;
    }
    return 0;
}
}
