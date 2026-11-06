/* Restarts a stream controller: stops it first (FUN_00277278) when it is active, then marks it
 * active as state 2 when +36 is positive and state 1 otherwise; a null controller is reported as
 * "E0003: Illigal parameter lsc=NULL". */
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

extern void FUN_00277278(struct Lsc277 *lsc);

void FUN_00277210(struct Lsc277 *lsc) {
    if (lsc == 0) {
        FUN_002777f8(E0003_Illigal_parameter_lsc_NULL);
        return;
    }
    if (lsc->active != 0) {
        FUN_00277278(lsc);
    }
    if (lsc->count36 > 0) {
        lsc->active = 2;
    } else {
        lsc->active = 1;
    }
}
