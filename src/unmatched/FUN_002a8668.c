/* Moves a state word from 4 to 3; any other state becomes 0. */
void FUN_002a8668(int *state) {
    if (state != 0) {
        if (*state == 4) {
            *state = 3;
        } else {
            *state = 0;
        }
    }
}
