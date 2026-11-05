struct R { int w0; };
extern "C" {
int FUN_00328ab0(...);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
}
class Sub { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
 virtual R v29();
 virtual void d30();
 virtual R v31(int);
};
class Q { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); 
 virtual unsigned v26();
 int pad[2];
 Sub *s3; Sub *s4; int pad3; unsigned cap; int pad2[2]; int f36; unsigned f40;
};
extern "C" void Gap__Core__igStandardQueue__vfunc_32(int *out, Q *q, unsigned a) {
    R t[5];
    if (a >= q->cap || q->f36 == 0) {
        q->f40 = a;
        *out = DAT_004fb410[0];
    } else {
        t[4] = q->s3->v31(1);
        if (a < q->v26()) {
            t[3] = q->s3->v29();
            *out = DAT_004fb418[0];
        } else {
            t[2] = q->s4->v31(1);
            FUN_00328ab0(q, a);
            q->f40 = q->cap;
            t[1] = q->s3->v29();
            t[0] = q->s4->v29();
            *out = DAT_004fb410[0];
        }
    }
}
