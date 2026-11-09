#include "dw4/reflected.h"

struct igResult { int value; };
class SleepingThread {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual igResult sleep(unsigned long long time);
};
struct ThreadList { int _vtable; unsigned int _refCount; int _count; int _capacity; SleepingThread **_data; };
struct ThreadManager { int _vtable; unsigned int _refCount; ThreadList *_threads; };
extern "C" {
extern ThreadManager *DAT_005871d0;
int FUN_00333970(igAdxFile *file);
void FUN_00332cd0(void);
void FUN_00332cf0(int);
int FUN_00333990(igAdxFile *file);
}

int FUN_00333990(igAdxFile *file) {
    while (FUN_00333970(file) != 3) {
        if (file->_bUseAsync && file->_bUseAlchemyAsync) {
            DAT_005871d0->_threads->_data[0]->sleep(file->_lSleepTime);
        } else {
            FUN_00332cd0();
        }
        FUN_00332cf0(0);
    }
    return 3;
}
