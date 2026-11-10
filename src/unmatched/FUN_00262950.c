/* One pass of the ADX server: unless a pass is already running (DAT_0049c8c0 non-zero, checked
 * under the FUN_0025f2d0 lock), runs the service functions in a fixed order, recording the step
 * number in DAT_0049c8c0 as it goes. */
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void FUN_00272118(void);
void cvFsExecServer(void);
void FUN_0026a908(void);
void FUN_00262398(void);
extern int DAT_0049c8c0; /* server step, 0 when idle */

void FUN_00262950(void) {
    FUN_0025f2d0();
    if (DAT_0049c8c0 != 0) {
        FUN_0025f2e8();
        return;
    }
    DAT_0049c8c0 = 1;
    FUN_0025f2e8();
    DAT_0049c8c0 = 2;
    FUN_00272118();
    DAT_0049c8c0 = 3;
    cvFsExecServer();
    DAT_0049c8c0 = 4;
    FUN_0026a908();
    DAT_0049c8c0 = 5;
    FUN_00262398();
    DAT_0049c8c0 = 6;
    FUN_0026a908();
    DAT_0049c8c0 = 7;
    cvFsExecServer();
    DAT_0049c8c0 = 8;
    FUN_00272118();
    DAT_0049c8c0 = 0;
}
