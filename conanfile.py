from conans import ConanFile


class ConanPackage(ConanFile):

    name = "serialize-buffer"
    version = "0.1.0"

    generators = "cmake_find_package"

    requires = [
        "gtest/1.10.0",
    ]
