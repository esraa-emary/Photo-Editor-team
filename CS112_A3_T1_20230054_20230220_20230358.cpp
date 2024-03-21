/*
File name: CS112_A3_T1_20230054_20230220_20230358.cpp
Purpose: Make an application that takes a photo and apply a filter to it.
Version: 1.0

---> Author 1: Esraa Emary Abd Elsalam.          ID: 20230054
---> Author 2: Abdelrahman Yasser Ali.           ID: 20230220
---> Author 2: Mohamed Nabil Elsaied Ali.        ID: 20230358

*/
//========================================================================================================================================//
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Save the image after applying the filter.
void saving(){

}

// Get the image from the user to apply the filter.
void uploading(string photo){

}


//================================================================= Main Program ==============================================================//

int main(){
    // Welcome message and brief lines about our application.
    cout << "#==================== Welcome to our application ====================#" << endl;
    cout << "---> This application takes any photo and applies some filters to it." << endl;
    cout << "---> Insert any image to apply filters to it in any of these formats:" << endl;
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    while (true)
    {
        // Print the menu for choosing what the user want to do.
        cout << "What do you want to do ?\n[1] Appling a fiter to a photo.\n[2] Exit." << endl;
        string choice;
        getline(cin, choice);
        cin.ignore(0,'\n');
        if(choice == "1"){
            string photo;
            cout << "Enter the photo name: ";
            cin >> photo;
            uploading(photo);
        }

        // Exit the program.
        else if(choice == "2")
            break;
        
        // Invalid choice for the menu.
        else{
            cout << "Please enter a valid choice." << endl << endl;   
            continue;
        }
    }

    cout << "#===== Thanks for using our application =====#" << endl;
    return 0;
}