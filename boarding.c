/*
	Name: Holly Groves
	Matric number: 18007261
	Module code: AC21008
	Multi-Paradigm programming Assignment 1
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
	// checks that there is a name to add to the new passenger
	if (name[0] == NULL)
		return INVALID_INPUT_PARAMETER;
	// checks that there is a passport number to add to the new passenger
	if (passportNumber < 1)
		return INVALID_INPUT_PARAMETER;
	//checks that there is a seat numver to add to the new passenger
	if (seatNumber < 1)
		return INVALID_INPUT_PARAMETER;

	//initialise fields in the new passenger
	strcpy(newPassenger->name[0], name[0]);
	newPassenger->passportNumber = passportNumber;
	newPassenger->seatNumber = seatNumber;
	//next passenger should be set to null
	newPassenger->next = NULL;


	// set the new passenger's next pointer to the next node in the queue
	// it will be set to whatever is currently the bottom of the queue
	// this is because a new passenger is added to the bottom of the queue while a priority passenger is added to the top
	newPassenger->next = qPtr->tail;

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
	// checks that there is a name to add to the new passenger
	if (name[0] == NULL)
		return INVALID_INPUT_PARAMETER;
	// checks that there is a passport number to add to the new passenger
	if (passportNumber < 1)
		return INVALID_INPUT_PARAMETER;
	//checks that there is a seat numver to add to the new passenger
	if (seatNumber < 1)
		return INVALID_INPUT_PARAMETER;

	//initialise fields in the new node
	strcpy(newPassenger->name[0], name[0]);
	newPassenger->passportNumber = passportNumber;
	newPassenger->seatNumber = seatNumber;
	//set the next passenger to the passenger at the top of the queue
	newPassenger->next = qPtr->head;

	// set the new passengers next pointer to the next node in the queue
	// it will be set to whatever is currently the top of the queue
	newPassenger->next = qPtr->head;

	//make the new passenger the bottom of the queue
	qPtr->head = newPassenger;

	return SUCCESS;
}

//remove the passenger at the top of the queue
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

	//create a pointer to the passenger that is being removed
	Passenger *pToRemove = qPtr->head;

	//make the head of the queue to be the next passenger in the queue
	qPtr->head = qPtr->head->next;

	//remove the passenger from the queue
	pToRemove->next = NULL;
	free(pToRemove);

	return SUCCESS;
}

//peek at the passenger who is first in the queue
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

int sortBoardingQueue(BoardingQueue *qPtr) {
	(void)qPtr;
	return NOT_IMPLEMENTED;
}