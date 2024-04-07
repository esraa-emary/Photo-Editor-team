/*
File name   :   CS112_A3_Part1_S21_20230054_20230220_20230358.cpp
Purpose     :   Make an application that takes a photo and apply a filter to it.
Version     :   1.0

                              Authors                   |           Filters         |                   Contributions
---> 1: Esraa Emary Abd Elsalam.          ID: 20230054  |   Merge - Lighten/Darken  |   how_to_save() - Main menu - Output formatting
---> 2: Abdelrahman Yasser Ali.           ID: 20230220  |     Black/White - Flip    |            load() - Filters adjustments
---> 2: Mohamed Nabil Elsaied Ali.        ID: 20230358  |      Rotate - Invert      |                  Resizing algorithm


Professor           :   Dr.Mohamed ElRamly
Teaching Assistant  :   Eng.Rana Abdelkader
Section Number      :   S21-S22

*/
//========================================================================================================================================//

#include <iostream>
#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

// Save the effect in a new photo or the same one.
void how_to_save(Image image, string photo){
    cout << "Do you want to save the effect in a new photo or replace the base ?\n[1] New photo.\n[2] Replace the base.\nChoice: ";
    while (true)
    {
        string choice;
        getline(cin, choice);

        // Save the effect in a new photo.
        if(choice == "1"){
            string new_name;
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "The new file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "- Please enter the new file name\n--> ";
            getline(cin, new_name);

            // Check the validity of the new file name.
            while(new_name.size() < 5 || ((new_name.substr(new_name.size() - 4 , 4) != "jpeg") && (new_name.substr(new_name.size() - 3 , 3) != "jpg") && (new_name.substr(new_name.size() - 3 , 3) != "png") && (new_name.substr(new_name.size() - 3 , 3) != "bmp"))){
                cout << "\n----------------------------------------------------------------------" << endl << endl;
                cout << "The new file name must be one of the following format.\n";
                cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
                cout << "- Please enter a valid new file name\n--> ";
                getline(cin, new_name);
            }
            image.saveImage(new_name);
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "- Photo has been saved successfully" << endl;
            break;
        }
        
        // Save the effect in the same photo.
        else if(choice == "2"){
            image.saveImage(photo);
            cout << "- Photo has been saved successfully" << endl;
            break;
        }
        
        // Invalid choice.
        else{
            cout << "Please enter a valid choice." << endl << endl;   
            continue;
        }
    }
}

// Save the effect in a new photo only.
void how_to_save2(Image image){
    string new_name;
    cout << "The new file name must be one of the following format.\n";
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    cout << "- Please enter the new file name\n--> ";
    getline(cin, new_name);

    // Check the validity of the new file name.
    while(new_name.size() < 5 || ((new_name.substr(new_name.size() - 4 , 4) != "jpeg") && (new_name.substr(new_name.size() - 3 , 3) != "jpg") && (new_name.substr(new_name.size() - 3 , 3) != "png") && (new_name.substr(new_name.size() - 3 , 3) != "bmp"))){
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "The new file name must be one of the following format.\n";
        cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
        cout << "- Please enter a valid new file name\n--> ";
        getline(cin, new_name);
    }
    image.saveImage(new_name);
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "- Photo has been saved successfully" << endl;
}

// Get the image from the user to apply the filter.
string load(string name){
    while (true) {
        cout << endl;
        try {
        Image image(name);
        cout << "----------------------------------------------------------------------" << endl << endl;
        cout << "- Photo Loaded Successfuly.\n";
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        return name;
        }
        catch (invalid_argument) {
            cout << "Please enter a valid file name: ";
            getline(cin, name);
        }
    }
}
//================================================================ Main Functions =============================================================//

// Filter 1 (Grayscale Conversion).
void Grayscale_Conversion(){
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    string photo;                                                                   // Get the photo and make it as an image.
    cout << "The file name must be one of the following format.\n";
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    cout << "- Please enter the file name\n--> ";
    getline(cin, photo);
    photo = load(photo);
    Image image(photo);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0;                                                  // Initialize average value.
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);                                              // Accumulate pixel values.
            }
            avg /= 3;                                                               // Calculate average.
            image(i, j, 0) = avg;                                                   // Set all channels to the average value.
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    how_to_save(image,photo);
}

// Filter 2 (Darken and Lighten Image).
void Darken_and_Lighten(){
    while (true)
    {
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "Do you want to darken or lighten the image ?\n[1] Darken The Image.\n[2] Lighten The Image.\n[3] Back.\nChoice: ";
        string choice2;
        getline(cin, choice2);

        // Darken The Image.
        if (choice2 ==  "1"){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            string photo;                                                         // Get the photo and make it as an image.
            cout << "The file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "- Please enter the file name\n--> ";
            getline(cin, photo);
            photo = load(photo);
            Image image(photo);
            float darken = 0.5;                                                   // Initialize darken value.
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k) *= darken;                                 // Change pixel values.
                    }
                }
            }
            how_to_save(image,photo);
            break;
        }

        // Lighten The Image.
        else if(choice2 == "2"){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            string photo;                                                         // Get the photo and make it as an image.
            cout << "The file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "- Please enter the file name\n--> ";
            getline(cin, photo);
            photo = load(photo);
            Image image(photo);
            float lighten = 1.5;                                                // Initialize lighten value.
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        int val = image(i, j, k) * lighten;                     // Change pixel values.
                        if (val > 255)      // Check if channel value exceeds 255 
                            (image(i, j, k) = 255);
                        else
                            image(i, j, k) = val;
                    }
                }
            }
            how_to_save(image,photo);
            break;
        }

        // Back to the main menu.
        else if (choice2 =="3")
            break;

        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
}

// Filter 3 (Merge Images).
void Merge_Images(){
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    string photo1;                                                              // Get the first photo and make it as an image.
    cout << "The file name must be one of the following format.\n";
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    cout << "- Please enter the first file name\n--> ";
    getline(cin, photo1);
    photo1 = load(photo1);
    Image photo11(photo1);

    string photo2;                                                              // Get the second photo and make it as an image.
    cout << "The file name must be one of the following format.\n";
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    cout << "- Please enter the second file name\n--> ";
    getline(cin, photo2);
    photo2 = load(photo2);
    Image photo22(photo2);

    // Declare minimum width and minimum height to unify dimensions for both photos
    int width = min(photo11.width, photo22.width);
    int height = min(photo11.height, photo22.height);

    Image photo_result(width, height);                                          // Create the new photo
    Image photo1_sized(width, height);
    Image photo2_sized(width, height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < 3; z++) {
                // Resize the new photos by discarding unneeded pixels based on the ratio between dimensions
                photo1_sized(x, y, z) = photo11(x*(photo11.width/(float) width), y*(photo11.height/(float) height), z); // Resize photo 1
                photo2_sized(x, y, z) = photo22(x*(photo22.width/(float) width), y*(photo22.height/(float) height), z); // Resize photo 2
            }
        }
    }
                        
    for (int i = 0; i < photo_result.width; ++i) {                              // Applying merge
        for (int j = 0; j < photo_result.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int avrg = 0;
                avrg = (photo1_sized(i,j,k) + photo2_sized(i,j,k))/2;
                photo_result(i, j, k) = avrg;
            }
        }
    }
    how_to_save2(photo_result);
}

// Filter 4 (Invert Image).
void Invert_Image(){
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    string photo_name;                                                           // Get the photo and make it as an image.
    cout << "The file name must be one of the following format.\n";
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    cout << "- Please enter the file name\n--> ";
    getline(cin, photo_name);
    photo_name = load(photo_name);
    Image image(photo_name);
    for(int i=0; i<image.width; i++){
        for(int j=0; j<image.height; j++){
            for(int k=0; k<3; k++){
                image(i,j,k) = 255 - image(i,j,k);                               // Change pixel values.
            }
        }  
    }
    how_to_save(image,photo_name);
}

// Filter 5 (Rotate Image).
void Rotate_Image(){
    while (true)
    {
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "What rotation do you want ?\n[1] Rotate 90.\n[2] Rotate 180.\n[3] Rotate 270.\n[4] Back.\nChoice: ";
        string choice2;
        getline(cin, choice2);

        // Rotate 90°.
        if (choice2 ==  "1"){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            string photo;                                                       // Get the photo and make it as an image.
            cout << "The file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "- Please enter the file name\n--> ";
            getline(cin, photo);
            photo = load(photo);
            Image image(photo);

            int width,height;                                                   // Initialize values of width and height.                                 
            width = image.width;
            height = image.height;

            Image rotate(height,width);                                         // Make new image rotate that have swaped dimensions of the image.
            for(int x=1;x<image.width;x++){
                for(int y=1; y<image.height;y++){
                    for(int z=0; z<3;z++){
                        rotate(y ,x ,z) = image(x, image.height - y, z);        // Change pixel values.
                    }
                }
            }
            how_to_save(rotate, photo);
            break;
        }

        // Rotate 180°.
        else if(choice2 == "2"){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            string photo;                                                       // Get the photo and make it as an image.
            cout << "The file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "- Please enter the file name\n--> ";
            getline(cin, photo);
            photo = load(photo);
            Image image(photo);

            int width,height;                                                   // Initialize values of width and height.    
            width = image.width;
            height = image.height;

            Image rotate (height,width);                                        // Make new image rotate that have swaped dimensions of the image.
            Image rotate180 (width,height);                                     // Make new image rotate180 that have same dimensions of the image.
            for(int x = 1;x < width;x++){
                for(int y=1; y<height;y++){
                    for(int z=0; z<3;z++){
                        rotate180(x, y, z) = image(width - x,height - y, z);    // Change pixel values.
                    }
                }
            }
            rotate = rotate180;
            how_to_save(rotate, photo);
            break;
        }

        // Rotate 270°.
        else if(choice2 == "3"){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            string photo;                                                       // Get the photo and make it as an image.
            cout << "The file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "- Please enter the file name\n--> ";
            getline(cin, photo);
            photo = load(photo);
            Image image(photo);

            int width,height;                                                   // Initialize values of width and height.    
            width = image.width;
            height = image.height;

            Image rotate(height,width);                                         // Make new image rotate that have swaped dimensions of the image.
            for(int x = 0 ; x < rotate.width ; x++){
                for(int y = 0 ; y < rotate.height ; y++){
                    for(int z = 0 ; z < 3 ; z++){
                        rotate(x,y,z)=image(rotate.height - y, x, z);           // Change pixel values.
                    }
                }
            }
            how_to_save(rotate,photo);
            break;
        }

        // Back to the main menu.
        else if (choice2 =="4")
            break;

        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
}

// Filter 6 (Black and White).
void Black_n_White() {
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    string photo_name;                                                          // Get the photo and make it as an image.
    cout << "The file name must be one of the following format.\n";
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    cout << "Please enter the photo name: ";
    getline(cin, photo_name);
    photo_name = load(photo_name);
    Image image(photo_name);

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned  int avg = 0;                                              // Initialize average value.
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);                                          // Accumulate pixel values.
            }
            avg /= 3;                                                           // Calculate average.
            int val;
            if (avg > 127) {
                val = 255;
            }
            else {
                val = 0;
            }
            // Set all channels to either 0 or 255 (to obtain black and white only)
            image(i, j, 0) = val;
            image(i, j, 1) = val;
            image(i, j, 2) = val;
        }
    }
    how_to_save(image, photo_name);
}

// Filter 7 (Flip).
void Flip() {
    while (true) {
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "Do you want to flip horizontally or vertically ?\n"<< "[1] Horizontally\n"
            << "[2] Vertically\n"<< "[3] Back.\n"<< "Choice: ";
        string choice;
        getline(cin, choice);

        // Flip horizontally
        if (choice == "1") {
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            string photo_name;                                                  // Get the photo and make it as an image.
            cout << "The file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "Please enter the photo name: ";
            getline(cin, photo_name);
            photo_name = load(photo_name);
            Image image(photo_name);
            int width = image.width;
            int height = image.height;

            for (int i = 0; i < width/2; i++) {                                 // Loop until reaching half of the image width
                for (int j = 0; j < height; j++) {
                    int temp;

                    for (int k = 0; k < 3; k++) {
                        temp = image(i, j, k);                                  // Temp variable to store the pixel before swapping
                        image(i, j, k) = image(width - 1 - i, j, k);            // Swap the pixel with each opposite one (horizontally)
                        image(width - 1 - i, j, k) = temp;                      // Assign the old value to the opposite pixel
                    }

                }
            }
            how_to_save(image, photo_name);
            break;
        }

        // Flip vertically
        else if (choice == "2") {
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            string photo_name;                                                  // Get the photo and make it as an image.
            cout << "The file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "Please enter the photo name: ";
            getline(cin, photo_name);
            photo_name = load(photo_name);
            Image image(photo_name);
            int width = image.width;
            int height = image.height;

            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height/2; j++) {                            // Loop until reaching half of the image width
                    int temp;
                    for (int k = 0; k < 3; k++) {
                        temp = image(i, j, k);                                  // Temp variable to store the pixel before swapping
                        image(i, j, k) = image(i, height - 1 - j, k);           // Swap the pixel with each opposite one (vertically)
                        image(i, height - 1 - j, k) = temp;
                    }
                }
            }
            how_to_save(image, photo_name);
            break;
        }

        // Back to the main menu.
        else if (choice == "3") 
            break;
        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
}

// Filter 8 (Infrared Photography).
void Infrared_Photography(){
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    string photo;                                                                   // Get the photo and make it as an image.
    cout << "The file name must be one of the following format.\n";
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    cout << "- Please enter the file name\n--> ";
    getline(cin, photo);
    photo = load(photo);
    Image image(photo);
    for(int i=0; i<image.width; i++){
        for(int j=0; j<image.height; j++){
            for(int k=0; k<3; k++){
                image(i, j, k) = 255 - image(i, j, k);
                image(i, j, 0) = 255;
            }
        }  
    }
    how_to_save(image,photo);
}

//================================================================= Main Program ==============================================================//

int main(){
    // Welcome message and brief lines about our application.
    cout << "#==================== Welcome to our application ====================#" << endl << endl;
    cout << "---> This application takes any photo and applies some filters to it." << endl;
    cout << "---> Insert any image to apply filters to it in any of these formats:" << endl;
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    while (true)
    {
        // Print the menu for choosing what the user want to do.
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "What do you want to do ?\n[1] Apply a filter to a photo.\n[2] Exit.\nChoice: ";
        string choice;
        getline(cin, choice);

        // Applying a filter to the entered photo.
        if(choice == "1"){
            while (true){
                cout << "\n----------------------------------------------------------------------" << endl << endl;
                cout << "What filter do you want to apply ?\n"<< "[1] Grayscale Conversion.\n"<< "[2] Darken and Lighten Image.\n"
                    << "[3] Merge Images.\n"<< "[4] Invert Image.\n"<< "[5] Rotate Image.\n"<< "[6] Black and White.\n"
                    << "[7] Flip.\n"<< "[8] Infrared Photography.\n" << "[9] Back.\n"<< "Choice: ";
                string choice1;
                getline(cin, choice1);

                // Applying filter1 (Grayscale Conversion).
                if (choice1 == "1")
                {
                    Grayscale_Conversion();
                    break;
                }

                // Applying filter2 (Darken and Lighten Image).
                else if (choice1 == "2")
                {
                    Darken_and_Lighten();
                    break;
                }

                // Applying filter3 (Merge Images).
                else if (choice1 == "3")
                {
                    Merge_Images();
                    break;
                }

                // Applying filter4 (Invert Image).
                else if (choice1 == "4")
                {
                    Invert_Image();
                    break;
                }

                // Applying filter5 (Rotate Image).
                else if (choice1 == "5")
                {
                    Rotate_Image();
                    break;
                }

                // Applying filter6 (Black and White Image).
                else if (choice1 == "6")
                {
                    Black_n_White();
                    break;
                }

                // Applying filter7 (Flip Image).
                else if (choice1 == "7")
                {
                    Flip();
                    break;
                }

                // Applying filter7 (Flip Image).
                else if (choice1 == "8")
                {
                    Infrared_Photography();
                    break;
                }

                // Back to the main menu.
                else if (choice1 =="9")
                    break;

                // Invalid choice.
                else{
                    cout << "Please enter a valid choice." << endl;   
                    continue;
                }
            }
        }
        // Exit the program.
        else if(choice == "2")
            break;
        
        // Invalid choice for the menu.
        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "#===== Thanks for using our application =====#" << endl;
    return 0;
}