#include"config.h"
#include"window.h"
int main(int argc, char** argv)
{
  parse_argv(argc,argv);

  InitWindow(width,height,"smenu");
  SetWindowPosition(left,top);
  SetTargetFPS(60);
  DisableCursor();
  SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);

  while(!WindowShouldClose())
    {
      

      
      BeginDrawing();
      ClearBackground(background_color);
      EndDrawing();     
    }
  
  return 0;
}
