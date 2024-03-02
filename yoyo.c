#include "stdlib.h"
#include "stdio.h"

#include "yoyo.h"

#define STACK_SIZE (32)
#define VARIABLE_STACK_SIZE (255)

void process(char instruction, char arg);

static char stack[STACK_SIZE];
static char variables[VARIABLE_STACK_SIZE];

static unsigned int stack_pointer = 0;

void process(char instruction, char arg) {
  switch (instruction) {
    case ADD: {
      process(PUSH, stack[stack_pointer] + stack[stack_pointer - 1]);
      break;
    }
    case SUB: {
      process(PUSH, stack[stack_pointer - 1] - stack[stack_pointer]);
      break;
    }
    case SET: {
      *(variables + arg) = stack[stack_pointer];
      break;
    }
    case GET: {
      process(PUSH, *(variables + arg));
      break;
    }
    case PUSH: {
      ++stack_pointer;
      stack[stack_pointer] = arg;
      break;
    }
    case PUT_CHAR: {
      putchar(stack[stack_pointer]);
      break;
    }
    case CMP: {
      process(PUSH, stack[stack_pointer - 1] > stack[stack_pointer]);
      break;
    }
    default: {
      printf("Unknown instruction.\n");
      break;
    }
  }
}

int main(int argc, char** argv) {
  char prog[512] = {0};
  FILE* fp = fopen(argv[1], "rb");
  int i;

  (void)argc;

  fread(prog, 512, 1, fp);

  for (i = 0; i < 256; ++i) {
    process(prog[i * 2], prog[i * 2 + 1]);
  }

  fclose(fp);

  return 0;
}

