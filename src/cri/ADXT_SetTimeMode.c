enum AdxtTmode {
    ADXT_TMODE_STD = 0,     /* time from decoded samples */
    ADXT_TMODE_NTSC = 1,
    ADXT_TMODE_PAL = 2
};

extern int adxt_time_mode;
extern int adxt_time_unit;  /* V-syncs per 100 seconds */

void ADXT_SetTimeMode(int mode)
{
    if (mode == ADXT_TMODE_NTSC) {
        adxt_time_unit = 5994;
    } else if (mode == ADXT_TMODE_PAL) {
        adxt_time_unit = 5000;
    }
    adxt_time_mode = mode;
}
