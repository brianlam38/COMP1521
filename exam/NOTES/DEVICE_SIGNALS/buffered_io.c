// QN: Build a buffered i/o library like stdio

FILE *fopen(char *name, char mode) ... mode = 'r' or 'w'

int getc(FILE *fp) ... return value is char or EOF

putc(FILE *fp, char ch) ... append ch to fp's stream

int fgets(FILE *fp, char *buf, int max)

// Assume a data structure like

typedef struct _file {
   char  mode;
   int   pos;
   char *buffer;
} FILE;

