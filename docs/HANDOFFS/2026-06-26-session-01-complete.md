# Handoff — 2026-06-26 — Session 1 (Minimal Scaffold) complete + in-silico Phase 1 plan locked, next: Session 2 (Custom Physics List)

Project: **Graded-Z Shielding MSc** — University of Nairobi, Institute of Nuclear Science & Technology
Author: Brian Kipruto Kosgei (FNS6/48630/2025)
Last completed: **Session 1 — Minimal Working Scaffold** (commit `5e268da` on `main`, pushed to GitHub)
Current branch: `main` (clean, no uncommitted changes expected)
Next session: **Session 2 — Custom Modular Physics List**

---

## Repo state — read first

- Repo: `~/projects/graded-z-shielding` (also at `git@github.com:Brian-Kipruto/Brian-Kipruto/graded-z-shielding.git`)
- Branch: `main` (no feature branches in use yet; thesis project, sequential builds, history stays linear)
- Commits so far:
  - `3ab6555` — Initial commit: project skeleton, gitignore, README
  - `5e268da` — Minimal working Geant4 scaffold: world + polyethylene slab, electron gun
- Build directory: `build/` (gitignored). Binary lives at `build/graded-z`.
- VS Code is the editor. Native Ubuntu (no WSL). Geant4 11.2.1 auto-sourced via `~/.bashrc`.

**Before writing any code at session start, ask Brian to paste:**

```bash
cd ~/projects/graded-z-shielding
git status
git log --oneline | head -5
geant4-config --version
ls include/ src/
```

This confirms repo cleanliness, Geant4 environment, and which files exist.

---

## Why Session 2 next

Currently the simulation uses bare `FTFP_BERT` as a placeholder physics list. This is wrong for the project's physics:

- No HP (High Precision) neutron data → Am-Be neutron transport will be fictional once we swap the source.
- No `EmStandardPhysics_option4` → Bremsstrahlung yields in Pb will be biased.
- The proposal explicitly commits to a custom modular list.

Session 2 replaces `FTFP_BERT` with a custom `PhysicsList` class combining four constructors. It is a small code change (~50 lines, 2 new files, 1 line of `main.cc` modified) but it's the **foundation everything else depends on**. Doing it now means Sessions 3+ scoring numbers are physically meaningful.

---

## Scope of Session 2

- Create `include/PhysicsList.hh` and `src/PhysicsList.cc` — a class inheriting `G4VModularPhysicsList`.
- Register four physics constructors inside it:
  - `G4EmStandardPhysics_option4` — precision EM
  - `G4HadronPhysicsFTFP_BERT_HP` — hadronic + HP neutrons
  - `G4HadronElasticPhysicsHP` — HP elastic scattering
  - `G4RadioactiveDecayPhysics` — decay chains
- Modify `main.cc` to use the new `PhysicsList` instead of `FTFP_BERT` (one-line change).
- Update CMake? **No.** GLOB picks up the new files automatically — but `cmake ..` must be re-run before `make` (a noted gotcha).
- Verify: build, run, confirm the Geant4 banner now prints custom physics constructors.
- Commit + push.

Estimated time: 30–45 minutes including reading and verification.

---

## The big picture: in-silico Phase 1 plan (locked 2026-06-26)

Brian is doing the **lab experiment later** (INST recon visit pending). To avoid being blocked, we've committed to building a **simulated mock of Phase 1** through Sessions 2–9, so that when real lab data arrives all that changes is a few numbers (source spectrum, slab dimensions).

The locked roadmap:

| Session | What gets built | End state |
|---|---|---|
| 2 | Custom modular physics list | Banner shows custom physics; physics now trustworthy |
| 3 | RunAction + EventAction + basic per-event CSV | `/run/beamOn 1000` produces a CSV with 1000 rows |
| 4 | Three-layer PE/Pb/Al geometry + NaI(Tl) detector geometry (no scintillation yet) | Visualization shows real Graded-Z stack + detector |
| 5 | DetectorMessenger + vector-of-layers | Runtime-configurable geometry from macro |
| 6 | Swap electron gun for mock Am-Be GPS (placeholder spectrum, same shape as real Am-Be) | Sim fires neutrons + 4.4 MeV gammas |
| 7 | Rich scoring: primary/secondary classification by particle type and creator process | ML-ready features start appearing in CSV |
| 8 | Minimal Python orchestrator: generate macros, run binary in loop, aggregate CSVs | One Python command runs N configs, produces master CSV |
| 9 | First plots: energy deposit vs HDPE thickness, transmission vs layer order | Real-looking Phase 1 figures, mock data |

After Session 9: complete in-silico Phase 1. When real lab data arrives → swap the source spectrum, swap geometry parameters, re-run sweep, validate.

---

## Carry-forward technical notes (landmines)

These are bugs-not-yet-made. Do not reintroduce.

- **The flux units bug from old code:** `totalFlux / (1.0/cm2)` evaluates to `totalFlux * 100`, not a unit conversion. To convert per-mm² to per-cm², multiply by `cm2` (which equals 100 in Geant4's internal unit system). Sanity-check unit math against Geant4's unit constants.
- **Do NOT `delete G4AnalysisManager::Instance()`.** It's a Geant4-owned singleton. Deleting causes double-free crashes on shutdown. The old code had this; new code must not.
- **`G4Box` constructor takes HALF-extents, not full dimensions.** Easy to halve twice and get quarter-sized slabs.
- **`G4PVPlacement`: always pass `true` for overlap checking during dev.** Worth the CPU. Catches geometry bugs instantly.
- **Material ownership ≠ volume ownership.** Geant4 owns logical/physical volumes once we register them — do NOT delete. But things we `new` ourselves (e.g., `G4ParticleGun`) we DO delete in our destructors. Ownership rules vary case by case; read the docs when uncertain.
- **`G4PSCellFlux` returns track length / volume in Geant4 internal units.** Don't apply "convenient" divisions without checking the unit conversion math.
- **`file(GLOB)` in CMakeLists.txt does not auto-detect new files.** When adding new .cc/.hh files, run `cmake ..` from the build dir before `make`, or get "undefined reference" linker errors.
- **The Geant4 lifecycle has a specific order:** `Initialize()` calls `DetectorConstruction::Construct()`, then physics, then `ActionInitialization::Build()`. Don't try to access volumes/scorers before `Initialize()` runs.

---

## Brian's learning state — assume known

C++ concepts already covered in working code:
- Header/implementation split, include guards (`#ifndef`/`#define`/`#endif`).
- Forward declarations vs. full `#include` (header lean / cc full).
- Inheritance from abstract base classes (`G4VUser...`).
- `override` keyword as a safety net for virtual overrides.
- `const` after method declaration (e.g., `void Build() const override`).
- Member initializer lists in constructors.
- `auto*` for type inference on `new`-returned pointers.
- Raw pointers and the convention of Geant4 ownership transfer via `new` + register.
- `nullptr` over `NULL` or `0`.

Geant4 concepts already covered:
- The volume trinity: Solid → LogicalVolume → PhysicalVolume.
- The action factory pattern (`ActionInitialization::Build()` vs. `BuildForMaster()`).
- `G4NistManager::FindOrBuildMaterial` for NIST-defined materials.
- Run manager construction (`SerialOnly` mode), three mandatory user initializations.
- Particle gun basics (`G4ParticleGun`, set particle/energy/position/direction).
- Visualization macro structure (`/vis/open`, `/vis/drawVolume`, trajectories).
- Interactive mode vs. batch mode in `main.cc`.

Workflow concepts already covered:
- Git three-stage flow (working → staged → committed).
- Out-of-source CMake builds.
- SSH-based GitHub remote.
- Commit message conventions for thesis projects.

---

## Brian's learning state — still being introduced

Coming in Session 2:
- `G4VModularPhysicsList` and `RegisterPhysics()`.
- Why physics constructor choice matters (Bremsstrahlung in high-Z, HP neutron data, etc.).

Coming in Session 3:
- `G4AnalysisManager` and ntuples.
- `G4UserRunAction::BeginOfRunAction`/`EndOfRunAction` lifecycle.
- `G4UserEventAction::EndOfEventAction` for per-event scoring.
- `G4MultiFunctionalDetector` and primitive scorers.
- Hits collections and `G4THitsMap`.

Coming in Session 4:
- Cylindrical volumes (`G4Tubs`).
- Building a NaI(Tl) detector geometry (material + scoring volume + housing).
- Why we deliberately skip real scintillation modeling (deferred to Session 11+).

Coming in Session 5 (the big one):
- `G4UImessenger` and how UI commands are exposed.
- `G4UIdirectory`, `G4UIcommand`, `G4UIcmdWith...`.
- `G4RunManager::ReinitializeGeometry()`.
- The macro language as the Python ↔ C++ contract.

Coming later but on the radar:
- `G4GeneralParticleSource` (Session 6).
- `G4UserSteppingAction` and tracking creator-process names (Session 7).
- Python `subprocess`, `joblib`, parquet (Session 8).

Concepts the new chat should **slow down on**, even if asked to move fast:
- Anything involving ownership semantics in Geant4 (who deletes what, when).
- Anything involving unit conversion — show the arithmetic, don't hand-wave.
- The Messenger architecture in Session 5 — this is the single most architecturally important class in the project.

---

## Open decisions (mid-flight)

Things deferred, with reasoning. Decide explicitly in the relevant session, don't drift into a default.

- **Production cuts per region:** loose in world, tight in slabs. Defer to Session 4 when there are multiple regions. Not Session 2.
- **Variance reduction strategy:** not needed for thin shields and 10⁴–10⁵ events. Revisit if simulations time out during Session 8's sweeps.
- **Mock Am-Be spectrum source:** which reference to use as a placeholder? Likely a continuous neutron component (1–11 MeV, peak ~4 MeV) + discrete 4.4 MeV gamma line. Decide concretely in Session 6 — could be a Gaussian-mixture approximation or a coarse-binned histogram.
- **Real NaI(Tl) scintillation modeling:** deferred to Session 11 or later. For now, score energy deposit in the crystal volume, apply Gaussian smearing in Python.
- **Permission-style decisions for the Messenger UI commands:** not applicable here — Geant4 macros aren't security-sensitive. Note for parity with RANGER thinking.
- **Master dataset format:** CSV per-run, Parquet master. Locked. See Architecture Lockdown in vault.

---

## Workflow rules (Graded-Z thesis edition, non-negotiable)

1. **Concept first, code second.** Brian understands before typing. Each new file gets explained — what's its job, what's the pattern, what are the pitfalls — *before* he sees the code.
2. **Small focused chunks.** One concept per file when possible. Heavy comments. This is a thesis project; every file is documentation as well as code.
3. **No big silent code dumps.** Code arrives in pasteable chunks of 20–80 lines, each followed by a brief explanation. Brian rewrites by hand in his own files (not just copy-paste).
4. **Paste-output verification at each step.** After every significant chunk (file created, build succeeded, run produced output), Brian pastes the actual terminal output. Don't proceed past silent compile errors.
5. **End each session with: working build, git commit, push, retrospective note in handoff.**
6. **ADR for every non-trivial decision.** File in `docs/adr/NNNN-title.md`. The committee will ask.
7. **Don't reintroduce known bugs** (see Carry-forward).
8. **Paste errors verbatim.** Don't try to fix alone if stuck. The new chat reads the actual error message, not a paraphrase.
9. **Forward declarations in headers, full includes in .cc files.** Keep headers lean.
10. **`override` on every virtual override.** Always.
11. **`true` for overlap checking in `G4PVPlacement` during dev.** Always.

---

## Vault notes to skim before starting (Obsidian)

Brian's Obsidian vault lives at `~/Documents/.../graded-z-shielding/` (path may vary). The mind map is `Project Mind Map.canvas`. Skim these notes specifically:

- `00 - Overview/Master Overview.md` — current state of the project.
- `00 - Overview/Architecture Lockdown.md` — structural rules, the macro/CSV/parquet contracts.
- `00 - Overview/Open Questions.md` — what hasn't been decided.
- `02 - Phase II - Geant4/Phase II Overview.md`
- `02 - Phase II - Geant4/Custom Physics List.md` — Session 2's specific plan.
- `02 - Phase II - Geant4/Modeling Flexibility.md` — the composite-material approach.
- `04 - Code Architecture/Code Architecture Overview.md`
- `04 - Code Architecture/PhysicsList.md` — Session 2's target class.

---

## Path reminders

- C++ source/headers/macros: relative to `~/projects/graded-z-shielding/` (repo root).
- Build dir: `~/projects/graded-z-shielding/build/`.
- Binary: `~/projects/graded-z-shielding/build/graded-z`.
- Geant4 install: `/home/brian/geant4/geant4-v11.2.1-install/` (auto-sourced via `.bashrc`).
- `vis.mac` lives in `macros/`, gets copied to `build/` by CMake at configure time.

---

## Fresh-terminal start sequence

```bash
cd ~/projects/graded-z-shielding

# Geant4 env is auto-sourced via ~/.bashrc — verify with:
geant4-config --version    # should print 11.2.1

# Incremental rebuild (after most code changes):
cd build && make -j$(nproc)

# Full reconfigure + rebuild (after adding new .cc/.hh files):
cd build && cmake .. && make -j$(nproc)

# Clean slate rebuild (rarely needed):
rm -rf build && mkdir build && cd build && cmake .. && make -j$(nproc)

# Run interactively:
./graded-z

# Run batch (Session 5+):
./graded-z some_macro.mac
```

---

## Files to have in context for Session 2

Required:
- This handoff (`docs/HANDOFFS/2026-06-26-session-01-complete.md`).
- `main.cc` (will be modified one line).
- `include/ActionInitialization.hh`, `src/ActionInitialization.cc` (reference for the class pattern).

Reference (read if needed):
- Vault: `02 - Phase II - Geant4/Custom Physics List.md`.
- Vault: `04 - Code Architecture/PhysicsList.md`.
- Proposal PDF §2.3.2 (the physics list discussion in the lit review).
- Proposal PDF §3.2.2.2 (the physics list section in methodology).

---

## Retrospective notes (Session 1, written 2026-06-26)

What worked:
- Step-by-step ask-paste-verify cadence kept errors caught early.
- Out-of-source build was understood first try.
- The "explain why this exists" preamble before each file paid off.
- Git discipline from the very first commit avoided the "build a project then try to add git" mess.

What to do differently in Session 2:
- Brian wants to rewrite by hand, not copy-paste. Format code chunks to make this easy: small, focused, fully commented.
- Don't introduce too many concepts per file. Stick to one big idea.
- Spell out unit-system arithmetic explicitly — never assume the conversion is obvious.

What surprised:
- The first run produced visible Bremsstrahlung from a 10 MeV electron in PE — happy accident that the placeholder physics gave a teachable moment.
- Brian's instinct to ask about flexibility modeling Session 1 was earlier than expected. Good — it surfaced the composite-material design before any code was written that would have to be refactored.

---

*Next handoff to be written at end of Session 2.*
