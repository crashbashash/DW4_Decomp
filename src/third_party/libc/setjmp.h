#ifndef DW4_LIBC_SETJMP_H
#define DW4_LIBC_SETJMP_H
#ifdef __cplusplus
extern "C" {
#endif
typedef int jmp_buf[52];
int setjmp(jmp_buf);
void longjmp(jmp_buf, int);
#ifdef __cplusplus
}
#endif
#endif
