#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct CSG{
	char* Course;
	int StudentId;
	char* Grade;
	struct CSG* next;
} CSG;

CSG* CSG_new(char* course, int id, char* grade){
	CSG* csg = (CSG*) malloc(sizeof(CSG));
	csg->Course = course;
	csg->StudentId = id;
	csg->Grade = grade;
	csg->next = NULL;
	return csg;
}

void CSG_print(CSG* csg){
    if (csg == NULL) {
        printf("NULL\n");
        return;
    }
	printf("{%s, %d, %s}, ", csg->Course, csg->StudentId, csg->Grade);
	if(csg->next != NULL) {
		CSG_print(csg->next);
	}
}

typedef struct CSGTable{
	CSG* table[1009];
} CSGTable;

CSG* CSG_back_of_list(CSG* csg){
	if(csg->next == NULL){
		return csg;
	} else {
		return CSG_back_of_list(csg->next);
	}
}

CSG* CSG_list_search(int id, CSG* list, CSG* csg){
	if(list == NULL) {
		return csg;
	} else {
		if(list->StudentId == id){
			csg = CSG_new(list->Course, list->StudentId, list->Grade);
			csg->next = CSG_list_search(id, list->next, csg->next);
			return csg;
		} else {
			csg = CSG_list_search(id, list->next, csg);
			return csg;
		}
	}
}
CSG* CSG_lookup(int id, CSGTable* table){
	int hashval = HashCSG(id);
	CSG* csg = CSG_list_search(id, table->table[hashval], NULL);
	return csg;
}
void CSG_insert(CSG* csg, CSGTable* table){
    if (CSG_lookup(csg->StudentId, table) == NULL) {


		int hashval = HashCSG(csg->StudentId);
		if(table->table[hashval] == NULL){
			table->table[hashval] = csg;
		} else {
			CSG_back_of_list(table->table[hashval])->next = csg;
		}
	} else {
        if(strcmp(CSG_lookup(csg->StudentId, table)->Course, csg->Course)!=0){
            int hashval = Hash(csg->StudentId);
		if(table->table[hashval] == NULL){
			table->table[hashval] = csg;
		} else {
			CSG_back_of_list(table->table[hashval])->next = csg;
		}
        }
	}
}


void CSGTable_print(CSGTable* table){
	for(int i = 0; i< 1009; i++){
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			CSG_print(table->table[i]);
			printf("\n");
		}
	}
}

CSGTable* CSGTable_new(){
	CSGTable* csg = (CSGTable*) malloc(sizeof(CSGTable));
	for(int i = 0; i < 1009; i++){
		csg->table[i] = NULL;
	}
	return csg;
}

void CSG_delete_hash(int id, char* course, CSG* list) {
	if(list->next == NULL){
		return;
	} else if(list->next->StudentId == id && strcmp((list->next)->Course, course)== 0){
		list->next = list->next->next;
		CSG_delete_hash(id, course, list->next);
		return;
	} else {
		CSG_delete_hash(id, course, list->next);
	}
}

void CSG_delete(int id, char* course, CSGTable* table) {
	int hashval = HashCSG(id);
	if((table->table[hashval])->StudentId == id && strcmp((table->table[hashval])->Course, course)== 0){
		table->table[hashval] = (table->table[hashval])->next;
	} else {
		CSG_delete_hash(id, course, table->table[hashval]);
	}
}

unsigned int string_hashCSG(void *string) {
	
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}

int HashCSG(int id) {
	return abs(id % 1009);
}

CSGTable* CSG_Selection(CSGTable* table, char* attribute, char* search) {
        CSGTable* newTable = CSGTable_new();
        if (strcmp(attribute, "course")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Course, search) == 0) {
                                        CSG_insert(CSG_new(table->table[i]->Course, table->table[i]->StudentId, table->table[i]->Grade), newTable);
                                }
                                CSG* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Course, search) == 0) {
                                                CSG_insert(CSG_new(element->Course, element->StudentId, element->Grade), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "student")==0) {
                int sid = atoi(search);
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (sid==table->table[i]->StudentId) {
                                        CSG_insert(CSG_new(table->table[i]->Course, table->table[i]->StudentId, table->table[i]->Grade), newTable);
                                }
                                CSG* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (sid==element->StudentId) {
                                                CSG_insert(CSG_new(element->Course, element->StudentId, element->Grade), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}



