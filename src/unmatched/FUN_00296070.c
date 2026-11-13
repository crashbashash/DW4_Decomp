/* Dispatches on mwsfd_spr_cpu_copy: FUN_002960e8 while it is clear, FUN_002960b0 otherwise. */
extern int mwsfd_spr_cpu_copy;
extern int FUN_002960e8(void);
extern int FUN_002960b0(void);

/* matching construct: manual — an int function that falls off the end; a void
 * function or `return f()` turns the two calls into tail jumps, retail keeps jal + return. */
int FUN_00296070(void) {
    if (mwsfd_spr_cpu_copy == 0) {
        FUN_002960e8();
    } else {
        FUN_002960b0();
    }
}
