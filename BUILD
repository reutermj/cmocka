load("@rules_cc//cc:defs.bzl", "cc_library")

# Main cmocka library target
cc_library(
    name = "cmocka",
    srcs = [
        "include/cmocka_private.h",  # Private header needed for compilation but not exposed
        "include/config.h",  # Private header needed for compilation but not exposed
        "src/cmocka.c",
    ],
    hdrs = [
        "include/cmocka.h",
        "include/cmocka_pbc.h",
        "include/cmocka_version.h",
    ],
    copts = [
        "-std=c99",
        "-DHAVE_CONFIG_H",
        "-D_GNU_SOURCE",
        "-D_XOPEN_SOURCE=700",
    ],
    includes = ["include"],
    visibility = ["//visibility:public"],
)

# Private library for tests that need access to cmocka internals
# This exposes cmocka.c as a header so tests can include it directly
cc_library(
    name = "cmocka_private",
    hdrs = [
        "include/cmocka_private.h",
        "src/cmocka.c",
    ],
    includes = [
        "include",
        "src",
    ],
    visibility = ["//tests:__pkg__"],
)
