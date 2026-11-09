extern "C" {
int Gap__Core__igObject__vfunc_11(...);
int List_Resize(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int FUN_00455ad0(...);
struct ObserverRefView { int w0; int rc; };
struct ObserverIntListView { int w0; int w4; int cnt; int cap; int *data; };
struct ObserverEventView : ObserverRefView { int w8; int a; ObserverIntListView *list; };
struct ObserverModelView { char pad[40]; ObserverRefView *ref; int flags; int fn; };
struct MousePosObserverView { char pad[16]; ObserverModelView *m; int f20; };
ObserverEventView *FUN_0019e680(...);
static inline int count_of(const ObserverIntListView *list) { return list->cnt; }
struct ObserverEventRef {
    ObserverEventView *p;
    ObserverEventRef(ObserverEventView *event) : p(event) {}
    ~ObserverEventRef() {
        ObserverRefView *object = p;
        if (object != 0) {
            object->rc = object->rc - 1;
            if ((object->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    ObserverEventView *get() const { return p; }
};
static inline void setEvent(MousePosObserverView *self, const ObserverEventRef &event) {
    ObserverRefView *retained = event.get();
    ObserverModelView *model = self->m;
    ObserverRefView *previous;
    if (retained != 0) {
        retained->rc = retained->rc + 1;
    }
    previous = model->ref;
    if (previous != 0) {
        previous->rc = previous->rc - 1;
        if ((previous->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    model->ref = retained;
}
void Gap__Gui__igMousePosObserver__vfunc_13(MousePosObserverView *self) {
    ObserverEventView *created;
    ObserverIntListView *list;
    int top;
    Gap__Core__igObject__vfunc_11(self);
    ObserverEventRef event(FUN_0019e680(igObject_GetAllocator(self)));
    created = event.get();
    ObjectList_AppendRetained(created->a, self->f20);
    list = created->list;
    top = count_of(list);
    if (top < list->cap) {
        list->cnt = list->cnt + 1;
    } else {
        List_Resize(list, top + 1, 4);
    }
    list->data[top] = 2;
    setEvent(self, event);
    self->m->flags = 0;
    self->m->flags = self->m->flags | 4;
    self->m->fn = (int)&FUN_00455ad0;
}
}
