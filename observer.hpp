
#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <algorithm>

class Observer {
    public:
        virtual void onNotify (unsigned short int event) = 0;
};

class Subject {
    public:
        void addObserver (Observer* obs);
        void removeObserver (Observer* obs);
        void notify (unsigned short int event);
    protected:
        std::vector<Observer*> observers;
};

#endif
