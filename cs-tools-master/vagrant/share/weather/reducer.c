#include <stdio.h>
#include <string.h>
int max(int a, int b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}


int main(int argc, char *argv[]){
	char line[2048];
	char last_key[5];
	int max_val = 0;

	last_key[0] = '\0';

	while(fgets(line, 1024,stdin) != NULL){
		char key[5];
		int val;
		sscanf(line, "%s %d", key, &val);

		//printf("year = %s temp = %d\n", key, val);
		if(last_key[0] != '\0' && strcmp(last_key, key)){
			printf("%s\t%d\n", last_key, max_val);
			strcpy(last_key, key);
			max_val = val;
		}
		else{
			strcpy(last_key, key);
			max_val = max(max_val, val);

		}
	}
	printf("%s\t%d\n", last_key, max_val);
	return 0;

}
