#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Database {
    CSGTable *CSG;
    SNAPTable *SNAP;
    CPTable *CP;
    CDHTable *CDH;
    CRTable *CR;
}Database;

Database* Database_New() {
	Database *db = (Database *)malloc(sizeof(Database));
	db->CSG = CSGTable_new();
	db->SNAP = SNAPTable_new();
	db->CP = CPTable_new();
	db->CDH = CDHTable_new();
	db->CR = CRTable_new();
	return db;
}

void Database_print(Database* db) {
    printf("SNAP Table:\n");
    SNAPTable_print(db->SNAP);
    printf("CP Table:\n");
    CPTable_print(db->CP);
    printf("CR Table:\n");
    CRTable_print(db->CR);
    printf("CSG Table:\n");
    CSGTable_print(db->CSG);
    printf("CDH Table:\n");
    CDHTable_print(db->CDH);
}

void DataBase_Save(Database* database, char* fileName) {
    FILE *f = fopen(fileName, "w");
    if (f == NULL) {
        printf("NULL\n");
        exit(1);
    }

    const char *text = "Database:";

    fprintf(f, "%s\n", text);


    fprintf(f, "CDH:\n");
    for (int i=0; i<1009; i++) {
        if (database->CDH->table[i] != NULL) {
            CDH* temp = database->CDH->table[i];
            while (temp != NULL) {
                fprintf(f, "%s\n%s\n%s\n", temp->Course, temp->Day, temp->Hour);
                temp = temp->next;
            }
        }
    }
    fprintf(f, "CP:\n");
    for (int i=0; i<1009; i++) {
        if (database->CP->table[i] != NULL) {
            CP* temp = database->CP->table[i];
            while (temp != NULL) {
                fprintf(f, "%s\n%s\n", temp->Course, temp->Prerequisite);
                temp = temp->next;
            }
        }
    }
    fprintf(f, "CR:\n");
    for (int i=0; i<1009; i++) {
        if (database->CR->table[i] != NULL) {
            CR* temp = database->CR->table[i];
            while (temp != NULL) {
                fprintf(f, "%s\n%s\n", temp->Course, temp->Room);
                temp = temp->next;
            }
        }
    }
    fprintf(f, "CSG:\n");
    for (int i=0; i<1009; i++) {
        if (database->CSG->table[i] != NULL) {
            CSG* temp = database->CSG->table[i];
            while (temp != NULL) {
                fprintf(f, "%s\n%d\n%s\n", temp->Course, temp->StudentId, temp->Grade);
                temp = temp->next;
            }
        }
    }
    fprintf(f, "SNAP:\n");
    for (int i=0; i<1009; i++) {
        if (database->SNAP->table[i] != NULL) {
            SNAP* temp = database->SNAP->table[i];
            while (temp != NULL) {
                fprintf(f, "%d\n%s\n%s\n%d\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
                temp = temp->next;
            }
        }
    }
    fprintf(f, "End DB\n");
    fclose(f);
}

Database* DataBase_Load(char* fileName) {
    Database* db = Database_New();
    FILE *fp;
    char buff[255];
    int typeReading = 0; 
    fp = fopen(fileName, "r");
    while (strcmp(buff, "End DB\n") != 0) {
        char* course = (char*)malloc(sizeof(char)*255);
        char* day = (char*)malloc(sizeof(char)*255);
        char* time = (char*)malloc(sizeof(char)*255);
        char* phone = (char*)malloc(sizeof(char)*255);
        char* prereq = (char*)malloc(sizeof(char)*255);
        char* room = (char*)malloc(sizeof(char)*255);
        char* address = (char*)malloc(sizeof(char)*255);
        char* studentID = (char*)malloc(sizeof(char)*255);
        char* grade = (char*)malloc(sizeof(char)*255);
        char* name = (char*)malloc(sizeof(char)*255);
        int phoneNum = (int)malloc(sizeof(int));
        int idNumber = (int)malloc(sizeof(int));
        fgets(buff, 255, (FILE*)fp);

        if (strcmp(buff, "End DB\n") == 0) {
            break;
        }

        if (strcmp(buff, "CDH:\n")==0) {
            typeReading = 1;
        } else if (strcmp(buff, "CP:\n")==0) {
            typeReading = 2;
        } else if (strcmp(buff, "CR:\n")==0) {
            typeReading = 3;
        } else if (strcmp(buff, "CSG:\n")==0) {
            typeReading = 4;
        } else if (strcmp(buff, "SNAP:\n")==0) {
            typeReading = 5;
        } else {
            
            if (typeReading == 1) {
                buff[strlen(buff)-1]= '\0';
                strcpy(course, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(day, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(time, buff);

                CDH* newCDH = CDH_new(course, day, time);

                CDH_insert(newCDH, db->CDH);

            } else if (typeReading ==2) {
                buff[strlen(buff)-1]= '\0';
                strcpy(course, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(prereq, buff);

                CP* newCP = CP_new(course, prereq);
                CP_insert(newCP, db->CP);

            } else if (typeReading ==3) {
                buff[strlen(buff)-1]= '\0';
                strcpy(course, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(room, buff);

                CR* newCR = CR_new(course, room);
                CR_insert(newCR, db->CR);
            } else if (typeReading ==4) {
                buff[strlen(buff)-1]= '\0';
                strcpy(course, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(studentID, buff);
                idNumber = atoi(studentID);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(grade, buff);

                CSG* newCSG = CSG_new(course, idNumber, grade);

                CSG_insert(newCSG, db->CSG);
            } else if (typeReading == 5) {
                
                buff[strlen(buff)-1]= '\0';
                strcpy(studentID, buff);
                idNumber = atoi(studentID);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(name, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(address, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(phone, buff);
                phoneNum = atoi(phone);

                SNAP* newSNAP = SNAP_new(idNumber, name, address, phoneNum);

                SNAP_insert(newSNAP, db->SNAP);
            }


        }
    }
    fclose(fp);
    return db;
}
