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
    Link* table;
    unsigned size;
    hash(T value){
        hash<T> hashVal;
        return hashVal(value);
    }
    public:
    Hash_Table(unsigned tableSize){
        size = tableSize;
        table = Link[size];
    }
    loadMember(T value){
        Link* pathToEdit = (table + (hash(value)%size));
        while(true) {//please forgive me
            if (pathToEdit->link == 0) {

                break;
            } else {
                pathToEdit = pathToEdit->link;
            }
        }
    }

};


#endif //ACRYLIC2D_HASH_TABLE_H
