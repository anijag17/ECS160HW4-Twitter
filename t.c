#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int SIZE = 20000;  //size will not exceed 20k

struct tweeter {  //data
    char name[56];
    int tweetCount;
};

struct pair {
  char key[56];
  struct tweeter data;
};

//https://stackoverflow.com/questions/2624192/good-hash-function-for-strings
int hashf(char* name){
  int size = strlen(name);
  int hash = 7;
  for (int i = 0; i < size; i++) {
    hash = hash*31 + (int)name[i];
  }
  return abs(hash%SIZE);
}

//function
int put(struct pair* table,char* name){
  printf("start put ");
  printf("%s %d\n",name,hashf(name));
  int hash = hashf(name);
  if (!strcmp(table[hash].key,name)){  //result of hash has same name
    table[hash].data.tweetCount++;     //increase the count
    return 0;
  }
  else if (!strcmp(table[hash].key,"\0")){ //bucket has not been initialized
    strcpy(table[hash].key,name);
    strcpy(table[hash].data.name,name);
    table[hash].data.tweetCount++;
    return 0;
  }
  else {  //collision :(
    /* todo */
    int inc = hash++;
    while (strcmp(table[inc].key,name)){ //while they do not equal each other, check gthe next one
      if (table[inc].data.tweetCount == 0){ //if it is empty,place in this bucket
        strcpy(table[inc].key,name);
        strcpy(table[inc].data.name,name);
        table[inc].data.tweetCount++;
        return 0;
      }
      else inc++;
    }
    //found here
    strcpy(table[inc].key,name);
    strcpy(table[inc].data.name,name);
    table[inc].data.tweetCount++;
    return 0;
  }
}


int getTweeterLocation(char* parse){
	int find = -1;
	char* token;
	int count = 0;
	token = strtok(parse,",");
	while (token != NULL) {
		if (!strcmp(token,"\"name\"")){
			find = count;
			break;
		}
		count++;
		token = strtok(NULL,",");
	}
	return find;
}

char* getName(char* parse, int location){
	char* token;
	token = strtok(parse,",");
	for (int i = 0; i < location; i++){
		token = strtok(NULL,",");
	}
	//printf("n: %s\n",token);
	return token;
}

int main(int argc, char** argv){
  //checks
  if (argc != 2){
		return -1;
	}
	FILE *fp=fopen(argv[1], "r");
	if (fp == NULL){
		return -1;
	}

	char parse[512];
	if( fgets (parse, sizeof(parse), fp)==NULL ){
		return -1;
	}
  int location = getTweeterLocation(parse);
  if (location == -1)
    return -1;
  //end of checks
  struct pair table[SIZE];
  struct pair init;
  strcpy(init.key,"\0");
  strcpy(init.data.name,"\0");
  init.data.tweetCount = 0;
  for (int i = 0; i < SIZE; i++){
    table[i] = init;
  }
  //table initialized
  char* curr;
  while (fgets(parse,sizeof(parse),fp)!= NULL){
    curr = getName(parse,location);
    put(table,curr);
  }

  for (int i = 0; i < SIZE; i++){
    if (table[i].data.tweetCount != 0){
      printf("%s %d\n",table[i].key,table[i].data.tweetCount);
    }
  }

}
