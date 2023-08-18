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
    generators = "cmake"

    def requirements(self):
        if self.settings.os == "Windows":
            self.requires("boost/1.78.0@enterprise_messaging/stable")
        elif self.settings.os == "Linux":
            self.requires("boost/1.78.0")  
        self.requires("stonex-cms-amqp-lib/0.2.3@enterprise_messaging/test")
        self.requires("stonex-logger-wrapper/0.0.2@enterprise_messaging/test")
        self.requires("zlib/1.2.13", override=True)

        
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def source(self):
         self.run("git clone https://github.com/StoneXLabs/stonex-cms-amqp-test-engine.git")  

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
        self.copy("*.h", dst="include",src="message-content/include")
        self.copy("*.h", dst="include",src="message-content-verifier/include")
        self.copy("*.h", dst="include",src="message-decorator/include")
        self.copy("*.h", dst="include",src="message-receiver/include")
        self.copy("*.h", dst="include",src="message-sender/include")
        self.copy("*.h", dst="include",src="stonex-cms-amqp-test-engine/include")
        self.copy("*.h", dst="include",src="stonex-cms-amqp-test-notifier/include")
        self.copy("*.h", dst="include",src="stonex-cms-amqp-wrapper/include")
        self.copy("*.h", dst="include",src="test-utils/include")
        self.copy("*.h", dst="include",src="common/activemq-cpp/src/main")
        
        self.copy("*.lib", dst="lib",src="lib", keep_path=False)
        self.copy("*.so*", dst="lib",src="lib", keep_path=False)
        self.copy("*.a", dst="lib",src="lib", keep_path=False)
        self.copy("*.pdb", dst="lib",src="lib", keep_path=False)
        self.copy("*.exe", dst="bin",src="bin", keep_path=False)
        
        self.copy("*.config", dst="bin",src="message-content/Test")
        self.copy("*.config", dst="bin",src="message-decorator/Test")
        self.copy("*.config", dst="bin",src="message-receiver/Test")
        self.copy("*.config", dst="bin",src="message-sender/Test")
        self.copy("*.config", dst="bin",src="stonex-cms-amqp-test-engine/Test")
        self.copy("*.config", dst="bin",src="stonex-cms-amqp-wrapper/Test")
        
        self.copy("*message*.txt", dst="bin",src="message-content/Test")
        self.copy("*message*.txt", dst="bin",src="message-decorator/Test")
        self.copy("*message*.txt", dst="bin",src="message-receiver/Test")
        self.copy("*message*.txt", dst="bin",src="message-sender/Test")
        self.copy("*message*.txt", dst="bin",src="stonex-cms-amqp-test-engine/Test")
        self.copy("*message*.txt", dst="bin",src="stonex-cms-amqp-wrapper/Test")

    def package_info(self):
        self.cpp_info.libs = self.collect_libs()

