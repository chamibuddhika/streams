
#include <stdlib.h>
#include <stdio.h>
#include "cyclic_buffer.h"

#define crBegin static int state=0; switch(state) { case 0:
#define crReturn(x) do { state=__LINE__; return x; \
                         case __LINE__:; } while (0)
#define crFinish }

c_buf* buf0;
c_buf* buf1;

void consumer();

void producer() {
    int i, ret;
    crBegin;
    while (1) {
      i = 43;
      printf("Producing %d\n", i);
      ret = push(buf0, i);
      if (ret == -1) {
        crReturn();
      }
    }
    crFinish;
}

void consumer() {
    crBegin;
    while (1) {
      int val;
      int ret = pop(buf0, &val);
      if (!ret) {
        printf("Consuming %d\n", val);
      } else {
	producer();
      }
    }
    crFinish;
}

void source();

void filter();

void source() {
    int i, ret, flip;
    flip = 0;
    crBegin;
    while (1) {
      if (flip) {
        i = 42;
      } else {
        i = 43;
      }
      flip = ~flip;
      printf("Producing %d\n", i);
      ret = push(buf0, i);
      if (ret == -1) {
        crReturn();
      }
    }
    crFinish;
}

void filter() {
    int val, ret;
    crBegin;
    while (1) {
      ret = pop(buf0, &val);
      if (!ret) {
        printf("At filter %d\n", val);
	if (val == 43) {
          push(buf1, val);
	} 
	crReturn();
      } else {
	source();
      }
    }
    crFinish;
}

void map() {
    int val, ret;
    crBegin;
    while (1) {
      ret = pop(buf1, &val);
      if (!ret) {
        printf("At map %d\n", val);
      } else {
	filter();
      }
    }
    crFinish;
}

int main() {
  buf0 = new_buffer();
  buf1 = new_buffer();

  map();
}
