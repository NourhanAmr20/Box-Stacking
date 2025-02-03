// Algorithms project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<algorithm>
using namespace std;
struct Box {
    int height, width, length;
};
//bool compare( Box box1 ,Box box2) {
//    if (box1.width * box1.length > box2.width * box2.length) {
//        return true;
//    }
//    else {
//        return false;
//    }
//}
bool compare(Box box1, Box box2) {
    return (box1.width * box1.length) > (box2.width * box2.length);
}
int maxHeightDynamic(int Height[], int Width[], int Length[],int size) { //time comp=>O(n2)
    //space comp=>O(n)
    int len = 3*size; //each box has 3 rotations so we create an array of boxes with triple the size for each rotaions
    Box * box = new Box [len];
    int index = 0;
    for (int i = 0; i < size; i++) {
        box[index].height = Height[i]; //first rotation
        box[index].width = max(Width[i], Length[i]);
        box[index].length= min(Width[i], Length[i]);
        index++;
        box[index].height = Width[i]; //second rotation
        box[index].width = max(Height[i], Length[i]);
        box[index].length = min(Height[i], Length[i]);
        index++;
        box[index].height = Length[i]; //third rotation
        box[index].width = max(Width[i], Height[i]);
        box[index].length = min(Width[i], Height[i]);
        index++;
    }
    sort(box, box + len, compare); //sort desc according to the area 
    //box=>pointer to the first array element 
    //box+len=>pointe to an ositio after the last element
    
    int* maxHeightt = new int[len]; // array of heights so we can update the possble solutions and retrive the maximum
    Box* boxes = new Box[len];
    for (int i = 0; i < len; i++) {
        maxHeightt[i] = box[i].height;
    }
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if ((box[i].width < box[j].width) && (box[i].length < box[j].length) && (maxHeightt[i] < maxHeightt[j] + box[i].height)) {
                //if the current maxHeightt[i] we have is smaller than maxHeightt[j]+ the current height box we have we update its value
                // example
                //maxHeightt[2]=>32
                //maxHeightt[0]=>10 //j
                //box[2].height=>32
                //32<32+10(42)=>so we maxHeightt[2]=>42
                maxHeightt[i] = maxHeightt[j] + box[i].height;
               /* boxes[i].height = box[j].height;
                boxes[i].width = box[j].width;
                boxes[i].length = box[j].length;*/
            }
        }
    }
   /* for (int i = 0; i < len; i++) {
        cout << "box "<<i+1 << "height " << boxes[i].height << " width " << boxes[i].width << " length " << boxes[i].length << endl;
    }*/
    int max = 0; //retrive the max value
    for (int i = 0; i < len; i++) {
        if (max < maxHeightt[i])
            max = maxHeightt[i];
    }
    return max;

}

int maxHeightGreedy(int Height[], int Width[], int Length[], int size) { //space com>O(n)
    //time comp=>O(nlogn)
    int len = 3 * size; // Each box has 3 rotations so we create an array of boxes with triple the size for each rotation
    Box* box = new Box[len];
    int index = 0;

    for (int i = 0; i < size; i++) {
        // First rotation
        box[index].height = Height[i];
        box[index].width = max(Width[i], Length[i]);
        box[index].length = min(Width[i], Length[i]);
        index++;

        // Second rotation
        box[index].height = Width[i];
        box[index].width = max(Height[i], Length[i]);
        box[index].length = min(Height[i], Length[i]);
        index++;

        // Third rotation
        box[index].height = Length[i];
        box[index].width = max(Height[i], Width[i]);
        box[index].length = min(Height[i], Width[i]);
        index++;
    }

    sort(box, box + len, compare); // Sort in descending order according to the area
    //box=>pointer to the first array element 
    //box+len=>pointe to an ositio after the last element
 
    int maxHeight = 0; // Maximum height achieved
    int currentHeight = 0; // Current height of the stack

    int previousWidth = box[0].width;
    int previousLength = box[0].length;
    //to store dim of the first box;
  
    for (int i = 0; i < len; i++) {
        
        if (i == 0 || (box[i].width < previousWidth && box[i].length < previousLength)) {
            //=0=>make sure that the first boxis always includedd
            // Check if the current box can be placed on top of the previous box
            currentHeight += box[i].height; // Add the height of the current box
            previousWidth = box[i].width; // Update previous box's width
            previousLength = box[i].length; // Update previous box's length
            maxHeight = currentHeight; // Update the maximum height
        }
    }


    return maxHeight;
}

int main()
{
    int Height[] = { 10, 4, 4 };
    int Width[] = { 12, 6, 5 };
    int Length[] = { 32, 7,6 };
    int size = sizeof(Height) / sizeof(Height[0]);

    int result = maxHeightGreedy(Height, Width, Length, size);
    int result2 = maxHeightDynamic(Height, Width, Length, size);
    cout << "The maximum height is using Greedy Approach " << result << endl;
    cout << "The maximum height is using Dynamic Approach " << result2 << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
