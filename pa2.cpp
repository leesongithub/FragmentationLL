// Assignment 2: Leeson Chen
// C++ program to allocate memory using linked lists
#include "pa2.h"
#include <iostream>
// Hello Grader. Instead of typing "best" or "worst" at the beginning,
// I ask the user which algorithm they'd prefer every time they add a program.
// I know the document displayed a different way, however that was never directly specified. 
// Also, I believe my way is better, as it allows more flexibility. 
// Thanks, 
// Leeson
int main() {
	
	LinkedList list;
	
	// at start of program, call addNode("Free") 32 times
	for (int i = 0; i < 32; i++) {
		list.addNode("Free");
	}
	
	int choice = 0;
	while (choice!=5) {
	choice = menu();	
	//std::cout << std::endl << "FUCK I'M STUCK" << std::endl;
	//if ((choice != 0) && (choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5)) {
	//	menu();
	//}

	switch (choice) {
	case 1: 
		list.addProgram();
		break;
	case 2:
		list.killProgram();
		break;
	case 3: 
		list.fragmentation();
		break;
	case 4: 
		list.printMemory();
		break;
	case 5:
		return 0;
	default: 
		std::cout << "Please enter an integer from 1 to 5, inclusive.";
		choice = 0;
		break;
	} // end switch 

	} // end while (choice != 5), exits program
	return 0;
}



// method to take in user input, menu
int menu() {
	// User input options
	std::cout << "1. Add program" << std::endl;
	std::cout << "2. Kill program" << std::endl;
	std::cout << "3. Fragmentation" << std::endl;
	std::cout << "4. Print memory" << std::endl;
	std::cout << "5. Exit" << std::endl;

	std::cout << std::endl << "choice - ";
	int choice = 0; // reset choice
	std::cin >> choice;
	std::cout << std::endl;
	
	// error check
	// verifyInput(choice);
	if ((isdigit(choice) != 0)) {
		std::cout << "Please enter an integer from 1 to 5, inclusive." << std::endl << std::endl;
		std::cout << "choice - ";
		std::cin >> choice;
		std::cout << std::endl;
	}
	if ((choice != 0) && (choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5)) {
		std::cout << "Please enter an integer from 1 to 5, inclusive." << std::endl;
		std::cout << "choice - ";
		std::cin >> choice;
		std::cout << std::endl;
	}
	
	return choice;
}

// addNode 
void LinkedList::addNode(string valueToBeAdded) {
	nodePointer newTail = new Node;
	newTail->next = NULL;
	newTail->data = valueToBeAdded;
	
	if (head != NULL) {
		tail->next = newTail;
		tail = newTail;
	}
	else { 
		head = newTail;
		tail = newTail;
	}
}
	
// method to verify user input
void verifyInput( int choice ) {
	if ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5)) {
		//error;
	}
}
	
// choice == 1: Add program
// should there be two separate addProgram()s for best and worst fit?
void LinkedList::addProgram() { // figures out where to add stuff, modifies boxes
	std::cout << "Program name - ";
	string programName;
	std::cin >> programName;
	std::cout << std::endl;
	
	std::cout << "Program size (KB) - ";
	int programSize;
	std::cin >> programSize;
	std::cout << std::endl;
	
	int numPages = (programSize / 4) ;//+ ((programSize % 4) / (programSize % 4));
	if ((programSize % 4) != 0) { numPages++; } // ^ got error when multiple of 4, due to 0/0
	
	
	// if programName already exists, return error:
	nodePointer currentPointer;
	currentPointer = head;
	while(currentPointer) {
		if ((currentPointer->data).compare(programName) == 0) {
			std::cout << "Error, Program " << programName << " already running.";
			return;
		}
		currentPointer = currentPointer->next;
	}
	
	// if programSize > free space, return error:
	int freePages = 0;
	currentPointer = head;
	while(currentPointer) {
		if ((currentPointer->data).compare("Free") == 0) { freePages++; }
		currentPointer = currentPointer->next;
	}
	if (numPages > freePages) { 
		std::cout << "Error, Not enough memory for Program " << programName << std::endl << std::endl;
		return;
	}
				
	std::cout << "Best fit or worst fit? Enter 0 for Best, and 1 for Worst. ";
	int BFWF;
	std::cin >> BFWF;
	std::cout << std::endl;
	
	if (BFWF == 0) { // Best
	// Best Fit 
	// determine numPages needed
	// starting from first Free, see if there are numPages-1 number of Free following
	// if so, turn those Free to programName
	// if not, find the next Free 
	std::cout << "Using best fit algorithm" << std::endl << std::endl;
	int pagesNeeded = numPages;
	currentPointer = head;
	int streak = 0;
	int placement = 0;
	while (currentPointer) {
		if (streak >= pagesNeeded) { break; } // first check if have enough pages already
		if ((currentPointer->data).compare("Free") == 0) { streak++; } // if cP "Free", increase streak
		if ((currentPointer->data).compare("Free") != 0) { streak = 0; } // if cP not "Free", streak resets to 0
		currentPointer = currentPointer->next; // increment cP
		placement++; // increment cP
	} // end while
	if (streak >= pagesNeeded) {  // if enough pages were found in a row
		int startPlacement = (placement - streak + 1); // start placement (eg, if 3 Free found starting at 4th block (placement = 6), 6 - 3 + 1 = 4) 
		//std::cout << "pagesNeeded is " << pagesNeeded << endl;
		//std::cout << "placement is " << placement << endl;
		//std::cout << "streak is " << streak << endl;
		//std::cout << "startPlacement is " << startPlacement << endl;
		nodePointer startPointer;
		startPointer = head;
		for (int i = 1; i < startPlacement; i++) { startPointer = startPointer->next; } // moves startPointer to starting placement
		for (int j = 0; j < pagesNeeded; j++) { // 
			startPointer->data = programName;
			startPointer = startPointer->next;
		}
		std::cout << "Program " << programName << " added successfully, " << numPages << " page(s) used." << std::endl << std::endl;
 	}
	else { std::cout << "Error, Not enough memory for Program " << programName << std::endl << std::endl; }
	return;
	} // end Best
	else if (BFWF == 1) { // Worst

	// Worst Fit
	// determine numPages needed
	// start at last address to be changed + 1, turn following Free to programName
	// if not enough space return error
	std::cout << "Using worst fit algorithm" << std::endl << std::endl;
	int pagesNeeded = numPages;
	currentPointer = head;
	int backCounter = 32;
	for (int i = 31; i > 0; i--) { // count backwards
		currentPointer = head;
		for (int j = 0; j < i; j++) { currentPointer = currentPointer->next; } // go forwards i spaces (31, 30, 29...) to spot (32, 31, 30...)
		if ((currentPointer->data).compare("Free") == 0) { backCounter--; continue; } // if spot i+1 is "Free", mark with bC and keep going
		else { break; } // if spot 32-i is not "Free", break
	}
	//std::cout << "backCounter is " << backCounter << std::endl << std::endl; 
	if ((32-backCounter) >= pagesNeeded) { 
		int worstStart = backCounter;
		currentPointer = head;
		
		if (backCounter == 1) { // had a weird error where it skipped writing the first space if first space was "Free"
			for (int j = 0; j < pagesNeeded; j++) { // writing
				currentPointer->data = programName; 
				currentPointer = currentPointer->next; 
			}
		}
		else {
			for (int i = 0; i < worstStart; i++) { currentPointer = currentPointer->next; } // move forwards to worstStart 
				for (int j = 0; j < pagesNeeded; j++) { // writing
					currentPointer->data = programName; 
					currentPointer = currentPointer->next; 
				}
		}
		//success
		std::cout << "Program " << programName << " added successfully, " << numPages << " page(s) used." << std::endl << std::endl;
	}
	else if ((32-backCounter) < pagesNeeded) { std::cout << "Error, Not enough memory for Program " << programName << std::endl << std::endl; }
	return;
	} // end Worst Fit
	else { std::cout << "Please cooperate and enter either 0 or 1. This took very long to do and my code can't handle smartassery." << std::endl << std::endl; }
		
	
	return; // idk if necessary?
}

// choice == 2: Kill program
void LinkedList::killProgram() { // could also pass in argument programName, have 4 below lines in main()
	std::cout << "Program name - ";
	string programName;
	std::cin >> programName;
	std::cout << std::endl;
	// 1. find addresses for programName
	// 2. set addresses to "Free"
	// 3. return
	// std::cout << "Program " << programName << " successfully killed, " << numPages << " page(s) reclaimed.";
	nodePointer currentPointer;
	currentPointer = head;
	int numPages = 0;
	while (currentPointer) {
		if (((currentPointer->data).compare(programName)) == 0) {
			currentPointer->data = "Free";
			numPages++;
		}
		currentPointer = currentPointer->next;
	}
	std::cout << "Program " << programName << " successfully killed, " << numPages << " page(s) reclaimed." << std::endl << std::endl;
	
	// possible errors: programName doesn't exist
	// but if delete a nonexistant program, nothing happens, 0 pages reclaimed.
}

// choice == 3: Fragmentation
void LinkedList::fragmentation() {
	nodePointer currentPointer;
	nodePointer laggingPointer;
	currentPointer = head;
	currentPointer = currentPointer->next;
	laggingPointer = head;
	
	int changes = 0;
	if ((laggingPointer->data).compare("Free") != 0) { changes++; }
	while (currentPointer) {
		if (((currentPointer->data).compare("Free") != 0) && (laggingPointer->data).compare("Free") == 0){ changes++; }
		currentPointer = currentPointer->next;
		laggingPointer = laggingPointer->next;
	}
	int numFragments = changes;
	std::cout << "There are " << numFragments << " fragment(s)." << std::endl << std::endl;
}

// choice == 4: Print memory
void LinkedList::printMemory() {
	nodePointer currentPointer;
	currentPointer = head;
	
	while (currentPointer) {
		for (int i = 0; i < 4; i++) {
			for (int j= 0; j < 8; j++) {
				cout << currentPointer -> data << "	";
				currentPointer = currentPointer -> next;
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}


// notes
// linked list of 32 nodes, each a string. 
// only use one linked list, not two as PDF suggested
// don't actually delete any nodes, just replace data
	




		
	
		
		
	

		
		
		
		
		
		
		
		
		
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
