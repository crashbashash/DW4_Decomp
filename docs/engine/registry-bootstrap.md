# Registry bootstrap and allocator-context lookup

**17 complete bodies / 1,512 bytes** are recovered in
[registry-bootstrap.c](../../recovered/engine/registry-bootstrap.c): six contiguous
registry-list methods, global registry initialization/shutdown, current context and
five adjacent context dispatch wrappers, and two concrete record-lookup methods.
Fifteen bodies /1,448 bytes have exact source. New list init104/release116/append168
and concrete named lookup156 add **544 matched bytes**. Current-context getter84 matches in
[Memory_GetCurrentContext.c](../../src/unmatched/Memory_GetCurrentContext.c) and concrete selector244 in
[FUN_002f2730.cpp](../../src/unmatched/FUN_002f2730.cpp).
List allocate/delete32 each have no C source yet.

Six body-derived names are applied through `config/SLUS-20836/names/RegistryBootstrap.tsv`.
Concrete methods retain their generated, evidenced class/virtual-slot names;
unknown dispatch roles are not assigned speculative semantic names. Matching
[registry-list.cpp](../../src/engine/registry-list.cpp) and
[context-record-name.cpp](../../src/engine/context-record-name.cpp) use observed
ABI projections rather than claiming original C++ declarations. The subsequent [context lifecycle recovery](context-lifecycle.md) establishes
the128-byte name buffer and corrects the earlier constructor label.

## Registry-list lifetime and publication

The list header is12 bytes: data+0, signed count+4, capacity+8. Initialization
(`2fa4d0`) sets capacity64/count0, allocates capacity×4 through the current object
system's allocator at `*(586dc8)+48`, slot216, publishes data and clears the current
capacity×4 bytes. Capacity is reloaded after the callback.

Append (`2fa610`) compares count/capacity as signed32. When full, it increases
capacity by4, reallocates through the current system allocator's slot232, publishes
the new data and zeroes the four-cell tail using the **current** capacity. It reloads
count, stores incremented count first and then writes the new pointer at the old
index. It does not increment the appended object's reference count.

Release (`2fa540`) skips null list/data. A non-null data buffer is freed through
current system allocator slot264. A positive signed low16-bit delete flag then
frees the header through `2fa6e0`, which reloads the current system allocator. The
routine returns the original list pointer and does not clear its fields. The
allocate/delete wrappers (`2fa6c0`/`2fa6e0`) directly tail-dispatch slots216/264.
The existing forward `IndexOf` method remains the same original72-byte routine.

Global initialization (`2f2180`) allocates/initializes the primary list, publishes
`586f58`, appends the supplied root allocator and clears its byte7. It then
allocates/initializes the empty secondary list and publishes `586f60`. Original
allocation failures do not acquire new guards in the adapter: the comparison
fixture preserves the original calls/writes without asserting safe live-game OOM
behavior.

Shutdown (`2f2200`) releases the current primary then current secondary list with
delete flag1, clears both globals and invokes root allocator slot392. Publication
is reloaded before releasing the second list, so a callback can change it. The
slot392 implementation remains external; the oracle checks that both globals are
already zero when it is called.

## Current context and wrappers

`Memory_GetCurrentContext` (`2f8680`) reads signed mode at `587010`. Modes1..3 select
`*(586ffc + mode×4)`; mode0 returns the non-null pointer at `586fd0`. Negative or
≥4 modes return null, and a null selected slot remains null. `2f88d0` is its tail
alias. The wrappers capture their input, get that context and invoke:

| Entry | Context slot | Observed role |
| --- | --- | --- |
| `2f88e0` | 92 | Allocator selector lookup, including default selector2 |
| `2f8920` | 96 | Allocator lookup by pool-name string |
| `2f8960` | 104 | One-argument dispatch; wider role unresolved |
| `2f89a0` | 108 | One-argument dispatch; wider role unresolved |
| `2f89e0` | 116 | One-argument dispatch; wider role unresolved |

The wrappers do not introduce a null-context guard. Context-stack manipulation
and the provider's record initialization remain separate dependencies.

## Concrete selector and name receivers

Constructor `2f25d0` and destructor `2f2670` store vtable `52f510`; its slots92/96 point at `2f2730` and
`2f2830`. The selector method accepts signed indices0..45. Each144-byte record has
an allocator pointer at context+20+index×144, inline name at+24, and the queried
flags word at+160. A present pointer returns immediately.

If an absent pointer's flags include `04000000`, selector lookup invokes context
slot208 with an output temporary first, context and selector (also preserving
the observed context value in register a3), then reloads the
captured pointer cell. It does not use the returned status word. Slot208's body
remains a callback. Otherwise, at depth≥2 it searches the active context array at
`587000` backward for this context and asks its immediately preceding context's
slot92. No found predecessor or a repeated identical predecessor returns null.
It preserves the original search and adds no inferred upper-depth bound.

Named lookup rejects null/empty names, compares all46 inline names in order and,
on the first match, invokes the context's **current** slot92. It reloads that
vtable after string comparison callbacks. Thus it does not implement an independent
name-based allocation path or search every parent context's names.

## Verification and remaining work

`python3 testing/test_registry_bootstrap_retail.py` compares **191** original-instruction
RAM, defined-return and ordered-call cases across all17 bodies. Tests cover64-slot
initialization, four-slot growth, signed16 deletion flags, failure call behavior,
callback-time capacity/count/allocator/publication changes, real global lifetime,
context modes/slots, selector bounds/presence/special requests, recursive parent
lookup and repeated-parent prevention, and null/empty/first/last/mutating names.

`python3 testing/test_memory_field_values_retail.py --registry-bootstrap` passes
**116** checkpoints through actual registry creation, real metadata registration,
populated Work/list lifetime, runtime header copying and registry shutdown. Default
and named lookup use the original46-record algorithms. Context record contents and
allocator virtual behavior are still fixture inputs. This mode replaces the old
pointer-shaped value at `587040` with valid fixture selector2; it does **not** claim
that2 is the game's published metadata selector. Prior modes keep their113/114
checkpoint counts.

Twenty dependency tests independently check startup/teardown call sites, global
publication, list dispatch slots, context constructor/vtable receiver bindings and
prior engine contracts. Four reviewed producer/receiver roots add these required
paths without inventing virtual edges. Retail objdump also confirms their shapes.
Root matching, relink and typed checks remain independent of these behavioral
oracles. Native gameplay is unchanged.

The subsequent context lifecycle recovery covers original record-name initialization,
retained slot updates, and special208/212 delegation/removal. The slot204 builder,
context-stack manipulation, allocator virtual internals/close hook, type/scalar
publication, actual cloning and broader gameplay remain open.
