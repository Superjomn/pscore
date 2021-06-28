add_subdirectory(pb)

cc_library(pscore_status
    SRCS
    status.cc
    DEPS
    error_codes_proto
    )

cc_library(pscore_core
        SRCS
            servable_state.cc
            servable_id.cc
            loader.cc
            resource.cc
            resource_manager.cc
            any_ptr.cc
        DEPS
            pscore_status
            error_codes_proto
            absl::base
            glog
        )

cc_test(test_pscore_resource SRCS resource_test.cc DEPS pscore_core)
cc_test(test_any_ptr SRCS any_ptr_test.cc DEPS pscore_core)
