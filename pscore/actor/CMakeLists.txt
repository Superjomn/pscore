cc_library(pscore_actor
  SRCS
    actor.cc
    actor_logging.cc
    actor_registry.cc
  DEPS
    pscore_common
    absl_base
    pscore_status
    absl_strings
    absl_strings_internal
    absl_str_format_internal
  )

cc_test(test_pscore_actor
  SRCS actor_test.cc
  DEPS
  pscore_common
  pscore_actor
  Threads::Threads
  pscore_status
  )

cc_test(test_pscore_actor_registry
  SRCS actor_registry_test.cc
  DEPS
  pscore_common
  pscore_actor
  Threads::Threads
  pscore_status
  )
