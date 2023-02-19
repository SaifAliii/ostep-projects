#include <stdlib.h>
#include <stdio.h>  
#include <stdbool.h>
bool stringExist(char * str2, char * str1)
{
	int i = 0;
	int j = 0;
	bool status = false;
	while (str2[j] != '\0' && status != true)
	{
		i = 0;
		int k = j;
		while (str1[i] == str2[k] && str1[i] != '\0')
		{
			i++;
			k++;
		}
		if (str1[i] == '\0')
			status = true;
		j++;
	}
	return status;
}

int main(int argc, char ** argv)
{
	if(argc == 1)
	{
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}
	/* Open the file for reading */
	char *str = NULL;
	size_t size = 0;
	ssize_t lsize;
	bool status;
	FILE *fp;
	if(argc == 2)
	{
		str = (char*)malloc(1 * (sizeof(char)));
		while(fgets(str,500, stdin) != NULL)
		{
			status = stringExist(str, argv[1]);
			if(status == true)
			{
				printf("%s\n", str);
			}
		}
			
	}
	int k = 2;
	/* Loop through until we are done with the files name. */
	while(k < argc)
	{
		status = false;
  
		fp = fopen(argv[k], "r");
		if (!fp)
		{
			printf("wgrep: cannot open file\n");
			exit(1);
		}

		/* Get the first line of the file. */
		lsize = getline(&str, &size, fp);
		status = stringExist(str, argv[1]);
		if(status == true)
		{
			printf("%s\n", str);
		}
		/* Loop through until we are done with the file. */
		while (lsize >= 0)
		{
			status = false;
			/* Get the next line */
			lsize = getline(&str, &size, fp);
			if(lsize != -1)
			{
				status = stringExist(str, argv[1]);
				if(status == true)
				{
					
					printf("%s", str);
				}
			}
		}
		/* Closing file */
		fclose(fp);
		k++;
	}
	/* Free space */
	free(str);
	str = NULL;
 	return 0;
}
