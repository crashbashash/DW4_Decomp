/* Stream volume: beCriAudio adds pack base + sound volume, then CRI clamps
 * to [-999,0] and indexes the Q8 table at 0x004b0e20. Resident SFP follows
 * the separate SFX path and must not use this attenuation. */
#ifndef DW4_AUDIO_LEVEL_H
#define DW4_AUDIO_LEVEL_H
#include <math.h>
static inline unsigned dw4_audio_stream_level(int volume)
{
    if (volume > 0) volume = 0;
    if (volume < -999) volume = -999;
    return (unsigned)(256.0 * pow(10.0, volume / 200.0));
}
static inline float dw4_audio_stream_gain(int volume)
{
    return dw4_audio_stream_level(volume) / 256.0f;
}
#endif
