/* 0x002771d0 — FUN_002771d0 (64 bytes). Resets the three counters (+28, +32, +36) of a stream controller
   ("lsc") unless its active byte (+1) is set; a null controller is reported as
   "E0003: Illigal parameter lsc=NULL". Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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
extern const char s_E0003_Illigal_parameter_lsc_NULL_004f0b08[];

void FUN_002771d0(struct Lsc277 *lsc) {
    if (lsc == 0) {
        FUN_002777f8(s_E0003_Illigal_parameter_lsc_NULL_004f0b08);
        return;
    }
    if (lsc->active == 0) {
        lsc->count28 = 0;
        lsc->count32 = 0;
        lsc->count36 = 0;
    }
}
