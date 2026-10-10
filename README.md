# harness — the user's own agent for the ecosystem (R4 interface)

Future builds belong to [b](https://github.com/vex-graph/b). No runnable agent
target exists yet.

## Current State

**Draft — not finalized.** The scope below may change as the design lands.

**Role:** R4 interface — the user's **own agent**, integrated with this
ecosystem rather than a third-party agent host. It drives the user's projects,
external tools and R5 applications through registered seams, consumes `api-haven`
as-is (AI providers + connectors), and composes `darling-framework` for
interface. It is an R4 interface, never an R5 engine.

**Current source:** the `src/space/` draft values — `ModelUser`, `Channel`,
`Message` and `Task` (C23 class pairs) plus header-only support. They expose
persona metadata, channel identity, borrowed message spans and task
transitions/delegation. No HarnessServer, mention router, live provider execution
or Darling UI exists.

**Behavioral owners (offline):** `tests/harness/space/{support,model_user,channel,message,task}_test.c`
plus a compile-negative arity battery (`space_arity_test.py`), run by
`python3 tests/harness/run.py` (strict `-Wall -Wextra -Werror` and ASan/UBSan) and
by `./tools/b test <unit>`. They prove construction, boundary/rejection behaviour,
reject-and-preserve failure, null-safe getters and bounded projections. They do
**not** prove a provider, server, UI or cross-platform runtime.

**Specified only:** the Harness Host Boundary Law and the Agent Integration Law
(forward contracts with nothing to bind yet).

**Runtime platforms proven:** none. Workspace code-model proof is separately scoped
in `tests/tools/harness_ide_test.py`; it does not prove agent execution or actual
IDE appearance.

## What it is
`harness` is the user's own agent — a coding-agent harness that feels like pi,
opencode or Claude Code, but scoped to this ecosystem instead of renting someone
else's host. It holds a model, drives prompts and history, calls tools (read and
write files, run `func` and other commands), hosts its own MCP surface and speaks
to external MCP servers, and presents through `darling-framework`. It borrows R2
memory/CPU and consumes `api-haven` connectors as-is; it owns no connector, GPU,
session or OS implementation.

### Planned objects (first to build)
- `Model` — an AI model binding (variant, speed, context/token budget).
- `Prompt` — a composed request (system + messages + attachments) and its builder.
- `Conversation` — the turn history.
- `Answer` — a streamed response chunk/result.
- `Question` — the interactive question/prompt section surface.
- `Tool` — a callable the agent invokes (read/write files, run `func`, MCP call).
- `ToolRegistry` — the agent's tool set (built-ins + `func` + MCP).
- `HarnessMcp` — the agent's own MCP surface; the external MCP client speaks to
  Claude/other servers. Names are prefixed to avoid colliding with api-haven's
  `McpServer`. This is agent-level registration over API Haven's protocol/hosting
  contracts, not a competing R4 JSON-RPC or transport implementation.
- `Harness` — the agent host tying Model + Tools + Conversation + interface together.

## Depends on (Vertical Integration Law allowlist)
R4 interface: borrows `relational-engine` (memory/IO), `vexspoke`, and
`api-haven` (connectors, **consumed as-is**) plus `darling-framework` for
interface. R5 applications are driven through registered seams (opaque handles +
fn-tables), never by including R5 headers. Never included by R1/R2/R3. It may
**invoke** the personal `func` and `b` tools as bounded child processes; those are
tools, not includes.

## Layout
- Draft coordination values: `src/space/` — four class pairs and shared support.
- Interface (future): the agent host, its R5/project/tool seams and the injected
  `harness_run`/`harness_poll` driver.
- Tests: the shared `../../../tests` repo hosts the `tests/harness/` partition
  (mirrored per unit, the Test Tree Mirror Law); no test file lives inside this
  repo's source directories (the Test Segregation Law).

## Laws that govern work here
- Constitution: the [canonical preferences.md Gist](https://gist.github.com/vex-graph/4132a6c45cb6d3797c3e8eff2e94035a); one real, Git-ignored workspace-root `../../../preferences.md`, not a Vexspoke file or symlink.
- Commits land in THIS repo root, one cohesive unit each; never push unless asked.
- Bounded Wait Law is load-bearing here: every external tool is a bounded child
  (100 ms reap slices, `SIGTERM` cancel), never an unbounded wait.

## Scope and Limitations

**Scope (intended):** R4 agent interface — operate the user's projects, external
tools and R5 applications through one integrated host, driving `api-haven`'s
connectors, `func`'s compile-time opcodes and `darling-framework`'s interface.

**Deliberately not covered:** no connector, session, GPU or OS implementation; no
R5 engine of its own; GPU shaders/dispatch remain Graphvex R3; network/transport
stays in api-haven and Relational Engine.

**Known limits and gaps:** the space values are behaviorally owned offline but
remain a draft with no runtime build target, no provider/server/UI integration and
no proven platform. The planned agent objects above remain specification only. No
runtime platform is proven. Message text is borrowed, not durable history;
identity/accessor exceptions and projections need contract review before completing
the core. IDE metadata does not close these gaps.
