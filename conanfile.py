from conans import ConanFile


class ConanPackage(ConanFile):

    name = "network-monitor"
    version = "0.1.0"

    generators = "cmake_find_package"

    requires = [
        ("boost/1.74.0",),
        ('openssl/1.1.1h',),
    ]

    default_options = (
        "boost:shared=False",
    )

