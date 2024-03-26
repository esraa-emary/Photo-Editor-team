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
#include "Image_class\Image_Class.h"
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
            cout << "- Please enter the new file name\n-->";
            getline(cin, new_name);

            // Check the validity of the new file name.
            while((new_name.substr(new_name.size() - 4 , 4) != "jpeg") && (new_name.substr(new_name.size() - 3 , 3) != "jpg") && (new_name.substr(new_name.size() - 3 , 3) != "png") && (new_name.substr(new_name.size() - 3 , 3) != "bmp")){
                cout << "\n----------------------------------------------------------------------" << endl << endl;
                cout << "- Please enter a valid new file name\n-->";
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
            cout << "\n----------------------------------------------------------------------" << endl << endl;
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
    cout << "- Please enter the new file name\n-->";
    getline(cin, new_name);

    // Check the validity of the new file name.
    while((new_name.substr(new_name.size() - 4 , 4) != "jpeg") && (new_name.substr(new_name.size() - 3 , 3) != "jpg") && (new_name.substr(new_name.size() - 3 , 3) != "png") && (new_name.substr(new_name.size() - 3 , 3) != "bmp")){
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "- Please enter a valid new file name\n-->";
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
    cout << "- Please enter the file name\n-->";
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
            cout << "- Please enter the file name\n-->";
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
            cout << "- Please enter the file name\n-->";
            getline(cin, photo);
            photo = load(photo);
            Image image(photo);
            float lighten = 1.125;                                                // Initialize lighten value.
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k) *= lighten;                                // Change pixel values.
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
    string image1_name , image2_name;
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "- Please enter the file name\n-->";
    cin.ignore();
    getline(cin,image1_name);
    image1_name = load(image1_name);
    cout << "- Please enter the second file name\n-->";
    getline(cin,image2_name);
     image2_name = load(image2_name);
Image photo1(image1_name), photo2(image2_name),photo3(2500,1500),photo4(2500,1500);//photo3 makes changed to make it as photo1 but in size(2500,1500)
                                                                                  ////photo4 makes changed to make it as photo2 but in size(2500,1500)
   //try to make photo1 and photo2 with same dimensions(2500,1500) 
   float step_width1 = photo1.width/2500.0;
   float step_height1 = photo1.height/1500.0;
   float step_width2 = photo2.width/2500.0;
   float step_height2=photo2.height/1500.0;
   for(int i =0 ;i<2500;i++){
    for(int j=0;j<1500;j++){
        for(int k=0;k<3;k++){
            photo3(i,j,k)=photo1((i*step_width1),(j*step_height1),k);
            photo4(i,j,k)=photo2(i*step_width2,j*step_height2,k);
        }
    }
   }
    //Now photo3 is photo1 with dimensions(2500,1500)  , photo4 is photo2 with dimenions(2500,1500)
     Image photo_result(2500,1500); //merge after make two photos with same width (2500) and same height(1500) 
  for(int i = 0,x=1; i < 2500; i+=2,x+=2) {
        for(int j = 0,y=1; j < 1500; j+=2,y+=2) {
            for(int k = 0; k < 3; k++) {
                // Calculate the average of corresponding pixel values from two images
                photo_result(i, j, k) = photo3(i, j, k);
                 photo_result(x, y, k) = photo4(x, y, k);

            }
        }
    }
    how_to_save2(photo_result);
}

// Filter 4 (Invert Image).
void Invert_Image(){
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    string photo_name;                                                           // Get the photo and make it as an image.
    cout << "- Please enter the file name\n-->";
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
            cout << "- Please enter the file name\n-->";
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
            cout << "- Please enter the file name\n-->";
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
            cout << "- Please enter the file name\n-->";
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
                    << "[7] Flip.\n"<< "[8] Back.\n"<< "Choice: ";
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

                // Back to the main menu.
                else if (choice1 =="8")
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
