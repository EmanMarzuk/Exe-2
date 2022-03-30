#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define S 6



// *****************************  A  *****************************
typedef struct Worker
{
    unsigned long  id;
    char* name;
    unsigned long  salary;

    union YearOfWork
    {
        char HebrewYear[S];
        unsigned long  year;
    } YearOfWork;
}Worker;

// *****************************  B  *****************************
Worker* CreateWorker(int unionChoice) // constructor
{

    Worker* w = (Worker*)calloc(1, sizeof(Worker)); // initialize all data to 0
    //allocation success checks
    if (w == NULL) {
        printf("Allocation failed!");
        return 0;
    }
    char* sName = (char*)malloc(sizeof(char));
    char* sYear = (char*)malloc(sizeof(char));

    printf("Enter ID number: ");
    scanf(" %d", &w->id);

    printf("Enter the name: ");
    scanf(" %[^\n]s", sName);
    w->name = sName;
    printf("");

    printf("Enter the salary: ");
    scanf("%d", &w->salary);

    printf("Enter the year of work: ");
    if (unionChoice) {
        scanf(" %[^\n]s", w->YearOfWork.HebrewYear);

    }
    else {
        scanf("%d", &w->YearOfWork.year);
    }


    return w;
}

void PrintWorker(Worker* w, int unionChoice) // printing the details of the worker
{
    printf("Worker Details:\nID: %ld\nName: %s\nSalary: %ld\n", w->id, w->name, w->salary);
    if (unionChoice)        printf("Year of starting work: %s\n", w->YearOfWork.HebrewYear);
    else     printf("Year of starting work: %ld\n", w->YearOfWork.year);
}

// *****************************  C  *****************************
typedef struct WorkerList
{
    Worker* data;
    struct WorkerList* next;
} WorkerList;

// ** C1 **

// finding the tail of workersList
WorkerList* findTail(WorkerList* head) {

    WorkerList* temp = head;
    WorkerList* tail = (WorkerList*)malloc(sizeof(WorkerList));

    if (head->next == NULL) {     // 1 node
        tail = head;
        return tail;
    }
    if (head == NULL)    return NULL;   // list is empty

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    tail = temp;
    return tail;
}

WorkerList* addWorker(WorkerList* head, Worker* w) {

    WorkerList* newWorker, * tail, * temp, * ptr;
    newWorker = (WorkerList*)calloc(1, sizeof(WorkerList)); // initialize all data to 0

    //allocation success check
    if (newWorker == NULL) {
        printf("Allocation failed!");
        return 0;
    }

    // creating a new node-data for the worker
    newWorker->data = w;

    int val = w->salary;

    // case list is empty
    if (head == NULL)
    {
        //all of newNode's fields except "value" are 0 due to calloc (as they should be)
        head = newWorker;
        return head;
    }

    // case val should be first element in WorkerList
    if (val < head->data->salary)
    {
        newWorker->next = head;
        head = newWorker;
        return head;
    }

    // finding the tail of workersList
    tail = findTail(head);

    // case val should be last element in list
    if (tail->data->salary < val)
    {
        tail->next = newWorker;
        tail = newWorker;
        return head;
    }

    // general case - add in some middle position of the sorted WorkerList
    temp = head;
    if (temp->next->data->salary < val) {
        temp = temp->next;
    }
    else {
        ptr = temp->next;
        temp->next = newWorker;
        newWorker->next = ptr;
    }
    return head;
}

// ** C2 **

int index(WorkerList* head, long unsigned id) {
    WorkerList* temp = head;
    int ind = 0;

    while (temp != NULL) {
        if (temp->data->id == id)    return ++ind;
        ind++;
        temp = temp->next;
    }
    return -1;
}

int RecindexTemp(WorkerList* head, long unsigned id, int len) {

    if (head == NULL)
        return -1 - len;      // we reach the end and the id does not exist in the list.

    if (head->data->id == id)
        return 0;

    else return 1 + RecindexTemp(head->next, id, ++len);  // counting how much workers there are before the worker we search for.
}

int Recindex(WorkerList* head, long unsigned id) {

    RecindexTemp(head, id, 0);
}


// ** C3 **
WorkerList* deleteWorstWorker(WorkerList* head)
{
    WorkerList* temp = head;

    if (head == NULL) // empty list
    {
        printf("list is empty");
        return 0;
    }

    if (head->next == NULL) // 1 node list
    {
        free(head);
        head = NULL;
        printf("The list had 1 node!");
        return 0;
    }

    temp = head;
    head = temp->next;
    free(temp);
    temp = NULL;
    return head;
}

// ** C4 **
void update_worker(WorkerList* head, float percent)
{
    WorkerList* temp = head;
    while (temp != NULL)
    {
        temp->data->salary = temp->data->salary * (100 + percent * 100) / 100;
        temp = temp->next;
    }
}

// ** C5 **

// finding the previouse node of the tail
WorkerList* findPrev(WorkerList* head, WorkerList* tail) {

    WorkerList* temp = head;
    while (temp->next != tail)
    {
        temp = temp->next;
    }
    return temp;
}


WorkerList* reverse(WorkerList* head)
{
    WorkerList* temp, * tail, * prev, * ptr;
    ptr = head;
    temp = head;
    tail = findTail(head);
    while (tail != ptr)
    {
        prev = findPrev(head, tail);
        head = tail;
        head->next = temp;
        prev->next = NULL;
        tail = prev;
        temp = head;

    }
    return temp;
}

// ** C6 **
void freeWorkers(WorkerList* head)
{
    WorkerList* temp;
    if (head == NULL) // list is empty
        return;

    while (head != NULL)
    {
        temp = head;
        head = temp->next;
        free(temp);
        temp = NULL;
    }
}

// *****************************  D  *****************************

void main()
{
    Worker* w1 = CreateWorker(0);
    printf("\n");
    Worker* w2 = CreateWorker(1);
    printf("\n");
    Worker* w3 = CreateWorker(0);
    printf("\n");


    WorkerList* workers = (WorkerList*)malloc(sizeof(WorkerList));
    if (workers == NULL) {
        printf("Allocation failed");
        return;
    }

    workers = NULL;
    workers = addWorker(workers, w1);
    printf("\n");
    workers = addWorker(workers, w2);
    printf("\n");
    workers = addWorker(workers, w3);
    printf("\n");


    PrintWorker(w1, 0);
    printf("\n");
    PrintWorker(w2, 1);
    printf("\n");
    PrintWorker(w3, 0);
    printf("\n");


    if (index(workers, 208661127) != -1)    printf("The ID is suitable for worker number %d \n", index(workers, 208661127));
    else    printf("This ID 208661127 is not existed!\n");
    printf("\n");

    if (Recindex(workers, 123456789) != -1)    printf("The ID is suitable for worker number %d\n", Recindex(workers, 123456789));
    else    printf("This ID 123456789 is not existed!\n");
    printf("\n");

    workers = deleteWorstWorker(workers);

    update_worker(workers, 0.2);

    workers = reverse(workers);

}

