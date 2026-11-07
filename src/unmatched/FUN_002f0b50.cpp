struct L { int *data; int count; };
extern "C" {
extern L *DAT_00586f58[4];
extern L *DAT_00586f60[4];
bool FUN_002f0b50(int arg0, int arg1);
}
class VM { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v108(int); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int v132(); };
bool FUN_002f0b50(int arg0, int arg1) {
    int s2;
    VM *o;
    int s1;
    VM *q;
    bool s0;
    s0 = false;
    s1 = DAT_00586f60[0]->count - 1;
    while (s1 >= 0) {
        o = (VM *)DAT_00586f60[0]->data[s1];
        if (o != 0 && o->v132() != 0 && o->v108(arg1) != 0) {
            s0 = true;
        }
        s1--;
    }
    s2 = DAT_00586f58[0]->count - 1;
    while (s2 >= 0) {
        q = (VM *)DAT_00586f58[0]->data[s2];
        if (q != 0 && q->v132() != 0 && q->v108(arg1) != 0) {
            s0 = true;
        }
        s2--;
    }
    return s0;
}
