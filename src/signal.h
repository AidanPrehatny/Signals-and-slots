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

        template <typename T>
        int connectMember(T *instance, void (T::*func)(Args...) const) const {
            return connect([=](Args... args) {
                (instance->*func)(args...);
            });
        }

        int connect(std::function<void(Args...)> const& slot) const {
            this->slots.insert(std::make_pair(++this->currentId, slot));
            return this->currentId;
        }

        void disconnect(int id) const {
            slots.erase(id);
        }

        void disconnect_all() const {
            slots.clear();
        }

        void emit(Args ... p) {
            for(auto it : slots) {
                it.second(p...);
            }
        }
        
        Signal& operator=(Signal const& other) {
            disconnect_all();
        }


    private:
        mutable std::map<int, std::function<void(Args...)>> slots;
        mutable int currentId;
};

#endif