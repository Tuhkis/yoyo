#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "yoyo.h"

#define MAX_MACROS (1024 * 8)

typedef struct {
  char instruction;
  char arg;
} __attribute__((packed)) Asm;

typedef struct {
  char name[64];
  char pointer;
} VarMacro;

typedef struct {
  /* assembly */
  Asm* a;
  int a_len;
  /* variadic macros */
  VarMacro vm[MAX_MACROS];
  int vm_len;
} Prog;

int main(int argc, char** argv) {
  int i;

  if (argc < 2) {
    return 1;
  }

  for (i = 1; i < argc; ++i) {
    char scratch[128];
    char string[128];
    FILE* fp = fopen(argv[i], "r");
    int iiii = 0;
    int iiiii = 0;
    Prog prog = {0};
    prog.a = calloc(16, sizeof(Asm));
    prog.a_len = 16;
    (void) prog;

    if (fp == NULL) {
      printf("Failed to open %s\n", argv[i]);
      return 1;
    }

    for (;fgets(string, 128, fp);) {
      int ii = 0;
      ++iiiii;
      while (string[ii] == ' ' || string[ii] == '\t') ++ii;
      if (string[ii] == ';' || string[ii] == '\n' || string[ii] == '\0') {}
      else if (string[ii] == '#') {}
      else if (string[ii] == '@') {}
      else {
        Asm a;
        int iii = 0;
        memset(scratch, 0, 128);
        for (;;) {
          if (!isalpha(string[ii])) break;
          scratch[iii] = string[ii];
          ++ii;
          ++iii;
        }
        if (strcmp(scratch, "add") == 0) {
          a.instruction = ADD;
        }
        else if (strcmp(scratch, "sub") == 0) {
          a.instruction = SUB;
        }
        else if (strcmp(scratch, "set") == 0) {
          a.instruction = SET;
        }
        else if (strcmp(scratch, "get") == 0) {
          a.instruction = GET;
        }
        else if (strcmp(scratch, "push") == 0) {
          a.instruction = PUSH;
        }
        else if (strcmp(scratch, "putc") == 0) {
          a.instruction = PUT_CHAR;
        }
        else {
          printf("Unknown instruction %s on line %d\nCould not compile.\n", scratch, iiiii);
          fclose(fp);
          free(prog.a);
          return 1;
        }

        memset(scratch, 0, 128);
        iii = 0;
        ++ii;
        for (;;) {
          if (!isalnum(string[ii])) break;
          scratch[iii] = string[ii];
          ++ii;
          ++iii;
        }
        a.arg = atoi(scratch);

        prog.a[iiii] = a;
        ++iiii;

        if (iiii > prog.a_len - 1) {
          prog.a_len += 16;
          prog.a = realloc(prog.a, prog.a_len * (int)sizeof(Asm));
        }
      }
    }

    fclose(fp);
    fp = fopen("out.rom", "wb");
    fwrite(prog.a, iiii * sizeof(Asm), 1, fp);
    fclose(fp);
    free(prog.a);
  }
  return 0;
}

