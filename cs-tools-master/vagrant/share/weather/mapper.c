#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	char line[4096], year[5], temp[6], q;

	while(fgets(line, 1024, stdin) != NULL){
		//puts(line);
		year[0] = line[15];
		year[1] = line[16];
		year[2] = line[17];
		year[3] = line[18];
		year[4] = '\0';


		q = line[92];
		
		temp[0] = line[87];
		temp[1] = line[88];
		temp[2] = line[89];
		temp[3] = line[90];
		temp[4] = line[91];
		temp[5] = '\0';


		int t1 = !strcmp(temp, "+9999");
		int t2 = q == '0' || q =='1' || q == '4' || q == '5' || q =='9';

  		if(!t1 && t2){
  			printf("%s\t %s\n",year, temp);
  			//printf("year = %s\n", year);
  		}
		//printf("[[%s]] \n", line);
	}

	return 0;
}
