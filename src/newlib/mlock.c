int GetThreadId(void);
int WaitSema(int sema_id);
int SignalSema(int sema_id);
extern int __malloc_lock_owner;
extern int call_count;
extern int __sce_sema_id;

void __malloc_lock(void)
{
    int thread = GetThreadId();

    if (__malloc_lock_owner == thread) {
        call_count++;
        return;
    }
    WaitSema(__sce_sema_id);
    __malloc_lock_owner = thread;
    call_count++;
}

void __malloc_unlock(void)
{
    if (--call_count == 0) {
        __malloc_lock_owner = -1;
        SignalSema(__sce_sema_id);
    }
}
