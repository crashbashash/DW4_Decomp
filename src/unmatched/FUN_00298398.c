/* Calls vtable slot +20 of the stream joint held at +400, if any. */
typedef struct SjObj SjObj;
typedef struct {
    char pad0[20];
    void (*fn20)(SjObj *sj); /* 20 */
} SjVtbl;
struct SjObj {
    SjVtbl *vtbl;
};

typedef struct {
    char pad0[400];
    SjObj *sj;    /* 400 */
} Obj298398;

void FUN_00298398(Obj298398 *obj) {
    SjObj *sj = obj->sj;

    if (sj != 0) {
        sj->vtbl->fn20(sj);
    }
}
