/* Waits for the handle's +100 flag to clear, at most 10 rounds of FUN_0029af90(handle, 1),
 * ADXM_ExecVsyncFrame(), FUN_0029af90(handle, 0). */
void FUN_0029af90(void *handle, int on);
void ADXM_ExecVsyncFrame(void);

struct Handle0029a450 {
    char pad0[100];
    int busy; /* +100 */
};

void FUN_0029a450(struct Handle0029a450 *handle) {
    int i;

    for (i = 0; i < 10; i++) {
        FUN_0029af90(handle, 1);
        ADXM_ExecVsyncFrame();
        FUN_0029af90(handle, 0);
        if (handle->busy == 0) {
            break;
        }
    }
}
