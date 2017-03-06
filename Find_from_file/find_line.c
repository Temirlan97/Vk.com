#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
done by: Temirlan Ulugbek uulu
for Vk
*/

/*
Short description of the code:
	This solution uses Trees to store every line in the file.
	Later takes input from stdin until "exit" is typed.
	Traverses tree and gives "YES" and "NO" answers accordingly.
*/
#define SZ (127-32+1)

struct tries{
	char c;
	struct tries * leafs[SZ];
	short last;//is it the last character if the line? 
} typedef Tree;


void tree_insert (Tree * r, char * str){
	if (*str == '\0'){
		return;
	}
	Tree * t_ptr = r -> leafs[(int)(*str)-32];
	Tree * prev = r;
	char last_c = *str;
	while (*str != '\0'){
		if (t_ptr == NULL){
			t_ptr = (Tree*) malloc(sizeof(Tree));
			if (t_ptr == NULL){
				printf("Couldn't allocate memory for node\n");
				exit(1);
			}
			t_ptr -> c = *str;
			t_ptr -> last = 0;
		}
		prev -> leafs[(int)last_c-32] = t_ptr;
		last_c = *str;
		prev = t_ptr;
		t_ptr = t_ptr -> leafs[(int)(*str)-32];
		str++;
	}
	prev -> last = 1;
}

void find(Tree * r, char * str){
	if (*str == '\0'){
		printf("NO\n");
		return;
	}
	Tree * t_ptr = r -> leafs[(int)(*str)-32];
	short yes = 0;
	while(*str != '\0'){
		//printf("Have %c?\n", *str);
		if (t_ptr == NULL){
			printf("NO\n");
			return;
		}
		yes = t_ptr -> last;
		t_ptr = t_ptr -> leafs[(int)(*str)-32];
		str++;
	}
	if (yes)
		printf("YES\n");
	else{
		printf("NO\n");
	}
}

int main (){
	char file_name[100];
	fgets(file_name, sizeof(file_name), stdin);
	file_name[strlen(file_name)-1] = '\0';
	FILE * fp = fopen(file_name, "r");
	if (fp == NULL){
		printf("Couldn't open the file\n");
		exit(1);
	}
	Tree * r;//root
	r = (Tree*) malloc(sizeof(Tree));
	if (r == NULL){
		printf("Failed to create root\n");
		exit(1);
	}
	char line[1000];
	while(fgets(line, sizeof(line), fp)){
		tree_insert(r, line);
	}
	while(1){
		fgets(line, sizeof(line), stdin);
		if (strcmp(line, "exit\n") == 0){
			break;
		}
		find(r, line);
	}
	fclose(fp);
	return 0;
}