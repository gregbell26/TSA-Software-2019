//
// Created by jimmy on 11/20/2019.
//

#ifndef ACRYLIC2D_HASH_TABLE_H
#define ACRYLIC2D_HASH_TABLE_H
template <typename T>

struct Link{
    T value;
    Link* link;
};

class Hash_Table {
    private:
    unsigned long* table;
    unsigned size;
    hash(T value){
        hash<T> hashVal;
        return hashVal(value);
    }
    public:
    Hash_Table(unsigned tableSize){
        size = tableSize;
        table = unsigned long[size*2];
    }
    loadMember(T value){
        (table + (hash(value)));
    }

};


#endif //ACRYLIC2D_HASH_TABLE_H
