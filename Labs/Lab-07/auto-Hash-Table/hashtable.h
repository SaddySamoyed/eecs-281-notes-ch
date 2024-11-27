// Project Identifier: 2C4A3C53CD5AD45A7BEA3AE5356A3B1622C9D04B
#ifndef HASHTABLE_H
#define HASHTABLE_H

// Project Identifier: 2C4A3C53CD5AD45A7BEA3AE5356A3B1622C9D04B

// INSTRUCTIONS:
// fill out the methods in the class below.

// You may assume that the key and value types can be copied and have default
// constructors.

// You can also assume that the key type has (==) and (!=) methods.

// You may assume that Hasher is a functor type with a
// size_t operator()(const Key&) overload.

// The key/value types aren't guaranteed to support any other operations.

// Do not add, remove, or change any of the class's member variables.
// The num_deleted counter is *optional*. You might find it helpful, but it
// is not required to pass the lab assignment.

// Do not change the Bucket type.

// SUBMISSION INSTRUCTIONS:
// Submit this file, by itself, in a .tar.gz.
// Other files will be ignored.

#include <cstdint>
#include <functional> // where std::hash lives
#include <vector>
#include <cassert> // useful for debugging!
#include <iostream>

// A bucket's status tells you whether it's empty, occupied, 
// or contains a deleted element.
enum class Status : uint8_t {
    Empty,
    Occupied,
    Deleted
};

template<typename K, typename V, typename Hasher = std::hash<K>>
class HashTable {
    // used by the autograder; do not change/remove.
    friend class Verifier;
public:
    // A bucket has a status, a key, and a value.
    struct Bucket {
        // Do not modify Bucket.
        Status status = Status::Empty;
        K key;
        V val;
    };

    HashTable() {
        // TODO: a default constructor (possibly empty).
        buckets.resize(20);
        // You can use the following to avoid implementing rehash_and_grow().
        // However, you will only pass the AG test cases ending in _C.
        // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
        //    buckets.resize(10000);
    }

    size_t size() const {
        return num_elements;
    }

    // returns a reference to the value in the bucket with the key, if it
    // already exists. Otherwise, insert it with a default value, and return
    // a reference to the resulting bucket.
    V& operator[](const K& key) {
        // TODO
        // grow?
        if (num_elements >= (buckets.size() / 2)) {
            rehash_and_grow();
        }


        Hasher hasher;
        size_t currentindex = 0;
        size_t firstDeletedIndex = SIZE_MAX;
        bool metDeleted = false;
        size_t idealIndex = hasher(key) % buckets.size();

        while (true) {
            idealIndex = (hasher(key) + currentindex) % buckets.size();
            
            // if we have searched around the table, it means that there are only deleted elements and 
            // wrong occupied elements, we should insert at the first deleted index
            if (currentindex >= buckets.size()) {
                buckets[firstDeletedIndex] = Bucket{ Status::Occupied, key, V() };
                num_elements++;
                return buckets[firstDeletedIndex].val;
            }

            // we will only use the first deleted index met, in case we have not found
            if (buckets[idealIndex].status == Status::Deleted) {
                if (!metDeleted) {
                    firstDeletedIndex = idealIndex;
                }
                metDeleted = true;
                currentindex++;
                // specially if there aint no element, we should insert at the first deleted index
                if (num_elements == 0) {
                    buckets[idealIndex] = Bucket{ Status::Occupied, key, V() };
                    num_elements++;
                    return buckets[idealIndex].val;
                }
                continue;
            }

            else if (buckets[idealIndex].status == Status::Empty) {
                // empty: once met, then there is no existing key as "key". whatever, we insert it
                // and note: if we have met deleted, we should insert at the first deleted index
                if (metDeleted) {
                    buckets[firstDeletedIndex] = Bucket{ Status::Occupied, key, V() };
                    num_elements++;
                    return buckets[firstDeletedIndex].val;
                }
                else {
                    buckets[idealIndex] = Bucket{ Status::Occupied, key, V() };
                    num_elements++;
                    return buckets[idealIndex].val;
                }
            }

            else {
                // occupied: if key is found, return the value
                if (buckets[idealIndex].key == key) {
                    return buckets[idealIndex].val;
                }
                currentindex++;
            }
        }
    }

    // insert returns whether inserted successfully
    // (if the key already exists in the table, do nothing and return false).
    bool insert(const K& key, const V& val) {
        // grow?
        if (num_elements >= (buckets.size() / 2)) {
            rehash_and_grow();
        }


        // basically the same as operator[], except that we dont care about the index
        Hasher hasher;
        size_t currentindex = 0;
        size_t firstDeletedIndex = SIZE_MAX;
        bool metDeleted = false;
        size_t idealIndex = hasher(key) % buckets.size();

        while (true) {
            idealIndex = (hasher(key) + currentindex) % buckets.size();
            
            // if we have searched around the table, it means that there are only deleted elements and 
            // wrong occupied elements, we should insert at the first deleted index
            if (currentindex >= buckets.size()) {
                buckets[firstDeletedIndex] = Bucket{ Status::Occupied, key, val };
                num_elements++;
                return true;
            }

            // we will only use the first deleted index met, in case we have not found
            if (buckets[idealIndex].status == Status::Deleted) {
                if (!metDeleted) {
                    firstDeletedIndex = idealIndex;
                }
                metDeleted = true;
                currentindex++;
                // specially if there aint no element, we should insert at the first deleted index
                if (num_elements == 0) {
                    buckets[idealIndex] = Bucket{ Status::Occupied, key, val };
                    num_elements++;
                    return true;
                }
                continue;
            }

            else if (buckets[idealIndex].status == Status::Empty) {
                // empty: once met, then there is no existing key as "key". whatever, we insert it
                // and note: if we have met deleted, we should insert at the first deleted index
                if (metDeleted) {
                    buckets[firstDeletedIndex] = Bucket{ Status::Occupied, key, val };
                    num_elements++;
                    return true;
                }
                else {
                    buckets[idealIndex] = Bucket{ Status::Occupied, key, val };
                    num_elements++;
                    return true;
                }
            }

            else {
                // occupied: if key is found, return the value
                if (buckets[idealIndex].key == key) {
                    return false;
                }
                currentindex++;
                continue;
            }
        }
        return true;
    }




    // erase returns the number of items remove (0 or 1)
    size_t erase(const K& key) {
        if (num_elements == 0) {
            return 0;
        }
        Hasher hasher;
        size_t currentindex = 0;
        while (true) {
            if (currentindex > buckets.size()) {
                return 0;
            }
            size_t idealIndex = (hasher(key) + currentindex) % buckets.size();
            if (buckets[idealIndex].status == Status::Empty) {
                // empty: once met, then there is no existing key as "key".
                return 0;
            }
            else if (buckets[idealIndex].status == Status::Occupied) {
                if (buckets[idealIndex].key == key) {
                    buckets[idealIndex].status = Status::Deleted;
                    num_elements--;
                    return 1;
                }
                currentindex++;
                continue;
            }
            else {
                currentindex++;
                continue;
            }
        }
        
    }


private:
    size_t num_elements = 0;
    size_t num_deleted = 0; // OPTIONAL: you don't need to use num_deleted to pass
    std::vector<Bucket> buckets;

    void rehash_and_grow() {
        // You can avoid implementing rehash_and_grow() by calling
        //    buckets.resize(10000);
        // in the constructor. However, you will only pass the AG test cases ending in _C.
        // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
        std::vector<Bucket> cache = buckets;
        buckets.clear();
        buckets.resize(cache.size() * 2);


        num_elements = 0;

        for (auto bucket : cache) {
            if (bucket.status == Status::Occupied)
                insert(bucket.key, bucket.val);
        }

    }

    // You can add methods here if you like.
    // TODO
};

#endif // HASHTABLE_H