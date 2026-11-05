struct igMetaObj { char pad[18]; short id; };
class igMetaField {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual igMetaObj *vX();
    char pad[12];
    short typeIndex;
};
extern "C" short igMetaField_GetTypeIndex(igMetaField *arg0);
extern "C" short igMetaField_GetTypeIndex(igMetaField *arg0) {
    if (arg0->typeIndex == -1) {
        arg0->typeIndex = arg0->vX()->id;
    }
    return arg0->typeIndex;
}
