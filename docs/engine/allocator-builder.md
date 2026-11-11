# Allocator builder and metadata-name selection

The complete 2,064-byte context slot 204 builder (`2f5cd0`), plus its active
object-system metadata-name lookup60 and default-system wrapper16: three bodies /
2,140 bytes. The builder is in
[igMemoryPoolContextInfo.cpp](../../src/engine/igMemoryPoolContextInfo.cpp); the two lookup helpers /76 bytes
include the default wrapper's16 bytes.

This is the allocator construction *dispatcher*. Concrete allocator classes,
their factories and virtual backend operations remain separate dependencies.

## Inputs, defaults and option flags

Arguments are output status cell, context, selector and mode. The routine captures
the default metadata handle586a88, context records0/1/3 and the requested record's
descriptor/current allocator. Missing primary/current values query globals587018/
587020 through selector dispatch, with current falling back to primary. Missing
record3 triggers the587030 lookup for its side effects; its result is discarded.

Selector2 publishes current into the requested cell and retains it before further
work, while the previously captured target remains the existing-target decision.
With no descriptor, selectors below30 return the word at4fb418; selectors30 and
above return4fb410. The builder itself adds no selector-bound guard.

A non-null descriptor+52 option string resets record flags+140. LongTerm suppresses
Level/Frame; otherwise Level sets bit0 and Frame sets bit1, with Level precedence.
Create, Reset and OnDemand set01000000,02000000 and04000000. With mode0, nonzero
low24 bits and Create/OnDemand defer construction and report the current success
word. These conditions are preserved, not reduced to a generic OnDemand boolean.

An existing captured target uses descriptor+28 length and+44 kind. Nonzero length
with null/Dynamic kind invokes output-first target172; other kinds skip resize.
The routine then queries target132 and invokes120 when necessary. Resize status
is ignored; output receives the current4fb410 word.

## Recursive aliases and proxy ownership

A nonempty descriptor+24 alias name is resolved through context116. A missing
target record recursively invokes current context204, then compares its output
with the **current**4fb410 success word. A failed comparison writes current4fb418
and stops. A successful call reloads the captured alias cell.

With a resolved alias, context bit2 decides ownership: clear borrows the allocator;
set creates a proxy through2cd170 and attaches the alias through proxy400.
OnDemand in any of its three observed spellings defers a mode0 proxy. The selector5
temporary context+740 publication/clear behavior remains literal. Context100
publishes/retains the result; only the owned proxy's temporary reference is released.
The result is enabled through132/120 and the output receives success.

## Metadata selection and backing policies

An absent target/alias optionally resolves descriptor+40 class name. Active
object-system lookup uses its metadata registry at+24 and the name-field descriptor
585c28 (offset28). Inactive systems return null. Failed named lookup re-reads the
default metadata handle. Without a class name, the entry-captured handle is used.
Instance creation runs through2fda40 with the captured primary allocator.

Descriptor+28 supplies backing length. Tracker587218 slot84 is queried twice:
the first value forms length+alignment-1; the second masks that wrapped32-bit
result. The implementation does not collapse the calls or assume identical values.

Nonzero length selects these policies:

| Kind / backing name | Original operation |
| --- | --- |
| Null or Dynamic kind | Output-first target172 with raw length |
| Fixed / SystemMemory, Low, High or Virtual | Tracker68 allocates rounded bytes; target96 receives backing/rounded/flag0; storage bit1 is set |
| Fixed / HighSpeed | Target96 receives descriptor+36 or70000000, raw signed length and flag0 |
| Fixed / Raw or Custom | No backing setup before descriptor application |
| Fixed / another nonempty name | Context96 selects the backing allocator, falling back to current |
| Fixed / empty name | Current backing allocator |

The ordinary backing allocator is enabled via132/120, allocates **raw**, not rounded,
length through216, and supplies target96 with signed length/flag1. Its reference
word increments and record storage bit0 is set. Other kinds skip backing setup.

The routine applies the descriptor through output-first target180, publishes through
context100, releases its temporary allocator reference, enables the captured target
and stores current success. Temporary virtual-method status words are ignored
except the recursive alias guard. Original failure/null behavior is not replaced
with new safety guards.

## Remaining work

`testing/test_lua_engine_dependencies.py` checks slot204 binding, creation/metadata/proxy
sites, output status publication and the authoritative metadata name-field descriptor.

The dispatcher and its dependencies are not the complete allocator backend.
Next: actual proxy/allocator factories and virtual resize/backing/apply/enable
implementations, context configuration/stack control and the remaining Lua
gameplay receivers.


## Alias pool backend trace

Static inspection of the retail instructions and vtable identifies a builder
dependency, `igAliasMemoryPool`: factory `0x2cd170` uses metadata handle
`0x5869b0`; its bootstrap path allocates 184 bytes and calls `0x2d1540`.
Constructor/initialization helpers publish vtable `0x5313a0` and clear the lock,
event tracker and aliased pool fields at offsets 116, 152 and 180.

Slot 400 binds `0x2d0560` (152 bytes). It retains the new alias before releasing
the previous alias, publishes offset 180, and queries the alias through slot 376
for the byte at offset 113. Even an identical alias still follows this sequence.
Slot 412 binds `0x2d1210` (740 bytes), the central allocation/reallocation/free
backend. It takes the lock, floors alignment by offset 176, checks the 64-bit
allocation limit, delegates through alias slots 220/236/264, updates allocation
and free counters/high-water marks, reassigns ownership and unlocks. A byte count
of -1 selects free. Lock, ownership and backing implementations remain dependencies.

The vtable also exposes starts `0x2d0ae0`, `0x2d0b00`, `0x2d0c00`, `0x2d0d80`,
`0x2d0da0` and `0x2d0e30`; the [alias-pool runtime](alias-pool-runtime.md) reviews
their function boundaries. The contiguous alias pool
factory/binding/backend module is in [alias-pool binding](alias-pool-binding.md)
and [alias-pool runtime](alias-pool-runtime.md).
