struct KeyFloatList { char pad0[8]; unsigned int count; char pad1[4]; float *data; };
struct KeyIndexList { char pad0[8]; int count; int capacity; int *data; };
typedef union KeyFloatBits { float f; struct { unsigned char p0, p1, p2; unsigned char lo : 7; unsigned char sign : 1; } b; } KeyFloatBits;
class KeyChannel {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();
    virtual void setKeyCount(int);
    virtual void d23();
    virtual void setKeyValue(int, float);
    virtual void d25();
    virtual void setKeyIndex(int, int);
};
struct KeyChannelList { char pad0[8]; int count; char pad1[4]; KeyChannel **data; };
struct KeyChannelOwner { char pad0[16]; KeyChannelList *channels; };
struct KeyReducer { char pad0[44]; KeyFloatList *values; KeyIndexList *kept; char pad1[4]; KeyChannelOwner *owner; };
extern "C" void FUN_002d6790(KeyIndexList *, int, int);
static inline void appendIndex(KeyIndexList *l, int v) {
    int n = l->count;
    if (l->capacity > n) {
        l->count = l->count + 1;
    } else {
        FUN_002d6790(l, n + 1, 4);
    }
    l->data[n] = v;
}
extern "C" void FUN_001d15a0(KeyReducer *self) {
    unsigned int n;
    KeyChannelList *channels;
    unsigned int kept;
    int c;
    KeyChannel *channel;
    unsigned int k;
    int index;
    unsigned int i;
    int at;
    KeyIndexList *list;
    self->kept->count = 0;
    n = self->values->count;
    for (i = 0; i < n; i++) {
        KeyFloatBits u;
        u.f = self->values->data[i];
        u.b.sign = 0;
        if (u.f > 4.99999999e-07f) {
            list = self->kept;
            at = (*(int const *)&list->count);
            if (list->capacity > at) {
                list->count = list->count + 1;
            } else {
                FUN_002d6790(list, at + 1, 4);
            }
            list->data[at] = i;
        }
    }
    channels = self->owner->channels;
    kept = self->kept->count;
    for (c = 0; c < channels->count; c++) {
        channel = channels->data[c];
        channel->setKeyCount(kept);
        for (k = 0; k < kept; k++) {
            index = self->kept->data[k];
            channel->setKeyValue(k, self->values->data[index]);
            channel->setKeyIndex(k, index);
        }
    }
}
