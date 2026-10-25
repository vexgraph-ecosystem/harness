# harness — Repo-Local Living Preferences
> Repo-local preferences governed by the Living Documentation Law.
> Universal constitution: `gist.md` is the compressed law list; `PREFERENCES.md` is its rationale.

## 0. Constitution Link (supreme)
- [gist.md](https://gist.github.com/vex-graph/4132a6c45cb6d3797c3e8eff2e94035a#file-gist-md) — the compressed law list, mirrored in this workspace at `../../../metadata/gists/preferences/gist.md`. It is the only normative law text; `../../../metadata/gists/preferences/PREFERENCES.md` carries the rationale and is never ingested whole. Numbers are slice addresses inside one file, never law identity: cite by Title.
- All universal laws bind this repository. Read one on demand from the workspace root: `./tools/prefs law "<title>"`, `./tools/prefs section "<section>"`, `./tools/prefs repo <name>`.
- These exclusive preferences govern `harness` (R4 agent interface), the user's **own agent** integrated with this ecosystem. R4 borrows Relational Engine memory/IO and Vexspoke CPU/behavior, consumes `api-haven` connectors **as-is**, and composes `darling-framework` for interface. This blueprint has no implemented engine integration; connector/GPU/OS implementation ownership does not move.

## 1. Repo-Local Law Index (Binding Matrix)

Universal laws are inherited from the compressed constitution (`../../../metadata/gists/preferences/gist.md`); this table indexes the additional laws specific to this repository.

| Law Title | Scope | Enforcement |
| :--- | :--- | :--- |
| **Harness Host Boundary Law** | R4 agent interface | Mandatory for `harness` |
| **Agent Integration Law** | R4 agent execution | Mandatory for `harness` |

## 2. Exclusive Repo-Local Laws (FULL PROSE RESTATEMENT)

### Harness Host Boundary Law

#### Definition:
`harness` is the user's **own agent**, an R4 interface integrating this ecosystem, not a third-party agent host. It borrows Relational Engine memory/IO and Vexspoke CPU/behavior; consumes `api-haven` connectors plus `harness_run`/`harness_poll` **as-is** through opaque handles and fn-tables (the Conflict Triage Law canonical move); composes `darling-framework`; and drives R5 applications through registered seams. It owns no connector, transport, session, GPU or OS implementation.

#### The Why:
R4 is interfaces, not drivers. Reimplementing an api-haven connector or Graphvex pipeline would create a divergent second owner, the drift the Vertical Integration Law forbids. Consuming api-haven as-is keeps one owner per seam so the agent focuses on operating the user's own things.

#### The Rule:
1. **Interface tier, own agent.** Borrow public contracts from `relational-engine`, `vexspoke`, `api-haven` and `darling-framework`; never include R5 engine or supervisor headers; R1/R2/R3 never include harness.
2. **api-haven as-is.** Consume connector and `harness_run`/`harness_poll` shapes unchanged; supply the injected driver behind them, never a parallel connector implementation.
3. **R5 through seams.** Drive R5 apps through registered opaque handles + fn-tables, never `#include` an R5 header.
4. **Tools, not includes.** Invoke personal tools `func` and `b` as bounded child processes (Bounded Wait Law); never `#include` them.

---

### Agent Integration Law

#### Definition:
The agent operates the user's **own** projects, external tools and R5 applications through registered ecosystem contracts. Orchestration uses `func` **compile-time opcodes** and compiled native artifacts, never a shipped interpreted runtime; each external action is a bounded child.

#### The Why:
Reaching into R5 internals or shipping interpreted orchestration couples the agent to unstable surfaces and adds a runtime to every host. Registered seams keep it aligned with the Vertical Integration Law; compile-time opcodes keep orchestration deterministic, dependency-free and legible to the AI pair system.

#### The Rule:
1. **Integrate only via contracts.** Reach projects, tools and R5 apps through declared seams (opaque handle + fn-table), never another tier's internals. This is an ecosystem-scoped harness agent, not a general-purpose host.
2. **Compile-time, not interpreted.** Compile orchestration to native code through `func`; ship no interpreted orchestration runtime state.
3. **Bounded children only.** Every external tool is a bounded child: 100 ms reap slices, `SIGTERM` cancel (Bounded Wait Law); no unbounded wait or `system()`.
4. **Cold validation.** Validate agent input once at the cold seam (Cold-Strict, Hot-Minimal Validation Law); failures reject loudly (THROW Law).
5. **Agent objects, not duplicate drivers.** Planned Model, Prompt, Conversation, Answer, Question, Tool, ToolRegistry and Harness objects own agent policy, history and interface state. HarnessMcp describes the agent's own tool/resource surface; protocol parsing/hosting and external MCP transport consume API Haven contracts, never a parallel R4 implementation. This vocabulary is planned, not an implemented API or model/provider integration claim.
6. **Proof before trust.** Future mirrored `../../../tests/harness` owners prove registry growth/exhaustion, bounded retained history/output, failure/recovery, cancellation and actual tool/provider seams. Legal shared-state pressure follows the Deliberate Exhaustion and Backend Trust Law; fake providers and documentation checks alone prove neither live integration nor production readiness.

---

## 3. Repo-Local Extensions (managed, per the Conflict Triage Law)

### Current draft and IDE evidence boundary

`src/space` contains C23 ModelUser, Channel, Message and Task class pairs plus header-only support. Offline behavioral owners in `../../../tests/harness/space` (including a compile-negative arity battery) run via `python3 tests/harness/run.py` and `./tools/b test <unit>`. This is not live agent/provider/UI integration; message text remains borrowed and projections/identity retain their stated limits.

The workspace owns all editor indexing, supplies local Vexspoke headers and recursively discovers `.c`/`.h` sources; this repository has no CMake entry. Workspace compiler tests prove source contexts, header resolution and recursive discovery only—not actual highlighting/inlay appearance or runtime dependency closure. Planned agent objects and ownership boundaries above remain unchanged.

;;INTENTION("R4 agent interface: the user's own agent integrated with the ecosystem; consumes api-haven as-is; drives projects/tools/R5 apps through registered seams; owns no connector/GPU/OS implementation; bounded child tools only.")

## 4. Readiness Cross-Reference (Living Documentation Law)

- Feature readiness matrix: [harness](https://gist.github.com/vex-graph/6943f92acb931b25dad1073c46da6ce7#file-harness-md).
- Open blockers and deferred decisions: [ecosystem blockers Gist](https://gist.github.com/vex-graph/e921fa188eebbd0c68c4e59646109887).
