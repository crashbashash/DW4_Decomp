# Common selector and SELECTCTRL protocol composition

Finding [#918](../findings/findings-0751-1000.md#f918) adds a joint original-instruction oracle for the common shop
selector owner, its concrete SELECTCTRL handler/update, pad-record lookup and
empty close queues. The owner obtains its selected value and completion flag
from the real handler's append operations. It has no fixture-selected result
or fixture completion flag.

Run from the repository root:

```sh
python3 testing/test_selector_manager_composition_retail.py
```

The suite compares **144 complete component lifecycles /3,146 persistent
RAM-and-ordered-call checkpoints**. A checkpoint invokes one source entry;
the harness controls the order of owner and manager updates. It compares every
non-stack RAM byte, ordered external calls with arguments/state snapshots, and
the delivered command history against the original retail instructions.
Before generation, the old selected field is poisoned so successful publication
requires the real GENERATE handler to establish the requested start point.

## Executed bodies

These eight bodies were already recovered. This checkpoint adds joint validation,
with **zero new matching bytes**.

| Original entry | Body | Span bytes |
| --- | --- | ---: |
| `0x004233f0` | Common WindowSelect owner update | 772 |
| `0x00423700` | CanRequestFO2TOP | 84 |
| `0x0039cbf0` | SELECTCTRL manager update | 2,864 |
| `0x0039d720` | General SELECTCTRL handler | 1,960 |
| `0x0039b810` | Pad manager record selection | 88 |
| `0x003f5a40` | Queued text close | 580 |
| `0x003f5f80` | Queued model close | 272 |
| `0x003f6090` | Close completion polling | 696 |

The joint scenarios execute **1,293/1,829 instruction addresses** across these
7,316 bytes. That is the measured coverage for these scenarios, rather than
an exhaustive path claim. The separate manager/pad and selector/initializer
oracles retain their broader input/callback coverage.

## Request and response boundary

An explicit test bridge models immediate SD delivery, enum decoding and primitive
message buffers. It verifies the SELECTCTRL target name and player, captures the
owner's integer/vector/string/decision-byte arguments, then invokes the actual
handler on both the MIPS and recovered-C sides. GETSELECT and ISEND responses
come from that handler's append operations. FO2TOP readiness likewise comes from
its real ISFO2TOP branch. A nested retail call receives a separate guest stack
frame; its caller's CPU state is restored while RAM, coverage and events remain
shared. Native C callbacks use separate scratch frames.

The owner publishes the current selection to its mother's return word while the
manager is active. It starts closing only after the manager has completed its
own close phases, cleared active and released its work reference. The three
owner close helpers execute their real bodies with valid empty queues and an
empty child list.

## Scenarios and limits

Scenarios cover all four players, both orientations, supplied decision flags,
normal and fallback pad records, 1/2/3/7 choices, cold registry allocation and
both allocator paths. They include:

- Generation and start-point publication, pending opening waits, directional
  movement and result publication while the owner remains active.
- Accepted selection and pending confirmation/close waits.
- Cancellation winning over simultaneous confirmation.
- NOCANCEL and disabled-choice rejection through the original 16-count wait,
  followed by a valid choice.
- FO2TOP acceptance resetting the selection to zero, busy rejection preserving
  the parent's existing result, and return to ordinary selection.
- Every returned index0..6 in a seven-choice cursor, with the corresponding
  `i_stcursor01` receiver name. One-choice and ordinary dialogs use
  `i_stmessky` and `i_stmesscr` fixture names respectively.

Pad records are controlled input. Fallback-record cases populate that record to
exercise the lookup path; neutral-record initialization and physical sampling
remain outside this suite. Model execution, real frame scheduling, SD receiver
selection/delivery/primitive storage, enum construction, factories/registry,
formatting, string/list services and generic object destruction are also
controlled boundaries. A default initializer supplies owner fields directly.
The actual ShopSelect initializers, fonts, Lua execution and XDATA transactions
still need to join this call tree. Full script/dispatch closure, nonempty close
queues and native gameplay acceptance remain separate work.

See the [selector contracts](shop-selectors.md), [manager/input contracts](selectctrl.md),
[window presentation](window-presentation.md) and [full hub completion contract](../systems/hub-recovery.md).
