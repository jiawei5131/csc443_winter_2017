#define MAX_CHARS_PER_LINE 10

typedef struct record {
	int uid1;
	int uid2;
	struct record *next;
} Record;

int read_txt_file(char*);
void clean_records(Record*);