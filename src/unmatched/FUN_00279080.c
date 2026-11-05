/* 0x00279080 — FUN_00279080 (168 bytes). Sets the two 3D-sound parameters (+236, +240) of the sound object
   behind an ADXT handle after FUN_00278d58 on its +232 resource; reports "E2003091605 : NULL pointer is
   specified." for a null handle and "E2003091606 : ADXT handle must be created for 3D sound." when the
   handle is not ready (+3 below 2) or has no 3D resource. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Sound279 {
    char pad0[232];
    int resource;      /* +232 */
    int param236;      /* +236 */
    int param240;      /* +240 */
};

struct Stream279 {
    int f0;
    struct Sound279 *sound;    /* +4 */
};

struct Adxt279 {
    signed char f0;
    signed char f1;
    signed char f2;
    signed char state;         /* +3 */
    struct Stream279 *stream;  /* +4 */
};

extern void FUN_002607e8(const char *message);
extern void FUN_00278d58(int resource);
extern const char s_E2003091605_NULL_pointer_is_specified_004f14a8[];
extern const char s_E2003091606_ADXT_handle_must_be_created_for_3D_sound_004f14d8[];

void FUN_00279080(struct Adxt279 *adxt, int param236, int param240) {
    struct Sound279 *sound;
    int resource;

    if (adxt == 0) {
        FUN_002607e8(s_E2003091605_NULL_pointer_is_specified_004f14a8);
        return;
    }
    sound = adxt->stream->sound;
    resource = sound->resource;
    if (adxt->state < 2 || resource == 0) {
        FUN_002607e8(s_E2003091606_ADXT_handle_must_be_created_for_3D_sound_004f14d8);
        return;
    }
    FUN_00278d58(resource);
    sound->param236 = param236;
    sound->param240 = param240;
}
