int M2VERR_InitErrInf();
extern int m2verrinf[4];
void M2VERR_Init(void) {
    M2VERR_InitErrInf(&m2verrinf[0]);
}
