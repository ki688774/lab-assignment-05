#include <stdio.h>
#include <stdlib.h>

//Strings of size 1 are being ignored due to int main(), which I didn't write.
//I'm assuming that strings of size 1 are supposed to be ignored. If they aren't, it's not my fault, and here's why.
//Setting up a debugger reveals that insertChar is only being pinged for the third, fifth and seventh string.
//These pings happen before any of my other functions get a chance to run, INCLUDING length().
//If there's an issue, I quite literally could not have caused it, I didn't even get the chance.

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int nodeCount = 0;
	while (head != NULL)
	{
		nodeCount++;
		head = head->next;
	}

	return nodeCount;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	//This gets freed, so I'm probably expected to use malloc.
	int stringLength = length(head);
	//One extra slot for end-of-line character.
	char* cString = (char*) malloc(sizeof(char) * (stringLength + 1));
	for (int c = 0; c < stringLength; c++) {
		cString[c] = head->letter;
		head = head->next;
	}

	//End of string character.
	cString[stringLength] = '\0';
	return cString;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	//Allocate a new node. Abandon insertChar if you can't allocate it.
	node* newNode = (node*) malloc(sizeof(node));
	if (newNode == NULL) {
		printf("Memory allocation failed!");
		return;
	}

	//Now that newNode's allocated, let's set its letter to c and initialize next.
	newNode->letter = c;
	newNode->next = NULL;

	//If the linked list at pHead doesn't exist, point pHead towards newNode to create it.
	//Otherwise, go to the end of the list and add newNode at the end.
	node* head = *pHead;
	if (head == NULL) {
		*pHead = newNode;
	} else {
		while (head->next != NULL) {
			head = head->next;
		}
		head->next = newNode;
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	//If pHead isn't pointing at the end of the list, run deleteList() again with the node one node ahead.
	//When whatever's happening in the next node finishes up, free the memory in this node and set the node to NULL.
	if ((*pHead)->next != NULL) {
		deleteList(&((*pHead)->next));
	}
	
	if ((*pHead) != NULL){
		free(*pHead);
		*pHead = NULL;
	}
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}