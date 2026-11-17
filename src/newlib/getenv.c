#include "dw4/newlib_reent.h"
#include "dw4/newlib_env.h"


char *_findenv(const char *name, int *offset)
{
    return _findenv_r(_REENT, name, offset);
}

char *getenv(const char *name)
{
    int offset;

    return _findenv_r(_REENT, name, &offset);
}
