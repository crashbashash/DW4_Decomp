typedef struct AdxtObj AdxtObj;
typedef void (*AdxtDecInfoFunc)(AdxtObj *adxt, int sfreq, int nch, int total_nsmpl);

extern AdxtDecInfoFunc adxt_decinfo_func;

AdxtDecInfoFunc ADXT_EntryDecInfoFunc(AdxtDecInfoFunc func)
{
    AdxtDecInfoFunc old;

    old = adxt_decinfo_func;
    adxt_decinfo_func = func;
    return old;
}
