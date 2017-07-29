
#ifndef OPERATOR_H
#define OPERATOR_H

#include <cstdlib>
#include <ctime>  
#include "queue.hpp"
#include <iostream>

class Operator {
	protected:
		BlockingQueue<int>* in;
		BlockingQueue<int>* out;
		int window;
		int* pull();

	public:
		Operator(BlockingQueue<int>* in, int window);
		virtual void execute() = 0;
		void start();
		BlockingQueue<int>* getOutBuffer();
};

class Map : public Operator {
	private:
		int (*fp)(int);

	public:
		Map(BlockingQueue<int>* in, int window, int (*fp)(int)) : Operator(in, window), fp(fp) {
		}

		void execute() {
			while(true) {
			  int* data = pull();
			  for (int i=0; i < window; i++) {
			    out->push(fp(data[i]));
			  }
			}
		}
};

class Filter : public Operator {
	private:
		bool (*fp)(int);

	public:
		Filter(BlockingQueue<int>* in, int window, bool (*fp)(int)) : Operator(in, window), fp(fp) {
		}

		void execute() {
			while(true) {
			  int* data = pull();
			  for (int i=0; i < window; i++) {
				if (fp(data[i])) {
				  out->push(data[i]);
				}
	  		  }
			}
		}
};

class Fold : public Operator {
	private:
		int (*fp)(int*);

	public:
		Fold(BlockingQueue<int>* in, int window, int (*fp)(int*)) : Operator(in, window), fp(fp) {
		}

		void execute() {
	          while(true) {
		    int* data = pull();
		    out->push(fp(data));
	   	  }
		}

};

class Source : public Operator {
	public:
		Source() : Operator(NULL, 0) {
		}

		void execute() {
			while(true) {
			  srand(time(0));
			  int r = rand();
			  out->push(r);
			}
		}
};

class Sink : public Operator {

	public:
		Sink(BlockingQueue<int>* in) : Operator(in, 0) {
		}

		void execute() {
			while(true) {
		          int* data = pull();
			  for (int i=0; i < window; i++) {
				  std::cout << data[i] << " ";
			  }
			}
		}
};

#endif
