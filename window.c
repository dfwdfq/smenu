#include"window.h"

char input[STR_BUF_LEN] = "\0";
int letter_counter = 0;
int current_selection = -1;

int read_input(int matches_amount)
{
  if(IsKeyPressed(KEY_ENTER))return 1;
  
  if(IsKeyPressed(KEY_BACKSPACE) &&
     letter_counter != 0)
    {
      letter_counter--;
      input[letter_counter] = '\0';
      return 0;
    }
  if(IsKeyReleased(KEY_DOWN) &&
     matches_amount > 0)
    {
      if(current_selection + 1 < matches_amount)
	current_selection++;
      return -1;
    }
  if(IsKeyReleased(KEY_UP) &&
     current_selection != -1)
    {
      current_selection--;
    }
  
  int key = GetCharPressed();
  if((key >= 32) && (key <= 126))//allow only printable characters
    {
      input[letter_counter] = (char)key;
      letter_counter++;
      input[letter_counter] = '\0';
    }

  if(key <= 0)return -1;
  if(letter_counter+1 == STR_BUF_LEN) return 1;
  
  return 0;
}
