from conans import ConanFile, CMake, tools

class SauSaGeConan(ConanFile):
    name = "SauSaGe"
    version = "1.0.0"
    license = "MIT"
    author = "<Rudy Chung> <rudychung@hotmail.com>"
    url = "<https://github.com/rudychung/SauSaGe>"
    description = "<A static site generator.>"
    topics = ("<Static>", "<Site>", "<Generator>")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake"
    exports_sources = "src/*", "CMakeLists.txt"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="src")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="src", src="src")
        self.copy("*.cpp", dst="src", src="src")
        self.copy("*.hpp", dst="src", src="src")
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("CMakeList.txt", dst="src", src="src")

    def package_info(self):
        self.cpp_info.libs = ["SauSaGe"]
