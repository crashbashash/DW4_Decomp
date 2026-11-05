/* 0x0028ec70 — FUN_0028ec70 (172 bytes). Searches the caller's buffer (base, size) with FUN_0028de10 and stores the offset of the hit, or the whole size when there is none, through *out; reports 0 or error 0xFF030305 through FUN_0028eb38, and 0xFF03020A when FUN_002913f8 rejects the object. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002913f8(void *obj);
extern int FUN_0028eb38(void *obj, int code);
extern char *FUN_0028de10(char *base, int size, int arg);

typedef struct {
    char *base;
    int size;
} Buf28ec70;

int FUN_0028ec70(void *obj, Buf28ec70 *buf, int *out) {
    char *base;
    int size;
    char *hit;
    int code;

    if (FUN_002913f8(obj) != 0) {
        return FUN_0028eb38(0, 0xFF03020A);
    }
    base = buf->base;
    size = buf->size;
    hit = FUN_0028de10(base, size, 204);
    code = 0xFF030305;
    if (hit == 0) {
        *out = size;
    } else {
        *out = hit - base;
        code = 0;
    }
    return FUN_0028eb38(obj, code);
}
