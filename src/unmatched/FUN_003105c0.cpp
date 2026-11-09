struct ArenaChunkWord { unsigned lo:5; unsigned size:19; unsigned mid:7; unsigned big:1; };
struct ArenaChunkBytes { unsigned char inUse:1; unsigned char align:4; unsigned char pad:3; char p1[2]; unsigned char mid:7; unsigned char big:1; char p2[4]; unsigned short ext:12; unsigned short pad2:4; char p3; unsigned char free:1; };
struct ArenaCheckState { char pad[44]; char *top; char pad2[1968]; int flags; };
class ArenaCheckPool { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106();
 virtual char *Low();
 virtual char *High();
 char pad[108]; ArenaCheckState *state; char pad2[68]; int errorLevel; int checkLevel; int pad3[2]; int minimum;
};
extern "C" {
void FUN_002f8870(int, ArenaCheckPool *);
int FUN_003081d0(...);
extern char DAT_004fb570[];
extern char DAT_004fb970[];
extern char DAT_004fb990[];
extern char DAT_004fb9b0[];
extern char DAT_004fb620[];
extern char DAT_004fb9d0[];
extern char DAT_004fb9f0[];
extern char DAT_004fba10[];
extern char DAT_004fba50[];
extern char DAT_004fba80[];
extern char DAT_004fbab0[];
extern unsigned char GPR_00554c8c;
extern unsigned char GPR_00554c90;
extern unsigned char GPR_00554c94;
extern unsigned char GPR_00554c98;
extern unsigned char GPR_00554c9c;
extern unsigned char GPR_00554ca0;
extern unsigned char GPR_00554ca4;
extern unsigned char GPR_00554ca8;
extern unsigned char GPR_00554cac;
}
static inline int isFreeChunk2(ArenaChunkBytes *h) { if (((ArenaChunkBytes *)h)->big == 1) { return h->free; } return 0; }
static inline int isFreeChunk(ArenaChunkBytes *h) { if (h->big == 1) { return h->free; } return 0; }
extern "C" void FUN_003105c0(ArenaCheckPool *self, ArenaChunkBytes *h, int requested) {
    ArenaCheckState *state;
    unsigned int size;
    int r;
    char *high;
    char *low;
    unsigned int total;
    state = self->state;
    size = ((ArenaChunkWord *)h)->size;
    if (h->big == 1) {
        size += h->ext << 19;
    }
    size = (size + 3) & ~3;
    total = size + (h->align + 1) * 4;
    high = self->High();
    low = self->Low();
    if (isFreeChunk(h) == 0) {
        if ((char *)h != state->top) {
            if (state->flags & 1) {
                if (self->errorLevel > 0 && self->checkLevel > 0 && (char *)h < low && self->checkLevel > 0) {
                    FUN_002f8870(0, self);
                    if (GPR_00554c8c == 0) {
                        r = FUN_003081d0(DAT_004fb570, h, DAT_004fb970, low);
                        if (r != 1 && r == 2) {
                            GPR_00554c8c = 1;
                        }
                    }
                }
                if (self->errorLevel > 0 && self->checkLevel > 0 && high < (char *)h + total && self->checkLevel > 0) {
                    FUN_002f8870(0, self);
                    if (GPR_00554c90 == 0) {
                        r = FUN_003081d0(DAT_004fb570, h, DAT_004fb990, high);
                        if (r != 1 && r == 2) {
                            GPR_00554c90 = 1;
                        }
                    }
                }
            }
        } else {
            if (self->errorLevel > 0 && self->checkLevel > 0 && total < ((self->minimum + 7) & ~7) && self->checkLevel > 0) {
                FUN_002f8870(0, self);
                if (GPR_00554c94 == 0) {
                    r = FUN_003081d0(DAT_004fb570, h, DAT_004fb9b0, (self->minimum + 7) & ~7);
                    if (r != 1 && r == 2) {
                        GPR_00554c94 = 1;
                    }
                }
            }
            if (self->errorLevel > 0 && self->checkLevel > 0 && !h->inUse && self->checkLevel > 0) {
                FUN_002f8870(0, self);
                if (GPR_00554c98 == 0) {
                    r = FUN_003081d0(DAT_004fb620, h, DAT_004fb9d0);
                    if (r != 1 && r == 2) {
                        GPR_00554c98 = 1;
                    }
                }
            }
        }
    } else if (self->errorLevel > 0 && self->checkLevel > 0 && isFreeChunk2(h) != 0 && self->checkLevel > 0) {
        FUN_002f8870(0, self);
        if (GPR_00554c9c == 0) {
            r = FUN_003081d0(DAT_004fb620, h, DAT_004fb9f0);
            if (r != 1 && r == 2) {
                GPR_00554c9c = 1;
            }
        }
    }
    if (self->errorLevel > 0 && self->checkLevel > 0 && total < ((self->minimum + 7) & ~7) && self->checkLevel > 0) {
        FUN_002f8870(0, self);
        if (GPR_00554ca0 == 0) {
            r = FUN_003081d0(DAT_004fb570, h, DAT_004fba10, total);
            if (r != 1 && r == 2) {
                GPR_00554ca0 = 1;
            }
        }
    }
    if (self->errorLevel > 0 && self->checkLevel > 0 && ((int)((char *)h + (h->big == 0 ? 4 : 12)) & 7) && self->checkLevel > 0) {
        FUN_002f8870(0, self);
        if (GPR_00554ca4 == 0) {
            r = FUN_003081d0(DAT_004fb620, h, DAT_004fba50);
            if (r != 1 && r == 2) {
                GPR_00554ca4 = 1;
            }
        }
    }
    if (self->errorLevel > 0 && self->checkLevel > 0 && (int)(total - requested) < 0 && self->checkLevel > 0) {
        FUN_002f8870(0, self);
        if (GPR_00554ca8 == 0) {
            r = FUN_003081d0(DAT_004fb570, h, DAT_004fba80, total);
            if (r != 1 && r == 2) {
                GPR_00554ca8 = 1;
            }
        }
    }
    if (self->errorLevel > 0 && self->checkLevel > 0 && (int)(total - (requested + ((self->minimum + 7) & ~7))) >= 0 && self->checkLevel > 0) {
        FUN_002f8870(0, self);
        if (GPR_00554cac == 0) {
            r = FUN_003081d0(DAT_004fb570, h, DAT_004fbab0, total);
            if (r != 1 && r == 2) {
                GPR_00554cac = 1;
            }
        }
    }
}
