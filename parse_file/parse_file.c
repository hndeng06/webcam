
#include <stdlib.h>		/* getenv() */
#include <stdio.h>		/* printf() */
#include <string.h>		/* strcat() */
#include <limits.h>		/* PATH_MAX */
#include <unistd.h>		/* getpid() */


#define DEBUG
#define MAX_LINE	1024

#define EMPTY		'\0'

int parse_file(const char *pname)
{

	char cfgfile[40+1];
	char buff[MAX_LINE], *p;
	char key[256], value[256];
	FILE *fp;
	int len;
	int cfg_num = 0;
	static char *program = NULL;
	static const char *prog_wp = NULL;


	prog_wp = pname;
	program = strrchr (pname, '/');
	if (program) program++;
	else program = (char *)pname;

	strcpy (cfgfile, pname);
	//strcat (cfgfile, ".scf");
	fp = fopen (cfgfile, "rb");
	if (!fp) {
		return (0);
	}
	while (fgets (buff, MAX_LINE, fp) != NULL) {
		p = buff;
		while (*p && (*p == ' ' || *p == '\t'))
			p++;
		if (*p == '#')
			continue;
		*value = EMPTY;
		sscanf (p, " %[^= \t] = %[^\n]", key, value);
		if (*value) {
			len = strlen (value);
			if (len > 0) {
				if (*value == '"') {
					/* remove quote chars */
					memmove (value, value+1, len + 1);
					p = strrchr (value, '"');
					if (p)
						*p = EMPTY;
				} else {
					/* use last white char as end point */
					p = strchr (value, '\t');
					if (p)
						*p = EMPTY;
					else {
						p = strchr (value, ' ');
						if (p)
							*p = EMPTY;
					}
				}
			}
		} else {
			continue;
		}
#ifdef DEBUG
		fprintf (stderr, "key=%s, value=%s\n", key, value);
		//fprintf (stderr, "PATH_MAX=%d\n", PATH_MAX); //=4096
#endif
}
}

int main(int argc, char** argv)
{
	if(argc < 2){
		printf("too little params\n");
		exit(1);
	}
	parse_file(argv[1]);
	return 0;
}
