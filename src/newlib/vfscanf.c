#include "dw4/newlib_stdio.h"

extern const short basefix[17];
extern const char exponent_format[];
extern const char _ctype_[];
typedef int wchar_t;
int ungetc (int, FILE *);
size_t fread (void *, size_t _size, size_t _n, FILE *);
int sprintf (char *, const char *, ...);
double atof (const char *__nptr);
long atol (const char *__nptr);
long strtol (const char *__n, char **_end_PTR, int __base);
unsigned long strtoul (const char *_n_PTR, char **_end_PTR, int __base);
char *__sccl ();

int __svfscanf(register FILE *fp, char const *fmt0, va_list ap)
{
  register char *fmt = (char *) fmt0;
  register int c;
  register size_t width;
  register char *p;
  register int n;
  register int flags;
  register char *p0;
  int nassigned;
  int nread;
  int base = 0;
  int nbytes = 1;
  wchar_t wc;
  unsigned long (*ccfn) () = 0;
  char ccltab[256];
  char buf[(308+39+3)];
  char *lptr;
  short *sp;
  int *ip;
  float *flp;
  long double *ldp;
  double *dp;
  long *lp;
  nassigned = 0;
  nread = 0;
  for (;;)
    {
      wc = *fmt;
      fmt += nbytes;
      if (wc == 0)
        return nassigned;
      if (nbytes == 1 && ((_ctype_+1)[(unsigned)(wc)]&010))
        {
          for (;;)
            {
              if ((fp->_r <= 0 && __srefill(fp)))
                return nassigned;
              if (!((_ctype_+1)[(unsigned)(*fp->_p)]&010))
                break;
              nread++, fp->_r--, fp->_p++;
            }
          continue;
        }
      if (wc != '%')
        goto literal;
      width = 0;
      flags = 0;
    again:
      c = *fmt++;
      switch (c)
        {
        case '%':
        literal:
          lptr = fmt - nbytes;
          for (n = 0; n < nbytes; ++n)
            {
              if ((fp->_r <= 0 && __srefill(fp)))
                goto input_failure;
              if (*fp->_p != *lptr)
                goto match_failure;
              fp->_r--, fp->_p++;
              nread++;
              ++lptr;
            }
          continue;
        case '*':
          flags |= 0x08;
          goto again;
        case 'l':
          flags |= 0x01;
          goto again;
        case 'L':
          flags |= 0x02;
          goto again;
        case 'h':
          flags |= 0x04;
          goto again;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          width = width * 10 + c - '0';
          goto again;
        case 'D':
          flags |= 0x01;
        case 'd':
          c = 3;
          ccfn = (unsigned long (*)())strtol;
          base = 10;
          break;
        case 'i':
          c = 3;
          ccfn = (unsigned long (*)())strtol;
          base = 0;
          break;
        case 'O':
          flags |= 0x01;
        case 'o':
          c = 3;
          ccfn = strtoul;
          base = 8;
          break;
        case 'u':
          c = 3;
          ccfn = strtoul;
          base = 10;
          break;
        case 'X':
        case 'x':
          flags |= 0x100;
          c = 3;
          ccfn = strtoul;
          base = 16;
          break;
        case 'E':
        case 'G':
        case 'e':
        case 'f':
        case 'g':
          c = 4;
          break;
        case 's':
          c = 2;
          break;
        case '[':
          fmt = __sccl (ccltab, fmt);
          flags |= 0x20;
          c = 1;
          break;
        case 'c':
          flags |= 0x20;
          c = 0;
          break;
        case 'p':
          flags |= 0x10 | 0x100;
          c = 3;
          ccfn = strtoul;
          base = 16;
          break;
        case 'n':
          if (flags & 0x08)
            continue;
          if (flags & 0x04)
            {
              sp = __builtin_va_arg((ap), short *);
              *sp = nread;
            }
          else if (flags & 0x01)
            {
              lp = __builtin_va_arg((ap), long *);
              *lp = nread;
            }
          else
            {
              ip = __builtin_va_arg((ap), int *);
              *ip = nread;
            }
          continue;
        case '\0':
          return (-1);
        default:
          if (((_ctype_+1)[(unsigned)(c)]&01))
            flags |= 0x01;
          c = 3;
          ccfn = (unsigned long (*)())strtol;
          base = 10;
          break;
        }
      if ((fp->_r <= 0 && __srefill(fp)))
        goto input_failure;
      if ((flags & 0x20) == 0)
        {
          while (((_ctype_+1)[(unsigned)(*fp->_p)]&010))
            {
              nread++;
              if (--fp->_r > 0)
                fp->_p++;
              else
              if (__srefill (fp))
                goto input_failure;
            }
        }
      switch (c)
        {
        case 0:
          if (width == 0)
            width = 1;
          if (flags & 0x08)
            {
              size_t sum = 0;
              for (;;)
                {
                  if ((n = fp->_r) < width)
                    {
                      sum += n;
                      width -= n;
                      fp->_p += n;
                      if (__srefill (fp))
                        {
                          if (sum == 0)
                            goto input_failure;
                          break;
                        }
                    }
                  else
                    {
                      sum += width;
                      fp->_r -= width;
                      fp->_p += width;
                      break;
                    }
                }
              nread += sum;
            }
          else
            {
              size_t r = fread ((void *) __builtin_va_arg((ap), char *), 1, width, fp);
              if (r == 0)
                goto input_failure;
              nread += r;
              nassigned++;
            }
          break;
        case 1:
          if (width == 0)
            width = ~0;
          if (flags & 0x08)
            {
              n = 0;
              while (ccltab[*fp->_p])
                {
                  n++, fp->_r--, fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && __srefill(fp)))
                    {
                      if (n == 0)
                        goto input_failure;
                      break;
                    }
                }
              if (n == 0)
                goto match_failure;
            }
          else
            {
              p0 = p = __builtin_va_arg((ap), char *);
              while (ccltab[*fp->_p])
                {
                  fp->_r--;
                  *p++ = *fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && __srefill(fp)))
                    {
                      if (p == p0)
                        goto input_failure;
                      break;
                    }
                }
              n = p - p0;
              if (n == 0)
                goto match_failure;
              *p = 0;
              nassigned++;
            }
          nread += n;
          break;
        case 2:
          if (width == 0)
            width = ~0;
          if (flags & 0x08)
            {
              n = 0;
              while (!((_ctype_+1)[(unsigned)(*fp->_p)]&010))
                {
                  n++, fp->_r--, fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && __srefill(fp)))
                    break;
                }
              nread += n;
            }
          else
            {
              p0 = p = __builtin_va_arg((ap), char *);
              while (!((_ctype_+1)[(unsigned)(*fp->_p)]&010))
                {
                  fp->_r--;
                  *p++ = *fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && __srefill(fp)))
                    break;
                }
              *p = 0;
              nread += p - p0;
              nassigned++;
            }
          continue;
        case 3:
          if (--width > sizeof (buf) - 2)
            width = sizeof (buf) - 2;
          width++;
          flags |= 0x40 | 0x80 | 0x200;
          for (p = buf; width; width--)
            {
              c = *fp->_p;
              switch (c)
                {
                case '0':
                  if (base == 0)
                    {
                      base = 8;
                      flags |= 0x100;
                    }
                  if (flags & 0x200)
                    flags &= ~(0x40 | 0x200 | 0x80);
                  else
                    flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                  base = basefix[base];
                  flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case '8':
                case '9':
                  base = basefix[base];
                  if (base <= 8)
                    break;
                  flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                  if (base <= 10)
                    break;
                  flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case '+':
                case '-':
                  if (flags & 0x40)
                    {
                      flags &= ~0x40;
                      goto ok;
                    }
                  break;
                case 'x':
                case 'X':
                  if (flags & 0x100 && p == buf + 1)
                    {
                      base = 16;
                      flags &= ~0x100;
                      goto ok;
                    }
                  break;
                }
              break;
            ok:
              *p++ = c;
              if (--fp->_r > 0)
                fp->_p++;
              else
              if (__srefill (fp))
                break;
            }
          if (flags & 0x80)
            {
              if (p > buf)
                (void) ungetc (*(char *)-- p, fp);
              goto match_failure;
            }
          c = ((char *) p)[-1];
          if (c == 'x' || c == 'X')
            {
              --p;
                         ungetc (c, fp);
            }
          if ((flags & 0x08) == 0)
            {
              unsigned long res;
              *p = 0;
              res = (*ccfn) (buf, (char **) 0, base);
              if (flags & 0x10)
                *(__builtin_va_arg((ap), void * *)) = (void *) (unsigned long) res;
              else if (flags & 0x04)
                {
                  sp = __builtin_va_arg((ap), short *);
                  *sp = res;
                }
              else if (flags & 0x01)
                {
                  lp = __builtin_va_arg((ap), long *);
                  *lp = res;
                }
              else
                {
                  ip = __builtin_va_arg((ap), int *);
                  *ip = res;
                }
              nassigned++;
            }
          nread += p - buf;
          break;
        case 4:
        {
          long leading_zeroes;
          long zeroes, exp_adjust;
          char *exp_start;
          if (--width > sizeof (buf) - 2)
            width = sizeof (buf) - 2;
          width++;
          flags |= 0x40 | 0x80 | 0x100 | 0x200;
          zeroes = 0;
          exp_adjust = 0;
          for (p = buf; width; )
            {
              c = *fp->_p;
              switch (c)
                {
                case '0':
                  if (flags & 0x80)
                    {
                      flags &= ~0x40;
                      zeroes++;
                      goto fskip;
                    }
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                  flags &= ~(0x40 | 0x80);
                  goto fok;
                case '+':
                case '-':
                  if (flags & 0x40)
                    {
                      flags &= ~0x40;
                      goto fok;
                    }
                  break;
                case '.':
                  if (flags & 0x100)
                    {
                      flags &= ~(0x40 | 0x100);
                      leading_zeroes = zeroes;
                      goto fok;
                    }
                  break;
                case 'e':
                case 'E':
                  if ((flags & (0x80 | 0x200)) == 0x200
                      || ((flags & 0x200) && zeroes))
                    {
                      if (! (flags & 0x100))
                        {
                          exp_adjust = zeroes - leading_zeroes;
                          exp_start = p;
                        }
                      flags =
                        (flags & ~(0x200 | 0x100)) |
                        0x40 | 0x80;
                      zeroes = 0;
                      goto fok;
                    }
                  break;
                }
              break;
            fok:
              *p++ = c;
              width--;
            fskip:
              ++nread;
              if (--fp->_r > 0)
                fp->_p++;
              else
              if (__srefill (fp))
                break;
            }
          if (zeroes)
            flags &= ~0x80;
          if (flags & 0x80)
            {
              if (flags & 0x200)
                {
                  while (p > buf)
                    {
                      ungetc (*(char *)-- p, fp);
                    }
                  goto match_failure;
                }
              c = *(char *)-- p;
              --nread;
              if (c != 'e' && c != 'E')
                {
                  (void) ungetc (c, fp);
                  c = *(char *)-- p;
                  --nread;
                }
              (void) ungetc (c, fp);
            }
          if ((flags & 0x08) == 0)
            {
              double res;
              long new_exp;
              *p = 0;
              if ((flags & (0x100 | 0x200)) == 0x200)
                {
                  exp_adjust = zeroes - leading_zeroes;
                  new_exp = -exp_adjust;
                  exp_start = p;
                }
              else if (exp_adjust)
                new_exp = atol (exp_start + 1) - exp_adjust;
              if (exp_adjust)
                {
                  if (exp_start >= buf + sizeof (buf) - ((8 * sizeof (long) - 1) * 4 / 13 + 2))
                    exp_start = buf + sizeof (buf) - ((8 * sizeof (long) - 1) * 4 / 13 + 2) - 1;
                 sprintf (exp_start, exponent_format, new_exp);
                }
              res = atof (buf);
              if (flags & 0x01)
                {
                  dp = __builtin_va_arg((ap), double *);
                  *dp = res;
                }
              else if (flags & 0x02)
                {
                  ldp = __builtin_va_arg((ap), long double *);
                  *ldp = res;
                }
              else
                {
                  flp = __builtin_va_arg((ap), float *);
                  *flp = res;
                }
              nassigned++;
            }
          break;
        }
        }
    }
input_failure:
  return nassigned ? nassigned : -1;
match_failure:
  return nassigned;
}

char * __sccl(register char *tab, register char *fmt)
{
  register int c, n, v;
  c = *fmt++;
  if (c == '^')
    {
      v = 1;
      c = *fmt++;
    }
  else
    v = 0;
  for (n = 0; n < 256; n++)
    tab[n] = v;
  if (c == 0)
    return fmt - 1;
  v = 1 - v;
  for (;;)
    {
      tab[c] = v;
    doswitch:
      n = *fmt++;
      switch (n)
        {
        case 0:
          return fmt - 1;
        case '-':
          n = *fmt;
          if (n == ']' || n < c)
            {
              c = '-';
              break;
            }
          fmt++;
          do
            {
              tab[++c] = v;
            }
          while (c < n);
          goto doswitch;
          break;
        case ']':
          return fmt;
        default:
          c = n;
          break;
        }
    }
}
