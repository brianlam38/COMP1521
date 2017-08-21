typedef struct stack *stack_t;

// create a new stack
stack_t create(void);
// free a stack
void destroy(stack_t stack);
// add new item to stack
void push(stack_t stack, int item);
// remove top item from stack and return it
int pop(stack_t stack);
// return true if stack is empty
int is_empty(stack_t stack);
// return top item from stack but don't remove it
int top(stack_t stack);
// return number elements in stack
int size(stack_t stack);
// display contents of stack
void show(stack_t stack);
