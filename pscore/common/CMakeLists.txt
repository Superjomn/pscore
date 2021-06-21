cc_library(pscore_common
        SRCS
            hash.cc
            type_util.cc
            task_queue.cc
            channel.cc
            semaphore.cc
            managed_thread.cc
        DEPS
            glog
        )

cc_test(test_channel SRCS
    channel_test.cc
    DEPS pscore_common)
