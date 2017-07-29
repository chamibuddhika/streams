
#include "Operator.hpp"

bool filter(int val) {
	return true;
}

int mapper(int val) {
	return ++val;
}

int main(int argc, char* argv[]) {
	Source source;
	Map m(source.getOutBuffer(), 1, mapper); 
	Filter f(m.getOutBuffer(), 1, filter);
	Sink sink(f.getOutBuffer());

	source.start();
	m.start();
	f.start();
        sink.start();
}
