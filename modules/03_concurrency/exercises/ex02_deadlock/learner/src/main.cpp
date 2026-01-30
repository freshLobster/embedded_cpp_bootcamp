#include <cassert>
#include <mutex>
#include <thread>

struct Account {
    std::mutex m;
    int balance{0};
};

void transfer(Account& a, Account& b, int amount) {
    // TODO: lock both mutexes safely using std::scoped_lock.
    (void)a; (void)b; (void)amount;
}

int exercise() {
    #error TODO_implement_exercise
    Account a{ {}, 100 };
    Account b{ {}, 100 };
    std::jthread t1([&]() { for (int i = 0; i < 1000; ++i) transfer(a, b, 1); });
    std::jthread t2([&]() { for (int i = 0; i < 1000; ++i) transfer(b, a, 1); });
    t1.join();
    t2.join();
    if (a.balance + b.balance != 200) return 1;
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
