cc_library(
    name = "uv_lib",
    srcs = ["uv.cpp", "query_processor.cpp"],
    hdrs = ["uv.hpp", "query_processor.hpp"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "uv",
    srcs = ["main.cpp"],
    deps = [":uv_lib"],
)

cc_test(
    name = "uv_test",
    srcs = ["uv_test.cpp"],
    size = "small",
    deps = [
        ":uv_lib",
        "@googletest//:gtest_main",
    ],
)