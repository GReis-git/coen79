
#include "keyed_bag.h"
#include <cassert>
#include <algorithm>

using namespace std;
using namespace coen79_lab4;


namespace coen79_lab4 {

    const keyed_bag::size_type keyed_bag::CAPACITY;

    keyed_bag::keyed_bag() {
        used = 0;
    }

    void keyed_bag::erase() {
        used = 0;
    }

    bool keyed_bag::erase(const keyed_bag::key_type& key) {
        if(!has_key(key)) return false;

        for(int i = 0; i < used; i++) {
            if(keys[i] == key) {
                data[i] = data[used-1]; // data[used-1] will be overwritten if new insert
                keys[i] = keys[used-1];
                used--;
            } 
        }
    }

    void keyed_bag::insert(const keyed_bag::value_type& entry, const keyed_bag::key_type& key) {
        if(used < CAPACITY && !has_key(key)) {
            data[used] = entry;
            keys[used] = key;
            used++;
        }
        else return;
    }
    void keyed_bag::operator +=(const keyed_bag& addend) {
        if(!(used + addend.size() <= CAPACITY) || hasDuplicateKey(addend)) return;
        else {
            std::copy(addend.data, addend.data + addend.used, data+used);
            std::copy(addend.keys, addend.keys + addend.used, keys+used);
            used+=addend.used;
        }
    }

    bool keyed_bag::has_key(const keyed_bag::key_type& key) const {
        for(int i = 0; i < used; i++) {
            if (keys[i] == key) {
                return true;
            }
        }
        return false;
    }
    keyed_bag::value_type keyed_bag::get(const keyed_bag::key_type& key) const {
        if(!has_key(key));
        else {
            for(int i = 0; i < used; i++) {
                if(keys[i] == key) return data[i];
            }
        }
    }
    keyed_bag::size_type keyed_bag::size() const {
        return used;
    }
    keyed_bag::size_type keyed_bag::count(const keyed_bag::value_type& target) const {
        keyed_bag::size_type count = 0;
        for(int i = 0; i < used; i++) {
            if(data[i] == target) count++;
        }
        return count;
    }
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        for(int i = 0; i < used; i++) {
            if(otherBag.has_key(keys[i])) return true;
        }
        return false;
    }
    keyed_bag operator+(const keyed_bag& b1, const keyed_bag& b2) {
        if(b1.size() + b2.size() < b1.CAPACITY) {
            keyed_bag temp;
            temp+=b1;
            temp+=b2;
            return temp;
        }
    }
}