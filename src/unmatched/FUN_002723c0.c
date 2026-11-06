/* For the SRD object DAT_004a9288 in state 2: inside the FUN_0027e1c0/FUN_0027e1d8 critical
 * section, queries its request (+48) with FUN_00272838(request, 1, &status) between FUN_002725a0
 * trace markers (0x2400, then 0x2401 on failure or 0x2402); returns 1 when the status is non-zero,
 * else 0. */
typedef struct Srd_2723c0 {
    signed char used;   /* 0x00 */
    signed char pad1;
    signed char state;  /* 0x02 */
    char pad3[45];
    int request;        /* 0x30 */
} Srd_2723c0;

extern Srd_2723c0 DAT_004a9288;
void FUN_0027e1c0(void);
void FUN_0027e1d8(void);
void FUN_002725a0(int marker);
int FUN_00272838(int request, int mode, int *status);

int FUN_002723c0(void) {
    int status;

    if (DAT_004a9288.state == 2) {
        FUN_0027e1c0();
        FUN_002725a0(0x2400);
        if (FUN_00272838(DAT_004a9288.request, 1, &status) < 0) {
            FUN_002725a0(0x2401);
        } else {
            FUN_002725a0(0x2402);
            if (status != 0) {
                FUN_0027e1d8();
                return 1;
            }
        }
        FUN_0027e1d8();
    }
    return 0;
}

