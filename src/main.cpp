#include "signal.h"
#include <iostream>

int main() {
    // pass arguments to the function to store in the signal
    Signal<std::string, std::string> sig;
    sig.connect([] (std::string foo, std::string bar) {
        return foo + bar;
    });
    return 0;
}