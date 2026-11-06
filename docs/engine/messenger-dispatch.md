# Messenger receiver selection and dispatch

The contiguous fourteen-body block at `0x0038d470..0x0038e8f0` contains
5,192 code bytes. All bodies have readable [behavioral C](../../recovered/engine/messenger-dispatch.c)
with guest references behind the shared memory/call API. Five forwarding bodies
(244 bytes) retain exact matching source in
[beMessengerDispatch.cpp](../../src/game/beMessengerDispatch.cpp).
These were existing matches; the consolidation corrects their signatures and
removes surplus forwarded arguments without adding matching bytes.
records the evidence and limits. The semantic names describe verified operations,
not original C++ method spellings.

## Data and entry points

Reflection identifies `beMessenger._argData` (+16), `_groupList` (+20),
`_workStack` (+24), `_delayStack` (+28), `_freezeTime` (+40), and
`_isMemoryAssign` (+48). Its owner/system reference at +12 provides the current
64-bit clock at +80. Work records contain group name +8, information name +12,
RAM number +16, message +20, cached RAM numbers +24 and retained RAM references
+28. Group records contain parallel information-name (+12), RAM-number (+16)
and retained RAM (+20) lists. Delay records contain use byte +8, group/name
+24/+28 and RAM number +32. See [reflection metadata](reflection-metadata.md)
and [result channels](messenger-results.md).

| Address | Recovered operation |
| --- | --- |
| `38d470` | Set freeze time to the system clock when enabled, otherwise zero |
| `38d4a0` | Resolve an enum value, caching type/name/value on success |
| `38d560` | Register a RAM receiver in parallel group lists |
| `38d7a0` | Destroy a temporary reference owner, optionally delete storage |
| `38d820` | Register using receiver +8 number and +12 information object's +8 name; fall back to the retail default string |
| `38d860` | Select a work record and populate its receiver cache |
| `38e060` | Dispatch the selected message or service a special query |
| `38e530` | Second temporary reference-owner destructor |
| `38e5b0` | Select group and RAM number, with null information filter |
| `38e5d0` | Select group with null information filter and RAM number -1 |
| `38e5f0` | Select group/name/number and dispatch the fifth argument |
| `38e630` | Select group/number and dispatch the fourth argument |
| `38e670` | Select group and dispatch the third argument |
| `38e6b0` | Prepare the last unused delay record, allocating another when busy |

The precise instantiated owner types of the two destructors are unresolved;
they retain `FUN_` names. They release the referenced object using the low
23-bit reference-count rule and delete owner storage only for a positive signed
16-bit deletion flag. The enum resolver returns -1 for a non-enum field; it does
not cache that failure. Its successful name copy uses the original unbounded
copy service and original fixed cache buffer; this recovery adds no new bound.

## Selection, cache and ownership

Selection initializes messenger memory when necessary, or clears its argument
context when already initialized. The work stack is a fixed, nonempty cache:
selection requires a reusable last record. Search compares group text, then
information text with null matching only null. A hit updates the numeric filter
and promotes that record to index zero. A miss reuses the last record, interns
its replacement strings, releases old cached receivers, clears both parallel
lists and promotes it. List capacities above four may shrink to four.

An empty receiver cache is repopulated from the group registry. A null work-name
filter accepts every information name; a null registered name also passes a
non-null filter. Numeric filtering occurs during dispatch, not cache creation.
Consequently changing the requested number reuses the same name-based cache.
Receiver/name lists, cached numeric lists and backing pointers are re-read at the
original service boundaries. Reference releases precede the zeroing pass, which
re-reads count after destructor callbacks. Cache removal and insertion balance
separate temporary/list ownership. The reference C preserves the order of these
operations, including intern-before-old-token-release.

Registration locates or constructs a group, appends its receiver, copies a
retained information token and appends the corresponding number. Deferred
selection similarly reuses an unused last delay record or constructs another,
then replaces group/information strings and number; enqueue time/message and
expiry are outside this block.

## Dispatch and queries

Dispatch interns and replaces the selected record's message before inspecting
it. Receiver count is captured once for the operation.

* `SEARCH` counts receivers whose number equals the requested number or for which
  either number is -1. It ignores receiver activity and context run-check state.
  It appends the original success/failure byte and either the hit count or the
  original no-hit integer sentinel to the result channels.
* `FIND_SPACE` appends the first receiver whose activity byte is zero to the
  object channel. It ignores numeric filtering and run-check state; no candidate
  produces no object result. Temporary retained ownership is released afterward.
* Ordinary messages with filter -2 select the first inactive receiver and stop
  after its callback. Other numeric filters accept equality or either side -1.
  When context run-check is exactly 1, inactive receivers are skipped; other
  context bytes do not impose that restriction.

For an accepted receiver, object +16 supplies a virtual check at byte slot 144,
receiving `(object, receiver, work)`. A zero low byte invokes slot 140 with
`(object, receiver, originalMessageText)`. The fallback reloads the object's
vtable after the check. The work filter is re-read afterward, so a callback that
changes it to -2 also stops the loop. Remaining iterations re-read context state
and backing pointers while retaining the originally captured receiver count.
This is synchronous mutable state, not evidence of thread safety.

## Verification and limits

Run from the repository root:

```sh
python3 testing/test_messenger_dispatch_retail.py
python3 tools/test_function_extents.py
make check
make typed-check
make link
```

The differential oracle executes private retail instructions for every body and
compares defined returns, RAM outside temporary stack frames, and ordered leaf
calls. **1,561 cases** cover cache misses/hits/promotion, null/non-null name
filters, IDs -2/-1/exact/missing, empty and 1/2/4/9/17-receiver groups, all three
message paths, activity/run-check combinations, callback return low bytes,
callback filter/state mutation, string/object lifetime edges, destructor count
mutation, relocated growth buffers, enum success/failure/cache, registration,
lazy pool creation and controlled allocation failure. Fixtures supply valid
nonempty work/delay stacks and parallel registry lists, as the original code
requires; no host bounds or fallback behavior is substituted.

Registry, list, intern, allocator/delete, argument clearing, object factories and
virtual receiver handlers remain controlled leaves in this oracle. Their tests
establish this block's own behavior against those contracts, not complete
receiver implementation. Lower list/string services have
[separate recovered bodies](list-services.md) and deeper
[result-channel composition](messenger-results.md); integrating those real
services into this selection oracle remains open. The other nine bodies match in
`src/unmatched/` (`FUN_0038e530` as the destructor emitted by `beMessenger_DispatchSelected.cpp`).

The reviewed Ghidra address sets contain holes: occupied byte counts truncated
the selector before `jr ra` and dispatch inside its epilogue. Generated
[data/function-extents.json](../../data/function-extents.json) now records spans
ending at `38e054` and `38e52c`, respectively, including return delay slots.
Original objdump confirms both epilogues. The split gains 44 code bytes previously
left in gaps; no binary content changes. Extent regressions cover both spans.

The subsequent [lifecycle recovery](messenger-lifecycle.md) covers argument
clearing, delayed enqueue/expiry and context nesting, with real integration
through this dispatcher. Registry/group construction, concrete receiver virtual
implementations and remaining compiler/allocator contracts remain open. This
block is one part of the full Lua-dependent engine recovery.

The [memory recovery oracle](messenger-memory.md) additionally executes cold
initialization and reset through this dispatcher. The standalone dispatcher suite
retains its explicitly controlled initialization boundary.
