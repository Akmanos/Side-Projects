#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>


/*create a struct*/
typedef struct{
	int a;
	int b;
}val;

int main(int argc, char **argv){
	val mul;
	//dynamically allocate memory
	char *input=(char *) malloc(50*sizeof(char));
	int a;
	int b;
	//prompt user for input
	printf("Enter an int a: ");
	fgets(input, 100, stdin);
   //check for valid input
	if(input == NULL || !isdigit(input[0])){
		printf("Invalid input: %s", input);
	}
	//strtoimax performs additional input checks
	a = strtoimax(input, (char **)NULL, 10);
	//assign it to the struct
	mul.a = a;
   
	//now do the same for b
	printf("Now enter an int b: \n");
	fgets(input, 100, stdin);
   if(input == NULL || !isdigit(input[0])){
		printf("Invalid input");
	}
	b = strtoimax(input, (char **)NULL, 10);
	mul.b = b;
	//do something with the data
	int product = (mul.a) * (mul.b);
	printf("The product of a*b is: %d\n", product);
	//deallocate memory
	free(input);
	return 0;
}
