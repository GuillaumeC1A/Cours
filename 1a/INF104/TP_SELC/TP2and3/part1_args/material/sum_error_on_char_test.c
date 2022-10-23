#include <stdio.h>
#include <string.h>

void display_message(char * message)
{
  printf(message);
}

char isCharInteger(char c);
//Declaring in order to use before implementation (call without knowing what it does first but still knowing whqt it is)

int main(int argc, char *argv[]) {
  /* to be completed */
  // next line just shows how to use display_message; could be removed
  display_message("PogStart\n");

  // first, check that the number of parameters is correct
  
  if(argc != 3) 
    return printf("Wrong usage, 2 parameters expected : ./sum parameter1 parameter2");
  
  // now, check that parameters represent integer values
  // declare, implement, and use function isCharInteger
  int i = 0;
  for(i; i < argc; i++) {
    
	char * charg = argv[i]; int j = 0;
    
	//As we get our parameters from argv, we have to be cautious :
    //we don't look into argv[i] directly, but in charg[j] which is more like argv[i][j]
    //This is why we use char* and not char directly. 
    
	while(charg[j] != '\0') {
      
	  //The condition here is simple : while we don't see the ending charachter, we keep going
      char arg = charg[j];
	  if(isCharInteger(arg) == 0)
	  	return printf("Invalid Format, expected char");
	  j++; 	
	}
    
  }
  //return 0;
}

char isCharInteger(char c) {
  switch(c) {
  case '0':
    return 1;
  case '1':
    return 1;
    //We return the same thing for all numbers as they all correspond to the same usage of the function = the right one.
  case '2':
    return 1;
  case '3':
    return 1;
  case '4':
    return 1;
  case '5':
    return 1;
  case '6':
    return 1;
  case '7':
    return 1;
  case '8':
    return 1;
  case '9':
    return 1;
  //To test if a char is a number, we just ask him if, digit by digit, it's a number. The switch case is a bit raw but gets the job done. 
  //NotJava -- case default:
  return 0;
  }
  //We only try for 0-9 results as mentionned in the subject
}
//We don't implement anything more yet, we just check the entries are correct
