#include "dw4/newlib_mallocr.h"

typedef struct __sFILE FILE;
int fiprintf(FILE *fp, const char *fmt, ...);
void __malloc_update_mallinfo(void);
extern const char max_system_bytes_format[], system_bytes_format[], in_use_bytes_format[];

void _malloc_stats_r(struct _reent *ptr)
{
    unsigned long local_max_total_mem;
    int local_sbrked_mem;
    struct mallinfo local_mallinfo;
    FILE *fp;

    __malloc_lock(ptr);
    __malloc_update_mallinfo();
    local_max_total_mem = max_total_mem;
    local_sbrked_mem = sbrked_mem;
    local_mallinfo = current_mallinfo;
    __malloc_unlock(ptr);

    fp = ptr->_stderr;
    fiprintf(fp, max_system_bytes_format, (unsigned int)local_max_total_mem);
    fiprintf(fp, system_bytes_format, (unsigned int)local_sbrked_mem);
    fiprintf(fp, in_use_bytes_format, (unsigned int)local_mallinfo.uordblks);
}
