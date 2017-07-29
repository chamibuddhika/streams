
#include <stdio.h>
#include <stdlib.h>
#include "cyclic_buffer.h"

#define crBegin static int state=0; switch(state) { case 0:
#define crReturn(x) do { state=__LINE__; return x; \
                         case __LINE__:; } while (0)
#define crFinish }

c_buf* new_buffer() {
  c_buf* buf = (c_buf*) malloc(sizeof(c_buf));
  buf->len = 10;
  buf->ptr = -1;
  return buf;
}

int push(c_buf* buf, int val) {
  // printf("Ptr at push : %d\n", ptr);
  if (buf->ptr < buf->len) {
    if (buf->ptr == -1) buf->ptr++;
    buf->buf[buf->ptr++] = val;
  } else {
    return -1;
  }
  return 0;
}

int pop(c_buf* buf, int* val) {
  // printf("Ptr at pop : %d\n", ptr);
  if (buf->ptr < 0) return -1;

  if (buf->ptr == 0) { 
    *val = buf->buf[buf->ptr--];
  } else {
    *val = buf->buf[--buf->ptr];
  }
  return 0;
}
