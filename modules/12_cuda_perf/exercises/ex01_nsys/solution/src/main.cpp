#include <cassert>
#include <string>

std::string profile_markers() {
    return "nsys:range=compute";
}

int exercise() {
    auto s = profile_markers();
    if (s.find("nsys") == std::string::npos) return 1;
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
