extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int FUN_00165cb0(...);
}
struct Obj {
    char p[940]; T *m940; T *m944; T *m948;
    inline void rel(T *&r) {
        T *object = r;
        if (object) {
            --object->references;
            if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
        r = 0;
    }
};
extern "C" void Gap__Core__igPsx2VisualContext__vfunc_35(Obj *arg0);
void Gap__Core__igPsx2VisualContext__vfunc_35(Obj *arg0) {
    FUN_00165cb0(arg0);
    arg0->rel(arg0->m940);
    arg0->rel(arg0->m944);
    arg0->rel(arg0->m948);
}
