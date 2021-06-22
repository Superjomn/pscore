cc_library(pscore_actor
  SRCS
    actor.cc
    actor_logging.cc
    actor_registry.cc
    actor_path.cc
  DEPS
    pscore_common
    absl::base
    absl::strings
    pscore_status
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

cc_test(test_pscore_actor_path
  SRCS actor_path_test.cc
  DEPS
  pscore_common
  pscore_actor
  Threads::Threads
  pscore_status
  )
