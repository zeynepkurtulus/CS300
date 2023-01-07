
#include "MPQ.hpp"

MPQ::MPQ(int buildingnum)
{
    heapNode zerothidx(0, 0); // we will keep the firts element of the vector empty: it will be 0,0 for simplicity
    Heap.push_back(zerothidx);
    Location.push_back(0); // we store the value 0 in the 0 th index bc. in Heap the value 0 is stored in the 0 th index
    Location.resize(buildingnum + 1); // create a vector with the given num of buildings with all zeros
    
}

//will update the location array

void MPQ::updateLocationArr(int newvalue, int oldvalue)
{
    Location[Heap[oldvalue].label] = newvalue;
    Location[Heap[newvalue].label] = oldvalue;
}


void MPQ::insert(const int value, int label)
{
    int hole = Heap.size(); // the insertion index is the first available index which is the end of the array
    heapNode headnode = heapNode(0,0);
    Heap.push_back(headnode); // but since I have to resize the vector with one more element bc. I will insert one element
    
    
    ///BUBBLE UP UNTIL WE FIND THE RIGHT PLACE
    for( ; Heap[hole/2].value < value && hole > 1 ; hole = hole/2)
    {
        
        //if Heap[hole/2] = parent of the hole is < value we want to insert then we should interchange bc. this is a max heap
        // hole > 1 means until the root, >= yaptıpımda 0. indexi de olaya dahil etti bunu istemiyoruz
        // hole = hole/2 means until the whole becomes it parent
        Heap[hole] = Heap[hole / 2];
        //We must update the Location array because we have changed the indexes of elements
        updateLocationArr(hole/2, hole);
    }
    Heap[hole].value = value;
    Heap[hole].label = label;
    Location[Heap[hole].label] = hole;

}



void MPQ::percolateDown(int hole) //ensures the heap order property
// we insert the new element to the leaf which guarantees the structure property  and now we have to reestablish the heap order property
    
    // it will be so that the parents has to be larger than or equal to the children bc. this will be a max queue.
{
    int child; // lets say this is at the i th index -> we dont know the side
    int left; // this will be at the 2i th index
    int right; // this will be at the 2i + 1 th index
    int temp = Heap[hole].value; // will store the value at the hole th index temp is the value that we want to percolate down
    int tlabel = Heap[hole].label; // it is the label that we want to percolate down

    for( ; hole < Heap.size()/2; hole = child)
    {
        left = hole * 2; // leftchild
        right = hole * 2 + 1; //rightchild
        child = left;
        if (child != Heap.size() && Heap[left].value > Heap[right].value) { // if the left child contains the bigger value we will swap with the left child since it is a max heap
            child = left;
        }
        else if (child != Heap.size() && Heap[left].value < Heap[right].value) { // if the left child contains the bigger value we will swap with the left child since it is a max heap
            child = right;
        }
        if (Heap[child].value > temp) { // if the child is bigger than
            Heap[hole] = Heap[child]; // swap the locations
        }
        else
            break;
        updateLocationArr(hole, child);
    }
    // at this point we have placed the hole so now we have to insert the value to the node we placed
    Heap[hole].value = temp;
    Heap[hole].label = tlabel;
    Location[Heap[hole].label] = hole;
}

//  returns true if empty

bool MPQ::isEmpty() const
{
    bool validator = false;
    if(Heap.size() <= 1)
    {
        validator = true;
    }
    return validator;
}

//remove element and return its value

int MPQ::remove(int label)// removes the value with the provided label from the Heap
//replace the element to be deleted with the last element in the heap: structure property is ensured delete the last element
// then percolate down the element we changed until the heap order property is satisfied

{
    if(!isEmpty()) //if not empty
    {
        int lastidx = Heap.size() -1; // index of th last element
        int temp = Heap[Location[label]].value; // value to be deleted for return
        Heap[Location[label]] = Heap[lastidx];  //put the element to be deleted into the last index of the Heap array
        int locaridx = Location[label];
        updateLocationArr(lastidx, Location[label]);// update the Location array because we have changed the indexes in the Heap array
        
        Location[Heap[Heap.size()-1].label] = 0; // let's again make all them zero when we delete it
        Heap.pop_back(); // delete the last index from the heap since we have deleted it
        if(locaridx != Heap.size()) // if the element that we deleted is not the last element we need to percolate down to keep the heap order property
            percolateDown(locaridx);
        return temp; // return the deleted element as asked
    }
    return 0; // give the first index if empty
}

// return the root of pq since it is a max heap

int MPQ::GetMax()
{
    int max = 0;
    if(!isEmpty())
    {
        max = Heap[1].value;
    }
    
    return max;
}
