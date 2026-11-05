/* 0x002956d8 — FUN_002956d8 (172 bytes). Starts a Sofdec handle on a memory buffer (its error string names it mwSfdStartMem): rejects an invalid handle, otherwise resets it, releases the previous stream joint through its vtable slot +12, wraps the buffer in a new one (FUN_0027b408) and kicks playback. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002968c0(void *sfd);
extern void FUN_0029a320(const char *msg);
extern void FUN_00295808(void *sfd);
extern void FUN_002954c8(void *sfd);
extern void FUN_00291d30(void *sfd);
extern char DAT_004f37b8[]; /* "E1122610 mwSfdStartMem: handle is invalid." */

typedef struct SjObj SjObj;
typedef struct {
    char pad0[12];
    void (*fn12)(SjObj *sj);
} SjVtbl;
struct SjObj {
    SjVtbl *vtbl;
};
extern SjObj *FUN_0027b408(void *buf, int size);

typedef struct {
    char pad0[464];
    SjObj *sj;        /* 464 */
    char pad468[32];
    SjObj *memSj;     /* 500: joint created over the buffer */
    void *buf;        /* 504 */
    int size;         /* 508 */
} Sfd2956d8;

void FUN_002956d8(Sfd2956d8 *sfd, void *buf, int size) {
    SjObj *sj;

    if (FUN_002968c0(sfd) == 0) {
        FUN_0029a320(DAT_004f37b8);
        return;
    }
    FUN_00295808(sfd);
    sfd->memSj->vtbl->fn12(sfd->memSj);
    sj = FUN_0027b408(buf, size);
    sfd->memSj = sj;
    sfd->sj = sj;
    sfd->buf = buf;
    sfd->size = size;
    FUN_002954c8(sfd);
    FUN_00291d30(sfd);
}
