#include "MPQ.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct cordHolder{ // hold the info to store in the array for the heap usefull for main
    int valuex; // value of the x coordinate
    int id;//id i.e. label 
    string direction; // either x left or x rigth
    
    cordHolder(string d, int v, int l){
        direction = d; // left or right
        valuex = v; // value of the x coord
        id = l; //id
       
    }
};

struct buildingNode{ // holds the info of buildings usefull for main
    int x_left;
    int x_right;
    int y;
    
    buildingNode(int xl, int xr, int h){
        x_left = xl;
        x_right = xr;
        y = h;
    }
};

void mergesort(vector<cordHolder> & leftvec, vector<cordHolder> & rightvec, vector<cordHolder> & sortedvec)
{
    int leftsize = leftvec.size();
    int rightsize = rightvec.size();
    int i = 0; // usde to fill in the sortedvec
    int a = 0; // used to compare size of leftside
    int z = 0; //used to compare size of rightside

    while (z < rightsize && a < leftsize)
    {
        if (leftvec[a].valuex < rightvec[z].valuex) {
            sortedvec[i] = leftvec[a];
            a++;
        }
        else {
            sortedvec[i] = rightvec[z];
            z++;
        }
        i++;
    }
    while (a < leftsize) {
        sortedvec[i] = leftvec[a];
        a++;
        i++;
    }
    while (z < rightsize) {
        sortedvec[i] = rightvec[z];
        z++;
        i++;
    }
}

void sort(vector<cordHolder> & cordarr)
{
    if (cordarr.size() <= 1) return;
    
    else{
        int center = cordarr.size() / 2;

        vector<cordHolder> leftside(cordarr.begin(), cordarr.begin() + center);
        vector<cordHolder> rightside(cordarr.begin() + center, cordarr.end());

        sort(leftside);
        sort(rightside);
        mergesort(leftside, rightside, cordarr);
    }
    
}


int main()
{
    ifstream input;
    string fn = "testCase9.txt", line;
    int xleft, xright, y, buildingnum;


    input.open(fn);

    vector<buildingNode> buildingarray;
    vector<cordHolder> coordarray; // will store only the coordinates and it will be used for the sorting part
    getline(input, line); // will only take the first line 

    istringstream iss(line);

    // first line will be the number of the buildings in this file
    iss >> buildingnum;

    MPQ modifiedpq = MPQ (buildingnum);  // created a MPQ obj with the number of buildings
    
    int id = 1;
    while(getline(input, line))
    {
        istringstream iss(line);
        
        // taking the values from the file
        iss >> xleft >> y >> xright;

        
        buildingNode building(xleft, xright, y);
        
        buildingarray.push_back(building);

 
        cordHolder leftside("left", xleft, id);
        cordHolder rightside("right", xright, id);
        coordarray.push_back(leftside);
        coordarray.push_back(rightside);
        id++; // will keep track of the building ids
    }
    
    //at this point all cordinates as stored inside the coordarr, but THEY ARE NOT SORTED, we have to sort them:
    sort(coordarray);

   
    int maxVal; // since if the max heap is the same we don't have to print so this variable holds max
    bool check= true; // first element cehecker
    
    for(unsigned int i = 0; i < coordarray.size(); i++)
    {
        if(coordarray[i].direction == "left") // borders are formed by left sides
        {
            modifiedpq.insert(buildingarray[coordarray[i].id-1].y, coordarray[i].id); // insert(height_value, label) if the direction is left
        }
        else if(coordarray[i].direction == "right")
        {
            modifiedpq.remove(coordarray[i].id);
        }

        //THE FIRST ELEMENT IS NOT 0 ~ OPTION 1
        if(coordarray[0].valuex != 0 && check )
        {
            check = false; // indicating that we are past the first elem
            cout << 0 << " " << 0 << endl; // if the first set of coordinates are not zero then we need to print (0,0) and the first element in the array
            cout << coordarray[i].valuex << " " << modifiedpq.GetMax() << endl;
            maxVal = modifiedpq.GetMax();
           
        }
        else if(coordarray[0].valuex != 0 && !check && maxVal != modifiedpq.GetMax() && coordarray[i].valuex != coordarray[(i+1)%coordarray.size()].valuex)
        {
            // coordinates[i].x_val != coordinates[(i+1)%coordinates.size()].x_val = for test4 and test5
            cout << coordarray[i].valuex << " " << modifiedpq.GetMax() << endl;
            maxVal = modifiedpq.GetMax();
        }
       //THE FIRST ELEMENT IS ZERO ~ OPTION 2
        else if(coordarray[0].valuex == 0 && check)
        {
            check = false; // indicating that we are passed the first elem
            cout << coordarray[i].valuex << " " << modifiedpq.GetMax() << endl;
            maxVal = modifiedpq.GetMax();
            
        }
        else if(coordarray[0].valuex == 0 && !check && maxVal != modifiedpq.GetMax() && coordarray[i].valuex != coordarray[(i+1)%coordarray.size()].valuex)
        {
            cout << coordarray[i].valuex << " " << modifiedpq.GetMax() << endl;
            maxVal = modifiedpq.GetMax();
        }
    }

    input.clear();
    input.seekg(0);
    input.close();

    return 0;
}
