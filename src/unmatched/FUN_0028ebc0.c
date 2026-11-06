/* Wraps the caller's buffer (base, size) in a temporary stream joint (FUN_0027b408), runs
 * FUN_0028ed28 on it, stores size - fn36(sj, 1) through *out and releases the joint (slot +12);
 * returns FUN_0028ed28's result, or -1 when the joint cannot be created. */
typedef struct SjObj SjObj;
typedef struct {
    char pad0[12];
    void (*fn12)(SjObj *sj);      /* 12 */
    char pad16[20];
    int (*fn36)(SjObj *sj, int a); /* 36 */
} SjVtbl;
struct SjObj {
    SjVtbl *vtbl;
};

typedef struct {
    void *base;
    int size;
} Buf28ebc0;

extern SjObj *FUN_0027b408(void *base, int size);
extern int FUN_0028ed28(void *obj, SjObj *sj, int arg);

int FUN_0028ebc0(void *obj, Buf28ebc0 *buf, int *out, int arg) {
    SjObj *sj = FUN_0027b408(buf->base, buf->size);
    int result;

    if (sj == 0) {
        return -1;
    }
    result = FUN_0028ed28(obj, sj, arg);
    *out = buf->size - sj->vtbl->fn36(sj, 1);
    sj->vtbl->fn12(sj);
    return result;
}
