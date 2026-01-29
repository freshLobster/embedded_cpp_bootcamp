#include <cassert>
#include <string>

std::string make_scp_cmd(const std::string& user, const std::string& host,
                         const std::string& local, const std::string& remote) {
    return "scp " + local + " " + user + "@" + host + ":" + remote;
}

int exercise() {
    auto cmd = make_scp_cmd("pi", "raspberrypi.local", "./app", "/home/pi/app");
    if (cmd.find("scp ./app pi@raspberrypi.local:/home/pi/app") == std::string::npos) {
        return 1;
    }
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
