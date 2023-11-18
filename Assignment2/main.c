// Priority queue using a linked list

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

int main()
{
	Item* mypq = Initialize();

	// test cases with empty queue
	Print(mypq);
	printf("Number of flights: %d\n",Count(mypq));
	Remove(mypq);


	// test cases without errors
	int returnval;
	returnval = Add(mypq,'S',1402,2317);
	if(returnval == 1) printf("Error adding to pq\n");
	returnval = Add(mypq,'C',70,1043);
	returnval = Add(mypq,'S',201,500);

	returnval = Add(mypq,'D',1691,1601);

	printf("Number of flights: %d\n",Count(mypq));
	printf("Number of Southwest flights: %d\n",CountAirline(mypq,'S'));
	printf("Number of Delta flights: %d\n",CountAirline(mypq,'D'));

	int flighttest = 100;
	printf("Number of flight numbers smaller/larger than %d: %d, %d\n",flighttest,
		CountSmaller(mypq,flighttest),CountLarger(mypq,flighttest));

	int mypriority = 1200;
	printf("Number of flights earlier/later than %d: %d, %d\n",mypriority,
		CountEarlier(mypq,mypriority),CountLater(mypq,mypriority));

	Remove(mypq);
	Print(mypq);

	Finalize(mypq);
	free(mypq);

	
	// // Custom test
	// printf("\n\nCustom tests\n\n");
	// // Initialize queue, delete from empty, count items
	// mypq = Initialize();
	// Remove(mypq);
	// Print(mypq);
	// printf("Number of flights: %d\n",Count(mypq));
	// // Add 10 flights, 2 of which are invalid 
	// returnval = 0;
	// returnval = Add(mypq, 'S', 1402, 2317);
	// returnval = Add(mypq, 'C', 70, 1043);
	// returnval = Add(mypq, 'U', 201, 500);
	// returnval = Add(mypq, 'A', 1402, -2317);
	// if(returnval == -1) printf("Error adding to pq\n");
	// returnval = Add(mypq, 'C', -70, 1023);
	// if(returnval == -1) printf("Error adding to pq\n");
	// returnval = Add(mypq, 'S', 201, 20);
	// returnval = Add(mypq, 'A', 1691, 1602);
	// // Print queue
	// Print(mypq);
	// // Compute statistics
	// printf("Number of flights: %d\n",Count(mypq));
	// printf("Number of Southwest flights: %d\n",CountAirline(mypq,'S'));
	// printf("Number of Delta flights: %d\n",CountAirline(mypq,'D'));
	// printf("Number of American flights: %d\n",CountAirline(mypq,'A'));
	// printf("Number of United flights: %d\n",CountAirline(mypq,'U'));
	// flighttest = 700;
	// printf("Number of flight numbers smaller/larger than %d: %d, %d\n",flighttest,
	// 	CountSmaller(mypq,flighttest),CountLarger(mypq,flighttest));
	// mypriority = 1200;
	// printf("Number of flights earlier/later than %d: %d, %d\n",mypriority,
	// 	CountEarlier(mypq,mypriority),CountLater(mypq,mypriority));
	// // Delete 4, print
	// printf("\nDeleting 2 flights, print\n");
	// Remove(mypq); Remove(mypq);
	// Print(mypq);
	// // Delete 4, print
	// printf("\n Delete 4 flights, print\n");
	// Remove(mypq); Remove(mypq); Remove(mypq); Remove(mypq);
	// Print(mypq);

	// // Free memory
	// free(mypq);


	// Try counting on empty queue
	printf("\n\nCounting operations on empty queue\n\n");
	mypq = Initialize();
	printf("Number of flights: %d\n",Count(mypq));
	printf("Number of Southwest flights: %d\n",CountAirline(mypq,'S'));
	printf("Number of Delta flights: %d\n",CountAirline(mypq,'D'));
	printf("Number of American flights: %d\n",CountAirline(mypq,'A'));
	printf("Number of United flights: %d\n",CountAirline(mypq,'U'));
	flighttest = 700;
	printf("Number of flight numbers smaller/larger than %d: %d, %d\n",flighttest,
	CountSmaller(mypq,flighttest),CountLarger(mypq,flighttest));
	mypriority = 1200;
	printf("Number of flights earlier/later than %d: %d, %d\n",mypriority,
	CountEarlier(mypq,mypriority),CountLater(mypq,mypriority));
	

	return 0;
}
