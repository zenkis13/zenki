/// bst.cpp
/// Medina, Fred
/// fmedina8
#include"bst.h"
#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<queue> // queue standard template library
#include<algorithm> // Needed for max
using namespace std;

/// CONSTRUCTOR & DESTRUCTOR
BST::BST(){
    root = NULL;
    listCount = 0; // Tracks size of link/tree
}
BST::~BST(){
    if(root)
        delete root;
}
// Destructor for nodes
BST::Node::~Node(){
    delete left;
    delete right;
}



/// WRITE TO STANDARD OUTPUT
///*************************************
// Do not insert into tree
// print for commenting purposes
//void BST::echo(string str )
string BST::echo(string str )
{
//    cout << str << endl; // Use if function is void
    return str; // Use if function is string
} // -echo




/// INSERT STRING INTO TREE & MAINTAIN PROPERTY AFTER
/// Public Member
// Calling public member to access and pass the
// (private) node pointer to another insert function
// because main does not have access to the
// (private) node pointer
///*************************************
bool BST::insert(string str){
    return insert(str, root); // Returns true/false
}




/// INSERT STRING INTO TREE & MAINTAIN PROPERTY AFTER
/// Private Member
// Return true/false if string is in tree
///*************************************
bool BST::insert(string str, Node *&curr_root)
{
    /// If current pointer is empty
    if( curr_root==NULL ){
        Node *newNode = new Node(); // Allocate new memory
        newNode->data = str;
        newNode->left = NULL;
        newNode->right = NULL;
        curr_root = newNode;
        listCount++; // Increment amount of nodes inserted
//        cout << "curr_root is: " << curr_root->data << endl;
//        cout << "Returning false..\n";
        return false;
    }
    /// If str exists in current pointer
    else if( curr_root->data == str ){
//        cout << "Returning true..\n";
        return true;
    }

    /// if str < data in current pointer
    // traverse left of tree
    else if( str < curr_root->data ){
//        cout << "Going left..\n";
        return insert(str, curr_root->left);
    }
    /// if str > data in current pointer
    // traverse right of tree
    else{
//        cout << "Going right..\n";
        return insert(str, curr_root->right);
    }
//    return false;
} // -insert




/// PRINT NUMBER OF ELEMENTS AND NODES IN THE TREE
///*************************************
int BST::size()
{
    return listCount; // Returns amount of nodes inserted
} // -size


/// PRINT IF STRING IS IN TREE OR NOT
/// Public Member
// Calling public member to access and pass the
// (private) node pointer to another find function
// because main does not have access to the
// (private) node pointer
///*************************************
bool BST::find(string str)
{
    return find(str, root);
} // -find




/// PRINT IF STRING IS IN TREE OR NOT
/// Private Member
// True if in tree
///*************************************
bool BST::find(string str, Node *&curr_root)
{
    if( curr_root != NULL ){ // NOT empty bst
        if( curr_root->data == str ){ // if str == current node's data
            return true;
        }
        else if( str < curr_root->data ){ // if str < current node's data
            return find(str, curr_root->left); // Traverse left
        }
        else if( str > curr_root->data ){ // if str > current node's data
            return find(str, curr_root->right); // Traverse right
        }
    } // -if( curr_root != NULL ){
    else
        return false;
    return false;

} // -find




/// PRINT ELEMENTS IN TREE USING DEPTH-FIRST TRAVERSAL
/// Public Member
///*************************************
// Use Depth-First Traversal - dft
// LDR - Left, Data, Right
void BST::print_dft(vector<string> &value)
{
    print_dft(value, root);
    /// Depth First Traversal, InOrder Traversal Concept
    //          5     LDR , Left, Data, Right
    //        /   \
    //       2     8
    //     /  \   /  \
    //    1   3  6   9
    // Prints: 1 2 3 5 6 8 9
    print_t(value);
} // -print




/// PRINT ELEMENTS IN TREE USING DEPTH-FIRST TRAVERSAL
/// Private Member
///*************************************
// Use Depth-First Traversal - dft
// Inorder Traversal
// LDR - Left, Data, Right
void BST::print_dft(vector<string> &value, Node *&curr_root)
{
    if(curr_root != NULL){
        // Traverse the pointer to the left edge of subtree,
        // to the leaf, then
        print_dft(value, curr_root->left);
        // Once pointer is at the edge leaf, record data
        value.push_back(curr_root->data);
        // Go back up the tree, one by one and
        // traverse to the right of each node
        print_dft(value, curr_root->right);
    }
    else{ // Empty BST
        return;
    }
} // -print




/// PRINT ELEMENTS IN TREE USING BREADTH-FIRST TRAVERSAL
/// Public Member
// Level Order Traversal
///*************************************
// Use Breadth-First Traversal - bft
void BST::print_breadth(vector<string> &value)
{
    print_breadth(value, root);
    /// Breadth First Traversal, Level Order Traversal Concept
    //          5     - 1
    //        /   \
    //       2     8   - 2
    //     /  \   /  \
    //    1   3  6   9  - 3
    // Prints: 5 2 8 1 3 6 9
    print_t(value);
} // -breadth





/// PRINT ELEMENTS IN TREE USING BREADTH-FIRST TRAVERSAL
/// Private Member
// Level Order Traversal
///*************************************
// Use Breadth-First Traversal - bft
// Level order traversal
void BST::print_breadth(vector<string> &value, Node *&curr_root)
{
    if(curr_root != NULL){
        queue<Node*> que; // Queue of node pointers
        que.push(curr_root); // Push element into que
        while(!que.empty() ){ // while queue not empty
            Node *curr = que.front(); // Position pointer
            value.push_back( curr->data ); // Push queued into vector
            que.pop(); // Remove from queue
            if(curr->left != NULL){
                que.push(curr->left); // Traverse to left subtree
            }
            if(curr->right != NULL){
                que.push(curr->right); // Traverse to right subtree
            }
        } // -while
    } // -if
    else{ // Empty BST
        return;
    }
} // -breadth




/// PRINT AVG DISTANCE NODES ARE FROM ROOT
///*************************************
// Root distance = 0, children = 1, grandchildren = 2
// Calculate distance for ALL nodes and take average
double BST::distance()
{
    double dist=0;
    double average = 0;
    dist = distance(dist, root); // Record returned value from distance fn
    average = dist/listCount; // Calculates average
    // average = total_distance_count / list_count
    return average;

} // -distance




/// PRINT AVG DISTANCE NODES ARE FROM ROOT
///*************************************
// Root distance = 0, children = 1, grandchildren = 2
// Calculate distance for ALL nodes and take average
double BST::distance(double dist, Node *&curr_root)
{
    if( curr_root==NULL ){ // EMPTY BST
        return 0;
    }
    else{
        // Returns current distance + the distance accumulated
        return dist + distance(dist+1, curr_root->left) + distance(dist+1, curr_root->right);
    }
} // -distance




/// LEVELS RETURNS WHICH SUBTREE IS THE LARGEST
///*************************************
int BST::levels(Node *&curr_root)
{
    if(curr_root == NULL)
        return 0;
    /// max
    // Returns which ever value is the largest
    else
        return 1+ max(levels(curr_root->left), levels(curr_root->right) );
        // 1+ because must count current node
}




/// PRINT IF TREE IS BALANCED OR NOT (HEIGHT-BALANCED)
///*************************************
// This type of balance is called height-balanced
int BST::balanced()
//bool BST::balanced()
{
    return balanced(root); // Use for int balanced
    /// FOR BOOL BALANCED
//    bool bal;
//    return bal = balanced(root);
    /// ^ FOR BOOL BALANCED

} // -balanced




/// PRINT IF TREE IS BALANCED OR NOT (HEIGHT-BALANCED)
///*************************************
// This type of balance is called height-balanced
int BST::balanced(Node *&curr_root)
//bool BST::balanced(Node *&curr_root)
{

    /// FOR INT BALANCED
    /////////////////////
    // This block works

    int leftHeight = 0;
    int rightHeight = 0;

    if(curr_root == NULL){ // EMPTY BST
        return 0;
    }
    leftHeight = levels(curr_root->left); // counts left subtree
    rightHeight = levels(curr_root->right); // counts right subtree

//    cout << "1 LH: " << leftHeight << " RH: " << rightHeight << endl;

    // Counts the difference between
    // left and right subtree levels
    // Using abs to return +(pos) in case result is -(neg)
    if( abs(leftHeight - rightHeight) > 1 ){
//        cout << "2 Unbalanced\n";
        return -1;
    }
    else{
        //
//        cout << "3 Balanced\n";
        // max(x,y) max returns highest. x or y
        // 1+ to count current node position
        return 1+ max(leftHeight, rightHeight);
    }
    /////////////////////
    /// ^ FOR INT BALANCED

    /*****************************************/

    /// FOR BOOL BALANCED
    /////////////////////
    // This block works

//    int leftHeight = 0;
//    int rightHeight = 0;
//
//    if(curr_root == NULL){
//        return true;
//    }
//
//    leftHeight = levels(curr_root->left);
//    rightHeight = levels(curr_root->right);
//
//    if( abs(leftHeight - rightHeight) <= 1 )
//        return true;
//    else{
//        return false;
//
//    }
    /////////////////////
    /// ^ FOR BOOL BALANCED
} // -balanced




/// DELETE TREE
///*************************************
//void BST::del_tree(Node *&curr_root)
//{
//    if(curr_root == NULL)
//    {
//        return ;
//    }
////    del_tree(curr_root->left); // Traverse left subtree
////    del_tree(curr_root->right); // Traverse right subtree
////    delete curr_root; // Delete current pointer
//
//    if(curr_root->left != NULL){del_tree(curr_root->left);}
//    if(curr_root->right != NULL){del_tree(curr_root->right);}
//    delete curr_root;
//    return ;
//} // -del_tree




/// MODIFY TREE SO IT'S BALANCED
/// NOT NEEDED IF DEFINED AND DECLARED IN BST.H
///*************************************
void BST::rebalance()
{
    vector<string> newElements; // Make a new array
//    cout << "1 Copying...\n";
    print_dft(newElements, root); // copy values
//    cout << "2 Printing...\n";
//    print_t(newElements);
//    del_tree(root);
    if(root){

//        cout << "3 Deleting Root: " << root->data << "...\n";
//        cout << "Node size: " << size() << endl;
        delete root;
//        cout << "Node size: " << size() << endl;
//        cout << "4 Deleted Root: " << root->data << "...\n";
    }
    root = NULL;
//    cout << "6 Inserting/Printing...\n";
//    print_t(newElements);
    insert_from_vector(newElements, 0, newElements.size()-1);
//    cout << "Vector Size: " << newElements.size() << endl;
//    cout << "Tree Size: " << size() << endl;
} // -rebalanced




/// RECURSIVE INSERT FROM FUNCTION
///*************************************
void BST::insert_from_vector(vector<string> &newElement, int startIndex, int endIndex)
{

    int midIndex;
//    cout << "\n1 Printing: S: " << startIndex << " E: " << endIndex << endl;
    if( startIndex == endIndex ){
//        cout << "\nTest 1 - S: " << startIndex << " E: " << endIndex << endl;
//        cout << "NE[startIndex]: " << newElement[startIndex] << endl;
        insert( newElement[startIndex], root );
        return ;
    }
    else if( endIndex - startIndex == 1 ){
//        cout << "\nTest 2 - S: " << startIndex << " E: " << endIndex << endl;
//        cout << "NE[startIndex]: " << newElement[startIndex];
//        cout << " NE[endIndex]: " << newElement[endIndex] << endl;
        insert( newElement[startIndex], root );
//        insert( newElement[endIndex], root );
        return ;
    }
    else{
        midIndex = (startIndex + endIndex) / 2;
//        cout << "\n2 Inserting M: " << midIndex << "...\n";
//        cout << "NE[midIndex]: " << newElement[midIndex] << endl;
//        insert( newElement[ (midIndex = (startIndex+endIndex) / 2) ] );
        insert( newElement[midIndex], root );
//        cout << "\n4 Inserting M: " << midIndex << " E: " << endIndex << endl;
//        cout << "5 M+1, E\n";
        insert_from_vector(newElement, midIndex+1, endIndex);
//        cout << "\n6 Inserting S: " << startIndex << " M: " << midIndex << endl;
//        cout << "7 S, M-1\n";
        insert_from_vector(newElement, startIndex, midIndex-1);
    }
} // -insert_from_vector



/// PRINT VECTOR
///*************************************
void print_t(vector<string> &value)
{
    cout << "{";
    for( unsigned int i=0; i<value.size(); i++){
        cout << value[i];
        if( i<(value.size()-1) ){
            cout << ", ";
        }
    }
    cout << "}" << endl;
}


