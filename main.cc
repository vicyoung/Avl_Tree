#include <cstdlib>
#include <iostream>
#include <string>

#include <fstream>
#include <iomanip>

#include "avl.h"
#include "file_handler.h"

using namespace std;

int main(void) {
    file_handler_t file_numbers; // Input file handler for a random number file
    string input_set;            // Input data set
    avl_t avl;                   // AVL tree





    /*****************************************************
     * TEST YOUR CODE HERE TO SEE IF AVL TREE IS WORKING *
     *****************************************************/
    avl.insert(935);
    avl.insert(173);
    avl.insert(238);
    avl.insert(812);
    avl.insert(343);
    avl.insert(132);
    avl.insert(499);
    avl.insert(727);
    

    cout << "AVL tree (preorder traversal): " << endl;
    avl.print();
    cout << "Height: "       << avl.height()                           << endl;
    cout << "size = "        << avl.size()                             << endl;
    cout << "min = "         << avl.find_min()                         << endl;
    cout << "max = "         << avl.find_max()                         << endl;
    cout << "contain(27) = " << (avl.contain(27) == true ? "yes":"no") << endl;
    cout << "contain(40) = " << (avl.contain(40) == true ? "yes":"no") << endl;
    cout << "contain(44) = " << (avl.contain(44) == true ? "yes":"no") << endl;

    avl.remove(735);
    avl.remove(761);
    avl.remove(813);
    avl.remove(647);
    avl.remove(590);
    avl.remove(224);
    avl.remove(270);
    avl.remove(282);
    avl.remove(768);
    avl.remove(145);
    avl.remove(250);
    avl.remove(176);
    avl.remove(507);
    avl.remove(598);

    cout << endl << "AVL tree (preorder traversal): " << endl;
    avl.print();
    cout << "Height: "       << avl.height()                           << endl;
    cout << "size = "        << avl.size()                             << endl;
    cout << "min = "         << avl.find_min()                         << endl;
    cout << "max = "         << avl.find_max()                         << endl;
    cout << "contain(27) = " << (avl.contain(27) == true ? "yes":"no") << endl;
    cout << "contain(40) = " << (avl.contain(40) == true ? "yes":"no") << endl;
    cout << "contain(44) = " << (avl.contain(44) == true ? "yes":"no") << endl;
    /********************
     * END OF TEST CODE *
     ********************/





    // Get the input set: last digit of student ID.
    while(input_set.empty()) {
        cout << endl << "Last digit of your student ID: ";
        cin >> input_set;
        if((input_set.find_first_not_of("0123456789") != string::npos) ||
           (input_set.size() > 1)) {
            cout << "Invalid digit " << input_set << endl;
            input_set.clear();
        }
    }
    file_numbers.read("inputs/"+input_set+"/avl.data");

    avl.clear();
    
    /*ofstream location_out;
    location_out.open("location_out.txt",std::ios::out | std::ios::app);
        if(!location_out.is_open())
            return 0;
    
    for(size_t i = 0; i< file_numbers.size();i++){
        location_out << i%3 <<' '<< file_numbers.get(i) << '\n';
    }
    
    location_out.close();
    
    
    
    
}*/

    

    // Generate a pseudo-random AVL tree.
    cout << endl << file_numbers.size() << " randomized insert and remove:" << endl;
    for(size_t i = 0; i < file_numbers.size(); i++) {
        if(i%3) { avl.insert(file_numbers.get(i)); }
        else    { avl.remove(file_numbers.get(i)); }
    }
    
    /*avl.print();*/
    
    cout << "Height: "       << avl.height()                           << endl;
    cout << "size = "        << avl.size()                             << endl;
    cout << "min = "         << avl.find_min()                         << endl;
    cout << "max = "         << avl.find_max()                         << endl;
    cout << endl << "AVL tree done." << endl;
    
    

    return 0;
}

