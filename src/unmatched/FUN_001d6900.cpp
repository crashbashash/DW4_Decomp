struct VertexFormat { int flags; };
struct VertexArray {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
    virtual int setPosition(int index, float *position);
};
struct Primitive {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual int configure(VertexFormat *format, int vertices, int a, int b);
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual int setPrimitives(int type, int count, int offset);
    int references;
    int f8;
    VertexArray *vertices;
};
extern "C" {
Primitive *FUN_00137810(int);
int FUN_002f8a20(void);
int igObject_Destroy(Primitive *);
}
struct PrimitiveRef {
    Primitive *p;
    PrimitiveRef(Primitive *object) : p(object) {}
    ~PrimitiveRef() {
        Primitive *object = p;
        if (object != 0) {
            object->references = object->references - 1;
            if ((object->references & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    Primitive *operator->() const { return p; }
};
extern "C" int FUN_001d6900(Primitive **out) {
    float v[18];
    PrimitiveRef quad(FUN_00137810(FUN_002f8a20()));
    VertexFormat format;
    int i;
    format.flags = 0;
    format.flags = 1 | format.flags;
    quad->configure(&format, 6, 0, 0);
    quad->setPrimitives(3, 2, 0);
    v[2] = 0.0f;
    v[0] = -1.0f;
    i = 0;
    v[1] = -1.0f;
    v[3] = 1.0f;
    v[4] = -1.0f;
    v[5] = 0.0f;
    v[6] = -1.0f;
    v[7] = 1.0f;
    v[8] = 0.0f;
    v[9] = 1.0f;
    v[10] = 1.0f;
    v[11] = 0.0f;
    v[12] = -1.0f;
    v[16] = -1.0f;
    v[13] = 1.0f;
    v[14] = 0.0f;
    v[15] = 1.0f;
    v[17] = 0.0f;
    do {
        quad->vertices->setPosition(i, &v[i * 3]);
        i += 1;
    } while (i < 6);
    *out = quad.p;
    Primitive *retained = *out;
    if (retained != 0) {
        retained->references = retained->references + 1;
    }
    return 0;
}
