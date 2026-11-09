extern "C" {
struct ResizeEvent { int word0; int references; float origin[2]; float size[2]; };
void igObject_Destroy(ResizeEvent *);
ResizeEvent *FUN_002332b0(...);
int FUN_00237ea0(...);
int igObject_GetAllocator(...);
extern float DAT_004e0fa0[4];
extern float DAT_004e0fa4[4];
}
struct ResizeEventRef {
    ResizeEvent *p;
    ResizeEventRef(ResizeEvent *event) : p(event) {}
    ~ResizeEventRef() {
        ResizeEvent *event = p;
        if (event != 0) {
            --event->references;
            if ((event->references & 0x7FFFFF) == 0) {
                igObject_Destroy(event);
            }
        }
    }
    ResizeEvent *operator->() const { return p; }
    ResizeEvent *get() const { return p; }
};
struct WindowInfo { char p[40]; int f40; };
struct Receiver { char p[8]; WindowInfo *f8; };
extern "C" int Gap__Insight__igWindowResizeEventReceiver__vfunc_32(Receiver *self, int width, int height);
int Gap__Insight__igWindowResizeEventReceiver__vfunc_32(Receiver *self, int width, int height) {
    ResizeEventRef event(FUN_002332b0(igObject_GetAllocator()));
    {
        ResizeEvent *e = event.get();
        e->origin[0] = DAT_004e0fa0[0];
        e->origin[1] = DAT_004e0fa4[0];
    }
    {
        ResizeEvent *e = event.get();
        e->size[0] = (float)width;
        e->size[1] = (float)height;
    }
    FUN_00237ea0(self->f8->f40, event.get());
    return 0;
}
