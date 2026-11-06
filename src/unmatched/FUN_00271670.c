/* Creates the single SRD object DAT_004a9288 inside the FUN_0027e1f0/FUN_0027e268 lock: when it is
 * free, runs FUN_00271640, marks it used with mode -1 and cleared state and counts the creation in
 * DAT_004a92e8. Returns the object, or 0 when it is already in use. */
typedef struct Srd_271670 {
    signed char used;   /* 0x00 */
    signed char pad1;
    signed char state;  /* 0x02 */
    signed char mode;   /* 0x03 */
    int status;         /* 0x04 */
} Srd_271670;

extern Srd_271670 DAT_004a9288;
extern volatile int DAT_004a92e8; /* creation count; retail updates it as volatile */
void FUN_0027e1f0(void);
void FUN_0027e268(void);
void FUN_00271640(void);

Srd_271670 *FUN_00271670(void) {
    Srd_271670 *srd = 0;

    FUN_0027e1f0();
    if (DAT_004a9288.used == 0) {
        FUN_00271640();
        DAT_004a9288.used = 1;
        DAT_004a9288.mode = -1;
        DAT_004a9288.state = 0;
        DAT_004a92e8++;
        DAT_004a9288.status = 0;
        srd = &DAT_004a9288;
    }
    FUN_0027e268();
    return srd;
}

