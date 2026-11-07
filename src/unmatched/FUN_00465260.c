struct R { int w0; int references; };
struct O { char pad[76]; struct R *f76; struct R *f80; };
struct R *FUN_001c5990();
int igObject_IsKindOf();
int igObject_Destroy();
extern int DAT_00561EA0[4];
static inline void * cast0(void * o) { if (o != 0 && igObject_IsKindOf(o, DAT_00561EA0[0]) != 0) { return o; } return 0; }
void FUN_00465260(struct O *self, struct R *arg1) {
    struct R *o;
    struct R *v;
    if (arg1 != 0) {
        if (arg1 != 0) {
            arg1->references = arg1->references + 1;
        }
        o = self->f76;
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
        self->f76 = arg1;
        v = FUN_001c5990(arg1);
        v = cast0(v);
        if (v != 0) {
            v->references = v->references + 1;
        }
        o = self->f80;
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
        self->f80 = v;
    }
}
