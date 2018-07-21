
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<unistd.h>

int main()
{
	FILE *pFile;
	long lSize;
	char *buffer;
	size_t result;
	pFile = fopen ( "myfile.txt" , "rb" );
	if (pFile == NULL)
	{
		    fputs ("File error", stderr);
			    exit (1);
	}

	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	buffer = (char *) malloc (sizeof(char) * lSize);
	if (buffer == NULL)
	{
		    fputs ("Memory error", stderr);
			    exit (2);
	}

	result = fread (buffer, 1, lSize, pFile);
	if (result != lSize)
	{
		    fputs ("Reading error", stderr);
			    exit (3);
	}


	fclose (pFile);
	free (buffer);
	return 0;
	// obtain file size:
	// fseek (pFile , 0 , SEEK_END);
	// lSize = ftell (pFile);
	// rewind (pFile);
	// // allocate memory to contain the whole file:
	// buffer = (char *) malloc (sizeof(char) * lSize);
	// if (buffer == NULL)
	// {
	//     fputs ("Memory error", stderr);
	//         exit (2);
	//         }
	//         // copy the file into the buffer:
	//         result = fread (buffer, 1, lSize, pFile);
	//         if (result != lSize)
	//         {
	//             fputs ("Reading error", stderr);
	//                 exit (3);
	//                 }
	//
	//                 /* the whole file is now loaded in the memory buffer. */
	//                 // terminate
	//                 fclose (pFile);
	//                 free (buffer);
	//                 return 0;
	//FILE * pFile;
	//int n;
	//char name [100];
	//pFile = fopen ("myfile.txt","w");
	//for (n=0 ; n<3 ; n++)
	//{
	//	puts ("please, enter a name: ");

	//	gets (name);
	//	fprintf (pFile, "Name %d [%-10.10s]\n",n+1,name);
	//}
	//fclose (pFile);
	//return 0;
	//char str [80];
	//float f;
	//FILE *pFile;
	//pFile = fopen ("myfile.txt", "w+");
	//fprintf (pFile, "%f %s", 3.1416, "PI");
	//rewind (pFile);
	//fscanf (pFile, "%f", &f);
	//fscanf (pFile, "%s", str);
	//fclose (pFile);
	//printf ("I have read: %f and %s \n", f, str);
	//return 0;
	//printf ("Characters: %c %c \n", 'a', 65);
	//printf ("Decimals: %d %ld\n", 1977, 650000L);
	//printf ("Preceding with blanks: %10d \n", 1977);
	//printf ("Preceding with zeros: %010d \n", 1977);
	//printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100
	//			, 100);
	//printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
	//printf ("Width trick: %*d \n", 5, 10);
	//printf ("%s \n", "A string");

	//return 0;
	////char str [80];
	//int i;
	//printf ("Enter your family name: ");
	//scanf ("%79s", str);
	//printf ("Enter your age: ");
	//scanf ("%d", &i);
	//printf ("Mr. %s , %d years old.\n", str, i);
	//printf ("Enter a hexadecimal number: ");
	//scanf ("%x", &i);
	//printf ("You have entered %#x (%d).\n", i, i);
	//return 0;
}
	//char string[200];
	//FILE* p_file = NULL;
	//p_file = fopen("myfile.txt", "a");
	//if(p_file == NULL)
	//  perror("open error");
	//printf("enter string\n");
	//fgets(string, 200, stdin);
	//fputs(string, p_file);
	//else
	//{
	//	if (fgets(string, 200, p_file) != NULL)
	//	{
	//		puts(string);
	//	}
	//}
//	fclose(p_file);
//	return 0;

	//printf("输入一句话\n");
	//gets(string);
	//puts(string);
	//printf("%s\n", string);
	//return 0;
	//int c = 0;
	//int n = 0;
	//FILE* p_file;
	//p_file = fopen("myfile.txt", "wt");
	//if(p_file == NULL)
	//{
	//	perror("error file open");
	//	//exit(EXIT_FAILURE);
	//}
	//else
	//{
	//	for(c = 'a'; c<='z'; c++)
	//	{
	//		putc(c, p_file);
	//	}
	////	do
	////	{
	////		c = getc(p_file);
	////		if(c == '$') n++;
	////	}
	////	while(c != EOF);
	//}
	//fclose(p_file);

	////printf("%d $\n", n);
	//return 0;
