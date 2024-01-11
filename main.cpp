#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<queue>

using namespace std;

struct BstNode {
    string data;
    BstNode* left;
    BstNode* right;
};

void read_insert(BstNode* tree, ifstream &myFile){
    string data;
    string element;
    myFile >> element;
    myFile.ignore();
    getline(myFile,data);
    tree->data = data;
    if(element=="#A"){
        return;
    }else{//recursive case
        tree->left = new BstNode;
        read_insert(tree->left,myFile);
        tree->right = new BstNode;
        read_insert(tree->right,myFile);
    }
}
BstNode* file_read(){
    ifstream myFile("animal_game_tree.txt");
    if(!myFile.is_open()){
        cout << "error, file is not found. " << endl;
    }else{
        BstNode* rootPtr = new BstNode;
        read_insert(rootPtr,myFile);
        return rootPtr;
    }

}
void insert(BstNode* tree, ofstream &myFile){
    if(tree!= NULL){// if the tree is not empty
        if(tree->left && tree->right){
            myFile << "#Q "<<tree->data << endl;
            insert(tree->left,myFile);
            insert(tree->right,myFile);

        }else{
            myFile << "#A " << tree->data << endl;
        }
    }
}

void save_game_tree(BstNode* rootPtr) {

    ofstream myFile("animal_game_tree.txt");
    insert(rootPtr, myFile);
}
void game(BstNode* rootPtr){
    queue<string> hist;
    BstNode* curr = new BstNode;
    curr = rootPtr;
    while(curr != NULL && (curr->right && curr->left)){
        cout << curr->data << " y/n : ";
        char yn;
        while(yn != 'y' && yn != 'n'){
            cout << "make sure you choose 'y' or 'n', it is case sensititive " << endl;
            cin >> yn;
        }
        if(yn == 'y'){
            hist.push(curr->data +" yes");
            curr = curr->left;
            yn = ' ';
        }
        else if (yn == 'n'){
            hist.push(curr->data +" no");
            curr = curr->left;
            yn = ' ';
        }
    }
    cout << curr->data << " y/n : ";
    char yn = ' ';
    while(yn != 'y' && yn != 'n'){
        cout << "make sure you choose 'y' or 'n', it is case sensititive " << endl;
        cin >> yn;
    }
    if (yn == 'y'){
        cout << "i guessed your animal" << endl;

    }
    else if(yn == 'n'){
        hist.push(curr->data + " no");
        cout << "I dont know your animal" << endl;
        cout << endl;
        cout << "do you want to expand the tree: y/n : ";
        char yn = ' ';
        while(yn != 'y' && yn != 'n'){
            cout << "make sure you choose 'y' or 'n', it is case sensititive " << endl;
            cin >> yn;
        }
        if(yn == 'y'){
            cout << "i asked so far:" << endl;
            while (!hist.empty()){// while the queue has stuff in it output the first in line an pop it out of the queue
                cout << hist.front() << endl;
                hist.pop();


            }
            cout << "Enter a new animal in the form of a question,\ne.g., 'Is it a whale?' :: ";
            string a;
            cin.ignore(); // catch empty enter-key from cin >> in line 108
            getline(cin,a);
            cout << "Now enter a question for which the answer is 'yes' for your newanimal;";
            string q;
            getline(cin,q);
            string node = curr->data;
            curr->data = q;
            curr->left = new BstNode;
            curr->left->data = a;
            curr->right = new BstNode;
            curr->right->data = node;


        }
        else if( yn == 'n'){
            cout << "OK then...." << endl;
        }
    }


}

int main() {
   BstNode* rootPtr = file_read();
   if(rootPtr == NULL){
       return -1;
   }
   while(true){
       int option;
       cout <<"Welcome to 20 questions!" << endl << " 1) Play the game" << endl << " 2) Save the game file" << endl << " 3) Quit" << endl << "Please make your selection: ";
       cin >> option;
       if(option == 1){
           game(rootPtr);
           break;
       }
       else if(option == 2){
           save_game_tree(rootPtr);
           break;
       }
       else if(option == 3){
           break;
       }else{
           cout << "enter 1 2 or 3>" << endl;

       }


   }
}
