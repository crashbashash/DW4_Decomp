# Messenger delayed delivery and argument contexts

Ten complete lifecycle bodies (4,476 code bytes) have readable
[behavioral C](../../recovered/engine/messenger-lifecycle.c), backed by original
instructions and reflection. They cover argument clearing, delay-record reuse,
initialization checking, expiry updates, enqueue and context push/pop. The six
bodies at `38e8f0..38f0e0` form a contiguous enqueue/nesting block; the adjacent
clear functions are `38ca40..38cff0`. Initialization/update retain their existing
vtable-slot names. Finding [#870](../findings/findings-0751-1000.md#f870) records the recovery and its boundaries.

Three forwarding bodies (192 bytes) have exact source in
[beMessengerLifecycle.cpp](../../src/game/beMessengerLifecycle.cpp). Group-delayed
send at `38ecf0` adds **84 matched bytes**; named-delayed send and group preparation
were existing matches and now have explicit, corrected signatures. Seven bodies
retain retail assembly. No native gameplay implementation changes are implied.

## Entry points and storage

| Address | Recovered operation |
| --- | --- |
| `38ca40` | Clear a complete `beMessengerArgData` object |
| `38ce70` | Reset a delay record and clear its owned argument context |
| `38d050` | `beMessenger::vfunc_25`: initialize memory if needed; return zero |
| `38d0a0` | `beMessenger::vfunc_27`: deliver expired records, or shift deadlines while frozen |
| `38e8f0` | Enqueue the prepared last delay record and capture current arguments |
| `38eca0` | Prepare group/name/number and enqueue message/delay (six arguments) |
| `38ecf0` | Prepare group with null name and number -1, then enqueue message/delay |
| `38ed50` | Prepare group with null name and number -1 |
| `38ed70` | Push the current argument context and use a spare context |
| `38ef50` | Clear the current context, restore the saved one and recycle the spare |

Reflection identifies messenger argument reference +16, delay stack +28,
context stack +32, context nesting count +36, freeze clock +40 and initialized
byte +48. Its owner/system reference +12 supplies the 64-bit clock at +80.
Delay records hold use byte +8, 64-bit deadline +16, group/name +24/+28,
number +32, message +36 and argument reference +40. See
[receiver dispatch](messenger-dispatch.md) and [typed channels](messenger-results.md).

## Argument clearing and lifetime

Argument clearing resets the run-check byte, interns a null replacement for its
name (+12), releases the previous token, then publishes the replacement. It clears
six scalar/aggregate channel counts in order: byte, int, float, long, vector and
matrix, with widths 1/4/4/8/12/64. Capacity above four may shrink to four.

String-list clearing replaces each token through the original null-intern service,
releasing the previous token before publishing its replacement. It captures count
before the loop and computes each slot before the service calls. A controlled
non-null result from null interning is preserved by this layer. Object-list
clearing releases all retained references, then re-reads count and backing storage
for the zeroing pass. Only afterward is count cleared and capacity reconsidered.
The string channel precedes the object channel. Recovered C preserves this order
and the callbacks' opportunity to change counts/pointers.

Delay reset clears use/deadline, replaces group, information and message strings,
clears the numeric selector and clears the owned argument context. It retains
that context reference for future reuse.

## Enqueue and delivery

Enqueue requires a valid prepared last delay record in a nonempty delay stack.
Its deadline is the current 64-bit clock plus `delay * 0x00fe502a`, with 64-bit
wrapping arithmetic. The delay argument occupies one full 64-bit EE register;
its high word is significant. This page does not infer a host time unit from the
constant alone. Ordering and expiry comparisons interpret deadlines as signed
64-bit values.

Enqueue swaps the messenger's current argument object with the delay record's
spare argument object. It saves references with separate temporary ownership;
it does not copy individual channel values. It then interns/replaces the message,
marks the record used, removes the old last list entry and inserts the record
before the first inactive record or strictly later deadline. Equal deadlines
retain enqueue order. List removal/insertion and temporary reference ownership
remain separate operations.

When memory is assigned and the delay stack count is nonzero, update captures its
initial count and current clock. With freeze clock zero, it repeatedly examines
the first record. An inactive record or future deadline stops delivery. For each
expired record, it selects the recorded receivers using the real recovered
[selection implementation](messenger-dispatch.md), swaps argument contexts,
dispatches the recorded message, resets the expired record, removes it from the
front and appends it as an unused spare. It then releases temporary ownership.
The current argument context is cleared at the end of the update.

A receiver may enqueue while dispatch is suspended. Newly queued messages can
run during this update if already due, but the original captured count bounds
the total iterations. The update uses its captured clock even if the receiver
changes the system clock. Tests exercise both behaviors through actual original
nested enqueue and dispatch bodies, with a controlled concrete receiver callback.

With a nonzero freeze clock, update shifts deadlines in the active prefix by
`currentClock - freezeClock`, stops at the first inactive record, and updates the
freeze clock. It dispatches no receivers on that path. Uninitialized or empty
stacks skip the update entirely; the recovery preserves those original conditions.

## Context nesting

Push takes the last spare context, assigns it as current, removes that last list
entry and inserts the prior context at the front; the nesting count increments.
Pop first clears the current context, restores the first saved context, removes
that front entry and appends the prior context as a spare; the nesting count
decrements. Both paths balance object references around assignment and list
ownership. These bodies assume usable spare contexts and do not introduce a host
bounds policy or overflow fallback.

## Validation and remaining dependencies

Run from the repository root:

```sh
python3 testing/test_messenger_lifecycle_retail.py
python3 testing/test_messenger_dispatch_retail.py
python3 testing/test_messenger_results_retail.py
make check
make typed-check
make link
```

The lifecycle suite passes **464 original-instruction RAM/defined-return/ordered-call
comparisons** across all ten bodies. It executes the real recovered
selection/dispatch alongside clearing, enqueue, expiry and nesting. Cases cover
all eight channels, 0/1/4/8/9/17 elements, string/object lifetime edges,
destructor count mutation, relocated shrink buffers, null-intern return propagation,
64-bit delay high words and wraparound, negative/equal/future deadlines,
freeze/resume clock shifts, initialized/empty stacks, persistent enqueue/delivery,
1/2/3-context push/pop and receiver-driven nested enqueue. Explicit assertions
prove the receiver callback ran, iteration bounds held and captured-clock behavior
was exercised. Temporary stack addresses are normalized across nested frames;
all other RAM and ordered leaf calls are compared.

List mutation/reserve, pool/interner, allocator/delete, memory initialization,
registry/factories and concrete receiver callbacks remain controlled leaves.
This validates the engine lifecycle itself; it does not prove those lower
contracts, concurrency, a real wall-clock unit or complete native gameplay.
Real list/pool/chunk composition remains a next integration step. Concrete
virtual receiver implementations and group registry behavior remain recovery
work, together with seven compiler residuals and broader Lua dependencies.

The subsequent [memory recovery](messenger-memory.md) covers original initialization
and reset, with a cold integration oracle through this lifecycle. Factory internals
and lower services remain controlled; the standalone lifecycle suite above retains
its declared initialization leaf.
