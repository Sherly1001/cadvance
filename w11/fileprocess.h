#define MAX_COL 30
#define MAX_ROW 30

// doc noi dung tu file va luu vao Graph
char ** readFile(const char* filename, int *row, int *col);

// ghi matran danh dau duong da chon
void writeFile(char **Graph, int *row, int *col, const char filename);

// ghi matran danh dau duong da chon
void printGraph(char **Graph, int row, int col);