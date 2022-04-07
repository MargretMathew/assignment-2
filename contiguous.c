#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SIZE 1048576

struct hashmap {
	char key[25];
	int start;
	int end;
	bool active;
};

int map_i = 0;
struct hashmap *map;

bool isCMD(char *,char *);
void rq(char *);
void initialize(char **);
void stat();
void rl(char *);
int* firstfit(int);
int* bestfit(int);

int main() {
	map = malloc(sizeof(struct hashmap)*25);
	// char *memory = malloc(MAX_SIZE+1);
	bool next = true;
	char cmd[50];
	while(next) {

		printf("allocator> ");
		fgets(cmd, 50, stdin);
		if(isCMD(cmd,"x") || isCMD(cmd,"X")) {
			printf("Exit\n");
			next = false;
		} else if(isCMD(cmd,"RQ")) {
			rq(cmd);
		}
		else if(isCMD(cmd,"RL")) {
			rl(cmd);
		}
		else if(isCMD(cmd,"C")) {
			printf("Continue C\n");
		}
		else if(isCMD(cmd,"STAT")) {
			stat();
		}
		else {
			printf("invalid command");

		}
	}

	return 0;
}

bool isCMD(char *inp,char *exp) {
	int n = strlen(exp);
	for(int i=0; i<n; i++) {
		if(inp[i]!=exp[i]) {
			return false;
		}
	}
	return true;
}

void rq(char *command) {
	int pos=0;
	char process[50];
	char size[7];
	char mode;
	int s=0;
	for(int i=3,j=0; i<strlen(command); i++) {
		// printf("%c-",command[i]);
		if(command[i]==' ') {
			pos++;
			j=0;
			continue;
		}
		if(pos==0) {
			// printf("%c-",command[i]);
			process[j++]=command[i];	
		}
		if(pos==1) {
			size[j++]=command[i];
		}
	}
	sscanf(size, "%d", &s);
	mode = command[strlen(command)-2];
	// printf("process: %s, size: %d, mode: %c\n",process,s,mode);
	if((s<1)||(s>MAX_SIZE)) {
		printf("invalid/insufficient memory\n");
		return;
	}
	int *start_end;
	if(mode=='F') {
		start_end = firstfit(s);
	}else if (mode=='B') {
		start_end = bestfit(s);
	}else if (mode=='W') {
		printf("indevelopment");
	}else {
		printf("Invalid Mode\n");
		return;
	}
	struct hashmap m;
	// *m.key = &process;
	strncpy(m.key,process,25);
	m.start = start_end[0];
	m.end = start_end[1];
	m.active = true;
	map[map_i++] = m;
}

void stat() {
	for(int i=0; i<map_i; i++) {
		if(map[i].active) {
			printf("process: %s, start: %d, end: %d\n",map[i].key, map[i].start, map[i].end);
		}
		
	}
}

void rl(char *command) {
	int pos=0;
	char process[50];
	for(int i=3,j=0; i<strlen(command); i++) {
		if(command[i]==' ') {
			pos++;
			j=0;
			continue;
		}
		if(pos==0) {
			process[j++]=command[i];	
		}
	}

	for(int i=0; i<map_i; i++) {
		if((map[i].active) && (isCMD(process,map[i].key))) {
			map[i].active = false;
		}
		
	}
}
int* firstfit(int s) {
	int p_start, p_end, count=0, r=0, c_start;
	int *result = malloc(sizeof(int) * 2);
	for(int i=0; i<=map_i; i++) {
		if(!(map[i].active || i==map_i)) {
			continue;
		}
		if(i==map_i) {
			c_start = MAX_SIZE;
		}else {
			
			c_start = map[i].start;
		}
		if(count++>0) {
			if((c_start-p_end) >= s) {
				result[0] = p_end;
				result[1] = p_end + s;
				return result;
			}else{
				p_start = map[i].start;
				p_end = map[i].end;
				continue;
			}
		}	
		p_start = map[i].start;
		p_end = map[i].end;
	}
	result[0] = 0;
	result[1] = s;
	return result;
}
int* bestfit(int s) {
	int p_start, p_end, count=0, r=0, c_start;
	int *result = malloc(sizeof(int) * 2);
	int best_start=0, best_size=MAX_SIZE;
	for(int i=0; i<=map_i; i++) {
		if(!(map[i].active || i==map_i)) {
			continue;
		}
		if(i==map_i) {
			c_start = MAX_SIZE;
		}else {
			
			c_start = map[i].start;
		}
		if(count++>0) {
			if((c_start-p_end) >= s) {
				// result[0] = p_end;
				// result[1] = p_end + s;
				// return result;
				if((c_start-p_end)<best_size) {
					best_start = p_end;
					best_size = c_start-p_end;
				}
			}else{
				p_start = map[i].start;
				p_end = map[i].end;
				continue;
			}
		}	
		p_start = map[i].start;
		p_end = map[i].end;
	}
	result[0] = best_start;
	result[1] = best_start + s;
	return result;
}