#include"config.h"

unsigned int top    = 10,
             left   = 10,
             width  = 500,
             height = 300;

unsigned int font_size = 32;

char** bins;
int bins_amount =256;
int current_dir_entry = 0;

Color background_color = BLACK;
Color selection_color = BLUE;
Color text_color = WHITE;
Color selected_text_color = YELLOW;

char* PATH = NULL;


extern void free_bins(void)
{
  for(int i = 0;i<bins_amount;++i)
    {
      free(bins[i]);
    }
  free(bins);
}
void read_path(void)
{
  PATH = getenv("PATH");
  if(!PATH)
    {
      fprintf(stderr,"smenu error: failed to read $PATH!\n");
      exit(-2);
    }
  bins = malloc(sizeof(char*)*bins_amount);
  if(!bins)
    {
      fprintf(stderr,"smenu error: failed malloc...");
      exit(-2);
    }
  else
    for(int i = 0;i<bins_amount;++i)
      {
	bins[i] = malloc(PATH_MAX);
	if(!bins[i])
	  {
	    fprintf(stderr,"smenu error: failed malloc...");
	    exit(-2);
	  }
      }
    
  char* token = strtok(PATH,":");
  while(token != NULL)
  {
    if(read_dir(token))
      {
	
      }
    
    token = strtok(NULL,":");    
  }
}
int read_dir(char* dir)
{
  DIR* d = opendir(dir);
  if(!d)
    {
      fprintf(stderr,"smenu error: failed to open '%s' directory!\n");
      return 0;
    }
  struct dirent *_dir;
  while((_dir = readdir(d)) != NULL)
    {
      if(_dir->d_type == DT_REG ||
	 _dir->d_type == DT_LNK)	
	{
	  if(current_dir_entry < bins_amount)	    
	    strcpy(bins[current_dir_entry++],_dir->d_name);	    
	  else
	    {
	    }
	}
    }
  closedir(d);

  for(int i = 0;i<bins_amount;++i)
    {
      printf("%s\n",bins[i]);
    }
}


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
