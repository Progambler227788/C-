#include "monitor.h"
#include <iostream>
#include <deque>
#include <thread>

using namespace std;

class SharedBuffer {
public:
    SharedBuffer() : evenCount(0), oddCount(0) {}

    void produceEven(int value) {
        MonitorGuard guard(monitor);

        while (evenCount >= 10 || (oddCount > evenCount && evenCount >= 3)) {
            // Wait for conditions to be met
            condProduce.wait();
        }

        buffer.push_back(value);
        ++evenCount;

        // Signal waiting consumers
        condConsume.signal();
    }

    void produceOdd(int value) {
        MonitorGuard guard(monitor);

        while (oddCount >= 10 || (evenCount >= oddCount && oddCount >= 7)) {
            // Wait for conditions to be met
            condProduce.wait();
        }

        buffer.push_back(value);
        ++oddCount;

        // Signal waiting consumers
        condConsume.signal();
    }

    int consumeEven() {
        MonitorGuard guard(monitor);

        while (evenCount < 3) {
            // Wait for conditions to be met
            condConsume.wait();
        }

        int value = buffer.front();
        buffer.pop_front();
        --evenCount;

        // Signal waiting producers
        condProduce.signal();

        return value;
    }

    int consumeOdd() {
        MonitorGuard guard(monitor);

        while (oddCount < 7) {
            // Wait for conditions to be met
            condConsume.wait();
        }

        int value = buffer.front();
        buffer.pop_front();
        --oddCount;

        // Signal waiting producers
        condProduce.signal();

        return value;
    }

private:
    Monitor monitor;
    Condition condProduce;
    Condition condConsume;
    std::deque<int> buffer;
    int evenCount;
    int oddCount;
};

void processA1(SharedBuffer& buffer) {
    for (int i = 0; i < 100; i += 2) {
        buffer.produceEven(i % 50);
    }
}

void processA2(SharedBuffer& buffer) {
    for (int i = 1; i < 100; i += 2) {
        buffer.produceOdd(i % 50);
    }
}

void processB1(SharedBuffer& buffer) {
    for (int i = 0; i < 50; ++i) {
        int value = buffer.consumeEven();
        std::cout << "B1 consumed: " << value << std::endl;
    }
}

void processB2(SharedBuffer& buffer) {
    for (int i = 0; i < 50; ++i) {
        int value = buffer.consumeOdd();
        std::cout << "B2 consumed: " << value << std::endl;
    }
}

int main() {
    SharedBuffer buffer;

    // Creating threads for processes
    thread a1(processA1, ref(buffer));
    thread a2(processA2, ref(buffer));
    thread b1(processB1, ref(buffer));
    thread b2(processB2, ref(buffer));

    // Joining threads
    a1.join();
    a2.join();
    b1.join();
    b2.join();

    return 0;
}
