#define _DEFAULT_SOURCE
#include"directory.h"

char** bins;
int bins_amount = STR_BUF_LEN;
int current_dir_entry = 0;

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
	bins[i] = malloc(STR_BUF_LEN);
	if(!bins[i])
	  {
	    fprintf(stderr,"smenu error: failed malloc...");
	    exit(-2);
	  }
      }

  char PATH_copy[strlen(PATH)+1];
  strcpy(PATH_copy,PATH);
  char* token = strtok(PATH_copy,":");
  while(token != NULL)
  {
    if(!read_dir(token))
      {	
	fprintf(stderr,"smenu error: failed to read '%s' directory!\n",token);
      }
    
    token = strtok(NULL,":");    
  }

  //free unused space
  if(current_dir_entry < bins_amount)
    {
      for(int i = current_dir_entry+1;i<bins_amount;++i)
	free(bins[i]);
      bins_amount = current_dir_entry;
    }

  //sort alphabeticaly
  qsort(bins,bins_amount,sizeof(char*),_strcmp);
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
	      char** temp = (char**)realloc(bins,sizeof(char*)*(bins_amount+STR_BUF_LEN));
	      if(!temp)
	      {
	        free_bins();
		closedir(d);
		return 0;
	      }
	  
	      bins = temp;
	      for(int i = bins_amount;i<bins_amount+STR_BUF_LEN;++i)
		{
		  bins[i] = malloc(STR_BUF_LEN);
		  if(!bins[i])
		    {
		      fprintf(stderr,"smenu error: failed memory allocation...\n");
		      for(int j = bins_amount;j<i;++j)free(bins[j]);
		      free_bins();
		      closedir(d);
		      return 0;
		    }
		}
	      bins_amount+=STR_BUF_LEN;
	      strcpy(bins[current_dir_entry++],_dir->d_name);
	    }
	}
    }
  closedir(d);
  return 1;
}
int get_fullpath(char *bin, char **output)
{
  char PATH_copy[strlen(PATH)+1];
  strcpy(PATH_copy,PATH);
  
  char* token = strtok(PATH_copy,":");
  char match_buf[STR_BUF_LEN];
  while(token != NULL)
  {
    int len = sprintf(match_buf,"%s/%s",token,bin);
    match_buf[len] = '\0';
    if(access(match_buf,F_OK | X_OK) == 0)
      {
	(*output) = malloc(strlen(match_buf)+1);
	if(!*output)return 0;
	strcpy(*output,match_buf);
	return 1;
      }
    
    token = strtok(NULL,":");    
  }
  return 0;
}
void launch_process(char* full_path)
{
    if (access(full_path, X_OK) != 0)
      {
        perror("Not executable");
        exit(126);
    }

    execv(full_path, (char *[]){ full_path, NULL });

    perror("execv failed");
    exit(127);
}
