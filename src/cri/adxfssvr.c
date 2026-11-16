/* The ADX file-system server: one pass over the file-reading layers, guarded against re-entry. */

void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
void SRD_ExecServer(void);
void cvFsExecServer(void);
void ADXSTM_ExecServer(void);
void ADXF_ExecServer(void);

/* The step the running pass has reached, 0 when no pass is running. */
int adxt_fssvr_step = 0;

void ADXT_ExecFsSvr(void)
{
    ADXCRS_Lock();
    if (adxt_fssvr_step != 0) {
        ADXCRS_Unlock();
        return;
    }
    adxt_fssvr_step = 1;
    ADXCRS_Unlock();
    adxt_fssvr_step = 2;
    SRD_ExecServer();
    adxt_fssvr_step = 3;
    cvFsExecServer();
    adxt_fssvr_step = 4;
    ADXSTM_ExecServer();
    adxt_fssvr_step = 5;
    ADXF_ExecServer();
    adxt_fssvr_step = 6;
    ADXSTM_ExecServer();
    adxt_fssvr_step = 7;
    cvFsExecServer();
    adxt_fssvr_step = 8;
    SRD_ExecServer();
    adxt_fssvr_step = 0;
}

void ADXT_ExecFsServer(void)
{
    ADXT_ExecFsSvr();
}

/* Whether a file-system server pass is running. The step word guards the pass against re-entry from the
 * file-system thread and from the main thread's blocking stream calls, so it is read through a volatile
 * access. */
int ADXT_IsActiveFsSvr(void)
{
    return *(volatile int *)&adxt_fssvr_step != 0;
}
