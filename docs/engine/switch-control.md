# Switch control (`beSwitchCtrl`)

`beSwitchCtrl` ([`src/game/beSwitchCtrl.cpp`](../../src/game/beSwitchCtrl.cpp)) shows or hides every child of
one `igSwitch` at once. It registers each of its rams with the messenger under the `SWITCHCTRL` group
(`beSwitchCtrl::RegisterReceiver`, through `beMessenger_RegisterReceiverFromInfo`); its info class is
`beSwitchCtrlInfo` (`beSwitchCtrl::GetInfoMeta`), whose `_switchNode` is the switch the ram drives.
`beSwitchCtrl::Prepare` and the per-frame `beSwitchCtrl::Update` are empty: everything happens in
`beSwitchCtrl::OnMessage`.

## Messages

The message is resolved against the `MsgAction` enum (`beSwitchCtrl_GetMessageEnum`): ALLON, ALLOF (0, 1).

- **ALLON**: enables every child of the info's switch (`igSwitch_EnableAllChildren`). Replies 1.
- **ALLOF**: disables every child of the info's switch (`igSwitch_DisableAllChildren`). Replies 1.

Any other message returns 0.

The stage scripts' layer-setup chunks in `lua/` send `be:sd("SWITCHCTRL", nil, -1, "ALLON")` to turn every
switch control's switch on; no script sends ALLOF.

## Open questions

- `beSwitchCtrl::Prepare` is the empty slot 32 that `beAction2_Prepare` also leaves empty; its role is only
  as established as that slot's (see [Action2](action2-jointset.md#open-questions)).
