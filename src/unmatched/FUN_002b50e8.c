/* One-time initialiser: while the counter DAT_004bf280 is not positive, stores FUN_002b5138's
 * result in DAT_005856a8 and bumps the counter. */
int FUN_002b5138();

extern int DAT_004bf280;                  /* initialisation count */
/* matching construct: manual — a volatile store target gives retail's la + sw 0(reg) and keeps the counter load ahead of it */
extern volatile int DAT_005856a8;

void FUN_002b50e8(void) {
    if (DAT_004bf280 <= 0) {
        DAT_005856a8 = FUN_002b5138();
        DAT_004bf280++;
    }
}
