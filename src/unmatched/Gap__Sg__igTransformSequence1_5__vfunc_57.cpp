struct SeqData {
    char pad0[4];
    int refCount;
    int count;
    int capacity;
};
extern "C" {
SeqData *FUN_0018a060(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int List_Resize(SeqData *list, int n, int size);
}
struct SeqTempRef {
    SeqData *p;
    SeqTempRef(SeqData *x) : p(x) {}
    ~SeqTempRef() {
        if (p) {
            --p->refCount;
            if (((unsigned long long)(long long)p->refCount & 0x7fffffULL) == 0)
                igObject_Destroy(p);
        }
    }
};
static inline void releaseRef(SeqData *old) {
    if (old) {
        --old->refCount;
        if (((unsigned long long)(long long)old->refCount & 0x7fffffULL) == 0)
            igObject_Destroy(old);
    }
}
static inline void assignRef(SeqData *&field, const SeqTempRef &r) {
    SeqData *o = r.p;
    if (o) { o->refCount++; }
    releaseRef(field);
    field = o;
}
static inline void setCount(SeqData *list, int n, int size) {
    if (n >= 0) {
        if (n <= list->capacity) { list->count = n; } else { List_Resize(list, n, size); }
    }
}
struct TransformSequenceView {
    char pad0[8];
    SeqData *translationKeys;
    SeqData *rotationKeys;
    SeqData *scaleKeys;
    char pad20[36];
    SeqData *keys;
    SeqData *translations;
    SeqData *rotations;
    SeqData *scales;
    unsigned char channels;
    unsigned char translationMode;
    unsigned char rotationMode;
    unsigned char scaleMode;
};
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_57(TransformSequenceView *s, int channel, unsigned int mode);
void Gap__Sg__igTransformSequence1_5__vfunc_57(TransformSequenceView *s, int channel, unsigned int mode) {
    if ((s->channels & channel) == 0) { return; }
    switch (channel) {
    case 1:
        if (mode < 3) {
            s->translationMode = mode;
            if (mode == 2) {
                assignRef(s->translations, SeqTempRef(FUN_0018a060(igObject_GetAllocator(s))));
                setCount(s->translations, s->keys->count * 2, 12);
            } else {
                releaseRef(s->translations);
                s->translations = 0;
            }
        }
        break;
    case 2:
        if (mode <= 1 || mode == 3) {
            s->rotationMode = mode;
            releaseRef(s->rotations);
            s->rotations = 0;
        }
        break;
    case 4:
        if (mode < 3) {
            s->rotationMode = mode;
            if (mode == 2) {
                assignRef(s->rotations, SeqTempRef(FUN_0018a060(igObject_GetAllocator(s))));
                setCount(s->rotations, s->keys->count * 2, 12);
            } else {
                releaseRef(s->rotations);
                s->rotations = 0;
            }
        }
        break;
    case 8:
        if (mode < 3) {
            s->scaleMode = mode;
            if (mode == 2) {
                assignRef(s->scales, SeqTempRef(FUN_0018a060(igObject_GetAllocator(s))));
                setCount(s->scales, s->keys->count * 2, 12);
            } else {
                releaseRef(s->scales);
                s->scales = 0;
            }
        }
        break;
    }
}
