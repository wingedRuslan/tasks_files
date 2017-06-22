/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{   
	if (argc != 2)
	{
		fprintf(stderr, "Include card.raw");
		return 1;
	}


	FILE* file = fopen("card.raw", "r");
	
	if (file == NULL)	
    {		
        	fclose(file);			
			fprintf(stderr, "Could not open card.raw");

        	return 1;
    }

	FILE* img;      // found .jpg file

	int count = 0 ; // counts jpg files 
	
	char title[10]; // stores the name of current opened file

	unsigned char buffer[512];   // buffer[0] may contain hex = 240
				     // so unsigned is used
	
	while (fread(&buffer, 512, 1, file))
	{	
		// start of a new .jpg ?
		if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] ==0xff) && ((buffer[3] == 0xe0) || (buffer[3] == 0xe1)))
		{
			
			count++;
		
			// just for the first case
			if (count > 1)	
				fclose (img);

						
			// name a found file
			
			sprintf (title, "%03d.jpg", count-1);		 
			img = fopen (title, "a");

		}
        	// If currently writing to file, write buffer
		if (count > 0)
			fwrite (&buffer, 512, 1, img);
	}

	fclose(img);
    fclose(file);

	return 0;
}
