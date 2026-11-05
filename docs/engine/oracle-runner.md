# The oracle runner: the byte oracle on every push

`.github/workflows/oracle.yml` runs the byte oracle for every pushed commit on a private,
self-hosted GitHub Actions runner labelled `dw4-oracle`. The hosted runners cannot do this:
`make check` and `make link` need the retail ELF and the proprietary compiler, neither of which
is in the repository (`.github/workflows/progress.yml` only *counts* what is committed). The
self-hosted runner keeps those private inputs outside the checkout and links them in for the
duration of a run, so every push gets a verdict from a process the pusher did not drive by hand.

## What a run proves

The workflow runs the gates the author of a change runs before reporting it
([CONTRIBUTING](../../CONTRIBUTING.md#checking-your-work)), in order, on a clean checkout of the pushed commit, and records one line per gate in the run's summary:

| gate | command | required line |
|---|---|---|
| mismatches | `make check` | `(N not matched: M mismatch, D debt)` with `M` = 0, no `compile failed` |
| no lost matches | `make check` | `cover : … K match byte-for-byte` with `K` >= `functions.fully_verified` in `docs/progress.json` of the pushed commit |
| relink | `make link` | `linkcheck: BYTE-IDENTICAL` |
| debt ratchet | `python3 tools/progress.py --debt-check` | exit 0 (skipped with a note while the option does not exist at that commit) |
| typed coverage | `make typed-check` | `… baseline matches` |
| host details | `make hygiene` | `check_host_details: clean` |
| progress files | `python3 tools/progress.py --check` | `up to date` |
| tool tests | `python3 -m unittest discover -s tools -p 'test_*.py'` | `OK` |

The byte gates are evaluated by the parser kept in `.githooks/pre-push` (`DW4_PREPUSH_GATE_ONLY=1
.githooks/pre-push CHECK_LOG LINK_LOG BASELINE`, with the debt-check exit code in `DEBT_RC`;
covered by `testing/test_prepush_gate.py`), so what counts as a mismatch or a lost match has one
definition, and a gate added to that parser (such as the
`linkcheck: orphans:` ceiling) is applied by the runner at the same commit. Every gate runs even
when an earlier one fails; the final *Summary* step writes the table to the run summary and
fails the job if any gate failed.

Not covered: the hook's *oracle-change rule* (commits that touch the oracle's own files must
carry an `oracle-change:` line and show the counterexample suite still failing). It needs the
pushed range, and the runner checks out the pushed commit alone (`fetch-depth: 1`); adding it
means fetching `github.event.before` as well and calling `DW4_PREPUSH_ORACLE_ONLY=1`.

The build cache under `build/` is kept between runs (it is keyed by content, exactly as in a
developer's clone, so a run after a small push only recompiles what changed); everything else
untracked is removed before each run. A manual run (`gh workflow run oracle.yml -f fresh=true`)
uses `make check-fresh` and `make link-fresh` to ignore the cache, as before a milestone.

Every `make` on the runner is wrapped in `flock` on a lock file the machine's interactive builds
share, so an oracle run never overlaps a developer's `make check`; the two simply take turns.
Run interactive builds through the same lock (`flock "$DW4_BUILD_LOCK" make check`) and a push
will not slow a build that is already running.

## What it cannot do

- **It does not block a push, and nothing local does either.** A failing oracle
  run is visible as a red status on the commit, in the *Actions* tab and in the run summary; the
  branch still moves. The pre-push hook does not run `make check` or `make link` (the author's
  run and this runner already cover them, and a third full build per push proves nothing new).
  So the first line of defence is the author's quoted
  gate lines, and a red run here means the commit is fixed forward at once. The hook
  blocks what cannot be recalled after a push: host details in the pushed lines and messages.
- To make the oracle *required*: branch protection with `oracle` as a required status check on
  `main`, after which a red run blocks the merge. Nothing in the workflow needs to change for that.
- It runs on one machine. If the runner is offline, pushes queue in GitHub until it returns
  (a queued run waits up to the workflow's 240-minute timeout once started; while nothing is
  online the run simply stays *queued*). Several pushes serialise through the `oracle`
  concurrency group and each keeps its own verdict; nothing is cancelled.
- It must not run untrusted workflow files. The workflow has no `pull_request` trigger: a
  pull request from a fork would execute the fork's workflow on the private machine. No forks
  exist; if one appears, keep the trigger list as it is.
- The `progress` workflow's bot commit never starts an oracle run: it is pushed with the
  default `GITHUB_TOKEN`, which does not trigger workflows, and its message carries
  `[skip ci]`, which GitHub honours for `on: push`. The bot commits in the history show no
  runs of any workflow.

## Private inputs

Nothing from `../local/` enters the repository or the workflow file. The runner's own `.env`
file (in the runner folder, outside Git) sets three variables; the workflow fails early with a
message naming the missing one, masks their values from the log, and never prints them:

| variable | meaning |
|---|---|
| `DW4_LOCAL_TOOLS` | absolute path of the folder the repository's `local` link points to (`wibo`, `mwcps2/3.0-011126/mwccps2.exe`, …) |
| `DW4_ROMS` | absolute path of the folder the repository's `roms` link points to (`dw4/game.elf` inside it) |
| `DW4_BUILD_LOCK` | absolute path of the lock file shared with the machine's interactive builds (created on first use) |

The workflow recreates `local` and `roms` in the checkout as symbolic links to those two folders
(a fresh checkout has neither: both are git-ignored) and checks that `orig/SLUS-20836/SLUS_208.36`, the
compiler and `wibo` are present behind them before the first `make`.

## Installing the runner on a machine

The runner holds the retail ELF and the compiler, so it belongs on a machine the project
trusts with them. Everything lives in one folder outside Git (the workspace sibling
`../local/actions-runner/` is the convention); nothing needs root.

1. Download the latest `actions-runner-linux-x64-<version>.tar.gz` from
   `github.com/actions/runner/releases` into that folder and verify its SHA-256 against the
   value in the release notes (`sha256sum -c`), then unpack it there. The runner's own
   dependencies are ICU, OpenSSL and Kerberos shared libraries; `ldd bin/Runner.Listener`
   must report nothing missing. The oracle itself also needs the repository's toolchain
   (`docs/engine/toolchain.md`): `mipsel-linux-gnu-as`/`ld`/`objdump`, `flock`, `python3`.
2. Register it to the repository with a short-lived registration token:
   `gh api -X POST repos/<owner>/DW4_Decomp/actions/runners/registration-token --jq .token`
   (the token is valid for one hour; never store it), then
   `./config.sh --unattended --url https://github.com/<owner>/DW4_Decomp --token <token>
   --name dw4-oracle --labels dw4-oracle --work _work`. GitHub adds `self-hosted`, `Linux`
   and `X64` itself; `runs-on: [self-hosted, dw4-oracle]` selects it.
3. Append the three variables above to the runner's `.env` file (`config.sh` creates it;
   `KEY=value` per line). The runner passes that file's variables to every job; this is the
   only place the paths exist.
4. Run it as a user service so it survives logouts and reboots: a unit under
   `~/.config/systemd/user/` with `ExecStart=<runner folder>/run.sh`,
   `WorkingDirectory=<runner folder>`, `Restart=always`, `KillMode=process`,
   `WantedBy=default.target`; then `systemctl --user daemon-reload`,
   `systemctl --user enable --now <unit>` and `loginctl enable-linger` (works without root
   where the user is allowed to linger; otherwise an administrator enables it once).
   `systemctl --user status <unit>` shows `√ Connected to GitHub` when it is listening, and
   `gh api repos/<owner>/DW4_Decomp/actions/runners` lists it as `online`.
5. The first run compiles everything (the build cache is empty); allow ten minutes. Later runs
   recompile only what the push changed.

`config.sh` writes the runner's credentials (`.credentials`, `.runner`) into that folder: keep it
private, and keep it out of any backup that leaves the machine.

## Rotating or removing the runner

- **Remove** (frees the name for another machine): stop the service
  (`systemctl --user disable --now <unit>`), then in the runner folder
  `./config.sh remove --token "$(gh api -X POST repos/<owner>/DW4_Decomp/actions/runners/remove-token --jq .token)"`.
  If the machine is gone, delete it from the repository instead:
  `gh api -X DELETE repos/<owner>/DW4_Decomp/actions/runners/<id>` (ids from the list call
  above).
- **Rotate credentials** (re-register in place): `./config.sh remove --token …`, then step 2
  again with a fresh registration token; `.env` and the systemd unit stay as they are.
- **Upgrade the runner software**: GitHub updates self-hosted runners automatically between
  jobs; a manual update is the download and unpack of step 1 over the existing folder with the
  service stopped.
- **Move it to another machine**: install there (steps 1-4) with `--replace` on `config.sh` so
  it takes over the `dw4-oracle` name, then remove the old one.
