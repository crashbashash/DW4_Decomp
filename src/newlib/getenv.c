#include "dw4/newlib_reent.h"

char *_findenv_r(struct _reent *ptr, const char *name, int *offset);

char *_findenv(const char *name, int *offset)
{
    return _findenv_r(_REENT, name, offset);
}

char *getenv(const char *name)
{
    int offset;

    return _findenv_r(_REENT, name, &offset);
}
