/* Dispatches on mwsfd_spr_cpu_copy: FUN_002961c0 while it is clear, FUN_00296190 otherwise. */
extern int mwsfd_spr_cpu_copy;
extern int FUN_002961c0(void);
extern int FUN_00296190(void);

/* matching construct: manual — an int function that falls off the end; a void
 * function or `return f()` turns the two calls into tail jumps, retail keeps jal + return. */
int FUN_00296150(void) {
    if (mwsfd_spr_cpu_copy == 0) {
        FUN_002961c0();
    } else {
        FUN_00296190();
    }
}
