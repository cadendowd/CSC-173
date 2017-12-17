#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct CP {
	char* Course;
	char* Prerequisite;
	struct CP* next;
} CP;

typedef struct CPTable{
	CP* table[1009];
} CPTable;

unsigned int string_hashCP(void *string) {
	
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}

int HashCP(int id) {
	return abs(id % 1009);
}

CP* CP_new(char* course, char* prerequisite) {
	CP* cp = (CP*) malloc(sizeof(CP));
	cp->Course = course;
	cp->Prerequisite = prerequisite;
	cp->next = NULL;
	return cp;
}
void CP_print(CP* cp){
    if (cp == NULL) {
        printf("CP printed is NULL\n");
        return;
    }
	printf("{%s, %s}, ", cp->Course, cp->Prerequisite);
	if(cp->next != NULL) {
		CP_print(cp->next);
	}
}
CP* CP_back_of_list(CP* cp){
	if(cp->next == NULL){
		return cp;
	} else {
		return CP_back_of_list(cp->next);
	}
}
void CP_insert(CP* cp, CPTable* table){
	int hashval = HashCP(string_hashCP(cp->Course));
	if(table->table[hashval] == NULL){
		table->table[hashval] = cp;
	} else {
		CP_back_of_list(table->table[hashval])->next = cp;
	}
}
CP* CP_list_search(char* course, CP* list, CP* cp){
	if(list == NULL) {
		return cp;
	} else {
		if(strcmp(list->Course, course)==0) {
			cp = CP_new(list->Course, list->Prerequisite);
			cp->next = CP_list_search(course, list->next, cp->next);
			return cp;
		} else {
			cp = CP_list_search(course, list->next, cp);
			return cp;
		}
	}
}
CP* CP_lookup(char* course, CPTable* table){
	int hashval = HashCP(string_hashCP(course));
	CP* cp = CP_list_search(course, table->table[hashval], NULL);
	return cp;
}
void CPTable_print(CPTable* table){
	for(int i = 0; i< 1009; i++){
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			CP_print(table->table[i]);
			printf("\n");
		}
	}
}
CPTable* CPTable_new(){
	CPTable* cp = (CPTable*) malloc(sizeof(CPTable));
	for(int i = 0; i < 1009; i++){
		cp->table[i] = NULL;
	}
	return cp;
}

void CP_delete_hash(char* course, CP* list) {
	if(list->next == NULL){
		return;
	} else if(strcmp(list->next->Course, course) == 0){
		list->next = list->next->next;
		CP_delete_hash(course, list->next);
		return;
	} else {
		CP_delete_hash(course, list->next);
	}
}

void CP_delete(char* course, CPTable* table) {
	int hashval = HashCP(string_hashCP(course));
	if(strcmp(table->table[hashval]->Course, course) == 0){
		table->table[hashval] = (table->table[hashval])->next;
	} else {
		CP_delete_hash(course, table->table[hashval]);
	}
}

CPTable* CP_Selection(CPTable* table, char* attribute, char* search) {
        CPTable* newTable = CPTable_new();
        if (strcmp(attribute, "course")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Course, search) == 0) {
                                        CP_insert(CP_new(table->table[i]->Course, table->table[i]->Prerequisite), newTable);
                                }
                                CP* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Course, search) == 0) {
                                                CP_insert(CP_new(element->Course, element->Prerequisite), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "prerequisite")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Prerequisite, search) == 0) {
                                        CP_insert(CP_new(table->table[i]->Course, table->table[i]->Prerequisite), newTable);
                                }
                                CP* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Prerequisite, search) == 0) {
                                                CP_insert(CP_new(element->Course, element->Prerequisite), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}




