typedef struct ViewerInput {
    char pad0[84];
    float zoom;
    char pad88[44];
    unsigned char toggled;
} ViewerInput;

void FUN_004658c0(ViewerInput *self);

void FUN_004657b0(ViewerInput *self, int button, int pressed) {
    switch (button) {
    case 0:
        self->zoom += pressed ? 1.0f : -1.0f;
        break;
    case 1:
        self->zoom -= pressed ? 1.0f : -1.0f;
        break;
    case 2:
        if (pressed) {
            self->toggled = !self->toggled;
            FUN_004658c0(self);
        }
        break;
    }
}
