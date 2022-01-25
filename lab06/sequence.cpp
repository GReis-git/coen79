//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }

    sequence::~sequence() {

        list_clear();

        tail_ptr = NULL;
        head_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
        
    }

    void start() {
        // 0 item list
        if (head_ptr == NULL) return;
        // 1 item list
        else if(head_ptr == tail_ptr) {
            cursor = head_ptr;
            precursor = NULL;
        }
        // 2+ item list
        else {
            cursor = head_ptr;
            precursor = NULL;
        }
    }

    void end() {
        // 0 item list
        if (tail_ptr == NULL) return;
        // 1 item list
        else if (head_ptr == tail_ptr) {
            cursor = tail_ptr;
            precursor = NULL;
        }
        // 2+ item list
        else {
            cursor = tail_ptr;
            precursor = list_locate(head_ptr, many_nodes-1);
        }
    }

    void advance() {
        precursor = cursor;
        cursor = cursor->link();
    }

    void insert(const value_type& entry) {
    	// 0 item list or 1 item list
  		if (head_ptr == NULL || head_ptr == tail_ptr) {
       		list_head_insert(head_ptr, entry);
       		cursor = head_ptr;
			precursor = NULL;
			tail_ptr = entry;
        }
		// insert at front or no item
        else if (cursor==head_ptr || !is_item()) {
            list_head_insert(precursor, entry);
			cursor = head_ptr;
			precursor =  NULL;
        }
        // 2 item list
        else {
        	// base case -> no special effects for +2 size
			list_insert(precursor, entry);
			cursor = precursor->link();
		}
        many_nodes++;    
    }
    
    void attach(const value_type& entry) {
		// 0 item list
		if(head_ptr == NULL) {
			list_head_insert(head_ptr, entry);
			cursor = head_ptr;
			precursor = NULL;
			tail_ptr = head_ptr;
		}
		// 1 item list  
		else if(precursor == NULL) {
			list_insert(cursor, entry)
			cursor = head_ptr->link();
			precursor = head_ptr;
			tail_ptr = cursor;
		}
		// 2+ item list
		else {
			list_insert(cursor, entry);
			cursor = precursor->link()->link();
			precursor = precursor->link();
			// set tail
			if(cursor->link() == NULL) tail_ptr = cursor;
		}
    	many_nodes++;
	}

    void operator=(const sequence& source) {

        list_clear(head_ptr);
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		many_nodes = source.size();
		
		/* 
        many_nodes = source.many_nodes;
        head_ptr = source.head_ptr;
        tail_ptr = source.tail_ptr;
        precursor = source.precursor;
        cursor = source.cursor;
    	*/
	}

    void remove_current() {
		if(!is_item()) return;
		// 0 item list
		if(head_ptr == NULL) return;
    	// 1 item list
		else if (precursor == NULL) {
			list_head_remove(head_ptr);
		}
		else {
			list_remove(precursor);
			cursor = precursor->link();
		}


	}
    
}
