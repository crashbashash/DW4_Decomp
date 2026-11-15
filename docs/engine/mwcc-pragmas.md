# MWCC pragmas

What `#pragma` lines our MWCC accepts, what each one changes in the code, and whether the project lets it into
`src/`. The two MWCC builds in `config/SLUS-20836/units.tsv` are `b52` (`3.0b52-030722`, 170 units) and
`combat` (21 units); both binaries carry the same pragma table (the names after `Win32_Plugins_MIPS_PS2` in
the executable's strings, and the second table ending in `exception_magic`).

**Verified** below means a 5–20 line probe compiled with b52 under the core profile (`-O4,s -sdatathreshold 2
-RTTI off -inline level=8,bottomup`) and, where marked `,p`, under `-O4,p -sdatathreshold 2 -inline
level=8,bottomup`, with the listing compared with and without the pragma. "No change" only means the probes
did not trigger it: the pragma is accepted, and a larger function may still react to it. On `combat`, spot
checks of `peephole` and `schedule` also changed the code.

## How the compiler reads a pragma

All verified on b52.

- **An unknown name is silently ignored.** `#pragma scheduling off` and `#pragma opt_peephole off` are not
  pragmas and compile to the same bytes as nothing. `#pragma warn_illpragma on` at the top of a probe, or
  `-w all`, reports each one as `illegal #pragma`; use it before concluding that a pragma "has no effect". A
  value out of range is an error (`optimization_level 9`).
- **The setting in force at the function's closing brace applies to the whole function.** A pragma written
  inside the body, even before the last statement, acts on all of it; switching it back on before the closing
  brace undoes it entirely (measured for `peephole`, `opt_propagation`, `optimization_level`,
  `readonly_strings` and `dont_inline`). There is no way to change only part of a function.
- **Type layout is the exception.** `reverse_bitfields` acts on the `struct` definitions written while it is
  on, not on the functions that use them.
- **An inline function carries no pragma.** A helper defined under `peephole off` and expanded into a caller
  compiled with it on gets the caller's setting, and the reverse.
- **`reset` undoes the last `on`/`off` of that pragma.** Each pragma keeps its own history: `off; off; reset`
  is still off, `off; on; reset` is off, `off; on; reset; reset` is the default again.
- **`push`/`pop` save and restore every pragma setting at once**, including `optimization_level`,
  `optimize_for_size` and the `opt_*` switches. A `pop` without a `push` is an error ("preceding '#pragma
  push' is missing"); a `push` never popped is accepted silently, so the setting leaks into the rest of the
  file.
- **`optimization_level N` resets the `opt_*` switches set before it**: `opt_propagation off` followed by
  `optimization_level 4` compiles as if neither were written, while the reverse order keeps the switch. It
  does not reset `optimize_for_size`.
- **An `asm` function does not change the functions after it.** A whole `asm` definition, or an `asm { }`
  statement, leaves the peephole pass of the following C functions on.

## Scoping a pragma to one function

```c
#pragma push
#pragma peephole off
void f(void)
{
    ...
}
#pragma pop
```

`push` before the function, the setting, `pop` after the closing brace. Do not write the pragma as an `on`/`off`
pair around the function: the second line is a setting, not a closing bracket, so it forces the default on
every later function even when the file meant something else, and a forgotten one leaks the setting to the
end of the file. A pragma inside the body is no narrower than one in front of the function (see above). If
the function's code comes from an inline helper, the pragma goes around the caller.

## The pragmas

Policy column: **free** (no rule restricts it), **scoped** (allowed with `push`/`pop` as documented),
**owner, counted** (a rise of `opt_pragma.statements` needs the owner), **diagnostic** (scratch copies only, never
in `src/`), **runtime** (the Metrowerks runtime files only).

### Optimiser

| Pragma | Effect on b52 | Policy |
|---|---|---|
| `optimization_level 0`…`4` | Verified. 0, 1 and 2 give longer code (81, 67, 57 instructions where the unit gives 52); 3 and 4 gave the unit's code in every probe. Resets the `opt_*` switches set before it. `0` keeps the optimiser out of an `asm` function ([asm bodies](asm-body-matches.md), measured there; a small probe here showed no difference either way) | owner, counted; asm bodies are not kept at all |
| `optimize_for_size on`/`off` | Verified. The source form of the `,s`/`,p` sub-flag. In a `-O4,p` unit `on` gave exactly the `-O4,s` code in every probe. In a `-O4,s` unit (or plain `-O3`) `off` gives the optimiser side of `,p`: a float literal such as `1e9f` loaded as its bits (`lui; ori; mtc1`) instead of an integer and `cvt.s.w` (the difference [action2-jointset](action2-jointset.md) found no pragma for; it tried other names), loops unrolled and strength-reduced. It does not give the scheduler side: one probe gets an extra `nop` before the epilogue under `-O4,p` that no pragma reproduces | owner, counted; it moves one function to another profile ([build profiles](build-profiles.md)) |
| `opt_strength_reduction off` | Verified. Changes code only when optimising for speed (`,p`: +20 instructions in the probe). Under `,s` the probe loops were not strength-reduced with or without it | owner, counted |
| `opt_loop_invariants off` | Verified: same length; the table address and an invariant product are computed inside the loop instead of before it | owner, counted |
| `opt_propagation off` | Verified: +3 (`,s`) / +7 (`,p`) instructions; a copy keeps its own saved register and the frame grows | owner, counted |
| `opt_common_subs off` | Verified: +6 / +4, repeated expressions computed again | owner, counted |
| `opt_dead_assignments off` | Verified: +1 / +2, the comparison of a dead `if` block is kept | owner, counted |
| `opt_unroll_loops off` | Verified under `,p`: the unrolled probe shrinks from 113 to 49 instructions; no change under `,s`, which does not unroll | owner, counted |
| `opt_dead_code`, `opt_lifetimes`, `global_optimizer`, `opt_vectorize_loops`, `opt_foldconstants`, `opt_pointer_analysis`, `opt_classresults`, `opt_scalarize`, `opt_rotateloops`, `opt_reverseloops`, `opt_strength_reduction_strict` | Verified: no change in any probe at `-O4` (`global_optimizer` also at `-O2` and `-O3`) | owner, counted |
| `opt_dumptypes`, `opt_alwaysdumpopts` | Verified: no change in the object. `opt_dumptypes on` adds types to the IR dump of `tools/mwcc_irdump/` ([understanding shapes](understanding-shapes.md#mwccs-optimizer-ir-dump)) | diagnostic |
| `peephole off` | Verified: the per-block PCode peephole is skipped, so `lbu` keeps a redundant `andi 0xff`; in the semaphore functions the pair of `xori 1` of a conversion to `bool` survives ([understanding shapes](understanding-shapes.md#types-and-values)). It is not the `,p` sub-flag (that is `optimize_for_size`) | owner, counted; approved for `igPsx2Semaphore_Signal` and `igPsx2Semaphore_Wait` only (owner, 2026-11-14) |
| `auto_inline on` | Verified: a plain `static` function is expanded at its calls (the `-inline level=8,bottomup` profiles expand only functions declared `inline`) | owner, counted |
| `dont_inline on` | Verified: no call written in the function where it is in force is expanded; it does not stop the function itself being expanded elsewhere. Read at the closing brace like the others | owner, counted |
| `inline_depth(0)` | Verified: no expansion at all; `inline_depth(1)` gave the unit's code | owner, counted |
| `always_inline on` | Verified: no change; b52 does not expand an `asm` function with it either ([source approvals](source-approvals.md)) | owner, counted |

### Code generation

| Pragma | Effect on b52 | Policy |
|---|---|---|
| `schedule off` | Verified: no scheduler pass. Instructions stay in the order the code generator wrote them and no delay slot is filled (`jr ra; nop`). The tool for reading that order ([MWCC with its scheduler off](understanding-shapes.md#mwcc-with-its-scheduler-off)) | diagnostic |
| `conditional_move off` | Verified: `movz`/`movn` selects become a branch and moves | owner, counted |
| `tailcall off` | Verified: a tail call `j f` becomes a frame, `jal f` and a return | owner, counted |
| `far_call on` | Verified: each call loads its target from a `gp`-relative `@dp` word and goes through `jalr` | owner, counted |
| `interrupt on` | Verified: the function saves every register it touches and ends with `eret` | owner, counted |
| `padloop on` | Verified: no change on b52 (see mvc2 below) | owner, counted |
| `usefloatacc`, `fast_fptosi`, `fastmath`, `prefetch`, `inline_intrinsics` | Verified: no change in the probes. `strcpy`/`memcpy` stay calls under `inline_intrinsics on` ([understanding shapes](understanding-shapes.md#types-and-values)) | owner, counted |

### Data and language

| Pragma | Effect on b52 | Policy |
|---|---|---|
| `readonly_strings on` | Verified: string literals go to `.rodata` instead of `.data`, the same as `-str readonly`; the setting at the closing brace places every literal of the function. The source form of the flag for functions of a unit whose row does not carry it ([understanding shapes](understanding-shapes.md#types-and-values)); used in three core files. It does not reach the literals MWCC emits at the end of the file (RTTI names, `__sinit` strings, a last function that instantiates a template): those take the setting at the end of the file, so a closing `pop` leaves them in `.data`; the unit's `-str readonly` row flag places them | scoped |
| `pool_strings on` | Verified: the file's literals become one `.rodata` object | owner, counted |
| `dont_reuse_strings on` | Verified: an equal literal in a second function gets its own copy | owner, counted |
| `explicit_zero_data on` | Verified: zero-initialised globals go to `.data` instead of `.bss`. No match has needed it: the zeros retail keeps in `.data`/`.sdata` are constants passed to `const T &` parameters, which b52 stores as unnamed `.data` temporaries | owner, counted |
| `const_strings on` | Verified: no change in section | owner, counted |
| `reverse_bitfields on` | Verified: bit-fields are allocated from the other end of their unit (a 3-bit first field at bits 29–31, byte 3, instead of bits 0–2, byte 0). Acts on the `struct` definitions written under it | owner, counted |
| `unsigned_char on` | Verified: plain `char` loads with `lbu` | owner, counted |
| `enumsalwaysint off` | Verified: an enum takes the smallest type that holds its values (a 1-byte `.sbss` object instead of 4-byte `.bss`) | owner, counted |
| `cats off` | Verified: the object loses its `.mwcats` section, no code change | owner, counted |
| `cplusplus on` … `cplusplus reset` | Compiles a region of a `.c` file as C++ (classes, `extern "C"`); used in `src/engine/p2texture.c` | free |
| `exception_terminate`, `exception_magic` | Markers of Metrowerks' own exception handler; in `src/runtime/ExceptionHandler.cpp` | runtime |
| `push`, `pop` | See above | free |

Accepted names not listed here are front-end and warning switches (`warn_*`, `ANSI_strict`, `RTTI`,
`bool`, `wchar_type`, …) and the remaining `opt_*` switches of the IR optimiser
(`opt_prelinearize` … `opt_scalarizeliveranges`), none of which a match has needed.

## The rules for gated pragmas

- An optimiser pragma in `src/` is counted by `opt_pragma.statements` in the [debt ratchet](debt-ratchet.md); a
  rise needs the owner (owner rule 2026-11-08). The counter (`OPT_PRAGMAS` in `tools/progress.py`) is the exact
  list of names b52 accepts that change code or data: every `opt_*`, `optimization_level`, `optimize_for_size`,
  `global_optimizer`, `peephole`, the inlining pragmas, the MIPS back-end switches (`schedule`,
  `conditional_move`, `tailcall`, …) and the data pragmas. `push`, `pop`, `cplusplus`, the exception markers and
  names b52 ignores are not counted, nor a `readonly_strings` inside a closed `push`/`pop` (the scoped form).
- A function is matched only under its unit's profile ([matched and readable](../../CLAUDE.md#matched-and-readable),
  [build profiles](build-profiles.md)). `optimize_for_size` or `optimization_level` around a function changes
  that function's profile from inside the file, so it is the same question as a per-function override.
- A pragma found by a sweep is a matching construct and carries the comment item 4 of
  [matched and readable](../../CLAUDE.md#matched-and-readable) asks for.
- `asm` and `volatile` are owner approvals of their own ([source approvals](source-approvals.md)); the
  semaphores' `peephole off` was approved together with their rows there.
- `schedule off` and `opt_dumptypes` are instruments for scratch copies
  ([understanding shapes](understanding-shapes.md)); asm bodies under `optimization_level 0` are not kept in
  the repository ([asm bodies](asm-body-matches.md)).

## Ideas from other projects

Other MWCC projects use different builds, so their code-generation findings are leads to test on b52, not facts
about it. What was tested here is marked.

- **Yu-Gi-Oh! Duelists of the Roses (MWCC PS2 2.3.3,
  [MATCHING-TIPS.md](https://github.com/kira-502/dotr-decomp/blob/main/docs/MATCHING-TIPS.md))** treats
  per-function `optimization_level 1|2|3`, `opt_propagation`, `conditional_move`, `opt_strength_reduction`,
  `global_optimizer`, `peephole` and `schedule` as honest C, written before the function with `#pragma <name>
  reset` after it, and reports that a dropped `reset` changed every later function of the module. It ties
  extra `nop`s at the ends of if-blocks to `conditional_move off` (verified here: the pragma turns `movz` into
  a branch) and a constant argument loaded in the wrong order to `opt_propagation off` (not verified). We gate
  all of these; `push`/`pop` avoids the leak.
- **Persona 4 (MWCC PS2 3.0.1 b210,
  [STYLE.md](https://github.com/Raikaru/Persona4-Decompilation/blob/main/docs/STYLE.md))** allows a scoped
  optimiser pragma only when the typed body matches with it and not without, with a `measured:` comment;
  scopes single functions with `push`/`pop`; and reports that `optimization_level` resets the optimiser
  switches (verified on b52, above). Its `tools/pragma_audit.py` checks pragma spellings; our counter once
  listed the non-pragma `scheduling`, which such a check catches.
- **Marvel vs. Capcom 2 (MWCC PS2 3.0.3 and 3.0-011126,
  [COMPILER.md](https://github.com/devin-thomas/mvc2-ps2/blob/main/docs/COMPILER.md))** reports that `#pragma
  padloop on` pads loop back-edges under 3.0-011126 but not under 3.0.3 (no change on b52, verified), and that
  `-Op` supplies a loop-exit `nop` plain `-O3` lacks, which matches the scheduler side of `,p` that
  `optimize_for_size off` does not reproduce here.
- **Super Mario 64 DS (mwccarm,
  [mwccarm-codegen.md](https://github.com/tangosdev/sm64ds-decomp/blob/main/notes/mwccarm-codegen.md))**: unknown
  pragmas are silently ignored (verified on b52, where `warn_illpragma` does report them); optimiser pragmas
  apply per function, so an inlined helper cannot carry its own (verified); a pragma kept as a crutch can
  rotate a whole function's register colouring, so a matched twin compiled without the pragma is the cheapest
  test of whether it is needed (not verified, a method worth keeping).
- **Super Mario Sunshine (MWCC GC/1.2.5,
  [AGENT_MATCHING_TIPS.md](https://github.com/doldecomp/sms/blob/main/docs/AGENT_MATCHING_TIPS.md))** shares the
  front end and IR optimiser with b52, not the back end. Transfers: `dont_inline` is read once, at the end of the
  function, and acts on the calls inside it (both verified on b52); it hides a real cause such as a callee over
  the inliner's statement limit, so treat it as a lead, not a fix. Does not transfer: that `dont_inline` also
  makes the function it wraps non-inlinable (on b52 such a function is still expanded at a later call,
  verified), that "an `asm` function turns off the peephole for every later function" (false on b52,
  verified), and every PowerPC instruction-level fact.
- **decomp-triage ([README](https://github.com/KakarottoCake/decomp-triage))**: its variant generator
  deliberately never emits `volatile` locals or peephole, scheduling or `fp_contract` toggles, because "those
  close byte gaps by producing source nobody would write", the same reason we gate them.
- **Xbox 360 MSVC
  ([PRAGMA_MATCHING_CHECKLIST.md](https://github.com/freeqaz/dc3-decomp/blob/main/docs/decomp/PRAGMA_MATCHING_CHECKLIST.md))**:
  only the method transfers: a layout pragma (there `bitfield_order`, here `reverse_bitfields`) must precede the
  type definition, which is where b52 reads it (verified); a wrong bit-field layout shows as wrong masks and
  shifts with right offsets.
- [mwccps2-debugger](https://github.com/Raikaru/mwccps2-debugger) captures PCode after each back-end pass
  (`after_peephole`, scheduling, colouring) for b210 and 2.4, not b52; it lists no pragmas. Our counterpart
  for b52 is `tools/mwcc_irdump/`. [decomp.wiki's MWCC page](https://decomp.wiki/compilers/MWCC) has no
  pragma material.
