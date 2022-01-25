// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
		
		this->company_name = company_name;
		this->head_ptr = NULL;
		this->tail_ptr = NULL;
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
		
		if (src.get_head() == NULL) return;
		else {
			this->company_name = src.get_name();
			this->head_ptr = NULL;
			this->tail_ptr = NULL;
			list_copy(src.get_head(), head_ptr, tail_ptr);
		}
    }

    
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
		
		list_clear(head_ptr);
		this->company_name = src.get_name();
		this->head_ptr = NULL;
		this->tail_ptr = NULL;
		list_copy(src.get_head(), head_ptr, tail_ptr);
		
		return *this;
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) { //list is empty
			// COMPLETE THE IMPLEMENTATION...
			//std::cout << product_name << std::endl;
            list_init(head_ptr, tail_ptr, product_name, price);
			//node* n = new node(product_name, price);
			//tail_ptr = head_ptr = head;
        }
        else { 
            // COMPLETE THE IMPLEMENTATION...
			//std::cout << product_name << std::endl;
			list_tail_insert(tail_ptr, product_name, price);
			
        }
        
        return true;
    }

    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
		
		node* check = list_search(head_ptr, product_name); //sets head points 
		
		if(check == NULL) return false;
		
		//node* cursor = head_ptr;
		/* list_search returns cursor which is at result
		while (cursor != check) {
		
			if(cursor == check) list_head_remove(cursor);
			cursor = cursor->getLink();
		
		}
		delete cursor;
		*/
		check->setName(head_ptr->getName());
		check->setPrice(head_ptr->getPrice());
		
		list_head_remove(head_ptr);
		
		return true;
		
    }
    
    
}
