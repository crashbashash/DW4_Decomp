#include "dw4/newlib_mallocr.h"

typedef struct __sFILE FILE;
int fiprintf(FILE *fp, const char *fmt, ...);
int _mallopt_r(struct _reent *ptr, int param, int value);
void _malloc_stats_r(struct _reent *ptr);
struct mallinfo _mallinfo_r(struct _reent *ptr);
extern const char memory_allocation_statistics_format[];

struct mallinfo mallinfo(void)
{
    return _mallinfo_r(_REENT);
}

void malloc_stats(void)
{
    _malloc_stats_r(_REENT);
}

int mallopt(int param, int value)
{
    return _mallopt_r(_REENT, param, value);
}

void _mstats_r(struct _reent *ptr, char *s)
{
    fiprintf(ptr->_stderr, memory_allocation_statistics_format, s);
    _malloc_stats_r(ptr);
}

void mstats(char *s)
{
    _mstats_r(_REENT, s);
}
