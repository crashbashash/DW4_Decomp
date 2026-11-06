/* mwPlySfdInit (named by its diagnostic string): checks the SFD library version "1.946",
 * initialises it with a parameter block whose second word is `arg`, and installs FUN_00295010
 * through FUN_002a0c68; failures record errors -301 / -303. */
int FUN_002a0998(const char *version, int size);
int FUN_002a09a8(void *params);
int FUN_002a0c68(int a, void (*fn)(), int b);
int FUN_00294ef8(int error);
void FUN_0029a320(const char *format, ...);
void FUN_00295010();

struct InitParams00294f48 {
    int f0;
    int arg; /* +4 */
};

extern struct InitParams00294f48 DAT_004f33a0; /* default parameter block */
extern char DAT_004f3420[];                    /* "1.946" */
extern char DAT_004f3428[];                    /* "E011081 mwPlySfdInit: Not compatible SFD Version." */

int FUN_00294f48(int arg) {
    struct InitParams00294f48 params = DAT_004f33a0;
    int result;

    params.arg = arg;
    if (FUN_002a0998(DAT_004f3420, 14072) != 1) {
        FUN_0029a320(DAT_004f3428);
        return -1;
    }
    if (FUN_002a09a8(&params) != 0) {
        return FUN_00294ef8(-301);
    }
    result = FUN_002a0c68(0, FUN_00295010, 0);
    if (result != 0) {
        result = FUN_00294ef8(-303);
    }
    return result;
}
