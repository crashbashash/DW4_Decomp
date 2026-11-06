/* Moves a state word from 4 to 2; any other state becomes 0. */
void FUN_002a8690(int *state) {
    if (state != 0) {
        if (*state == 4) {
            *state = 2;
        } else {
            *state = 0;
        }
    }
}
