/* 0x00277278 — FUN_00277278 (132 bytes). Stops an active stream controller: clears the active byte,
   stops a running read on its stream (+40) through FUN_0026a2a0, clears +44, resets the counters
   (FUN_002771d0) and clears +52; a null controller is reported as "E0003: Illigal parameter lsc=NULL".
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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

extern void FUN_0026a2a0(int stream);
extern void FUN_002771d0(struct Lsc277 *lsc);

void FUN_00277278(struct Lsc277 *lsc) {
    if (lsc == 0) {
        FUN_002777f8(s_E0003_Illigal_parameter_lsc_NULL_004f0b08);
        return;
    }
    if (lsc->active != 0) {
        lsc->active = 0;
        if (lsc->stream != 0 && lsc->reading == 1) {
            FUN_0026a2a0(lsc->stream);
            lsc->reading = 0;
        }
        lsc->f44 = 0;
        FUN_002771d0(lsc);
        lsc->f52 = 0;
    }
}
