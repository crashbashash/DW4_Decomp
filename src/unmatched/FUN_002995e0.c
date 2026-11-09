extern char DAT_004f4918[];
extern char DAT_004f4948[];
int FUN_002968c0(void *ply);
void FUN_0029a320(const char *format, ...);
int FUN_0029ece8(int handle);

typedef struct LinkStmPly {
    char pad[64];
    int handle;
    char pad68[48];
    signed char state;
    signed char prev;
} LinkStmPly;

/* matching construct: permuter, reduced by hand: the handle cast after its check */
void FUN_002995e0(void *hn, int value)
{
    LinkStmPly *ply;
    int handle;

    if (FUN_002968c0(hn) == 0) {
        FUN_0029a320(DAT_004f4918);
        return;
    }
    ply = (LinkStmPly *)hn;
    handle = ply->handle;
    if (ply->state == 1 && value == 0)
        ply->prev = 1;
    if (ply->state == 0 && value == 1 && FUN_0029ece8(handle) != 0)
        FUN_0029a320(DAT_004f4948);
    ply->state = value;
}
