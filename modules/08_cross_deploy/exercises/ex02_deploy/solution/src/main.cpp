// Solution: scp command builder
// Constructs a deterministic deployment command string.
// The output is pure text to keep the exercise platform-neutral.

#include <cassert> // assert() provides a minimal self-check.
#include <string>  // std::string for concatenation.

std::string make_scp_cmd(const std::string& user, const std::string& host,
                         const std::string& local, const std::string& remote) {
    // Format: scp <local> <user>@<host>:<remote>
    return "scp " + local + " " + user + "@" + host + ":" + remote;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    auto cmd = make_scp_cmd("pi", "raspberrypi.local", "./app", "/home/pi/app");
    if (cmd.find("scp ./app pi@raspberrypi.local:/home/pi/app") == std::string::npos) {
        return 1;
    }
    return 0;
}

int main(){
    // The solution must produce the expected command format.
    assert(exercise()==0);
    return 0;
}
