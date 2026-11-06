/* Calls FUN_00275090 with a, b and fields 8, 12 and 4 of a descriptor and returns its result; for
 * a null descriptor calls FUN_00274f10 with zeros and returns 0. */
/* Five-word descriptor read by FUN_0026ad50, FUN_0026adb0 and FUN_0026ae18. */
typedef struct Desc_26ad50 {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
} Desc_26ad50;
int FUN_00274f10(int a0, int a1, int a2, int a3);
int FUN_00275090(int a, int b, int c, int d, int e);

int FUN_0026adb0(Desc_26ad50 *desc, int a, int b) {
    int result = 0;

    if (desc != 0) {
        result = FUN_00275090(a, b, desc->f8, desc->f12, desc->f4);
    } else {
        FUN_00274f10(0, 0, 0, 0);
    }
    return result;
}
