#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <syncstream>

void slow(const std::string& name) {
    std::this_thread::sleep_for(std::chrono::seconds(7));
    std::osyncstream(std::cout) << name << " - 7 second" << std::endl;
}

void quick(const std::string& name) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::osyncstream(std::cout) << name << " - 1 second" << std::endl;
}

void work() {
    auto start = std::chrono::steady_clock::now();

    auto future_c2_d2 = std::async(std::launch::async, []{
        slow("C2");
        quick("D2");
    });

    quick("A");
    slow("B");
    quick("C1");

    future_c2_d2.wait();

    quick("D1");
    quick("F");

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::osyncstream(std::cout) << "\nTotal time: " << duration.count() << " seconds.\n";
    std::osyncstream(std::cout) << "Work is done!";
}

int main() {
    work();
    return 0;
}