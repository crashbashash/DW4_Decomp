/* While the wake request DAT_0049d9dc is pending (1), wakes the thread DAT_0049da28 if it is
 * waiting (THS_WAIT or THS_WAITSUSPEND) and clears the request once WakeupThread succeeds. */
/* Status block filled by ReferThreadStatus; ps2sdk reference: ee/kernel/include/kernel.h (ee_thread_status_t, THS_*). */
typedef struct ThreadStatus_265288 {
    int status;     /* 0x00 */
    int pad4[11];
} ThreadStatus_265288;  /* 0x30 bytes */

#define THS_WAIT        0x04
#define THS_WAITSUSPEND 0x0c

extern int DAT_0049d9dc;
extern volatile int DAT_0049da28; /* retail re-reads it before each call */
int ReferThreadStatus(int thread_id, ThreadStatus_265288 *info);
int WakeupThread(int thread_id);

void FUN_00265288(void) {
    ThreadStatus_265288 info;

    if (DAT_0049d9dc == 1) {
        ReferThreadStatus(DAT_0049da28, &info);
        if (info.status == THS_WAIT || info.status == THS_WAITSUSPEND) {
            if (WakeupThread(DAT_0049da28) == DAT_0049da28) {
                DAT_0049d9dc = 0;
            }
        }
    }
}
