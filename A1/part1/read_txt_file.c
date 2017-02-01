/* return -1 if an error has occured. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "read_txt_file.h"

int read_txt_file(char *fname)
{
	FILE *fp_read;
	char cur_line[MAX_CHARS_PER_LINE];
	const char *comma = ",";
	Record *records = NULL;
	Record *cur_rec = NULL;

	/* open text file for reading */
	if ( !( fp_read = fopen(fname, "r") ) )
	{
		fprintf(stderr, "Could not open file \"%s\" for reading. \n", fname);
		return (-1);
	}

	/* malloc */
	if ( (records = malloc(sizeof(Record))) == NULL )
	{
		fprintf(stderr, "Malloc records failed. \n");
		return (-1);
	}

	/* initialize */
	records->uid1 = 0;
	records->uid2 = 0;
	records->next = NULL;

	cur_rec = records;
	Record *temp = cur_rec;

	/* reading lines */
	while ( fgets(cur_line, MAX_CHARS_PER_LINE, fp_read) != NULL )
	{
		char *toke1, *toke2;

		/* remove end of line characters */
		cur_line[ strcspn(cur_line, "\r\n") ] = '\0';

		if (cur_line[0] == '\0')
		{	
			break;
		}

		/* malloc */
		if (cur_rec == NULL) 
		{
			if ( (cur_rec = malloc(sizeof(Record))) == NULL)
			{
				fprintf(stderr, "Malloc records failed. \n");
				return (-1);
			}

			temp->next = cur_rec;
			cur_rec->uid1 = 0;
			cur_rec->uid2 = 0;
			cur_rec->next = NULL;
		}

		/* process the line */
		toke1 = strtok(cur_line, comma);	// saperated by ','
		toke2 = strtok(NULL, comma);

		cur_rec->uid1 = atoi(toke1);
		cur_rec->uid2 = atoi(toke2);

		/* next record */
		temp = cur_rec;
		cur_rec = cur_rec->next;
	}

	/* test */
	Record *cur = records;
	while (cur)
	{
		printf("Record read UID1: %d, UID2: %d \n", cur->uid1, cur->uid2);
		cur = cur->next;
	}

	clean_records(records);
	fclose(fp_read);

	return 0;
}

/**
 * 
 * Clean all records
 */
void clean_records(Record *record)
{
	Record *cur_rec = record;
	Record *temp_rec = record;

	while (cur_rec)
	{
		cur_rec = cur_rec->next;
		free(temp_rec);
		temp_rec = cur_rec;
	}
}