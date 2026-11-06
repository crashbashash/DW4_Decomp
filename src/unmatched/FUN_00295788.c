/* Starts a Sofdec handle on a stream-joint source (its error string names it mwSfdStartSj):
 * rejects an invalid handle, otherwise resets it, records the source, sets state 2, clears the
 * counters and kicks playback. */
extern int FUN_002968c0(void *sfd);
extern void FUN_0029a320(const char *msg);
extern void FUN_00295808(void *sfd);
extern void FUN_002954c8(void *sfd);
extern void FUN_00291d30(void *sfd);
extern char DAT_004f37e8[]; /* "E1122609 mwSfdStartSj: handle is invalid." */

typedef struct {
    char pad0[464];
    int sj;       /* 464: stream joint passed by the caller */
    char pad468[16];
    int state;    /* 484 */
    int f488;
    int f492;
    int f496;
} Sfd295788;

void FUN_00295788(Sfd295788 *sfd, int sj) {
    if (FUN_002968c0(sfd) == 0) {
        FUN_0029a320(DAT_004f37e8);
        return;
    }
    FUN_00295808(sfd);
    sfd->sj = sj;
    sfd->state = 2;
    sfd->f488 = 0;
    sfd->f492 = 0;
    sfd->f496 = 0;
    FUN_002954c8(sfd);
    FUN_00291d30(sfd);
}
