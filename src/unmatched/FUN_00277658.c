/* Sets the value at +20 of an lsc object after checking it lies in 0..limit (+24); a NULL object
 * or out-of-range value is reported through FUN_002777f8. */
typedef struct Lsc_277658 {
    char pad0[20];
    int value;  /* 0x14 */
    int limit;  /* 0x18 */
} Lsc_277658;

extern char E0003_Illigal_parameter_lsc_NULL[];        /* 'E0003: Illigal parameter lsc=NULL\n' */
extern char E0010_Illigal_parameter_min_val_d[];       /* 'E0010: Illigal parameter min_val=%d\n' */
void FUN_002777f8(const char *format, ...);

void FUN_00277658(Lsc_277658 *lsc, int value) {
    if (lsc == 0) {
        FUN_002777f8(E0003_Illigal_parameter_lsc_NULL);
        return;
    }
    if (value < 0 || lsc->limit < value) {
        FUN_002777f8(E0010_Illigal_parameter_min_val_d, value);
        return;
    }
    lsc->value = value;
}
