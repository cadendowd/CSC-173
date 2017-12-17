#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int string_hashCR(void *string) {
	
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}

int HashCR(int id) {
	return abs(id % 1009);
}

typedef struct CR {
	char* Course;
	char* Room;
	struct CR* next;
} CR;

typedef struct CRTable{
	CR* table[1009];
} CRTable;

CR* CR_new(char* course, char* room) {
	CR* cr = (CR*) malloc(sizeof(CR));
	cr->Course = course;
	cr->Room = room;
	cr->next = NULL;
	return cr;
}
void CR_print(CR* cr){
    if (cr == NULL) {
        printf("CR printed is NULL\n");
        return;
    }
	printf("{%s, %s}, ", cr->Course, cr->Room);
	if(cr->next != NULL) {
		CR_print(cr->next);
	}
}
CR* CR_back_of_list(CR* cr){
	if(cr->next == NULL){
		return cr;
	} else {
		return CR_back_of_list(cr->next);
	}
}
void CR_insert(CR* cr, CRTable* table){
	int hashval = HashCR(string_hashCR(cr->Course));
	if(table->table[hashval] == NULL){
		table->table[hashval] = cr;
	} else {
		CR_back_of_list(table->table[hashval])->next = cr;
	}
}
CR* CR_list_search(char* course, CR* list, CR* cr){
	if(list == NULL) {
		return cr;
	} else {
		if(strcmp(list->Course, course)==0) {
			cr = CR_new(list->Course, list->Room);
			cr->next = CR_list_search(course, list->next, cr->next);
			return cr;
		} else {
			cr = CR_list_search(course, list->next, cr);
			return cr;
		}
	}
}
CR* CR_lookup(char* course, CRTable* table){
	int hashval = HashCR(string_hashCR(course));
	CR* cr = CR_list_search(course, table->table[hashval], NULL);
	return cr;
}
void CRTable_print(CRTable* table){
	for(int i = 0; i< 1009; i++){
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			CR_print(table->table[i]);
			printf("\n");
		}
	}
}
CRTable* CRTable_new(){
	CRTable* cr = (CRTable*) malloc(sizeof(CRTable));
	for(int i = 0; i < 1009; i++){
		cr->table[i] = NULL;
	}
	return cr;
}

void CR_delete_hash(char* course, CR* list) {
	if(list->next == NULL){
		return;
	} else if(strcmp(list->next->Course, course) == 0){
		list->next = list->next->next;
		CR_delete_hash(course, list->next);
		return;
	} else {
		CR_delete_hash(course, list->next);
	}
}
void CR_delete(char* course, CRTable* table) {
	int hashval = HashCR(string_hashCR(course));
	if(strcmp(table->table[hashval]->Course, course) == 0){
		table->table[hashval] = (table->table[hashval])->next;
	} else {
		CR_delete_hash(course, table->table[hashval]);
	}
}

CRTable* CR_Selection(CRTable* table, char* attribute, char* search) {
        CRTable* newTable = CRTable_new();
        if (strcmp(attribute, "course")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Course, search) == 0) {
                                        CR_insert(CR_new(table->table[i]->Course, table->table[i]->Room), newTable);
                                }
                                CR* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Course, search) == 0) {
                                                CR_insert(CR_new(element->Course, element->Room), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "room")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Room, search) == 0) {
                                        CR_insert(CR_new(table->table[i]->Course, table->table[i]->Room), newTable);
                                }
                                CR* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Room, search) == 0) {
                                                CR_insert(CR_new(element->Course, element->Room), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}