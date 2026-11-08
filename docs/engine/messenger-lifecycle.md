# Messenger delayed delivery and argument contexts

Ten complete lifecycle bodies (4,476 code bytes) cover argument clearing, delay-record reuse,
initialization checking, expiry updates, enqueue and context push/pop. The six
bodies at `38e8f0..38f0e0` form a contiguous enqueue/nesting block; the adjacent
clear functions are `38ca40..38cff0`. Initialization/update retain their existing
vtable-slot names.

Three forwarding bodies (192 bytes) have exact source in
[beMessengerLifecycle.cpp](../../src/game/beMessengerLifecycle.cpp). Group-delayed
send at `38ecf0` adds **84 matched bytes**; named-delayed send and group preparation
were existing matches and now have explicit, corrected signatures. Six more bodies
(3,312 bytes) match in one-function files under `src/unmatched/`; the expiry update
`38d0a0` (`beMessenger::vfunc_27`, 972 bytes) has no C source yet.

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
before the loop and computes each slot before the service calls. A non-null
result from null interning is published unchanged by this layer. Object-list
clearing releases all retained references, then re-reads count and backing storage
for the zeroing pass. Only afterward is count cleared and capacity reconsidered.
The string channel precedes the object channel, and callbacks can change
counts/pointers between these steps.

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
expired record, held under a temporary reference, it selects the recorded receivers through
[`38d860`](messenger-dispatch.md), swaps argument contexts, dispatches the recorded
message through `38e060`, resets the expired record through `38ce70`, removes it from the
front and appends it as an unused spare through `301e30`. It then releases temporary ownership.
The current argument context is cleared at the end of the update.

A receiver may enqueue while dispatch is suspended. Newly queued messages can
run during this update if already due, but the original captured count bounds
the total iterations. The update uses its captured clock even if the receiver
changes the system clock.

With a nonzero freeze clock, update shifts deadlines in the active prefix by
`currentClock - freezeClock`, stops at the first inactive record or the captured count,
updates the freeze clock and clears the current argument context. It dispatches no
receivers on that path. Uninitialized or empty stacks skip the update entirely.

## Context nesting

Push takes the last spare context, assigns it as current, removes that last list
entry and inserts the prior context at the front; the nesting count increments.
Pop first clears the current context, restores the first saved context, removes
that front entry and appends the prior context as a spare; the nesting count
decrements. Both paths balance object references around assignment and list
ownership. These bodies assume usable spare contexts and have no bounds check or
overflow fallback.

## Validation and remaining dependencies

Run from the repository root:

```sh
make check
make typed-check
make link
```

Concrete
virtual receiver implementations and group registry behavior remain recovery
work, together with the expiry update `38d0a0`, which has no C source yet, and broader
Lua dependencies. A real wall-clock unit for the delay constant and any concurrency
contract are not established. [Messenger memory](messenger-memory.md) covers
initialization and reset.
