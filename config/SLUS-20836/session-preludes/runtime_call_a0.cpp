/* Session prelude: compiled before the units that name it, in the same mwccps2 process
 * (docs/build-system.md#session-preludes); its object is discarded.
 *
 * MWCC 3.0b52 collects the registers a runtime call's arguments use in one global mask (0x567280 in
 * mwccps2.exe) and never clears it, not even between the files of one compile session. Once a runtime call
 * with an integer argument in a0 has been compiled, every later runtime call (such as __fixsfdi) also uses
 * a0, which keeps a0 live up to that call. Retail shows that state in units that make no such call
 * themselves: the original build compiled them after one that did. This conversion is a __floatdisf call
 * with its argument in a0, and it puts a0 alone in the mask. */
extern "C" float LeakA0(long long x) { return (float)x; }
