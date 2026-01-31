// Exercise: Deployment command builder
// Implement a deterministic scp command string constructor.
// The command is a plain string; no system() calls are required.

#include <cassert> // For assert() in main.
#include <string>  // For std::string building.

// TODO: build "scp <local> <user>@<host>:<remote>".
// HOW: use string concatenation in the exact order with spaces.
std::string make_scp_cmd(const std::string& user, const std::string& host,
                         const std::string& local, const std::string& remote) {
    // TODO: concatenate pieces in the correct order with single spaces.
    // Suggested outline:
    //   std::string cmd = "scp ";
    //   cmd += local;
    //   cmd += " ";
    //   cmd += user;
    //   cmd += "@";
    //   cmd += host;
    //   cmd += ":";
    //   cmd += remote;
    //   return cmd;
    (void)user;
    (void)host;
    (void)local;
    (void)remote;
    return {};
}

int exercise() {
    // Keep this error until make_scp_cmd() is implemented.
    #error TODO_implement_exercise
    auto cmd = make_scp_cmd("pi", "raspberrypi.local", "./app", "/home/pi/app");
    if (cmd.find("scp ./app pi@raspberrypi.local:/home/pi/app") == std::string::npos) {
        return 1;
    }
    return 0;
}

int main() {
    // The scp command must match the expected format.
    assert(exercise() == 0);
    return 0;
}
