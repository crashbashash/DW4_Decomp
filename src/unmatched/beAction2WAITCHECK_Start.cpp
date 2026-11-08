#include "dw4/reflected.h"
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class RandomSourceVirtual {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual unsigned Query();
};
extern "C" {
extern char DAT_004e0858[16];
extern int DAT_0050dfd8[4];
extern float DAT_0058a348[4];
long long __fixsfdi(float);
int FUN_003a7a20(beAction2InfoRam *, void *, long long);
int beAction2WAITCHECK_Start(beAction2 *mgr, beAction2InfoRam *act, beAction2WAITCHECK *comp) {
    beAction2InfoWork *w = (beAction2InfoWork *)act->_work;
    const char *name = (const char *)comp->_name;
    float secs = comp->_waitTime;
    const char *s = name ? name : DAT_004e0858;
    switch (*s) {
    case 'R': {
        const char *s2 = name ? name : DAT_004e0858;
        unsigned r, d;
        if (s2[3] == 'S') {
            DAT_0058a348[0] = secs;
            return 1;
        }
        d = (int)(100.0f * secs - 100.0f * DAT_0058a348[0]);
        r = ((RandomSourceVirtual *)((beSystem *)mgr->_system)->_random)->Query() % d;
        secs = DAT_0058a348[0] + (float)r / 100.0f;
    }
    case 'F':
        FUN_003a7a20(act, DAT_0050dfd8, __fixsfdi(1e9f * secs / 60.0f));
        w->_waitSt0 = 1;
        break;
    case 'M':
        w->_waitSt0 = 2;
        break;
    case 'J':
        w->_waitSt0 = 3;
        break;
    default:
        break;
    }
    return 0;
}
}
