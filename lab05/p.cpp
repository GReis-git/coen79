#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cassert>
#include <cmath>
#include "poly.h"

using namespace std;
using namespace coen79_lab5;

namespace coen79_lab5
{
    const unsigned int polynomial::MAXIMUM_DEGREE;

    // begin lab5 code

	// Copy constuctor
	polynomial::polynomial(const polynomial& source) {
        size = source.size;
        current_degree = source.current_degree;

        poly = new double[size];
        for(int i = 0; i < size; i++) poly[i] = source.poly[i];
	}
	
    // destructor
    polynomial::~polynomial() {
        delete[] poly;
    }

	// update_current_degree
	void polynomial::update_current_degree() {
        /*
        int i = 0;
        //while(poly[i] != 0) {
        while(i < size) {
            if(poly[i] != 0) current_degree = i;
            i++;
        }
        */
        for(int i = 0; i < size; i++)
            if(poly[i] != 0) current_degree = i;
	}

	// reserve
	void polynomial::reserve(size_t new_size) {
		if (new_size <= size);
        else {
            double* temp = poly;
            poly = new double[new_size];

            size = new_size;

            for(int i = 0; i < new_size; i++) poly[i] = 0;

            // current degree = size of old poly
            if(temp != NULL) {
                for (int i = 0; i <= current_degree; i++) {
                    poly[i] = temp[i];
                }
                delete[] temp;
            }
            current_degree = new_size-1;
        }
	}

	// trim
	void polynomial::trim() {
		reserve(degree()+1);
	}
	
    // original constructor modified with new private variables
    polynomial::polynomial(double c, unsigned int exponent)
    {
        size = 0;
        current_degree = 0;
        poly = NULL;
        reserve(exponent+1);
        //assert(exponent <= MAXIMUM_DEGREE);
        //for(int i = 0; i< MAXIMUM_DEGREE; i++) poly[i] = 0;
        poly[exponent] = c;
    }
    // assignment operator to zeroth degree
    polynomial& polynomial::operator =(double c) {
        for(int i = 0; i <= MAXIMUM_DEGREE; i++) poly[i] = 0;
        current_degree = 0;

        poly[0] = c;
        return *this;
    }

    // assignment operator for copy constructor
    polynomial& polynomial::operator =(const polynomial& source) {
        if (&source == this);
        else {
            delete[] poly;
            poly = new double[source.size];
            for(int i = 0; i < source.size; i++) {
                poly[i] = source.poly[i];
            }
            size = source.size;
            current_degree = source.current_degree;
        }
    }

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
        //assert(exponent<=MAXIMUM_DEGREE);
        if(exponent > current_degree) reserve(exponent+1);
        poly[exponent] = coefficient;
        //current_degree = (exponent > degree()) ? exponent : degree();
        update_current_degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
        if(exponent > current_degree) reserve(exponent+1);
        poly[exponent] += amount; 
        //current_degree = (exponent > degree()) ? exponent : degree();
        update_current_degree();
    }

    void polynomial::clear()
    {
        for(int i = 0; i <= MAXIMUM_DEGREE; i++)
            poly[i] = 0;
        current_degree = 0;
    }

    polynomial polynomial::antiderivative() const
    {
        assert(degree() <= MAXIMUM_DEGREE);
        polynomial a(0.0);
        for(int i = 0; i< MAXIMUM_DEGREE; i++)
        {
            a.poly[i+1] = (poly[i]/(i+1));
        }
        return a;
    }

    double polynomial::coefficient(unsigned int exponent) const
    {
        if(exponent > current_degree)
            return 0;
        else
            return poly[exponent];
    }  

    double polynomial::definite_integral(double x0, double x1) const
    {
        double up, low = 0.0; 
        polynomial a;
        a = antiderivative();
        for(int i = 0; i <= MAXIMUM_DEGREE; i++)
        {
            low += (a.poly[i]*pow(x0,i));
            up +=(a.poly[i]*pow(x1,i));
        }
        return up - low;
    }

    //unsigned int polynomial::degree() const
    //{
    //   for(int i = MAXIMUM_DEGREE; i >= 0; i--) 
    //   { 
    //        if(poly[i] != 0)
    //            return i;
    //   }
    //   return 0;
    //}

    polynomial polynomial::derivative() const
    {
        polynomial a; 
        for(int i = 1; i<MAXIMUM_DEGREE; i++)
        {
            if(coefficient(i) != 0)
                a.poly[i-1] = (poly[i]*i);
        }
        a.current_degree = degree() -1;
        return a;
    }

    double polynomial::eval(double x) const
    {
            double sum = coefficient(0);
            for(int i = 1; i< MAXIMUM_DEGREE; i++)
                sum+= (poly[i]*pow(x, i));
            return sum;
    }

    bool polynomial::is_zero() const
    {
        for(int i = 0; i<= MAXIMUM_DEGREE; i++)
        {
            if(poly[i] != 0)
                return false;
        }
        return true;
    }

    unsigned int polynomial::next_term(unsigned int e) const
    {
        for(int i = e+1; e< MAXIMUM_DEGREE; i++)
        {
                if(poly[i] != 0)
                    return i;
        }
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const
    {
        for(int i = e-1; i>=0; i--)
        {
            if(poly[i] != 0)
                return i;
        }
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
        polynomial temp;
        for(int i = 0; i < polynomial::MAXIMUM_DEGREE; i++)
            temp.assign_coef(p1.coefficient(i)+p2.coefficient(i),i);
        return temp;
    }

    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
        polynomial temp; 
        for(int i = 0; i< polynomial::MAXIMUM_DEGREE; i++)
            temp.assign_coef(p1.coefficient(i)-p2.coefficient(i), i);
        return temp;
    }

    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {
        polynomial a;
        for(int i = 0; i<=p1.degree(); i++)
        {
            for(int j = 0; j<= p2.degree(); j++)
                a.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
        }
        return a;
    }

    std::ostream& operator<<(std::ostream& out, const polynomial& p)
    {
        unsigned int i = p.degree();
        streamsize s = out.precision();
        out << fixed;
        out << setprecision(1);
        for(int i = p.degree(); i >= 0; i--) {              
            if(p.degree() == 0) 
                out << p.coefficient(0);
            else if(p.coefficient(i) != 0) {        
                if(i == p.degree())                             
                    out << p.coefficient(i) << "x^" << i << ' ';   
                else if(i < p.degree() && i > 1) {          
                    if(p.coefficient(i) < 0)
                        out << "- ";                       
                    else    
                        out << "+ ";                           
                    out << fabs(p.coefficient(i)) << "x^" << i << ' ';  
                }
                else if(i == 1) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                         
                    else
                        out << "+ "; 
                    out << fabs(p.coefficient(i)) << "x ";   
                }
                else if(i == 0) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                    
                    else
                        out << "+ ";                           
                    out << fabs(p.coefficient(i));            
                }
            }
        }
        out.unsetf(ios_base::floatfield);
        out << setprecision(s);
        return out;
    }   
}