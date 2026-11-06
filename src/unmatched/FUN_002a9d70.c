/* Once only, stops the play state's buffer at +4376 and records a value with the stopped flag
 * (+4292/+4296). */
typedef struct SfdPumpCtl {
    char pad0[28];
    int stopped;            /* +28 */
    int value;              /* +32 */
} SfdPumpCtl;

typedef struct SfdPlayState {
    char pad0[4264];
    SfdPumpCtl ctl;         /* +4264 */
    char pad4300[76];
    char buf[4];            /* +4376 */
} SfdPlayState;

typedef struct SfdHandle {
    char pad0[8120];
    SfdPlayState *play;     /* +8120 */
} SfdHandle;

extern void FUN_002a9680(void *buf);

void FUN_002a9d70(SfdHandle *handle, int value) {
    SfdPlayState *play = handle->play;
    SfdPumpCtl *ctl = &play->ctl;

    if (ctl->stopped != 1) {
        FUN_002a9680(play->buf);
        ctl->stopped = 1;
        ctl->value = value;
    }
}
