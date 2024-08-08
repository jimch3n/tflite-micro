
#if defined(KN_SUPPORT_ISS_PROF) && defined(__XTENSA__)
#include <xtensa/sim.h>
#include <xtensa/tie/xt_misc.h>
#include <xtensa/tie/xt_timer.h>
// To support profiling, the Simulator must be launched in "cycle
// accurate" mode, but since only some processing will be of interest
// and cycle accurate mode is computationally expensive, we need to
// shut off profiling as early as possible, then temporarily turn it
// back on during the execution windows of interesting processing.
// KN_SET_ISS_PROF_FUNCTIONAL encapsulates that initial shutdown,
// while KN_GET_ISS_CYCLES() wraps the temporary reactivations.
#define KN_SET_ISS_PROF_FUNCTIONAL           \
  {                                          \
    xt_iss_profile_disable();                \
    xt_iss_client_command("all", "disable"); \
  }

// The Simulator will track the per function call count and cycle cost
// of "x" and everything called within it, aggregating that information
// as it arrives into a report that is eventually dumped to file.
#define KN_GET_ISS_CYCLES(x)                   \
  {                                            \
    xt_iss_switch_mode(XT_ISS_CYCLE_ACCURATE); \
    xt_iss_client_command("all", "enable");    \
    xt_iss_profile_enable();                   \
    x;                                         \
    xt_iss_profile_disable();                  \
    xt_iss_client_command("all", "disable");   \
  }

// As KN_GET_ISS_CYCLES(), but with conditional profiling.
#define KN_GET_ISS_CYCLES_IF(c, x)               \
  {                                              \
    if (c) {                                     \
      xt_iss_switch_mode(XT_ISS_CYCLE_ACCURATE); \
      xt_iss_client_command("all", "enable");    \
      xt_iss_profile_enable();                   \
      x;                                         \
      xt_iss_profile_disable();                  \
      xt_iss_client_command("all", "disable");   \
    } else {                                     \
      x;                                         \
    }                                            \
  }

// As KN_GET_ISS_CYCLES_IF(), but also provides the calling code
// with before and after cycle counts for "x" as a whole.
#define KN_GET_ISS_CYCLES_IF_CC(c, x, b, a)      \
  {                                              \
    if (c) {                                     \
      xt_iss_switch_mode(XT_ISS_CYCLE_ACCURATE); \
      xt_iss_client_command("all", "enable");    \
      xt_iss_profile_enable();                   \
      b = XT_RSR_CCOUNT();                       \
      x;                                         \
      a = XT_RSR_CCOUNT();                       \
      xt_iss_profile_disable();                  \
      xt_iss_client_command("all", "disable");   \
    } else {                                     \
      x;                                         \
    }                                            \
  }
#else
#define KN_SET_ISS_PROF_FUNCTIONAL
#define KN_GET_ISS_CYCLES(x) \
  { x; }
#define KN_GET_ISS_CYCLES_IF(c, x) \
  { x; }
#define KN_GET_ISS_CYCLES_IF_CC(c, x, b, a) \
  { x; }
#endif
