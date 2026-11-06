/* Forwards three arguments to FUN_002aee00 on the handle's stream object from FUN_002963a8. */
extern void *FUN_002963a8(void *sfd);
extern void FUN_002aee00(void *stream, int a, int b, int c);

void FUN_002952d0(void *sfd, int a, int b, int c) {
    FUN_002aee00(FUN_002963a8(sfd), a, b, c);
}
