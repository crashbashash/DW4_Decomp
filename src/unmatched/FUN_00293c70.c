/* Forwards to UTY_MulDiv with the third argument converted from seconds to milliseconds (*
 * 1000). */
extern void UTY_MulDiv(int a, int b, int ms);

void FUN_00293c70(int a, int b, int seconds) {
    UTY_MulDiv(a, b, seconds * 1000);
}
