/*****************************************************************************

Project      : Sort
Version      : beta 1.0
Date         : 2012-08-20
Author       : Jae-Yeol, Shim                  
Company      : KETI                          
OS type	     : Linux (Cygwin for Vista)
Program type : .C

Comments: 1.

******************************************************************************/

#include "sort.h"

extern NodeStr *head;

uint8_t crossCheck(NodeStr * left, NodeStr * right){
				NodeStr * tmp = head;

				if(left == NULL || right == NULL)
								return 0;
				
				while(tmp != left){
								if(tmp == right)
												return 1;
								tmp = tmp->Next;
				}

				return 0;
}


NodeStr * indexToList(uint8_t index){
				NodeStr *list = head;
				while(index--)
								list = list->Next;
				return list;
}


uint8_t listToIndex(NodeStr *list){
				NodeStr *tmp = head;
				uint8_t index = 0;

				while(tmp != list){
								index++;
								tmp = tmp->Next;
				}
				return index;
}

void swapList(NodeStr * left, NodeStr * right){
		NodeStr * rightNext = right->Next;
		NodeStr * rightPre = right->Pre;
		NodeStr * leftNext = left->Next;
		NodeStr * leftPre = left->Pre;

		if(left == NULL && right == NULL ){
						return;
		}
		if(left == right){
						return;
		}

		if(left->Pre == NULL)
				head = right;
		
		else
				left->Pre->Next = right;

		left->Next->Pre = right;

		right->Pre->Next = left;

		if(rightNext != NULL)
				rightNext->Pre = left;

		if(leftNext != right)
						right->Next = left->Next;
		else
						right->Next = left;

		right->Pre = leftPre;
		
		left->Next = rightNext;

		if(leftNext != right)
						left->Pre = rightPre;
		else
						left->Pre = right;
}


PartStr partition(NodeStr * left, NodeStr * right){
	PartStr Part;
	NodeStr *pivot;//, *tmp;
	NodeStr *low, *high;
	uint8_t indLow, indHigh;

	pivot = left;
	Part.pivot = pivot;
	low = left->Next;
	high = right;

		// not cross
	while(!crossCheck(low,high)){
	
		while( low != right && low->Id < pivot->Id)
						low = low->Next;

		while( high != left && high->Id > pivot->Id)
						high = high->Pre;

		// low <= right
		if( low == right && low->Id < pivot->Id){
			indLow = listToIndex(left);
			indHigh = listToIndex(high);
			swapList(left, high);

			left = indexToList(indLow);
			high= indexToList(indHigh );

			Part.left = left;
			Part.right = high->Pre;
			return Part;
		}
		// low <= right
		else if( high == left && high->Id > pivot->Id){

			Part.left = left;
			Part.right = right;
			return Part;
		}
		else if(!crossCheck(low , high)){

			indLow = listToIndex(low);
			indHigh = listToIndex(high);

			swapList(low, high);

			low = indexToList( indLow );
			high= indexToList(indHigh );

		}
	}

	indLow = listToIndex(left);
	indHigh = listToIndex(high);
	swapList(left, high);
	left = indexToList(indLow);
	high= indexToList(indHigh );

	Part.left = left;
	Part.right = right;

	return Part;
}


void quickSort(NodeStr * left, NodeStr * right){
	PartStr part;

	if(!crossCheck(left, right) && left != right){
		part = partition( left, right);

		if(part.pivot->Pre != NULL)
			quickSort( part.left , part.pivot->Pre);
	
		if(part.pivot->Next != NULL )
			quickSort( part.pivot->Next, part.right);
	}

}

void command(uint8_t data){
		switch(data){

			case 'i':
			case 'I':
				break;

			case 'r':
			case 'R':
				break;

			case 's':
			case 'S':
				break;

			case 'l':
			case 'L':
				break;

			case 'c':
			case 'C':
				break;

			case 'e':
			case 'E':
				break;

			case 'q':
			case 'Q':
				printf("* Terminate Network Test *\n");
				serial_close();
				freeList();
				exit(0);
				break;

			default:
					break;

		}
}

void Sort(void){
		NodeStr *Last=head;

		Last=head;

		while(Last->Next != NULL)
			Last = Last->Next;

		quickSort(head ,Last);

}
