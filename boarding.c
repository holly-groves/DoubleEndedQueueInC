/*
	Name: Holly Groves
	Matric number: 18007261
	Module code: AC21008
	Multi-Paradigm programming Assignment 1
	Double Ended Queue
		Passengers boarding a plane
*/

#include "boarding.h"
#include <stdlib.h>
#include <string.h>

// create a new queue
// parameters:
// 	qPtr - will recieve a pointer to the newly allocated queue
int createBoardingQueue(BoardingQueue **qPtr) {
	// if no valid memory address of a queue is provided
	// then return that it is an invalid input patameter
	if (qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	// make sure the queue hasn't been implemented already
	// ensure the pointer doesn't point to something already
	if (*qPtr != NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	// allocate memory for a new queue and store it in the pointer provided
	// using myMalloc()
	(*qPtr) = (BoardingQueue*)myMalloc(sizeof(BoardingQueue)); //might have to be Stack instead of Queue

	// check for memory failure
	if ((*qPtr) == NULL)
	{
		return MEMORY_ALLOCATION_ERROR;
	}

	// initialise fields in the queue
	(*qPtr)->head = NULL;
	(*qPtr)->tail = NULL;

	return SUCCESS;
}

// add a new passenger to the queue
// add to the bottom of the queue so priority passengers are added at the top
// parameters:
// 	qPtr - a pointer to the queue
// 	name - name of passenger to be added
//	passportNumber - the passenger to be added passport's number
// 	seatNumber - passenger to be added's seat number
int addPassenger(BoardingQueue *qPtr, char name[], double passportNumber, int seatNumber) {
	// check that the pointer to the queue is valid
	if (qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	// create a new passenger to go into the queue
	Passenger *newPassenger = (Passenger*)myMalloc(sizeof(Passenger));

	// if the memory allocation of the passenger failed
	if (newPassenger == NULL) {
		return MEMORY_ALLOCATION_ERROR;
	}

	//INPUT VALIDATION CHECKS
	// checks that there is a name to add to the new passenger and it is less than 30 characters to avoid memory errors
	if (name == NULL)
		return INVALID_INPUT_PARAMETER;
	// checks that there is a passport number to add to the new passenger
	if (passportNumber < 1 || passportNumber > 88000)
		return INVALID_INPUT_PARAMETER;
	//checks that there is a seat numver to add to the new passenger
	if (seatNumber < 1 || seatNumber > 150)
		return INVALID_INPUT_PARAMETER;

	//initialise fields in the new passenger
	strcpy(newPassenger->name, name);
	newPassenger->passportNumber = passportNumber;
	newPassenger->seatNumber = seatNumber;
	//next passenger should be set to null
	newPassenger->next = NULL;

	//if the queue is empty set the head and tail of the queue to point to the new passenger
	if (qPtr->tail == NULL && qPtr->head == NULL)
	{
		qPtr->tail = newPassenger;
		qPtr->head = newPassenger;
	}

	//make the new passenger the bottom of the queue
	qPtr->tail = newPassenger;

	return SUCCESS;
}

//add a priority passenger to the queue
//add to the top of the queue as they have priority
//parameters:
// 	qPtr - a pointer to the queue
// 	name - name of passenger to be added
//	passportNumber - the passenger to be added passport's number
// 	seatNumber - passenger to be added's seat number
int addPriorityPassenger(BoardingQueue *qPtr, char name[], double passportNumber, int seatNumber) {
	// check that the pointer to the queue is valid
	if (qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	// create a new passenger to go into the queue
	Passenger *newPassenger = (Passenger*)myMalloc(sizeof(Passenger));

	// if the memory allocation of the passenger failed
	if (newPassenger == NULL)
		return MEMORY_ALLOCATION_ERROR;


	//INPUT VALIDATION CHECKS
	// checks that there is a name to add to the new passenger and it is less than 30 characters to avoid memory errors
	if (name == NULL)
		return INVALID_INPUT_PARAMETER;
	// checks that there is a passport number to add to the new passenger
	if (passportNumber < 1 || passportNumber > 88000)
		return INVALID_INPUT_PARAMETER;
	//checks that there is a seat numver to add to the new passenger
	if (seatNumber < 1 || seatNumber > 150)
		return INVALID_INPUT_PARAMETER;

	//initialise fields in the new node
	strcpy(newPassenger->name, name);
	newPassenger->passportNumber = passportNumber;
	newPassenger->seatNumber = seatNumber;
	//set the next passenger to the passenger at the top of the queue
	newPassenger->next = qPtr->head;

	//if the queue is empty 
	//set the head and tail of the queue to point to the new passenger
	if (qPtr->tail == NULL && qPtr->head == NULL)
	{
		qPtr->tail = newPassenger;
		qPtr->head = newPassenger;
	}

	//make the new passenger the bottom of the queue
	qPtr->head = newPassenger;

	return SUCCESS;
}

//remove the passenger at the head of the queue
//parameters:
//	qPtr a pointer to the queue
//	p the passenger to be removed
int removePassenger(BoardingQueue *qPtr, Passenger *p) {
	//check that the pointer given is to a valid queue
	if (qPtr == NULL)
		return INVALID_INPUT_PARAMETER;

	//check that the pointer given for the passenger points to a valid memory address
	if (p == NULL)
		return INVALID_INPUT_PARAMETER;

	//check that the queue isn't empty
	if (qPtr->head == NULL)
		return INVALID_QUEUE_OPERATION;

	//store the passenger to be removed (the passenger at the head of the queue)
	strcpy(p->name, qPtr->head->name);
	p->passportNumber = qPtr->head->passportNumber;
	p->seatNumber = qPtr->head->seatNumber;
	p->next = qPtr->head->next;

	//store the pointer to the passenger to be removed
	Passenger *pRemove = qPtr->head;


	//if the head passenger has a next passenger
	//if there is more than one passenger in the queue
	if (qPtr->head->next)
		qPtr->head = pRemove->next; //make the head of the queue to be the next passenger in the queue

	free(pRemove); //free the passenger

	return SUCCESS;
}

//peek at the passenger who is first in the queue (at the head)
//paramters:
//	qPtr a pointer to the queue
//	p will receive the passenger at the head of the queue
int peekAtHeadPassenger(BoardingQueue *qPtr, Passenger *p) {
	//check that we have a pointer to a valid queue
	if (qPtr == NULL)
		return INVALID_INPUT_PARAMETER;

	//check that the pointer to the passenger is valid
	if (p == NULL)
		return INVALID_INPUT_PARAMETER;

	//check that the queue isn't empty
	if (qPtr->head == NULL)
		return INVALID_QUEUE_OPERATION;

	//get the passenger information at the head of the queue
	//DOESN'T FUCKING WORK
	*p = *qPtr->head;

	return SUCCESS;

	// return NOT_IMPLEMENTED;
}

//peek at the passenger who is last in the queue (at the end)
//paramters:
//	qPtr a pointer to the queue
//	p will recieve the passenger at the tail of the queue
int peekAtTailPassenger(BoardingQueue *qPtr, Passenger *p) {
	//check that we have a pointer to a valid queue
	if (qPtr == NULL)
		return INVALID_INPUT_PARAMETER;

	//check that the pointer to the passenger is valid
	if (p == NULL)
		return INVALID_INPUT_PARAMETER;

	//check that the queue isn't empty
	if (qPtr->tail == NULL)
		return INVALID_QUEUE_OPERATION;

	*p = *qPtr->tail;

	return SUCCESS;
	// return NOT_IMPLEMENTED;
}

//empty a queue
//parameters:
//	qPtr - a pointer to the queue that will be cleared/emptied
int clearBoardingQueue(BoardingQueue *qPtr) {
	//check that the pointer is to a valid queue
	if (qPtr == NULL)
		return INVALID_INPUT_PARAMETER;

	//while loop for when there is still an item in the queue to free
	while (qPtr->head != NULL)
	{
		//get the pointer to the head of the queue
		Passenger *current = qPtr->head;

		//make the head of the queue the next passenger in the queue
		qPtr->head = qPtr->head->next;

		//free the passenger at the top of the queue
		free(current);
	}

	//free the queue after all the passengers have been freed
	free(qPtr);

	return SUCCESS;
	// return NOT_IMPLEMENTED;
}

//sorts the queue in order by seat number
//lowest seat number is at the front of the queue
//parameters:
//	qPtr - a pointer to the queue to be sorted
int sortBoardingQueue(BoardingQueue *qPtr) {

	//validation
	if (qPtr == NULL)
		return INVALID_INPUT_PARAMETER;

	//variable for loop
	int sorted = 0;

	//temporary variables;
	char tempName[30];
	double tempNum;
	int tempSeat;
	Passenger *temp;
	Passenger *nextInQ;

	//initalise values
	temp = qPtr->head;
	nextInQ = qPtr->head->next;

	//loop to go through the passengers and order them
	while (sorted != 1)
	{	
		if (temp->seatNumber > nextInQ->seatNumber)
		{
			//swap values for seat number
			tempSeat = temp->seatNumber;
			temp->seatNumber = nextInQ->seatNumber;
			nextInQ->seatNumber = tempSeat;

			//swap values for name
			strcpy(tempName, temp->name);
			strcpy(temp->name, nextInQ->name);
			strcpy(nextInQ->name, tempName);

			//swap values for passport number
			tempNum = temp->passportNumber;
			temp->passportNumber = nextInQ->passportNumber;
			nextInQ->passportNumber = tempNum;
		}

		temp = temp->next; //go to the next passenger in the queue
		nextInQ = temp->next;

		//exit condition
		if (temp->next == NULL)
		{
			sorted = 1;
		}
	}

	return SUCCESS;

	/*
	INCASE IT DOESN'T WORK
	(void)qPtr;
	return NOT_IMPLEMENTED;
	*/
}