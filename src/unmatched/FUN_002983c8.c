/* 0x002983c8 — FUN_002983c8 (88 bytes). When the object holds a stream joint (+400) and its +424 state is not 1, runs FUN_00298468 then FUN_00298618 on it. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00298468(void *obj);
extern void FUN_00298618(void *obj);

typedef struct {
    int state;    /* 0 */
} Rec2983c8;

typedef struct {
    char pad0[400];
    void *sj;           /* 400 */
    char pad404[20];
    Rec2983c8 rec;      /* 424 */
} Obj2983c8;

void FUN_002983c8(Obj2983c8 *obj) {
    Rec2983c8 *rec = &obj->rec;

    if (obj->sj != 0 && rec->state != 1) {
        FUN_00298468(obj);
        FUN_00298618(obj);
    }
}
