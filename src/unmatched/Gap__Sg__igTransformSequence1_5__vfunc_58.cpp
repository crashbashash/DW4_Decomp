struct SeqData {
    char pad0[4];
    int refCount;
    int count;
    int capacity;
};
extern "C" {
SeqData *FUN_0018a060(...);
SeqData *FUN_00189bd0(...);
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
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_58(TransformSequenceView *s, unsigned char channels);
void Gap__Sg__igTransformSequence1_5__vfunc_58(TransformSequenceView *s, unsigned char channels) {
    unsigned char old;
    if ((channels & 2) != 0 && (channels & 4) != 0) { return; }
    old = s->channels;
    s->channels = channels;
    if ((channels & 1) != 0) {
        s->translationMode = 1;
        if ((old & 1) == 0) {
            assignRef(s->translationKeys, SeqTempRef(FUN_0018a060(igObject_GetAllocator(s))));
            setCount(s->translationKeys, s->keys->count, 12);
            releaseRef(s->translations);
            s->translations = 0;
        }
    } else {
        releaseRef(s->translationKeys);
        s->translationKeys = 0;
    }
    releaseRef(s->translations);
    s->translations = 0;
    if ((channels & 2) != 0 || (channels & 4) != 0) {
        if ((old & 2) == 0 && (old & 4) == 0) {
            assignRef(s->rotationKeys, SeqTempRef(FUN_00189bd0(igObject_GetAllocator(s))));
            setCount(s->rotationKeys, s->keys->count, 16);
        }
        if ((channels & 2) != 0) {
            s->rotationMode = 3;
        } else {
            s->rotationMode = 1;
        }
    } else {
        releaseRef(s->rotationKeys);
        s->rotationKeys = 0;
    }
    releaseRef(s->rotations);
    s->rotations = 0;
    if ((channels & 8) != 0) {
        if ((old & 8) == 0) {
            assignRef(s->scaleKeys, SeqTempRef(FUN_0018a060(igObject_GetAllocator(s))));
            setCount(s->scaleKeys, s->keys->count, 12);
        }
        s->scaleMode = 1;
    } else {
        releaseRef(s->scaleKeys);
        s->scaleKeys = 0;
    }
    releaseRef(s->scales);
    s->scales = 0;
}
