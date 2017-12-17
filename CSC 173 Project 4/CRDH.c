#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//natural join of CR and CDH

typedef struct CRDH{
	char* Course;
	char* Room;
	char* Day;
	char* Hour;
	struct CRDH* next;
}CRDH;

unsigned int string_hashCRDH(void *string) {
	
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}

int HashCRDH(int id) {
	return abs(id % 1009);
}

CRDH* CRDH_new(char* course, char* room, char* day, char* hour){
	CRDH* crdh = (CRDH*) malloc(sizeof(CRDH));
	crdh->Course = course;
	crdh->Room = room;
	crdh->Day = day;
	crdh->Hour = hour;
	crdh->next = NULL;
	return crdh;
}

void CRDH_print(CRDH* crdh) {
	printf("{%s, %s, %s, %s}, ", crdh->Course, crdh->Room, crdh->Day, crdh->Hour);
	if (crdh->next != NULL) {
		CRDH_print(crdh->next);
	}
}
typedef struct CRDHTable{
	CRDH* table[1009];
}CRDHTable;

void CRDH_join_h(CR* cr_list, CDH* cdh_list, CRDHTable* table);
CRDH* CRDH_back_of_list(CRDH* in);

CRDHTable* CRDHTable_new(CRTable* cr_table, CDHTable* cdh_table){
	CRDHTable* crdh = (CRDHTable*) malloc(sizeof(CRDHTable));
	for(int i = 0; i < 1009; i++){
		crdh->table[i] = NULL;
	}
	for(int i = 0; i < 1009; i++){
		for(int j = 0; j < 1009; j++){
			CRDH_join_h(cr_table->table[i], cdh_table->table[j], crdh);
		}
	}
	return crdh;
}
CRDHTable* CRDHTable_new2(){
	CRDHTable* crdh = (CRDHTable*) malloc(sizeof(CRDHTable));
	for(int i = 0; i < 1009; i++){
		crdh->table[i] = NULL;
	}
	return crdh;
}


void CRDH_insert(CRDH* crdh, CRDHTable* table){
	int hashval = HashCRDH(string_hashCRDH(crdh->Room));
	if(table->table[hashval] == NULL){
		table->table[hashval] = crdh;
	} else {
		CRDH_back_of_list(table->table[hashval])->next = crdh;
	}
}

CRDH* CRDH_back_of_list(CRDH* crdh){
	if(crdh->next == NULL){
		return crdh;
	} else {
		return CRDH_back_of_list(crdh->next);
	}
}

void CRDH_join_h(CR* cr_list, CDH* cdh_list, CRDHTable* table){
	while(cr_list != NULL){
		while(cdh_list!= NULL){
			if(strcmp(cr_list->Course, cdh_list->Course) == 0){
				CRDH_insert(CRDH_new(cr_list->Course, cr_list->Room, cdh_list->Day, cdh_list->Hour), table);
			}
			cdh_list = cdh_list->next;
		}
		cr_list = cr_list->next;
	}
}

void CRDHTable_print(CRDHTable* table) {
	for (int i = 0; i < 1009; i++) {
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			CRDH_print(table->table[i]);
			printf("\n");
		}
	}
}

CRDHTable* CRDH_Selection(CRDHTable* table, char* attribute, char* search) {
        CRDHTable* newTable = CRDHTable_new2();
        if (strcmp(attribute, "course")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Course, search) == 0) {
                                        CRDH_insert(CRDH_new(table->table[i]->Course, table->table[i]->Room, table->table[i]->Day, table->table[i]->Hour), newTable);
                                }
                                CRDH* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Course, search) == 0) {
                                                CRDH_insert(CRDH_new(element->Course, element->Room, element->Day, element->Hour), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "room")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Room, search) == 0) {
                                        CRDH_insert(CRDH_new(table->table[i]->Course, table->table[i]->Room, table->table[i]->Day, table->table[i]->Hour), newTable);
                                }
                                CRDH* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Room, search) == 0) {
                                                CRDH_insert(CRDH_new(element->Course, element->Room, element->Day, element->Hour), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}