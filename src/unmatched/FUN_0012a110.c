/* newlib strcasecmp(s1, s2). */
extern const char D_004d3d10[];
#define _U 01
#define isupper(c) ((D_004d3d10+1)[(unsigned)(c)]&_U)
#define tolower(c) \
	__extension__ ({ int __x = (c); isupper(__x) ? (__x - 'A' + 'a') : __x;})

int FUN_0012a110(const char *s1, const char *s2)
{
  while (*s1 != '\0' && tolower(*s1) == tolower(*s2))
    {
      s1++;
      s2++;
    }

  return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}
