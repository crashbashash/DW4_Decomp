# Common selector and SELECTCTRL protocol composition

The common shop selector owner runs on top of its concrete SELECTCTRL
handler/update, pad-record lookup and close queues. The owner obtains its
selected value and completion flag from the handler's append operations; it
holds no result or completion flag of its own. The old selected field has no
part in publication: the GENERATE handler establishes the requested start point.

## Bodies

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

## Request and response protocol

The owner addresses the SELECTCTRL target by name and player and passes its
integer, vector, string and decision-byte arguments to the handler. GETSELECT
and ISEND responses come from that handler's append operations. FO2TOP readiness
likewise comes from its ISFO2TOP branch.

The owner publishes the current selection to its mother's return word while the
manager is active. It starts closing only after the manager has completed its
own close phases, cleared active and released its work reference. The three
owner close helpers then run over the window's close queues and child list.

## Protocol behaviour

The protocol applies to all four players and both orientations, with supplied
decision flags, normal and fallback pad records, and 1/2/3/7 choices:

- Generation publishes the start point, then pending opening waits, directional
  movement and result publication run while the owner remains active.
- Accepted selection is followed by pending confirmation/close waits.
- Cancellation wins over simultaneous confirmation.
- NOCANCEL and disabled-choice rejection go through the original 16-count wait,
  after which a valid choice is accepted.
- FO2TOP acceptance resets the selection to zero, busy rejection preserves the
  parent's existing result, and selection then returns to ordinary operation.
- Every returned index0..6 in a seven-choice cursor corresponds to the
  `i_stcursor01` receiver name. One-choice and ordinary dialogs use `i_stmessky`
  and `i_stmesscr`.

Full script/dispatch closure remains separate work.

See the [selector contracts](shop-selectors.md), [manager/input contracts](selectctrl.md),
[window presentation](window-presentation.md) and [full hub completion contract](../systems/hub-recovery.md).
