

#include <string>
#include <iostream>
#include <vector>

using namespace std;





class MPQ
{
public:
    MPQ(int numberOfBuildings); //constructor
    bool isEmpty() const;
    int GetMax();// returns the maximum value stored --> OK
    void updateLocationArr(int newvalue, int oldvalue); // will update the Location array each time the Heap array is modified to keep track of the locations --> OK
    void insert(int value, int label); //for insetion --> OK
    int remove(int label); // This method removes the value with this label and returns it.
   

private:
    struct heapNode
    {
        int value; // height
        int label; // like id
       heapNode(int v, int l)
        {
            value = v;
            label = l;
        }
    };
    vector<int> Location; // location array for the link between the value and the label so that the complexity is O(1)
    //Her ith index için, o indexe eşit olan label numarasının Heap arrayde kaçıncı index'te olduğunu storelayacak
    vector<heapNode> Heap; // the array heap which will consit of heapNodes
    //void buildHeap(); // for building the heap
    void percolateDown(int hole); // percolates down to keep the heap order property: hole will be the index --> OK
};
