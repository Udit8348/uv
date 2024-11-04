cc_library(
    name = "uv_lib",
    srcs = ["uv.cpp"],
    hdrs = ["uv.hpp"],
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
    deps = [
        ":uv_lib",
        "@com_google_googletest//:gtest_main",
    ],
)