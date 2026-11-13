/* CRI SJCRS: the critical section the stream joints take, and the count of server passes running. */

void SVM_Lock(void);
void SVM_Unlock(void);

extern int sjcrs_svr_cnt;

void SJCRS_Init(void)
{
    sjcrs_svr_cnt = 0;
}

void SJCRS_Finish(void)
{
    sjcrs_svr_cnt = 0;
}

void SJCRS_BeginSvr(void)
{
    sjcrs_svr_cnt++;
}

void SJCRS_EndSvr(void)
{
    sjcrs_svr_cnt--;
}

void SJCRS_Lock(void)
{
    SVM_Lock();
}

void SJCRS_Unlock(void)
{
    SVM_Unlock();
}
