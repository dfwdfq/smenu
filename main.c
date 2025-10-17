#include"config.h"
#include"window.h"
#include"directory.h"
#include"prefix_match_search.h"

int main(int argc, char** argv)
{
  parse_argv(argc,argv);
  read_path();
  
  InitWindow(width,height,"smenu");
  SetWindowPosition(left,top);
  SetTargetFPS(60);
  DisableCursor();
  SetTraceLogLevel(LOG_NONE);
  SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);

  Font df = GetFontDefault();
  Vector2 size = MeasureTextEx(df,"f",font_size,1);  
  int y_match_start = y_start+(int)size.y+2;
  int max_visible = GET_MAX_VISIBLE(size.y);
  
  char **matches = NULL;
  int matches_amount = 0;
  
  while(!WindowShouldClose())
    {
      int input_status = read_input(matches_amount);
      if(input_status == 1 && matches != NULL)
	{	  
	  //launch app
	  char* output = NULL;
	  if(get_fullpath(matches[current_selection],&output))
	    {
	      launch_process(output);
	    }
	  else break; //something went wrong
	}	
      else if(input_status == 0)
	{
	  free(matches);
	  matches = NULL;
	  matches_amount = 0;

	  if(!collect_prefix_matches(bins,
				    bins_amount,
				    input,
				    &matches,
				    &matches_amount))
	    {
	      matches = NULL;
	      matches_amount = 0;
	    }
	}

      if (matches_amount > 0)
	{
	  if (current_selection < 0) current_selection = 0;
	  if (current_selection >= matches_amount) current_selection = matches_amount - 1;
        }
      else
	{
	  current_selection = 0;
        }

      int page_start = 0;
      if (matches_amount > 0 && max_visible > 0)
	{
	  page_start = current_selection - max_visible / 2;
	  if (page_start < 0) page_start = 0;
	  if (page_start > matches_amount - max_visible)
	    {
	      page_start = matches_amount - max_visible;
	      if (page_start < 0) page_start = 0;
	    }
	}
		
      BeginDrawing();
      ClearBackground(background_color);


      DrawText(input,x_start,y_start,font_size,text_color);
      
      y_match_start = y_start+(int)size.y+2;
      int draw_count = (matches_amount - page_start < max_visible) 
	                 ? matches_amount - page_start 
                         : max_visible;
      
      for(int i = 0;i< draw_count;++i)
	{
	  int global_index = page_start + i;
	  
	  Color col = current_selection == global_index?selection_color:text_color;
	  DrawText(matches[global_index],x_start,y_match_start,font_size,col);
	  y_match_start+=(int)size.y+2;
	}

      EndDrawing();     
      }

  free_bins();
  return 0;
}
