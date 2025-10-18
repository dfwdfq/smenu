#include"config.h"

unsigned int top    = 10,
             left   = 10,
             width  = 500,
             height = 300;

unsigned int font_size = 32;

unsigned int x_start  = 15,
             y_start  = 15;

Color background_color = {10,10,21,150};
Color selection_color = {231,207,255,255};
Color text_color = {240,240,255,255};


void parse_argv(int argc, char **argv)
{  
  opterr = 0;
  
  int c;
  while((c = getopt(argc,argv,"t:w:h:l:")) != -1)
    {
      switch (c)
	{
	case 't':
	  top = atoi(optarg);
	  break;
	case 'l':
	  left = atoi(optarg);
	  break;
	case 'w':
	  width = atoi(optarg);
	  break;
	case 'h':
	  height = atoi(optarg);
	  break;
	case '?':
	  {
	    if(optopt)
	      fprintf(stderr,"Error: Option -%c requires an argument.\n",optopt);
	    else
	      fprintf(stderr,"Error: Unknown option: %s\n",argv[optind-1]);

	    exit(-1);
	  }
	  break;
	}
    }
}
