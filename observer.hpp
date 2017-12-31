
#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <algorithm>

class Observer {
    public:
        virtual void onNotify (unsigned int event, unsigned int data) = 0;
};

class Subject {
    public:
        void addObserver (Observer* obs);
        void removeObserver (Observer* obs);
        void notify (unsigned int event, unsigned int data);
    protected:
        std::vector<Observer*> observers;
};

#endif
