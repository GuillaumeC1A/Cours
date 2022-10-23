#include <stdio.h>
#include <string.h>
#include <math.h>
void display_message(char * message)
{
  printf(message);
}

char isCharInteger(char c);
char charToInteger(char c);
char stringToInteger(char* c);
char isStringInteger(char* c);
//Declaring everything needed in order to use before implementation (call without knowing what it does first but still knowing whqt it is)

int main(int argc, char *argv[]) {
  display_message("progstart\n");

  // first, check that the number of parameters is correct
  
  if(argc != 3) 
    return printf("Wrong usage, 2 parameters expected : ./sum parameter1 parameter2");
  
  // now, check that parameters represent integer values
  // declare, implement, and use function isCharInteger
  int i = 1;
  for(i; i < argc; i++) {
    
	char* charg = argv[i]; int j = 0;
    
	//As we get our parameters from argv, we have to be cautious :
    //we don't look into argv[i] directly, but in charg[j] which is more like argv[i][j]
    //This is why we use char* and not char directly. 
    
	if (charg[j]=='-')
      j++;
    //For relative numbers
	
	while(charg[j] != '\0') {
	  //The condition here is simple : while we don't see the ending character, we keep going
      char arg = charg[j];
	  if(isCharInteger(arg) == 1) {
	    printf("Wrong usage, param1 and param2 should be integers/char when executing./sum param1 param2. Invalid Format");
	    return -1;
	    }
	  j++; 	
	}
  }
  char c1 = stringToInteger(argv[1]); char c2 = stringToInteger(argv[2]);
  printf("The sum of your entries is %d", c1+c2);

  return 0;
}

char isCharInteger(char c) {
  switch(c) {
  case '0':
    return 0;
  case '1':
    return 0;
//0 for "it's ok keep going" and any other (-1,1,2...) for "something's wrong".
  case '2':
    return 0;
  case '3':
    return 0;
  case '4':
    return 0;
  case '5':
    return 0;
  case '6':
    return 0;
  case '7':
    return 0;
  case '8':
    return 0;
  case '9':
    return 0;

  } 
  return 1;
}

char charToInteger(char c)
{
  switch(c) {
  case '0':
    return 0;
  case '1':
    return 1;
  case '2':
    return 2;
  case '3':
    return 3;
  case '4':
    return 4;
  case '5':
    return 5;
  case '6':
    return 6;
  case '7':
    return 7;
  case '8':
    return 8;
  case '9':
    return 9;
}
  printf("I don't know how you ended up here... But next time, use an int-convertible char");
  return -1;
}

//Just adding another function to check if a given string is an integer. (a combination of integers, really)
char isStringInteger(char * c)
{
    int i=0;
    if (c[i] == '-')
      i++;
    while(c[i]!='\0')
    {
      char c1 = c[i];
      if(isCharInteger(c1)==1)
      	return 1;
      i++;
    }
    return 0;
}
char stringToInteger(char * c)
{
  
  if (isStringInteger(c) == 1) {
  	printf("The given string can't be converted to an integer.");
  	return 1;
   } //Proper coding implies verifying we can do things before actually doing them.
  
  int sign = 1; int sml = 0;
  if (c[0]='-'){
    sign = -1;
    sml = 1;
  } //Taking care of the sign issue. Problem is it occupies a slot in the table. That's what sml is used for. 
  
  int i = sml + 0; int c_tmp = 0; int c_len = 0;
  while (c[i] != '\0') {
    i++;
  	c_len++;
  }
  c_len -= 1; i = c_len;
  for (i; i>= 0 + sml; i--)
    c_tmp += charToInteger(c[i])*pow(10,c_len-i+1);
  return sign*c_tmp;
}
