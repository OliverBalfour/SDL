
#include "observer.hpp"

void Subject::addObserver (Observer* obs) {
    observers.push_back(obs);
}

void Subject::removeObserver (Observer* obs) {
    auto it = std::find(observers.begin(), observers.end(), obs);
    if (it != observers.end())
        observers.erase(it);
}

void Subject::notify (unsigned short int event) {
    for (int i = 0; i < observers.size(); i++) {
        observers[i]->onNotify(event);
    }
}
