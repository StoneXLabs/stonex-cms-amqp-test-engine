from conans import ConanFile, CMake, tools

def get_verion_tag():
    git = tools.Git("stonex-cms-amqp-test-engine")
    try:
        return "%s" % (git.get_tag())
    except Exception as e:
        return e

class StonexCmsAmqpTestEngineConan(ConanFile):
    name = "stonex-cms-amqp-test-engine"
    version = get_verion_tag()
    license = "<Put the package license here>"
    author = "krzysztof.obrebski@stonex.com"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "cms client testing engine"
    topics = ("cms","amqp","test")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    requires = ["stonex-cms-amqp-lib/0.3.0@enterprise_messaging/test","boost/1.78.0@enterprise_messaging/stable"]
    generators = "cmake"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def source(self):
        pass
        #self.run("git clone https://github.com/conan-io/hello.git")
        # This small hack might be useful to guarantee proper /MT /MD linkage
        # in MSVC if the packaged project doesn't have variables to set it
        # properly
        #tools.replace_in_file("hello/CMakeLists.txt", "PROJECT(HelloWorld)",
  

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
        self.copy("*.h", dst="include",src="./CMSClientWrapper/include")
        self.copy("*.h", dst="include",src="./common/include")
        self.copy("*.h", dst="include",src="./Configuration/include")
        self.copy("*.h", dst="include",src="./ConfigurationParser/include")
        self.copy("*.h", dst="include",src="./MessageContent/include")
        self.copy("*.h", dst="include",src="./MessageContentVerifiers/include")
        self.copy("*.h", dst="include",src="./MessageDecorator/include")
        self.copy("*.h", dst="include",src="./MessageReceiver/include")
        self.copy("*.h", dst="include",src="./MessageSender/include")
        self.copy("*.h", dst="include",src="./stonex-cms-amqp-test-engine/include")
        self.copy("*.h", dst="include",src="./TestEventHandler/include")
        self.copy("*.h", dst="include",src="./TestRaport/include")
        self.copy("*.h", dst="include",src="./TestSuite/include")
        self.copy("*.h", dst="include",src="./Verifier/include")
        self.copy("*.h", dst="include",src="./TestNotifier/include")
        
        
        self.copy("*.lib", dst="lib",src="lib", keep_path=False)
        self.copy("*.pdb", dst="lib",src="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = self.collect_libs()
        pass

