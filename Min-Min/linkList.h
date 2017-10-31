#include <string.h>
#include <iostream>
using namespace std;
int completionTime[50][50], optimumExecArray[50][3], lengthOfMetaList = 0;
struct ResourceStruct{
  char name[6];
  int readyTime;
};

struct TaskStruct{
  char name[6];
  int executionTime[50];
  int status = 1;
};

struct MetaTask{
  char task[6];
  int resourceId;
  int taskId;
  int executionTime;
  int completionTime;
  MetaTask *prev;
  MetaTask *next;
}*head=NULL,*temp,*iteratr,*tail;



void pop(char taskName[])
{
    int pos,i=1,count = 0;
    temp = head;
//LINEAR SEARCH
    while (temp != NULL)
    {
        if (strcmp(temp->task, taskName))
        {
            pos = count;
            break;
        }
        else
             temp = temp->next;
            count++;
    }

//DELETION
    temp = head;
        while (i < pos)
        {
            temp = temp->next;
            i++;
        }
        if (i == 1)
        {
            if (temp->next == NULL)
            {
                printf("\n\n\t\t\t\t\t\tTask %s successfully assigned and removed from the Meta Task list!\n\n\n\n", taskName);
                free(temp);
                temp = head = NULL;
                return;
            }
        }
        if (temp->next == NULL)
        {
            temp->prev->next = NULL;
            free(temp);
            printf("\n\n\t\t\t\t\t\tTask %s successfully assigned and removed from the Meta Task list!\n\n\n\n", taskName);
            return;
        }
        temp->next->prev = temp->prev;
        if (i != 1)
            temp->prev->next = temp->next;    /* Might not need this statement if i == 1 check */
        if (i == 1)
            head = temp->next;
          printf("\n\n\t\t\t\t\t\tTask %s successfully assigned and removed from the Meta Task list!\n\n\n\n", taskName);
        free(temp);

}
void create(char task[], int taskId, int executionTime, int resourceId, int completionTime)
{

    temp =(struct MetaTask *)malloc(1*sizeof(struct MetaTask));
    temp->prev = NULL;
    temp->next = NULL;
    strcpy(temp->task, task);
    // strcpy(temp->resource,resource);
    temp->resourceId = resourceId;
    temp->executionTime = executionTime;
    temp->completionTime = completionTime;
    temp->taskId = taskId;
}

void push(char task[], int taskId, int executionTime, int resourceId, int completionTime)
{
    if (head == NULL)
    {
        create(task,taskId, executionTime, resourceId, completionTime);
        head = temp;
        iteratr = head;
    }
    else
    {
        create(task,taskId, executionTime, resourceId, completionTime);
        iteratr->next = temp;
        temp->prev = iteratr;
        iteratr = temp;
    }
}

int isEmpty(){
  if(head == NULL)
  return 1;
  return 0;
}

/* sort the given list - insertion sort*/
void sort() {
      struct MetaTask *ptr1, *ptr2;
      int i, j, completionTime, resourceId, executionTime, taskId;
      char task[6];
      ptr1 = ptr2 = head;
      if(head == NULL){
        return;
      }
      for (i = 0; i < lengthOfMetaList; i++) {
              completionTime = ptr1->completionTime;
              strcpy(task, ptr1->task);
              resourceId = ptr1->resourceId;
              executionTime = ptr1->executionTime;
              taskId = ptr1->taskId;
              for (j = 0; j < i; j++)
                      ptr2 = ptr2->next;
              for (j = i; j > 0 && ptr2->prev->completionTime > completionTime; j--) {
                      ptr2->completionTime = ptr2->prev->completionTime;
                      strcpy(ptr2->task, ptr2->prev->task);
                      ptr2->resourceId = ptr2->prev->resourceId;
                      ptr2->executionTime = ptr2->prev->executionTime;
                      ptr2->taskId = ptr2->prev->taskId;
                      ptr2 = ptr2->prev;
              }
              ptr2->completionTime = completionTime;
              strcpy(ptr2->task, task);
              ptr2->resourceId = resourceId;
              ptr2->executionTime = executionTime;
              ptr2->taskId = taskId;
              ptr2 = head;
              ptr1 = ptr1->next;
      }
}
