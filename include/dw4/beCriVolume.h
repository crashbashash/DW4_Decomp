#ifndef DW4_BECRIVOLUME_H
#define DW4_BECRIVOLUME_H

struct beCriVolume;

#ifdef __cplusplus
extern "C" {
#endif

int beCriVolume_StartFade(struct beCriVolume *self, int baseVolume, float from, float to, float frames);
int beCriVolume_StepAdxLevel(struct beCriVolume *self, int baseVolume);
int beCriVolume_StepSndfLevel(struct beCriVolume *self, int baseVolume);

#ifdef __cplusplus
}
#endif

#endif
