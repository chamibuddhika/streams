
typedef struct c_buf{
  int buf[10];
  int len;
  int ptr;
} c_buf;

int push(c_buf* buf, int val);

int pop(c_buf* buf, int* val);

c_buf* new_buffer();
