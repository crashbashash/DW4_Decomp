/* CRI SRD per-handle server step for the host-file back end. State 1 seeks (sceLseek64 of sector
 * << 11) and reads into the buffer, then goes to 2, or to 9 with the negative result stored at
 * +52; state 2 polls sceIoctl(fd, 1, &busy): an error gives 9 / -1, a zero busy word completes the
 * transfer (3). An abort request (+4 == 1) first runs FUN_00271998 for a read in flight, then
 * resets the state to 0. */
typedef struct SrdHost {
    char used;
    char pad0;
    signed char state;       /* +2 */
    char pad1;
    int abort_request;       /* +4 */
    int pad2[4];
    void *buf;               /* +24 */
    int pad3;
    int size;                /* +32 */
    int pad4;
    long long sector;        /* +40 */
    int fd;                  /* +48 */
    int error;               /* +52 */
} SrdHost;

extern volatile int D_004a92e0;
extern volatile int D_004a92e4;

extern void FUN_002725a0(int marker);
extern void FUN_00271998(SrdHost *srd);
extern long long FUN_00272780(int fd, long long offset, int whence);
extern long long FUN_00272970(int fd, void *buf, int size);
extern int FUN_00272838(int fd, int cmd, int *arg);

void FUN_00271f38(SrdHost *srd)
{
    long long ret;
    int busy;

    if (srd->abort_request == 1) {
        switch (srd->state) {
        case 2:
            FUN_00271998(srd);
            srd->state = 0;
            D_004a92e4++;
            /* fall through */
        case 1:
        case 3:
        case 9:
            srd->state = 0;
            break;
        case 0:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            break;
        }
        srd->abort_request = 0;
    }
    if (srd->state == 1) {
        FUN_002725a0(0x2000);
        ret = FUN_00272780(srd->fd, srd->sector << 11, 0);
        FUN_002725a0(0x2001);
        if (ret < 0) {
            srd->state = 9;
            srd->error = (int) ret;
        }
        FUN_002725a0(0x2100);
        ret = FUN_00272970(srd->fd, srd->buf, srd->size);
        FUN_002725a0(0x2101);
        if (ret >= 0) {
            srd->state = 2;
            D_004a92e0++;
        } else {
            srd->state = 9;
            srd->error = (int) ret;
        }
    }
    if (srd->state == 2) {
        FUN_002725a0(0x2200);
        if (FUN_00272838(srd->fd, 1, &busy) < 0) {
            FUN_002725a0(0x2201);
            srd->state = 9;
            srd->error = -1;
        } else {
            FUN_002725a0(0x2202);
            if (busy == 0) {
                srd->state = 3;
                D_004a92e4++;
            }
        }
    }
}
