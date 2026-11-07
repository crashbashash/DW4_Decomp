struct MorphWordList { char pad0[8]; int count; char pad1[4]; unsigned int *data; };
struct MorphShortList { char pad0[16]; unsigned short *data; };
struct MorphParentTable { char pad0[16]; unsigned short *data; };
struct MorphBaseIndices { char pad0[12]; unsigned short *data; };
struct MorphTables {
    char pad0[12];
    MorphBaseIndices *base;
    MorphParentTable *parents;
    MorphShortList *steps;
    unsigned int firstFrame;
    unsigned int lastFrame;
    unsigned short leafCount;
};
class MorphIndexBuffer {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();
    virtual unsigned short *lock(int, int, int);
    virtual void d24();
    virtual void unlock(unsigned short *, int, int, int);
};
class MorphTarget {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();    virtual void d23();    virtual void d24();    virtual void d25();    virtual void d26();    virtual void d27();    virtual void d28();    virtual void d29();    virtual void d30();    virtual void d31();    virtual void d32();    virtual void d33();    virtual void d34();    virtual void d35();    virtual void d36();
    virtual void setRange(int, unsigned int, int);
};
struct MorphTargetList { char pad0[16]; MorphTarget **data; };
struct MorphLevelState {
    char pad0[32];
    MorphTargetList *targets;
    char pad1[8];
    MorphTables *tables;
    MorphIndexBuffer *indices;
    char pad2[4];
    MorphWordList *changed;
    unsigned int shownFrame;
    unsigned int frame;
    unsigned short shownLevel;
    unsigned short level;
};
extern "C" {
void FUN_001b1dc0(MorphWordList *);
void memcpy(void *, void *, int);
}
extern "C" void FUN_001d1da0(MorphLevelState *self, float t) {
    MorphShortList *steps;
    MorphBaseIndices *base;
    unsigned int count;
    unsigned int first;
    unsigned short *indices;
    unsigned int i;
    unsigned short j;
    unsigned short *parents;
    unsigned int last;
    unsigned short *from;
    unsigned short *walk;
    unsigned int done;
    unsigned short *src;
    int w;
    unsigned int bits;
    unsigned int v;
    MorphWordList *c;
    int n;
    unsigned int bit;
    unsigned int *word;
    unsigned int diff;
    unsigned int end;
    MorphTarget *target;
    MorphTables *tables;
    target = self->targets->data[0];
    tables = self->tables;
    first = tables->firstFrame;
    last = tables->lastFrame;
    steps = tables->steps;
    self->frame = (unsigned int)((float)first + t * (float)(last - first));
    if (self->frame != first) {
        unsigned int previous = self->frame - 1;
        self->level = steps->data[previous];
        if (self->frame < last) {
            if (self->level == steps->data[self->frame]) {
                self->frame = self->frame + 1;
            }
        }
    } else {
        self->level = self->tables->leafCount - 1;
    }
    if (self->shownFrame != self->frame) {
        base = self->tables->base;
        indices = self->indices->lock(0, 0, -1);
        parents = self->tables->parents->data;
        if (self->shownLevel > self->level) {
            count = self->frame * 3;
            for (i = 0; i < count; i++, indices++) {
                if (*indices > self->level) {
                    do {
                        *indices = parents[*indices];
                    } while (*indices > self->level);
                }
            }
            self->shownLevel = self->level;
        } else if (self->level > self->shownLevel) {
            diff = self->level - self->shownLevel;
            walk = indices;
            from = &parents[self->shownLevel];
            for (j = 0; j <= diff; j++) {
                v = *from;
                c = self->changed;
                w = v >> 5;
                bit = 1 << (v & 0x1f);
                word = &c->data[w];
                n = c->count;
                bits = bit | *word;
                if (n != 0 && w >= 0 && w < n) {
                    *word = bits;
                }
                from++;
            }
            done = self->shownFrame * 3;
            src = base->data;
            for (i = 0; i < done; i++, walk++, src++) {
                unsigned int v = *walk;
                if ((1 << (v & 0x1f)) & self->changed->data[v >> 5]) {
                    int level;
                    unsigned short x;
                    x = *src;
                    level = self->level;
                    while (x > level) {
                        x = parents[x];
                    }
                    *walk = x;
                }
            }
            end = self->frame * 3;
            memcpy(walk, src, (end - done) * 2);
            for (; done < end; done++, walk++) {
                int level;
                unsigned short x;
                x = *walk;
                level = self->level;
                while (x > level) {
                    x = parents[x];
                }
                *walk = x;
            }
            FUN_001b1dc0(self->changed);
            self->shownLevel = self->level;
        }
        self->indices->unlock(indices, 0, 0, -1);
        self->shownFrame = self->frame;
        target->setRange(3, self->frame, 0);
    }
}
