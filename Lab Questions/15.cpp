#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(){
	extern char **environ;
	while(*environ){
		if(strncmp(*environ, "USER", 4)==0){
			printf("%s\n",*environ);
		}
		environ++;
	}


}

