/* With slot 6 enabled and a threshold in slot 51, returns whether the position/rate from
 * FUN_002ae570 exceeds the threshold. */
int FUN_002adc40(int obj, int slot);
void FUN_002ae570(int obj, int block, int *pos, int *rate);

int FUN_002ae648(int obj) {
    int pos;
    int rate;
    int threshold;

    if (FUN_002adc40(obj, 6) == 0) {
        return 0;
    }
    threshold = FUN_002adc40(obj, 51);
    if (threshold == 0) {
        return threshold;
    }
    FUN_002ae570(obj, obj + 0xD28, &pos, &rate);
    return threshold < pos / rate;
}
