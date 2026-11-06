/* For the handles in DAT_0049da2c and (when FUN_00264808 returns 1) DAT_0049da30: calls
 * FUN_00264300 on a handle that FUN_00264368 reports back unchanged. */
/* Retail re-reads both globals after each call, so they are volatile. */
extern volatile int DAT_0049da2c;
extern volatile int DAT_0049da30;
int FUN_00264300(int handle);
int FUN_00264368(int handle);
int FUN_00264808(void);

void FUN_00265200(void) {
    if (FUN_00264368(DAT_0049da2c) == DAT_0049da2c) {
        FUN_00264300(DAT_0049da2c);
    }
    if (FUN_00264808() == 1 && FUN_00264368(DAT_0049da30) == DAT_0049da30) {
        FUN_00264300(DAT_0049da30);
    }
}
