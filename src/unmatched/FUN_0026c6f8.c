/* matching construct: hand search — an empty macro after the call keeps it from being a tail call */
#define EMPTY_MACRO() do { } while (0)
void ADXSJD_GetDefOutVol(int);
void FUN_0026c6f8(char *);
void FUN_0026c6f8(char * p0)
{
    ADXSJD_GetDefOutVol(*(int *)((char *)p0 + 4));
    EMPTY_MACRO();
}
