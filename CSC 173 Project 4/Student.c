#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct S{
	int StudentID;
	struct S* next;
} S;

S* S_new(int studentid){
	S* out = (S*) malloc(sizeof(S));
	out->StudentID = studentid;
	return out;
}

void S_print(S* s) {
	if (s->StudentID < 500000) {
		printf("{%d}, ", s->StudentID);
		if (s->next != NULL) {
			S_print(s->next);
		}
	}
}
typedef struct STable{
	S* table[1009];
}STable;

STable* STable_new(){
	STable* out = (STable*) malloc(sizeof(STable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}
S* S_back_of_list(S* s){
	if(s->next == NULL){
		return s;
	} else {
		return S_back_of_list(s->next);
	}
}

void S_insert(S* s, STable* table){
	int hashval = HashS(s->StudentID);
	if(table->table[hashval] == NULL){
		table->table[hashval] = s;
	} else {
		S_back_of_list(table->table[hashval])->next = s;
	}
}

STable* projection_s(CSGTable* table, char* column) {
    STable* stable = STable_new();
    for (int i=0; i < 1009; i++) {
        if (strcmp(column, "StudentId")==0) {
            if (table->table[i] != NULL) {

                S_insert(S_new(table->table[i]->StudentId), stable);

                CSG* elem = table->table[i];
                
                while (elem != NULL) {
                    if (elem->next == NULL)
                            break;
                    elem=elem->next;

                    S_insert(S_new(elem->StudentId), stable);
                }
            }
        }
    }
    return stable;
}
unsigned int string_hashS(void *string) {
	
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}

int HashS(int id) {
	return abs(id % 1009);
}


void STable_print(STable* table) {
	for (int i = 0; i < 1009; i++) {
		if (table->table[i] != NULL && table->table[i]->StudentID > 0) {
			printf("%d: ", i);
			S_print(table->table[i]);
			printf("\n");
		}
	}
}