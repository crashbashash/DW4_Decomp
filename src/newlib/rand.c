#include "dw4/newlib_reent.h"

void srand(unsigned int seed)
{
    _REENT->_new._reent._rand_next = seed;
}

int rand(void)
{
    _REENT->_new._reent._rand_next = _REENT->_new._reent._rand_next * 6364136223846793005UL + 1;
    return (int)((_REENT->_new._reent._rand_next >> 32) & 0x7fffffff);
}
