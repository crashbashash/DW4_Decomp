# Metrowerks runtime: start-up, double support, new/delete and C++ exceptions

The front of the image, `0x100008` up to `0x1029f8`, is the CodeWarrior for PlayStation 2 runtime the game links
before Sony's libraries: the start-up file, the conversions and comparisons MWCC calls for `double`, array
construction and `new`/`delete`, the terminate and unexpected handlers, the static-object chain and the C++
exception handler. It compiles as eight whole files under `b52`, `-O4,p -sdatathreshold 0`, one `units.tsv` row each
([whole-file units](emitted-functions.md#whole-file-units)): the runtime is its own library build, with no small
data. `operator new` reads the one-byte `__throws_bad_alloc` through an absolute address, and the variable sits in
`.data` beside `__new_handler`, out of `gp`'s reach; MWCC does both only at threshold 0, and no other runtime
function separates the thresholds.
The exception types are in `include/dw4/runtime/exception.h`, the C++ library classes and allocation hooks in
`include/dw4/runtime/cxxlib.h`.

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/runtime/crt0.S` | `runtime_crt0` | `0x100008` up to `0x100240` | `_start` (clears the registers and `.bss`, sets up the main thread, heap and system, runs `__init_cpp`, `main`, `__fini_cpp`, then `exit`), `_exit` (`Exit`) and `_root` (the main thread's `ExitThread` call) | the image's entry point; the approved assembly source ([assembly-sources.md](assembly-sources.md#the-start-up-file)); `_root` follows `_exit` as in Sony's `crt0.s` |
| `src/runtime/runtime.c` | `runtime_runtime` | `0x100240` up to `0x100390` | `_d_ulltod`, `_d_utod` and `_dpfeq` … `_dpfge`: the helpers MWCC calls for unsigned-to-`double` conversion and `double` comparison, forwarding to `__floatdidf`, `dpadd` and `dpcmp` | the names are the ones game objects call (`externals` rows of the Lua and libpng units); none has an exception record, as a C file compiled with exceptions off |
| `src/runtime/New.cpp` | `runtime_New` | `0x100390` up to `0x1007e0` | `__destroy_arr`, `__construct_array` and its `__partial_array_destructor`, `operator delete[]`, `operator delete`, `std::exception`'s destructor and `what`, `operator new[]`, `std::__default_new_handler` and `std::bad_alloc`'s destructor and `what` | `bad_alloc::what` ends the run as MWCC's trailing inline virtuals do; `.rodata` in code order from `0x4d1c00` (`std::exception`'s RTTI, `"exception"`, `operator new[]`'s `throw(std::bad_alloc)` string `0x4d1c30`, the handler's throw type `0x4d1c50`, `std::bad_alloc`'s RTTI, `"bad_alloc"`); `__new_handler` (`0x481c00`) holds the default handler |
| `src/runtime/NMWException.cpp` | `runtime_NMWException` | `0x1007e0` up to `0x100cb0` | `operator new`, `__throw_catch_compare`, `__call_unexpected_handler`, `__terminate`, the default unexpected and terminate handlers, `__destroy_global_chain`, `__register_global_object`, `__call_static_initializers` | `operator new` throws `bad_alloc` with its own copy of the throw type string (`0x4d1cb0`): it is not in the handler's file; `thandler` and `uhandler` (`0x481c10`, `0x481c18`) follow `__new_handler` and `__throws_bad_alloc` in `.data`; the next file is `__ptmf.c` |
| `src/runtime/__ptmf.c` | `runtime___ptmf` | `0x100cb0` up to `0x100cf0` | `__ptmf_scall`, the pointer-to-member call (an approved `asm` function) | Metrowerks' `__ptmf.c` |
| `src/runtime/ExceptionHandler.cpp` | `runtime_ExceptionHandler` | `0x100cf0` up to `0x1024e0` | the action-list decoding (`__DecodeUnsignedNumber`, `__DecodeSignedNumber`, `NextAction`), `__end__catch`, `__ThrowHandler`, `FindExceptionHandler`, `__unexpected` (which throws `std::bad_exception`), `FindMostRecentException`, `UnwindStack`, `__FindExceptionTable` | its jump tables and `bad_exception` strings run in code order from `0x4d1ce0`; `bad_exception::what` (`0x1024d0`) is the unit's trailing inline virtual; `__TransferControl` starts the target-specific file |
| `src/runtime/ExceptionHandlerTS.cpp` | `runtime_ExceptionHandlerTS` | `0x1024e0` up to `0x1029c0` | `__TransferControl` (an approved `asm` function), `__throw`, `__SkipFrameInfo`, `__GetExceptionIndexBounds`, `__SetupFrameInfo`, `__PopStackFrame`: the R5900 frame layout and the image's one exception index | the frame-format functions the generic file calls; the original is `ExceptionHandlerTS.cp` ([source approvals](source-approvals.md#metrowerks-runtime-asm-functions)); C++ with exceptions on, as `__SkipFrameInfo` and `__SetupFrameInfo` carry index records |
| `src/runtime/__init_cpp.c` | `runtime___init_cpp` | `0x1029c0` up to `0x1029f8` | `__fini_cpp` (`__destroy_global_chain`) and `__init_cpp` (the static initializers `0x522440` up to `0x522480`, with the exception index bounds) | called through the thunks at `0x2d1640`/`0x2d1650` from `entry`, around `main`; Sony's libgraph starts at `0x1029f8` |

`__call_static_initializers` calls each entry of the table from `__ctors_start__` (`0x522440`) up to `__ctors_end__`
(`0x522480`) in turn. An entry is the `.ctor` word of a file that constructs global objects, pointing at that file's
`__sinit_<file>`, which the linker put with every other file's after all `.text` (`0x51fd00` up to `0x522438`); both runs
are in link order, and each initialiser and its entry compile from the file that owns them
([static initialisers](emitted-functions.md#static-initialisers)).

## The exception handler

`__throw` saves the thrower's callee-saved registers into a `ThrowContext` and calls `__ThrowHandler`. Each
function with cleanups or catch blocks has an index entry (`ExceptionTableIndex`, the index runs from
`__exception_table_start__` `0x546fb0` to `__exception_table_end__` `0x554858`) pointing at its exception record:
a frame description (a flag byte with the count of saved `s` registers, the flush-back, frame-pointer and saved-
float bits, then the frame and argument sizes and the float count, packed as `__DecodeUnsignedNumber` reads them)
followed by code ranges, each with an action list. `__FindExceptionTable` finds the record and the range around a
return address; `__SetupFrameInfo` reads the frame; `FindExceptionHandler` walks the actions (`NextAction`
steps past each one and pops to the caller's frame at a list's end) until a catch block's type matches
(`__throw_catch_compare` on the mangled type strings, `!class!base!offset!…` for a class with bases) or an
exception specification is violated. `UnwindStack` then runs the destructors of everything between, and
`__TransferControl` restores the catching frame's registers and jumps into the handler. A rethrow
(`throwtype` null) takes the exception of the innermost active catch block (`FindMostRecentException`). A
violated specification lands in `__unexpected`, which calls the unexpected handler and turns what it throws into
a rethrow, a `std::bad_exception` or termination.

An action is a type byte (`EXACTION_*` in its low five bits, `EXACTION_ENDBIT` on the last action of a list, and
`EXACTION_REGCOND`/`EXACTION_REGPTR` when its condition or object pointer is in a saved register, numbered, rather
than at a frame offset) followed by its packed numbers and unaligned addresses. As in Metrowerks'
`ExceptionHandler.cp`, each action type has one inline handler that decodes its record and, when applied, runs its
cleanup: `NextAction` skips through them and `UnwindStack` applies them, stopping at the catch block or
specification it was given.

`operator new` loops on `malloc`; with no memory it calls `__new_handler` (the default throws `std::bad_alloc`),
or, with the handler cleared, throws `bad_alloc` when `__throws_bad_alloc` is set and returns null otherwise.

## Open questions

- No source yet: `__throw` is an MWCC `asm` function, as in Metrowerks' own runtime.
- `std::exception`'s destructor and `what` sit after `operator delete` rather than at the end of the unit, where
  MWCC puts a class's inline virtual functions; a function dead-stripped from the file may have used the class
  there. One file reproduces every function, so no boundary is drawn inside `0x100390` up to `0x1007e0`.
- The static-initializer table ends where `std::exception`'s vtable begins (`0x522480`).
- File names other than `__ptmf.c` and `ExceptionHandlerTS` are from the content, after Metrowerks' runtime
  conventions.
