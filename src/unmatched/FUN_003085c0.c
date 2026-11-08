void *FUN_002b9500();
int FUN_002f8a20();
int FUN_00306770();
int FUN_00306e50();
int Memory_GetAllocatorBySelector();
int igObject_Destroy();
int strcmp();
extern int DAT_004c22d8;
extern char *DAT_004c22f0;
extern char DAT_004f7910[];
extern char DAT_004f7958[];
extern char DAT_004f7968[];
extern char DAT_004fb350[];
extern char DAT_004fb360[];
extern char DAT_004fb378[];
extern char DAT_004fb380[];
extern char DAT_004fb388[];
typedef struct ShortStr { char pad[4]; int _refCount; char *text; } ShortStr;
typedef struct Root { char pad[56]; void *cur; } Root;
extern Root *DAT_00586dc8;
extern int DAT_00587048;
extern unsigned char GPR_005549b0;
extern unsigned char GPR_00554c14;
extern char GPR_00554c30;
static inline int allocator(void) {
    int a = FUN_002f8a20();
    if (GPR_00554c14 != 0) {
        return a;
    }
    return Memory_GetAllocatorBySelector(DAT_00587048);
}
static inline char *text(ShortStr *s) {
    char *t = s->text;
    if (t == 0) {
        return DAT_004c22f0;
    }
    return t;
}
void FUN_003085c0(void) {
    void *cur;
    ShortStr *name;
    ShortStr *held;
    char *t;

    GPR_00554c30 = 1;
    cur = DAT_00586dc8->cur;
    if (cur != 0) {
        FUN_00306e50(cur, 2, DAT_004fb350, &GPR_005549b0, 1, 0);
        name = FUN_002b9500(allocator());
        if (FUN_00306770(cur, 2, DAT_004fb360, &name, DAT_004f7910, 0) != 0) {
            t = text(name);
            if (strcmp(t, DAT_004fb378) == 0) {
                DAT_004c22d8 = 6;
            } else if (strcmp(t, DAT_004fb380) == 0) {
                DAT_004c22d8 = 5;
            } else if (strcmp(t, DAT_004fb388) == 0) {
                DAT_004c22d8 = 4;
            } else if (strcmp(t, DAT_004f7958) == 0) {
                DAT_004c22d8 = 2;
            } else if (strcmp(t, DAT_004f7968) == 0) {
                DAT_004c22d8 = 1;
            }
        }
        held = name;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }
}
