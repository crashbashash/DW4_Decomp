typedef struct Sj Sj;
typedef struct {
    void *pad0[9];
    int (*get_size)(Sj *, int);
} SjVtbl;
struct Sj {
    SjVtbl *vt;
};

typedef struct {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int f28;
} StmSlot;

typedef struct {
    signed char used;
    signed char f1;
    char pad2[6];
    Sj *sj;
    char pad12[8];
    int f20;
    int bufsize;
    char pad28[36];
    StmSlot slot[16];
} Stm;

extern char DAT_004f0aa8[];
extern char DAT_004f0ad8[];
void FUN_002777f8(const char *message);
void FUN_00277798(int *lock);
void FUN_002777b8(int *lock);
Stm *FUN_00276e50(void);

Stm *FUN_00276eb0(Sj *sj)
{
    int lock;
    Stm *stm;
    int n;
    int i;

    if (sj == 0) {
        FUN_002777f8(DAT_004f0aa8);
        return 0;
    }
    FUN_00277798(&lock);
    stm = FUN_00276e50();
    if (stm == 0) {
        FUN_002777f8(DAT_004f0ad8);
    } else {
        stm->f1 = 0;
        stm->sj = sj;
        n = sj->vt->get_size(sj, 0) + sj->vt->get_size(sj, 1);
        stm->bufsize = n;
        stm->f20 = n * 8 / 10;
        for (i = 15; i >= 0; i--) {
            stm->slot[i].f16 = 0;
        }
        stm->used = 1;
    }
    FUN_002777b8(&lock);
    return stm;
}
