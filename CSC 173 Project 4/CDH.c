#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int string_hashCDH(void *string) {
	
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}

int HashCDH(int id) {
	return abs(id % 1009);
}

typedef struct CDH {
	char* Course;
	char* Day;
	char* Hour;
	struct CDH* next;
} CDH;
typedef struct CDHTable{
	CDH* table[1009];
} CDHTable;

CDH* CDH_new(char* course, char* day, char* hour) {
	CDH* out = (CDH*) malloc(sizeof(CDH));
	out->Course = course;
	out->Day = day;
	out->Hour = hour;
	out->next = NULL;
	return out;
}
void CDH_print(CDH* cdh){
    if (cdh == NULL) {
        printf("CDH printed is NULL\n");
        return;
    }
	printf("{%s, %s, %s}, ", cdh->Course, cdh->Day, cdh->Hour);
	if(cdh->next != NULL) {
		CDH_print(cdh->next);
	}
}
CDH* CDH_back_of_list(CDH* cdh){
	if(cdh->next == NULL){
		return cdh;
	} else {
		return CDH_back_of_list(cdh->next);
	}
}
void CDH_insert(CDH* cdh, CDHTable* table){
	int hashval = HashCDH(string_hashCDH(cdh->Course));
	if(table->table[hashval] == NULL){
		table->table[hashval] = cdh;
	} else {
		CDH_back_of_list(table->table[hashval])->next = cdh;
	}
}
CDH* CDH_list_search(char* course, CDH* list, CDH* cdh){
	if(list == NULL) {
		return cdh;
	} else {
		if(strcmp(list->Course, course)==0) {
			cdh = CDH_new(list->Course, list->Day, list->Hour);
			cdh->next = CDH_list_search(course, list->next, cdh->next);
			return cdh;
		} else {
			cdh = CDH_list_search(course, list->next, cdh);
			return cdh;
		}
	}
}
CDH* CDH_lookup(char* course, CDHTable* table){
	int hashval = HashCDH(string_hashCDH(course));
	CDH* out = CDH_list_search(course, table->table[hashval], NULL);
	return out;
}
void CDHTable_print(CDHTable* table){
	for(int i = 0; i< 1009; i++){
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			CDH_print(table->table[i]);
			printf("\n");
		}
	}
}
CDHTable* CDHTable_new(){
	CDHTable* out = (CDHTable*) malloc(sizeof(CDHTable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}

void CDH_delete_hash(char* course, CDH* list) {
	if(list->next == NULL){
		return;
	} else if(strcmp(list->next->Course, course) == 0){
		list->next = list->next->next;
		CDH_delete_hash(course, list->next);
		return;
	} else {
		CDH_delete_hash(course, list->next);
	}
}
void CDH_delete(char* course, CDHTable* table) {
	int hashval = HashCDH(string_hashCDH(course));
	if(strcmp(table->table[hashval]->Course, course) == 0){
		table->table[hashval] = (table->table[hashval])->next;
	} else {
		CDH_delete_hash(course, table->table[hashval]);
	}
}

CDHTable* CDH_Selection(CDHTable* table, char* attribute, char* search) {
        CDHTable* newTable = CDHTable_new();
        if (strcmp(attribute, "course")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Course, search) == 0) {
                                        CDH_insert(CDH_new(table->table[i]->Course, table->table[i]->Day, table->table[i]->Hour), newTable);
                                }
                                CDH* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Course, search) == 0) {
                                                CDH_insert(CDH_new(element->Course, element->Day, element->Hour), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "day")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Day, search) == 0) {
                                        CDH_insert(CDH_new(table->table[i]->Course, table->table[i]->Day, table->table[i]->Hour), newTable);
                                }
                                CDH* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Day, search) == 0) {
                                                CDH_insert(CDH_new(element->Course, element->Day, element->Hour), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "hour")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Hour, search) == 0) {
                                        CDH_insert(CDH_new(table->table[i]->Course, table->table[i]->Day, table->table[i]->Hour), newTable);
                                }
                                CDH* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Hour, search) == 0) {
                                                CDH_insert(CDH_new(element->Course, element->Day, element->Hour), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}