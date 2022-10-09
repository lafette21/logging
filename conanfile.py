from conans import ConanFile

class Logging(ConanFile):
    name = "logging"
    version = "0.1.2"
    description = "C++ logging wrapper library."
    url = "https://github.com/laFette21/logging"
    exports_sources = "include/*"
    no_copy_source = True

    def requirements(self):
        self.requires("spdlog/1.10.0")

    def package(self):
        self.copy("*.h")
        self.copy("*.hh")
        self.copy("*.hpp")

    def package_id(self):
        self.info.header_only()

    def package_info(self):
        self.cpp_info.includedirs = ["include"]
