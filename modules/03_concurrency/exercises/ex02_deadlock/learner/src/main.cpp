// Exercise: Deadlock-free transfers
// Implement a transfer function that locks two accounts safely using scoped_lock.

#include <cassert> // For assert() in main.
#include <mutex>   // For std::mutex and std::scoped_lock.
#include <thread>  // For std::jthread.

struct Account {
    std::mutex m;
    int balance{0};
};

// Transfer must lock both accounts without deadlock.
void transfer(Account& a, Account& b, int amount) {
    // TODO: lock both mutexes safely using std::scoped_lock.
    // This avoids deadlock when threads lock the accounts in opposite order.
    (void)a;
    (void)b;
    (void)amount;
}

int exercise() {
    #error TODO_implement_exercise
    Account a{{}, 100};
    Account b{{}, 100};

    // Launch two threads that transfer in opposite directions.
    std::jthread t1([&]() { for (int i = 0; i < 1000; ++i) transfer(a, b, 1); });
    std::jthread t2([&]() { for (int i = 0; i < 1000; ++i) transfer(b, a, 1); });

    t1.join();
    t2.join();

    // Total balance should remain constant if transfers are correct.
    if (a.balance + b.balance != 200) return 1;
    return 0;
}

int main() {
    // The exercise returns 0 only if deadlocks are avoided.
    assert(exercise() == 0);
    return 0;
}
