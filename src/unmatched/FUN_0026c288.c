/* Reads a done/total pair for the handle through ADXT_GetTime and returns done as an integer
 * percentage of total. */
int ADXT_GetTime(int handle, int *done, int *total);

int FUN_0026c288(int handle) {
    int done;
    int total;

    ADXT_GetTime(handle, &done, &total);
    return (float)done / (float)total * 100.0f;
}
