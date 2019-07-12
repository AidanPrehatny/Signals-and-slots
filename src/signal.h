#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <functional>
#include <map>
#include <iostream>

template <typename ... Args>
class Signal {

    public:

        Signal() : currentId(0) {}

        Signal(Signal const& other) : currentId(0) {}
        
        template <typename... T>
        void print(T ... values) const {
            using arr = int[];
            arr{ 0, (std::cout << values << '\t', 0)... };
        }

        int connect(std::function<void(Args...)> const& slot) const {
            this->slots.insert(std::make_pair(++this->currentId, slot));
            return this->currentId;
        }

    private:
        mutable std::map<int, std::function<void(Args...)>> slots;
        mutable int currentId;
};

#endif