
#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <algorithm>

#include "input.hpp"

class Observer {
	public:
		virtual void onNotify (const Input& input) = 0;
};

class Subject {
	public:
		void addObserver (Observer* obs);
		void removeObserver (Observer* obs);
		void notify (const Input& input);
	protected:
		std::vector<Observer*> observers;
};

#endif
