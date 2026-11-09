/* CRI SRD (stream reader) per-handle server step. The state byte (+2) walks the CD read cycle: 1
 * read requested (sceCdRead issued) goes to 2, or 9 on failure; 2 read in flight (sceCdSync(1)
 * polled) goes to 3 done or 9 error. A pending abort request (+4 == 1) first breaks and syncs the
 * drive when a read is in flight, then resets the handle to state 0. The statistics words are
 * volatile, which produces the delay-slot and address-load shapes. */
typedef struct Srd {
    char used;
    char pad0;
    signed char state;      /* +2 */
    char pad1;
    int abort_request;      /* +4 */
    int lsn;                /* +8 */
    int sectors;            /* +12 */
    void *buf;              /* +16 */
    unsigned char trycount; /* +20, sceCdRMode */
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad2;
    int pad3[7];
    int error;              /* +52 */
} Srd;

extern char D_004efca8[];
extern volatile int D_004a92dc;
extern int D_004a92e0;
extern volatile int D_004a92e4;
extern int D_004a9300;
extern unsigned char D_004a9304;

extern void FUN_002725a0(int marker);
extern int sceCdBreak(void);
extern int sceCdSync(int mode);
extern int sceCdRead(int lsn, int sectors, void *buf, void *mode);
extern int FUN_00271c00(Srd *srd);
extern int FUN_0010d108(char *fmt, ...);

void FUN_00271d50(Srd *srd)
{
    int busy;
    int result;

    if (srd->abort_request == 1) {
        switch (srd->state) {
        case 2:
            FUN_002725a0(0x1600);
            busy = sceCdBreak();
            FUN_002725a0(0x1601);
            if (busy == 0)
                FUN_0010d108(D_004efca8, D_004a92dc);
            FUN_002725a0(0x1700);
            sceCdSync(0);
            FUN_002725a0(0x1701);
            srd->state = 0;
            D_004a92e4++;
            break;
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
        FUN_002725a0(0x1800);
        if (D_004a9300 == 1)
            srd->spindlctrl = D_004a9304;
        busy = sceCdRead(srd->lsn, srd->sectors, srd->buf, &srd->trycount);
        FUN_002725a0(0x1801);
        if (busy == 1) {
            D_004a92e0++;
            srd->state = 2;
        } else {
            srd->state = 9;
            srd->error = -1;
        }
    }
    if (srd->state == 2) {
        FUN_002725a0(0x1900);
        busy = sceCdSync(1);
        FUN_002725a0(0x1901);
        result = FUN_00271c00(srd);
        if (busy == 0) {
            srd->state = (result == 1) ? 9 : 3;
            D_004a92e4++;
        }
    }
}
