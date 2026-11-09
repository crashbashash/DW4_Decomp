extern float sqrtf(float);
extern const float g_vec3Zero[4];

typedef struct ViewerCameraTarget {
    char pad0[76];
    float aspect;
    char pad80[12];
    float f92;
    float f96;
    float f100;
    char pad104[56];
    float f160;
    float f164;
    float f168;
} ViewerCameraTarget;

typedef struct ViewerCameraState {
    char pad0[8];
    ViewerCameraTarget *target;
    char pad12[64];
    float distance;
    char pad80[8];
    unsigned char primaryButton;
    unsigned char secondaryButton;
    unsigned char tertiaryButton;
    char pad91[17];
    unsigned char f108;
    char pad109[3];
    int f112;
    unsigned char f116;
    unsigned char f117;
    char pad118[2];
    float yaw;
    float roll;
    float pitch;
    float zoom;
    float pan[3];
} ViewerCameraState;

/* matching construct: compound-subtract variants */
void FUN_00466220(ViewerCameraState *state) {
    ViewerCameraTarget *target = state->target;
    float dx;
    float dy;
    float dz;

    state->f108 = 0;
    state->f112 = 0;
    state->f116 = !state->f117;
    state->yaw = 0.0f;
    state->roll = 0.0f;
    state->pitch = 0.0f;
    state->zoom = 1.0f;
    state->pan[0] = g_vec3Zero[0];
    state->pan[1] = g_vec3Zero[1];
    state->pan[2] = g_vec3Zero[2];
    dx = target->f160;
    dy = target->f164;
    dz = target->f168;
    dx -= target->f92;
    dy -= target->f96;
    dz -= target->f100;
    state->distance = sqrtf(dx * dx + dy * dy + dz * dz);
}
