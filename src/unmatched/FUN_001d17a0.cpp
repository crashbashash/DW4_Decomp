struct igFloatListView {
    char pad0[8];
    int count;
    char pad1[4];
    float *data;
};
struct KeyTrackHeader {
    char pad0[16];
    igFloatListView *keys;
};
struct KeyTrackListView {
    char pad0[16];
    KeyTrackHeader **data;
};
struct KeyTrackOwner {
    char pad0[32];
    int count;
    KeyTrackListView *tracks;
};
static inline void setValue(igFloatListView *l, int i, const float *v) {
    int n = l->count;
    if (n != 0 && i >= 0 && i < n) {
        l->data[i] = *v;
    }
}
extern "C" void FUN_001d17a0(KeyTrackOwner *self, igFloatListView *out, int last) {
    int i;

    if (last == 0) {
        for (i = 0; i < self->count; i++) {
            igFloatListView *k = self->tracks->data[i]->keys;
            if (k->count > 0) {
                setValue(out, i, k->data);
            }
        }
    } else {
        for (i = 0; i < self->count; i++) {
            igFloatListView *k = self->tracks->data[i]->keys;
            setValue(out, i, &k->data[k->count - 1]);
        }
    }
}
