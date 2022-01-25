// FILE: node.cpp
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

    //begin implemented functions:
	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
		head_ptr = NULL;
		tail_ptr = NULL;
		
		// 1 size list
		if (start_ptr == end_ptr) return;
		// 0 size list
		else if (start_ptr == NULL) return;
		// 2+ size list
		else {
			// insert first node
			list_head_insert(head_ptr, start_ptr->data());
			tail_ptr = head_ptr;
			
			// fill in rest of nodes
			start_ptr = start_ptr->link();
			for (start_ptr; 
				start_ptr != NULL && start_ptr != end_ptr; 
				start_ptr=start_ptr->link()) {
				

				list_insert(tail_ptr, start_ptr->data());
				tail_ptr = tail_ptr->link();
			}
		}
	}

    size_t list_occurrences(node* head_ptr, const node::value_type& target) {
		
		size_t total = 0;
		
		// node iterator matching type of target
		const node* cursor;
		
		cursor = list_search(head_ptr, target);
		while (cursor != NULL) {
			cursor = list_search(cursor->link(), target);
			total++;
		}
		return total;
	}
    
	void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
		// node iterator
		node* cursor = head_ptr;
		if (position <= list_length(head_ptr)+1) return;
		else if (position < 1) return;
		else if (position > 1) {
			for(int i = 0; i < position-1; i++) cursor = cursor->link();
		}
		// add head if position is 1
		else list_head_insert (head_ptr, entry);
		
		list_insert(cursor, entry);	
	}
    
	node::value_type list_remove_at(node*& head_ptr, size_t position) {
	
		if (position > 0 && position <= list_length(head_ptr)+1) return NULL;
		if (position > 1) list_remove(list_locate(head_ptr, position-1));
		else list_head_remove(head_ptr);
		return head_ptr->data();
			
	}

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
		// nodes for list_piece args for new segment
		node* rethead = NULL;
		node* rettail = NULL;
		node* startnode = list_locate(head_ptr, start);
		node* finishnode = list_locate(head_ptr, finish+1);

		list_piece(startnode, finishnode, rethead, rettail);
		return rethead;

	}
    
	void list_print (const node* head_ptr) {
		// node iterator matching type head_ptr
		const node* cursor = head_ptr;
		while(cursor != NULL) {
			std::cout << cursor->data() << ", ";
			cursor = cursor->link();
		}
		cout << endl;
	}

    void list_remove_dups(node* head_ptr) {
		node* check;
		node* cursor;

		cursor = head_ptr;
		
		while (cursor != NULL && cursor->link() != NULL) {
			check = cursor;
			while (check->link() != NULL) {
				if(cursor->data() == check->link()->data()) list_remove(check);
				else check = check->link();
			}
			cursor = cursor->link();
		}
	}
    node* list_detect_loop (node* head_ptr) {
		// list size 0 or 1 cannot contain duplicates
		if (head_ptr == NULL) return NULL;	
		
		node* cursor = head_ptr;
		node* doubleMoveCursor = head_ptr;

		while (doubleMoveCursor != NULL && doubleMoveCursor->link() != NULL) {
			doubleMoveCursor = doubleMoveCursor->link()->link();
			cursor = cursor->link();

			if (doubleMoveCursor == cursor) break; // save position
		}
		
		if (doubleMoveCursor == NULL || doubleMoveCursor->link() == NULL) return NULL; // no loop found
		
		cursor = head_ptr;
		while (doubleMoveCursor != cursor) {
			doubleMoveCursor = doubleMoveCursor->link();
			cursor = cursor->link();
		}
		return cursor;
	}   
}
