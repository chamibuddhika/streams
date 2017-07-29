
#include <thread>
#include "Operator.hpp"

Operator::Operator(BlockingQueue<int>* in, int windowSize) {
	this->window = windowSize;
	this->in = in;
	this->out = new BlockingQueue<int>();
}

BlockingQueue<int>* Operator::getOutBuffer() {
	return out;
}

int* Operator::pull() {
	int* a = (int*) malloc(window);
	for (int i=0; i < window; i++) {
		a[i] = in->pop();
	}
	return a;
}

void Operator::start() {
	std::thread( [=] { execute(); } );
}
