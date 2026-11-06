/* Reads a done/total pair for the handle through FUN_0026bf90 and returns done as an integer
 * percentage of total. */
int FUN_0026bf90(int handle, int *done, int *total);

int FUN_0026c288(int handle) {
    int done;
    int total;

    FUN_0026bf90(handle, &done, &total);
    return (float)done / (float)total * 100.0f;
}
