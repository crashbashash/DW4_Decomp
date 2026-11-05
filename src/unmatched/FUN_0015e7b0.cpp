extern "C" int Memory_FreeBuffer(...);
struct Info { unsigned flags; };
class O { public:virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual Info *getInfo();virtual void d24();virtual void d25();virtual void d26();virtual void d27();virtual void d28();virtual void d29();virtual void d30();virtual void d31();virtual void d32();virtual void d33();virtual void d34();virtual void d35();virtual void d36();virtual void d37();virtual void d38();virtual void d39();virtual void d40();virtual void d41();virtual void d42();virtual void d43();virtual void d44();virtual void d45();virtual void d46();virtual void d47();virtual void d48();virtual void d49();virtual void d50();virtual void d51();virtual void d52();virtual void d53();virtual void d54();virtual void d55();virtual void d56();virtual void d57();virtual void d58();virtual void d59();virtual void f60();virtual void f61();
int pad1[1]; int *arr; int pad2[5]; int f32; int f36;
};
extern "C" void FUN_0015e7b0(O *o) {int a;int off;int b;int **p;int **q;Info *info;unsigned i;
info = o->getInfo();
if (info->flags & 1) { p = &o->arr; a = (*p)[0]; if (a != 0) { Memory_FreeBuffer(a); (*p)[0] = 0; } }
if (info->flags & 2) { p = &o->arr; a = (*p)[1]; if (a != 0) { Memory_FreeBuffer(a); (*p)[1] = 0; } }
if (info->flags & 4) { p = &o->arr; a = (*p)[2]; if (a != 0) { Memory_FreeBuffer(a); (*p)[2] = 0; } }

    if (o->f32 != 0) { Memory_FreeBuffer(o->f32); o->f32 = 0; }
    if (o->f36 != 0) { Memory_FreeBuffer(o->f36); o->f36 = 0; }
    i = 0;
    while (i < (unsigned char)((info->flags & 0xF0000) >> 16)) {
        off = (i + 11) * 4;
        q = &o->arr;
        b = *(int *)((char *)*q + off);
        if (b != 0) { Memory_FreeBuffer(b); *(int *)((char *)*q + off) = 0; }
        i++;
    }
    o->f60();
    o->f61();
}
