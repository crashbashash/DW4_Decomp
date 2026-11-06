/* Sets the byte at +3 of a stream controller; a null controller is reported as "E0003: Illigal
 * parameter lsc=NULL". */
struct Lsc277 {
    signed char f0;
    signed char active;   /* +1 */
    signed char reading;  /* +2 */
    signed char f3;       /* +3 */
    char pad4[24];
    int count28;          /* +28 */
    int count32;          /* +32 */
    int count36;          /* +36 */
    int stream;           /* +40 */
    int f44;              /* +44 */
    int f48;
    int f52;              /* +52 */
};

extern void FUN_002777f8(const char *message);
extern const char E0003_Illigal_parameter_lsc_NULL[];

void FUN_00277768(struct Lsc277 *lsc, int value) {
    if (lsc == 0) {
        FUN_002777f8(E0003_Illigal_parameter_lsc_NULL);
        return;
    }
    lsc->f3 = value;
}
