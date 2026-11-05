/* Exercise the callback offline with known sample values: no device scheduling
 * or second mixer implementation can hide a loop-boundary or clipping error. */
#include "../src/audio.c"
#include <assert.h>
int main(void)
{
#ifdef DW4_ENABLE_SDL2
    dw4_audio a = {0};
    int16_t pcm[] = {100,-100,200,-200,300,-300,400,-400,500,-500,600,-600};
    int16_t out[24];
    dw4_audio_clip clip = {pcm,6,2,5};
    const int expected[] = {100,200,300,400,500,300,400,500,300,400,500,300};
    a.voice[0].clip = &clip; a.voice[0].gain = 1;
    mix(&a, (Uint8 *)out, sizeof(out));
    for (unsigned i = 0; i < 12; i++) {
        assert(out[i * 2] == expected[i]); assert(out[i * 2 + 1] == -expected[i]);
    }
    assert(a.frames == 12);
    /* STATUS ducks selected sound gains without stopping their cursors or
     * changing music gain; a later menu voice starts at its own requested gain. */
    a.voice[0].gain=0;size_t duck_position=a.voice[0].pos;
    mix(&a,(Uint8 *)out,4);assert(!out[0] && !out[1] && a.voice[0].pos==duck_position+1);
    a.voice[0].gain=1;
    a.muted = 1;
    size_t before = a.voice[0].pos;
    mix(&a, (Uint8 *)out, 4);
    assert(out[0] == 0 && out[1] == 0);
    assert(a.frames == 14 && a.voice[0].pos == before + 1);
    a.muted = 0;
    mix(&a, (Uint8 *)out, 4);
    assert(out[0] == 300 && out[1] == -300 && a.frames == 15);
    memset(&a, 0, sizeof(a));
    clip.loop_end = 0;
    a.voice[0].clip = &clip; a.voice[0].gain = 100;
    a.voice[1].clip = &clip; a.voice[1].gain = 100;
    mix(&a, (Uint8 *)out, sizeof(out));
    assert(out[0] == 20000 && out[1] == -20000);
    assert(out[2] == 32767 && out[3] == -32768);
    for (unsigned i = 12; i < 24; i++) assert(out[i] == 0);
    assert(!a.voice[0].clip && !a.voice[1].clip);
    puts("audio mixer: authored loop, mute clock/voice advancement, overlapping voices, clipping and EOF silence ok");
#else
    puts("audio mixer: SDL2 not built; skipped");
#endif
    return 0;
}
