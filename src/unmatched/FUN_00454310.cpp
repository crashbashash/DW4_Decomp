class VP {
public:
    virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();
    virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();
    virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual void d23();
    virtual void d24();virtual void d25();virtual void d26();virtual void d27();virtual void d28();virtual void d29();
    virtual void getSize(int *, int *);
};
class Item {
public:
    virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();
    virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();
    virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();
    virtual int hit(float, float);
};
struct Mid { char p0[8]; int count; char p12[4]; Item **items; };
struct Mid2 { char p0[8]; Mid *m; };
struct Owner { char p0[12]; Mid2 *m2; };
struct Cur {
    char p0[12]; short x; short y; VP *vp; unsigned char valid; char pad[3]; float nx; float ny;
    void Update() {
        int w, h;
        vp->getSize(&w, &h);
        nx = 2.0f * ((float)x / (float)w - 0.5f);
        ny = 2.0f * ((float)y / (float)h - 0.5f);
        valid = 1;
    }
    float GetX() { if (!valid) Update(); return nx; }
    float GetY() { if (!valid) Update(); return ny; }
};
extern "C" void FUN_00454310(Owner *o, int unused, Cur *c) {
    int n = o->m2->m->count;
    int i = 0;
    while (i < n) {
        Item *it = o->m2->m->items[i];
        float x = c->GetX();
        float y = c->GetY();
        if (it->hit(x, y) & 0xFF) break;
        i++;
    }
}
