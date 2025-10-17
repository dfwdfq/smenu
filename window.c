#include"window.h"

char input[STR_BUFFER_LEN+1] = "\0";
int letter_counter = 0;


int read_input(void)
{
  if(IsKeyPressed(KEY_ENTER))return 1;
  
  int key = GetCharPressed();
  if((key >= 32) && (key <= 126))//allow only printable characters
    {
      input[letter_counter] = (char)key;
      letter_counter++;
      input[letter_counter] = '\0';
    }

  if(key <= 0)return 0;
  if(letter_counter == STR_BUFFER_LEN) return 1;
  
  return -1;
}
