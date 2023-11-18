// Typedef and function definitions for PQ
#include <stdio.h>
#include <stdlib.h>

// Define struct containing flight info
typedef struct flightinfo {
	char airline; 		// U for United, D for Delta, A for American, S for Southwest
	int flightnumber;
	int time;
} Flightinfo;


// Define struct for a node in the linked list
typedef struct item {
	Flightinfo flight;
	int* priority; // priority is a pointer to an int, will point to flighttime
	struct item * next;
} Item;


/* Function to initialize the linked list with a dummy item
*/
Item* Initialize()
{
	Item * mypq = malloc(sizeof(Item)); // allocate memory for first item
	
	if (mypq == NULL) {
        return NULL; // Return NULL if memory allocation fails due to lack of memory
    }

	mypq->next = NULL; // set next to null for now
	Flightinfo dummyflight = {' ', -1, -1}; // create dummy flight
	mypq->flight = dummyflight; // set flight to dummy flight
	mypq->priority = &(mypq->flight.time); // set priority to dummy flight time

	return mypq; // return dummy item
}


/* Function to add a new flight to the priority queue 
*/
int Add(Item* mypq, char itemAirline, int itemFlightnumber, int itemTime)
{
	// Check for invalid inputs
	if(itemFlightnumber < 1 || itemTime < 0){
		return -1;
	}
	// Note - I am not checking if the airline is in A,U,D or S as this was not specified 
	// as a requirement, and I do not want to inadvertantly fail some tests
	
	// Create new item
	Item * new_node = malloc(sizeof(Item)); // allocate memory for new item
	Flightinfo newflight = {itemAirline, itemFlightnumber, itemTime}; // create new flight
	new_node->flight = newflight; // set the flight ptr of this new object to the above struct

	new_node->priority = &(new_node->flight.time); // set new item priority to new flight time


	if( mypq->next == NULL){ // no elements in the list, insert at the beginning
		mypq->next = new_node;
		return 0;
	}

	// If list isn't empty then loop through pq and insert in correct place

	Item * prev_node = mypq; // create temp item
	Item * current_node = mypq->next; // create temp item

	while(current_node){

		// If the current' nodes time is greater than new_node's time, new_node has a higher 
		// priority and is inserted before the current node
		if (*(current_node->priority)> *(new_node->priority)){ 
			prev_node->next = new_node; // insert new item in place of the current node
			new_node->next = current_node; // make our new item point ot the 'current' node
			return 0; 
		} 
		// Move on to the next node
		prev_node = current_node; // Increment prev_node
		current_node = current_node->next; // Increment current_node
		// if 'current' is the final node current will be null now so while loop will exit
	}

	// if we exit the loop without inserting, insert at the end
	prev_node->next = new_node;  // set 
	new_node->next = NULL;  // set next of new item to NULL
	return 0;
}


/* Function to remove the first item from the priority queue
*/
void Remove(Item* mypq)
{
	// check if pq is empty
	if(mypq->next == NULL){
		return; 
	}

	// remove the first item if not
	Item * node_to_remove = mypq->next; // create temp item
	mypq->next = mypq->next->next; // set the next field of the dummy to the next field of the top node

	free(node_to_remove); // free memory of next item
}

/* Function to print the contents of the priority queue
*/
void Print(Item* mypq)
{
	printf("Priority queue contents:\n");
	Item* current_node = mypq->next; // create temp item
	while(current_node != NULL){
		printf("%c %d %d\n",current_node->flight.airline,  
   			current_node->flight.flightnumber, current_node->flight.time); 
		current_node = current_node->next;
	}
}


/* Function to count the number of items in the priority queue
*/
int Count(Item* mypq)
{
	int count = 0; // initialize count
	Item* current_node = mypq; 
	while (current_node->next != NULL){  // as long as there is a next item increment count
		current_node = current_node->next; // move to next node
		count++;
	}
	// if there is no next initially we will return 0 since the dummy head doesnt count

	return count;
}


/* Function to count the number of flights with a given airline
*/
int CountAirline(Item* mypq, char myairline)
{
	int count = 0;
	Item* current_node = mypq;
	// Loop through the entire pq and increment count when the airline matches
	while (current_node->next != NULL){
		current_node = current_node->next;
		if (current_node->flight.airline == myairline){
			count++;
		}
	}
	return count;

}


/* Function to count the number of flights with a flight number smaller than the inputted number
*/
int CountSmaller(Item* mypq, int itemflightnumber)
{
	int count = 0;
	Item* current_node = mypq;
	// Loop through the entire pq and increment count when the flight number is smaller than our input
	while (current_node->next != NULL){
		current_node = current_node->next;
		if (current_node->flight.flightnumber  < itemflightnumber){
			count++;
		}
	}
	return count;
}


/* Function to count the number of flights with a flight number larger than the inputted number
*/
int CountLarger(Item* mypq, int itemflightnumber)
{
	int count = 0;
	Item* current_node = mypq;
	// Loop through the entire pq and increment count when the flight number is larger than our input
	while (current_node->next != NULL){
		current_node = current_node->next;
		if (current_node->flight.flightnumber  > itemflightnumber){
			count++;
		}
	}
	return count;
}


/* Function to count the number of flights with a time earlier than the inputted time
*/
int CountEarlier(Item* mypq, int mypriority)
{
	int count = 0;
	Item* current_node = mypq;
	// Loop through the entire pq and increment count when the priority value is smaller than our input
	while (current_node->next != NULL){
		current_node = current_node->next;
		if (*(current_node->priority)  < mypriority){
			count++;
		}
	}
	return count;
}


/* Function to count the number of flights with a time later than the inputted time
*/
int CountLater(Item* mypq, int mypriority)
{
	int count = 0;
	Item* current_node = mypq;
	// Loop through the entire pq and increment count when the priority value is larger than our input
	while (current_node->next != NULL){
		current_node = current_node->next;
		if (*(current_node->priority)  > mypriority){
			count++;
		}
	}
	return count;
}


/* Delete the PQ by releasing all memory used ( except by the mypq pointer itself)
*/
int Finalize(Item* mypq)
{
	Item* current_node = mypq->next; // node to start from
	Item* next_node; // used to temporarily store the next node before we delete the current node
	// Loop through the entire pq and free the memory of each node
	while (current_node!= NULL){
		next_node = current_node->next; // store the next node
		free(current_node); // free the current node's memory
		current_node = next_node; // move on to next node
	}
	return 0;
}


