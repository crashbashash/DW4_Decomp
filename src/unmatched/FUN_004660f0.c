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

static inline void setVec3(float *v, float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

static inline void scaleVec3(float *v, float s) {
    v[0] = v[0] * s;
    v[1] = v[1] * s;
    v[2] = v[2] * s;
}

void FUN_004660f0(ViewerCameraState *state, const float *delta) {
    ViewerCameraTarget *target = state->target;

    if (state->primaryButton) {
        if (state->secondaryButton) {
            float d = delta[0]; state->zoom *= 1.0f - d / 2.0f;
        } else {
            const float pi = 3.1415927f;
            state->yaw += pi * delta[0];
            state->pitch += pi * delta[1];
        }
    } else if (state->secondaryButton) {
        setVec3(state->pan, delta[0], delta[1] / target->aspect, 0.0f);
        scaleVec3(state->pan, state->distance / 2.0f);
    }
}
