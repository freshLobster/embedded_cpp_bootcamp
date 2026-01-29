#include <cassert>

int work(int x) { return x * 2; }
int level3(int x) { return work(x + 1); }
int level2(int x) { return level3(x + 1); }
int level1(int x) { return level2(x + 1); }

int exercise() {
    int v = level1(1);
    if (v != 8) {
        return 1;
    }
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
