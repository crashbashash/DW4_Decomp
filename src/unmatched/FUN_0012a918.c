/* newlib strncasecmp(s1, s2, n). */
extern const char D_004d3d10[];
#define _U 01
#define isupper(c) ((D_004d3d10+1)[(unsigned)(c)]&_U)
#define tolower(c) \
	__extension__ ({ int __x = (c); isupper(__x) ? (__x - 'A' + 'a') : __x;})
typedef unsigned int size_t;

int FUN_0012a918(const char *s1, const char *s2, size_t n)
{
  if (n == 0)
    return 0;

  while (n-- != 0 && tolower(*s1) == tolower(*s2))
    {
      if (n == 0 || *s1 == '\0' || *s2 == '\0')
	break;
      s1++;
      s2++;
    }

  return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}
