#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int string_hashQ(void *string) {
	
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}

int HashQ(int id) {
	return abs(id % 1009);
}

//What grade did StudentName get in Course-Name?
char* GradeInCourse(char str[], Database* db) {
	
	char student[50] = "";
	char course[50] = "";
	static char grade[50] = "";
	char *A[] = {"What", "grade", "did", "*", "get", "in", "*"};
	int i = 0;
	int studentid = -1;
	int size = sizeof(A)/sizeof(char *);
	char * pch;
	pch = strtok (str," ?");
	while (pch != NULL) {
		
		if (i > size) {
			printf("fail\n");
			break;
		}
		if (strcmp(A[i], "*")!=0) {
			if (strcmp(A[i], pch)==0){}
			else {return "failed";}
		}
		else {
			if (strcmp(student, "")==0) {
				char temp[50];
				strncpy(temp, pch, strlen(pch));
				if (temp[strlen(pch)-1]=='\'') {
					temp[strlen(pch)-1]='\0';
					strcpy(student, pch);
				}
				else {
					while (temp[strlen(pch)-1]!='\'') {
						
						if (strcmp(student, "")==0) {
							 char *pch2 = pch+1;
							 strcat(student, pch2);
						}
						else
							strcat(student, pch);
						strcat(student, " ");
						pch = strtok (NULL, " ");
						strncpy(temp, pch, strlen(pch));
						if (pch == NULL)
							return "failed";
					}
					temp[strlen(pch)-1]='\0';
					strcat(student, temp);
				}
			}
			else if (strcmp(course, "")==0) {
				strcpy(course,pch);
			}
			else
				return "failed";
		}
		pch = strtok (NULL, " ?");
		i++;
	}
	if (strcmp(course, "")!=0) {
		SNAPTable* snapsearch = SNAP_Selection(db->SNAP, "name", student);
		for(int i = 0; i < 1009; i++) {
			if (snapsearch->table[i] != NULL) {
				studentid = snapsearch->table[i]->StudentId;
			}
		}
		if (studentid == -1)
			return "No results found";
		char id[6];
		sprintf(id, "%d", studentid);;
		CSGTable* csgsearch = CSG_Selection(db->CSG, "student", id);
		csgsearch = CSG_Selection(csgsearch, "course", course);
		if (csgsearch->table[Hash(studentid)] == NULL)
			return "No results found";
		strcpy(grade, csgsearch->table[Hash(studentid)]->Grade);
	}
	else
		return "failed";
  return grade;
}

//Where is StudentName at Hour on Day?
char* LocationOnDay(char str[], Database* db) {

	char student[50] = "";
	char hour[50] = "";
	char day[50] = "";
	char course[50] = "";
	static char location[50] = "";
	char *A[] = {"Where", "is", "*", "at", "*", "on", "*"};
	int i = 0;
	int studentid = -1;
	int size = sizeof(A)/sizeof(char *);
	char * pch;
	pch = strtok (str," ?");
	while (pch != NULL) {
		if (i > size) {
			printf("fail\n");
			break;
		}
		if (strcmp(A[i], "*")!=0) {
			if (strcmp(A[i], pch)==0){}
			else {printf("broke"); break;}
		}
		else {
			if (strcmp(student, "")==0) {
				char temp[50];
				strncpy(temp, pch, strlen(pch));
				if (temp[strlen(pch)-1]=='\'') {
					temp[strlen(pch)-1]='\0';
					strcpy(student, pch);
				}
				else {
					while (temp[strlen(pch)-1]!='\'') {
						
						if (strcmp(student, "")==0) {
							 char *pch2 = pch+1;
							 strcat(student, pch2);
						}
						else
							strcat(student, pch);
						strcat(student, " ");
						pch = strtok (NULL, " ");
						strncpy(temp, pch, strlen(pch));
						if (pch == NULL)
							return "failed";
					}
					temp[strlen(pch)-1]='\0';
					strcat(student, temp);
				}
			}
			else if (strcmp(hour, "")==0) {
				strcpy(hour,pch);
			}
			else if (strcmp(day, "")==0) {
				strcpy(day, pch);
			}
			else
				return "failed";
		}
		pch = strtok (NULL, " ?");
		i++;
	}
	

	if (strcmp(day, "")!=0) {
		SNAPTable* snapsearch = SNAP_Selection(db->SNAP, "name", student);
		for(int i = 0; i < 1009; i++) {
			if (snapsearch->table[i] != NULL) {
				studentid = snapsearch->table[i]->StudentId;
			}
		}
		if (studentid == -1)
			return "No results found";
		char id[6];
		sprintf(id, "%d", studentid);;
		CSGTable* csgsearch = CSG_Selection(db->CSG, "student", id);
		CDHTable* cdhsearch = CDH_Selection(db->CDH, "hour", hour);
		cdhsearch = CDH_Selection(cdhsearch, "day", day);
		for (int j = 0; j< 1009; j++) {
			if (csgsearch->table[j]!=NULL) {
				CSG* csg2 = csgsearch->table[j];
				while (csg2 != NULL) {
					CDHTable* cdhsearch2 = CDH_Selection(cdhsearch, "course", csg2->Course);
					for (int k = 0; k < 1009; k++) {
						if (cdhsearch2->table[k] != NULL) {
							CDH* cdh2 = cdhsearch2->table[k];
							while (cdh2 != NULL) {
								if (strcmp(cdh2->Day, day)==0 &&
									strcmp(cdh2->Hour, hour)==0) {
									strcpy(course, cdh2->Course);
									break;
								}
								cdh2 = cdh2->next;
							}
						}
					}
					csg2 = csg2->next;
				}
			}
		}
		if (strcmp(course,"")==0) {
			return "No results found";
		}
		else {
			CRTable* crsearch = CR_Selection(db->CR, "course", course);
			for (int i = 0; i < 1009; i++) {
				if (crsearch->table[i] != NULL) {
					strcpy(location, crsearch->table[i]->Room);
				}
			}
		}

	}
	else
		return "failed";

  return location;
}