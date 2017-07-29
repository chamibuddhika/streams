
#include "queue.hpp"

void map(BlockingQueue* in, BlockingQueue* out, int window) {
	if (window > 1) {
	for (int i=0; i < window; i++) {
		in.pop();
	}

}
