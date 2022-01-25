//
// FILE: sequence1.cpp
//  Sequence Class
//
//  COEN 79
//  
//
//
// INVARIANT for the sequence ADT (i.e. verbalization of rules governing
//   private member function behavior):
//   1. The number of items in the sequence is in the member variable used
//      (i.e. used = 0 means the sequence is empty).
//   2. For an empty sequence, we do not care what is stored in any of the
//      array data.  For a non-empty sequence, the items in the sequence are
//      stored in strictly maintained order in data[0] through
//      data[used].  We don't care what's in the rest of data (so don't
//      need to initialize data in the constructor).
//   3. To maintain strict order, current_index is used to keep track
//      of current location in data; when current_index is used-1,
//      we're at the last place in the array.  Also whenever current_index
//      is greater than or equal to used, there is no current item.
//   4. capacity keeps track of the current capacity of the array pointed
//      to by data; capacity starts out with the value initial_capacity
//      and is changed by resize as needed (whenever used is greater than
//      or equal to capacity).
//


#include "sequence1.h"
#include <cassert>
#include <cmath>

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {
	
	sequence::sequence() {
		used = 0;
		current_index = 0;	
	}

    
	void sequence::start() {
		current_index = 0;
	}

    
    void sequence::end() {
		// even if sequence is empty, should return the 'end' of the sequence
        current_index = used-1;
    }
    
    sequence::value_type sequence::current() const {
        return data[current_index];
	};
    
    
    void sequence::advance() {
        //TO DO
        //set the current index pointing to the next item
        //check: 1.if reach the end of the sequence; 2.if reach the capacity of the 'bag'
		if (current_index < CAPACITY) 
			current_index++;
	}

    bool sequence::is_item() const {
        //TO DO
        //does the current index point to an item or not
		return (current_index < size());
    }
    
    
	void sequence::insert(const value_type& entry) {
		//TO DO
		//check capacity first
		//if the current index pointing to no item, then insert the entry at the front of the sequence
		//otherwise, shifting other items over, and insert the new entry at the current index
		//don't forget to increment the 'used' variable
		assert(CAPACITY - used > 1);
		if (is_item()) {
			for(int i = used; i > current_index; i--) {
				data[i] = data[i-1];
			}
			data[current_index] = entry;
		}
		else {
			for(int i = used; i > 0; i--) {
				data[i+1] = data[i];
			}
			data[0] = entry;
		}
		used++;
	}

    
    void sequence::attach(const value_type& entry) {
    	//TO DO
    	//check capacity first
    	//if the current index pointing to no item, then insert the entry at the end of the sequence
		//otherwise, shifting other items over, and attach the new entry behind the current index (current_index+1)
		//don't forget to increment the 'used' variable
    	assert(CAPACITY - used > 1);
		if (!is_item()) {
			end();
			data[current_index+1] = entry;
		}
		else {
			
			//insert(entry); cannot call insert -- need to ++ index before insertion to data
			for(int i = used; i > current_index+1; i--) {
				data[i] = data[i-1];
			}
			current_index++;
			data[current_index] = entry;
		}
		used++;
	}

    void sequence::remove_current() {
    	if (is_item()) {
			for(int i = current_index; i < used-1; i++) {
				data[i] = data[i+1];
			}
			used--;
		}

    }

	void sequence::insert_front(const value_type& entry) {
		//TO DO
		//check capacity first
		//move the current index to the front and then insert
		assert(CAPACITY - used > 1);
		start();
		insert(entry);
	}


	void sequence::attach_back(const value_type& entry) {
		//TO DO
		//check capacity first
		//move the current index to the end and then attach
		assert(CAPACITY - used > 1);
		current_index = used;
		attach(entry);
	}

	void sequence::remove_front() {
		//TO DO
		//don't forget to check if there is an item or not
		// Move to front
		start();
		if (is_item()) remove_current();
	}

	sequence::size_type sequence::size() const {
		//TO DO
		//return the number of entry
		return used;
	}

    sequence::value_type sequence::operator[](int index) const {
		if (is_item()) return data[index];
	}
    
	sequence operator+(sequence& lhs, sequence& rhs) {
		//TO DO
		//combine 2 sequences to 1 new sequence
		//don't forget to check the total capacity
		assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
		
		sequence s;
		for(int i = 0; i < lhs.size(); i++) {
			lhs.start();
			s.attach(lhs.current());
			lhs.remove_front();
		}
		for(int i = 0; i < rhs.size(); i++) {
			rhs.start();
			s.attach(rhs.current());
			rhs.remove_front();
		}
		return s;


	}

	sequence operator+=(sequence& lhs, sequence& rhs) {
		lhs = lhs + rhs;
	}


	// Homework Question Functions
	double sequence::mean() const
	{
		double total;
		for(int i = 0; i < used; i++) {
			total+=data[i];
		}
		return total/used;
	}

	double sequence::standardDeviation() const
	{
		double mu = mean();
		double d1;
		for(int i = 0; i < used; i++) {
			d1 += pow((data[i] - mu), 2);
		}
		return sqrt(d1/used);

	}

	sequence::value_type summation(const sequence &s)
	{
		return s.mean()*s.size();
	}

}