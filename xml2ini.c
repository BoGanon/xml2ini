#include <stdio.h>
#include <string.h>
#include <expat.h>

typedef struct {
	int num;
	char A;
	char B;
	char C;
	char ox;
	char oy;
	char wid;
	char hgt;
	double X1;
	double Y1;
	double X2;
	double Y2;
} inidata_t;

typedef struct {
	int numchars;
	int spacewidth;
	inidata_t *inidata;
} fontdata_t;

static void startElement(void *userData, const char *name, const char **atts)
{
	int i;

	static int j = 0;

	int *depthPtr = (int *)userData;

	//for (i = 0; i < *depthPtr; i++)
	//	putchar('\t');

	if (!strcmp(name,"font"))
	{
		printf("[Header]\r\n");
		for (i = 0; atts[i]; i += 2)
		{
			if (!strcmp(atts[i],"numchars"))
			{
				printf("NumFont=%d\r\n",atoi(atts[i+1]));
			}
			if (!strcmp(atts[i],"spacewidth"))
			{
				printf("SpaceWidth=%d\r\n",atoi(atts[i+1]));
			}
		}
		printf("\r\n[FontData]\r\n");
	};

	if (!strcmp(name,"chardata"))
	{
		for (i = 0; atts[i]; i += 2)
		{
			if (!strcmp(atts[i],"char"))
			{
				printf("%dChar=%d\r\n",j,atoi(atts[i+1]));
			}

			if (!strcmp(atts[i],"A"))
			{
				printf("%dA=%d\r\n",j,atoi(atts[i+1]));
			}

			if (!strcmp(atts[i],"B"))
			{
				printf("%dB=%d\r\n",j,atoi(atts[i+1]));
			}

			if (!strcmp(atts[i],"C"))
			{
				printf("%dC=%d\r\n",j,atoi(atts[i+1]));
			}

			if (!strcmp(atts[i],"ox"))
			{
				printf("%dox=%d\r\n",j,atoi(atts[i+1]));
			}

			if (!strcmp(atts[i],"oy"))
			{
				printf("%doy=%d\r\n",j,atoi(atts[i+1]));
			}

			if (!strcmp(atts[i],"wid"))
			{
				printf("%dWid=%d\r\n",j,atoi(atts[i+1]));
			}

			if (!strcmp(atts[i],"hgt"))
			{
				printf("%dHgt=%d\r\n",j,atoi(atts[i+1]));
			}

			if (!strcmp(atts[i],"X1"))
			{
				printf("%dX1=%.10g\r\n",j,atof(atts[i+1]));
			}

			if (!strcmp(atts[i],"Y1"))
			{
				printf("%dY1=%.10g\r\n",j,atof(atts[i+1]));
			}

			if (!strcmp(atts[i],"X2"))
			{
				printf("%dX2=%.10g\r\n",j,atof(atts[i+1]));
			}

			if (!strcmp(atts[i],"Y2"))
			{
				printf("%dY2=%.10g\r\n",j,atof(atts[i+1]));
			}

		}

		j++;

	}

	*depthPtr += 1;

}

static void endElement(void *userData, const char *name)
{
	int *depthPtr = (int *)userData;
	*depthPtr -= 1;
}

void usage(void)
{
	printf("Usage: xml2ini infile > outfile\n");
}

int main(int argc, char **argv)
{
	int i;
	int done = 0;
	int size;
	FILE *file;
	char buffer[BUFSIZ];
	int depth = 0;

	for (i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i],"--help"))
		{
			usage();
			return 0;
		}
	}

	if (argc != 2)
	{
		usage();
		return 0;
	}

	file = fopen(argv[1],"r");

	if (file == NULL)
	{
		usage();
		return 0;
	}

	XML_Parser parser = XML_ParserCreate("UTF-8");
	XML_SetUserData(parser, &depth);
	XML_SetElementHandler(parser, startElement, endElement);

	while(!done)
	{
		if ((size = fread(buffer,1,sizeof(buffer),file)) < sizeof(buffer))
		{
			done = 1;
		}

		if (XML_Parse(parser, buffer, size, done) == XML_STATUS_ERROR)
		{
			printf("Error parsing XML file");
		} 

	}

	XML_ParserFree(parser);

	return 0;
}
