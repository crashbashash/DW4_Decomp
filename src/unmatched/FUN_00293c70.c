/* Forwards to FUN_002916f8 with the third argument converted from seconds to milliseconds (*
 * 1000). */
extern void FUN_002916f8(int a, int b, int ms);

void FUN_00293c70(int a, int b, int seconds) {
    FUN_002916f8(a, b, seconds * 1000);
}
