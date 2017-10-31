#include "linkList.h"
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

ResourceStruct Resources[50];
TaskStruct Tasks[50];
MetaTask MetaTaskList[50];
int noOfTasks, noOfResources, flag = 1;

void displayMetaTaskList();
void displayInitials();

void updateMetaTaskList(){
	int taskId;
	temp = head;
	while (temp != NULL)
	{
		taskId = temp->taskId;
		temp->resourceId = optimumExecArray[taskId][0];
		temp->completionTime = optimumExecArray[taskId][2];
		temp = temp->next;
	}
}

void updateReadyTime(int index, int executionTime){
	Resources[index].readyTime += executionTime;
}

void changeStatus(char task[]) {
	for(int i =0; i < noOfTasks; i++){
		if(strcmp(task,Tasks[i].name))
		{
			Tasks[i].status = 0;
		}
	}
}

void initialize(int noR = 3, int noT = 5){
	noOfTasks = noT;
	noOfResources = noR;
  /* initialize random seed: */
		srand (time(NULL));

		// number = rand() % 10 + 1;
    for(int i = 0; i < noR; i++){
       sprintf(Resources[i].name, "R%d", i+1);
       Resources[i].readyTime = 0;
    }

    for(int i = 0; i < noT; i++){
       sprintf(Tasks[i].name, "T%d", i+1);
			 for(int j = 0; j<noR; j++)
       Tasks[i].executionTime[j] = (rand() % 20 + 1);
    }

}

void updateCompletionTime(){
	for(int i=0; i < noOfTasks; i++){
		for(int j=0; j < noOfResources; j++){
			completionTime[i][j] = Tasks[i].executionTime[j] + Resources[j].readyTime;
		}
	}
}


void findMinFit(){
	int min, max;
	for(int i=0; i < noOfTasks; i++){
		min = max = completionTime[i][0];
		for(int j=0; j < noOfResources; j++){
			if(completionTime[i][j] >= max){
				max = completionTime[i][j];
				optimumExecArray[i][1] = j;
			}
		}
		for(int j=0; j < noOfResources; j++){
			if(completionTime[i][j] <= min){
				min = completionTime[i][j];
				optimumExecArray[i][0] = j;
				optimumExecArray[i][2] = min;
			}
		}
	}
}


void assignResource(){
	int resourceId;
	do {
			resourceId = head->resourceId;
			updateReadyTime(resourceId,head->completionTime);
		 	pop(head->task);
			lengthOfMetaList--;
			displayInitials();
			updateMetaTaskList();
			sort();
			displayMetaTaskList();
	} while(lengthOfMetaList != 0);
}

void displayInitials(){
	int i,k;

	updateCompletionTime();
	findMinFit();


	if(flag){
		for(int i = 0; i < noOfTasks; i++){
				push(Tasks[i].name, i, Tasks[i].executionTime[optimumExecArray[i][0]], optimumExecArray[i][0],optimumExecArray[i][2]);
				lengthOfMetaList++;
		}
		flag = 0;
	}



	system("clear");
	printf("\t\t\t\t\t\tTASKS\tRESOURCES\tEXEC TIME\tREADY TIME\tCOMP TIME\n");
	printf("\t\t\t\t\t\t-----------------------------------------------------------------\n");
	for(i=2,k=0; i <= (noOfTasks*noOfResources + noOfResources); i++,k++){
		for(int j = 0; j < noOfResources; j++, i++){

				printf("\t\t\t\t\t\t%s\t", Tasks[k].name);
				printf("%s\t\t", Resources[j].name);
				printf("%d\t\t", Tasks[k].executionTime[j]);
				printf("%d\t\t", Resources[j].readyTime);
				printf("%d\n", completionTime[k][j]);
		}
		printf("\n");
		sort();
	}
}
void displayMetaTaskList(){
	temp = head;

			if (temp == NULL){
				printf("\n\n\n\n\t\t\t\t\t\t\tALL TASK ASSIGNED TO AVAILABLE RESOURCES!\n\n \n");
				return;
			}
			printf("\n\t\t\t\t\t\t\tTASKS\tRESOURCES\tCOMP TIME\tEXEC TIME\n");
			printf("\t\t\t\t\t\t\t-------------------------------------------------\n");
	for(int i=2,k=0; k < lengthOfMetaList; i++, k++){
		printf("\t\t\t\t\t\t\t%s\t",temp->task);
		printf("R%d\t\t",temp->resourceId + 1);
		printf("%d\t\t",temp->completionTime);
		printf("%d\n",temp->executionTime);
				temp = temp->next;
		}
		printf("\n");
}
