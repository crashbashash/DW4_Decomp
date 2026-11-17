#include "dw4/newlib/newlib_stdio.h"
#include <string.h>
#include "dw4/newlib/newlib_env.h"

#define ENV_LOCK __env_lock(reent_ptr)
#define ENV_UNLOCK __env_unlock(reent_ptr)
extern char ***p_environ;

char *
_findenv_r(struct _reent *reent_ptr, register const char *name, int *offset)
{
  register int len;
  register char **p;
  const char *c;

  ENV_LOCK;

  /* In some embedded systems, this does not get set.  This protects
     newlib from dereferencing a bad pointer.  */
  if (!*p_environ)
    return NULL;

  c = name;
  len = 0;
  while (*c && *c != '=')
    {
      c++;
      len++;
    }

  for (p = *p_environ; *p; ++p)
    if (!strncmp (*p, name, len))
      if (*(c = *p + len) == '=')
	{
	  *offset = p - *p_environ;
          ENV_UNLOCK;
	  return (char *) (++c);
	}
  ENV_UNLOCK;
  return NULL;
}

char *_getenv_r(struct _reent *reent_ptr, const char *name)
{
    int offset;

    return _findenv_r(reent_ptr, name, &offset);
}
