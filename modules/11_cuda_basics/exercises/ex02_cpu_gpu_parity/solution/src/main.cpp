#include <cassert>
#include <vector>

std::vector<int> add_cpu(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> out;
    out.reserve(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        out.push_back(a[i] + b[i]);
    }
    return out;
}

int exercise() {
    std::vector<int> a{1,2,3};
    std::vector<int> b{4,5,6};
    auto out = add_cpu(a,b);
    if (out[0] != 5 || out[2] != 9) return 1;
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
