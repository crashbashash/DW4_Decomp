# Host details policy — hard rules

Nothing that identifies a developer's **machine or account** may be committed. This repository is cloned onto other people's
machines and may be public; a reader needs the *requirements* to reproduce a result, not a description of where one particular
machine keeps things or what it is built from. These rules are enforced mechanically (below), not by memory.

## The rules

1. **No absolute home or container paths.** Never write `/home/<user>/…`, `/Users/<user>/…`, `C:\Users\<user>\…` or a
   container mount such as `/workspace/…`. Use a path relative to the repository root, `../local/` (the toolchains and
   game data you supply), the placeholders `<repo>` / `<workspace>`, or `~/` when a home
   directory is unavoidable. Scripts resolve their own location (`os.path.dirname(os.path.abspath(__file__))`,
   `"$(dirname "${BASH_SOURCE[0]}")"`) instead of embedding a path.
2. **No specific hardware.** Never name a graphics card, processor, motherboard or controller *model or brand*, and never a
   PCI id, device node (`/dev/dri/…`, `/sys/class/drm/…`) or serial. Say *"a desktop AMD GPU"*, *"a desktop CPU"*, *"a physical
   gamepad"*. Measurements may be recorded as numbers; the machine they came from is not named.
3. **No host description.** Never name the distribution, desktop, kernel, driver, LLVM/Mesa version or display-server session of a
   particular machine. State **requirements** instead ("needs an X11 or XWayland window", "needs a Vulkan 1.0 driver"), never
   "on this host" facts.
4. **No identity or contact details.** No personal e-mail addresses, user names, host names, private network addresses or
   account handles. Commit authorship stays the repository's neutral identities.
5. **No credentials.** No tokens, keys or passwords, ever. If one is committed, treat it as compromised and rotate it first.
6. **It applies to everything that is committed**: code, comments, docs, test fixtures and strings, generated files, the
   **findings register**, and **commit messages**. Findings `evidence` names a repository-relative path.
7. **Do not bypass the checks.** No `--no-verify`. A genuine exception (a fixture that must contain such a string) goes in
   `scripts/host_details_allow.txt` with a comment saying why; it is reviewed like code.
8. **No emulator-driving facts.** The private emulator builds are driven through endpoints that belong to one machine and
   one session: PINE instance slots chosen for a profile, agent-socket paths that carry a user id (`/run/user/<uid>/…`,
   `/tmp/<tool>-agent-<uid>.sock`), `DISPLAY=:N` values and spare-display recipes, launch scripts and profile directories of
   a private build, and the savestate slot numbers of one profile. These live in the skills that drive
   the emulators, never in the repository. The repository states the **requirement** ("a PCSX2 build with the agent PINE
   protocol", "an X11 or XWayland display") and the **procedure** ("load the Terminal arrival state, pause, read the
   loader string"), and a session note says `pine read`, `state load` or `input press` rather than naming the endpoint.

Deliberate exceptions that are *not* violations: neutral vendor-level wording, standard layout names such as SDL's "Xbox 360"
mapping, placeholder paths (`/home/example/…`, `<uid>`), tool names (X11, XWayland, Vulkan) used as requirements, and a
protocol's documented default (PINE's standard slot) stated as the vendor default rather than as one machine's setting.

## Enforcement

| Layer | What it does |
| --- | --- |
| `scripts/check_host_details.py` | The checker: generic patterns per category (so it never has to name what it forbids). `--tree` scans every tracked text file; `--staged` the lines being committed; `--msg` a commit message; `--range` a pushed range. The rule set is listed below. |
| `.githooks/pre-commit`, `.githooks/commit-msg` | Run the checker on every commit. **Enable once per clone:** `scripts/install_git_hooks.sh` (sets `core.hooksPath`; it also enables `.githooks/pre-push`, the byte-oracle gate described in `docs/README.md`). |
| `.github/workflows/hygiene.yml` | CI re-runs the self-test, the whole-tree scan and the range scan on every push and pull request, so a clone without hooks is still caught. |
| `make hygiene` | The same self-test and whole-tree scan, locally. |
| `testing/test_check_host_details.py` | Proves each rule fires on a fake sample and that placeholders and generic wording pass. |

### Checker rules

Each rule is a generic pattern with a hint that says what to write instead. The tree-wide rules apply to every tracked
text file, staged line and commit message; the evidence rule applies to the findings register (`docs/findings/`).

| Rule | Catches | Write instead |
| --- | --- | --- |
| `home-path`, `workspace-path` | `/home/<user>/…`, `/Users/<user>/…`, `C:\Users\<user>\…`, `/workspace/…` | a repository-relative path, `../local/`, `<repo>`, `~/` |
| `gpu-model`, `gpu-family` | a graphics card model (`RTX 4090`, `RX 7900 XT`, `Arc A770`) or a GPU family/architecture (`RDNA 3`, `Navi 31`, `Vega 64`, `GeForce 1080`) | "a desktop GPU" (vendor-level, "an AMD GPU", is fine) |
| `cpu-model`, `cpu-vendor` | a processor model, or the vendor of the host's processor ("an AMD CPU", "Actual AMD CPU/GPU checks") | "a desktop CPU", "the CPU and GPU checks" |
| `controller-brand` | a third-party controller brand or model | "a physical gamepad" |
| `driver-version`, `host-description`, `device-node` | driver/kernel/LLVM/Mesa versions, the distribution or desktop, device nodes and PCI ids | a requirement ("needs a Vulkan 1.0 driver") |
| `personal-email`, `private-ip`, `secret` | e-mail addresses, private network addresses, credentials | nothing; rotate a leaked credential |
| `emulator-slot` | a private PINE socket slot (`PINE slot NNNNN`, `--slot NNNNN`, `slot-NNNNN`; a bare four-digit "slot" is left alone because vtable slot indices reach four digits). The rule cannot tell the vendor default from a private slot, so write "PINE's default slot" rather than its number | "the configured PINE slot" and the number from `PINE_SLOT` or the skill's config |
| `runtime-socket` | a per-user runtime socket directory (`/run/user/<uid>/…`, also spelled with `%d`, `$UID` or `<uid>`) | the path from `PINE_SOCK` or `XDG_RUNTIME_DIR` |
| `x-display` | the X display number of one machine (`DISPLAY=:9`, `Xwayland :9`, "display :9") | "an X11 or XWayland display", the number from `DISPLAY` |
| `opt-path` | an install location of one machine (`/opt/<tool>/…`) | the tool's name and the env var or config key that locates it (`<pcsx2-install>/…`) |
| `tmp-session-path` | a session- or account-stamped scratch path (an agent scratchpad, a uid-stamped `/tmp/<name>-NNNN`) | a path under `build/` |
| `db-scratch-path` (database only) | any `/tmp/…`, `/opt/…` or `/var/tmp/…` path in a finding — evidence must be reproducible from the repository | a repository-relative path |

A plain `/tmp/<file>` in a command example in the docs is generic and is not flagged by the tree-wide rules; in the findings
database it is, because a finding's evidence must name something a reader can open. `testing/test_check_host_details.py`
has a positive sample for every rule and a list of generic wordings that must pass.

## If something leaks anyway

1. Fix the working tree, the findings register included; `make hygiene` must be clean.
2. Remove it from history with `git filter-repo` (a blob callback applying the same replacements, plus a message callback),
   verify with `git log --all --text -S'<term>'` that no commit still contains it, then force-push with
   `--force-with-lease`. Rewriting history changes every commit id and everyone else must re-clone.
3. The host keeps old commits reachable by id (pull-request refs, forks, caches) until it garbage-collects; ask the host to run a
   GC and drop cached views, or recreate the repository if the detail is sensitive. Credentials are rotated regardless.
4. Add the missing pattern to `scripts/check_host_details.py` and a sample to its self-test so the same kind of leak cannot
   come back.
