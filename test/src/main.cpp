#include <chrono>
#include <print>
#include <thread>

int main() {
  std::println("Hello from test executable!");
  std::this_thread::sleep_for(std::chrono::seconds(60));
  std::println("Bye from test executable!");
  return 0;
}
