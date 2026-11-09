struct T { int word0; int references; };
extern "C" {
struct T *FUN_001dcc80(int, int);
int FUN_001e04c0(void *, struct T *);
int __divdi3(int, int);
int __moddi3(int, int);
int __floatdidf(int);
int dpadd(int, int);
int dpdiv(int, int);
int litodp(int);
int igObject_Destroy(struct T *);
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v104(); };
struct LookupRef {
    T *p;
    LookupRef(T *object) : p(object) {
        if (p != 0) p->references = p->references + 1;
    }
    ~LookupRef() {
        T *object;
        if ((object = p) != 0) {
            object->references = object->references - 1;
            if ((object->references & 0x7FFFFF) == 0) igObject_Destroy(object);
        }
    }
};
extern "C" int FUN_001bb090(VC *arg0, int arg1) {
    int v, s2;
    v = arg0->v104();
    s2 = __floatdidf(__moddi3(v, 0x3B9ACA00));
    s2 = dpdiv(s2, litodp(0x3B9ACA00));
    LookupRef found(FUN_001dcc80(arg1, dpadd(__floatdidf(__divdi3(v, 0x3B9ACA00)), s2)));
    if (found.p == 0) {
        return 0;
    }
    return FUN_001e04c0(arg0, found.p);
}
