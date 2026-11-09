class EventReceiver {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual int onKeyEvent(int, int, int);
    virtual void d26();
    virtual unsigned char onAxisEvent(int, int, float);
    virtual void d28();
    virtual unsigned char onButtonEvent(int, int);
};
struct DispatchKey;
#include "dw4/igTDataList.h"
struct ReceiverHolder { char pad[8]; igTDataList<EventReceiver *> *list; };
struct DispatchKeyHolder { char pad[8]; igTDataList<DispatchKey *> *list; };
struct EventDispatcherView { char pad[12]; ReceiverHolder *receivers; DispatchKeyHolder *keys; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_37(EventDispatcherView *self, int, DispatchKey *key) {
    igTDataList<DispatchKey *> *l = self->keys->list;
    int idx = l->find(key);
    int n = self->receivers->list->_count;
    for (int i = 0; i < n; i++) {
        unsigned char r = self->receivers->list->_data[i]->onButtonEvent(idx, 0);
        if (r) break;
    }
}
