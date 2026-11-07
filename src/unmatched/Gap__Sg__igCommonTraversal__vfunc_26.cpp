#include "dw4/reflected.h"
class igTimerSourceView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual long long getTime();
};
extern igTimerSourceView *DAT_005871d8;
extern "C" long long Gap__Sg__igCommonTraversal__vfunc_26(igCommonTraversal *t);
long long Gap__Sg__igCommonTraversal__vfunc_26(igCommonTraversal *t) {
    int top; igLongStack *stack = (igLongStack *)t->_timeStack; int n = stack->_count; top = n - 1;
    if (n == 0) {
        if (!t->_timeBuffered) {
            if (t->_userTimeState) {
                t->_timeLongBuf = t->_timeLong;
            } else {
                t->_timeLongBuf = DAT_005871d8->getTime();
            }
            t->_timeBuffered = 1;
        }
        return t->_timeLongBuf;
    }
    return ((long long *)stack->_data)[top];
}
