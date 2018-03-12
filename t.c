#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int SIZE = 20000;  //size will not exceed 20k

struct tweeter {  //data
    char name[16];
    int tweetCount;
};

struct pair {
  char key[16];
  struct tweeter data;
};

//https://stackoverflow.com/questions/2624192/good-hash-function-for-strings
int hashf(char* name){
  int size = strlen(name);
  int hash = 7;
  for (int i = 0; i < size; i++) {
    hash = hash*31 + name[i];
  }
  return hash%SIZE;
}

//function
int put(struct pair* table[SIZE],char* name){
  int hash = hashf(name);
  if (!strcmp(table[hash]->key,name)){  //result of hash has same name
    table[hash]->data.tweetCount++;     //increase the count
  }
  else if (!strcmp(table[hash]->key,"\0")){ //bucket has not been initialized
    strcpy(table[hash]->key,name);
    strcpy(table[hash]->data.name,name);
    table[hash]->data.tweetCount++;
  }
  else {  //collision :(
    /* todo */
    //int inc = hash++;
    //while (!strcmp(*table[inc].key.name,))
    printf("collision\n");
    return -1;
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
  struct pair table[SIZE];
  struct pair init;
  strcpy(init.key,"\0");
  strcpy(init.data.name,"\0");
  init.data.tweetCount = 0;
  for (int i = 0; i < SIZE; i++){
    table[i] = init;
  }


}
