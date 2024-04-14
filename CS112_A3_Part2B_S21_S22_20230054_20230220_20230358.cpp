/*
File name   :   CS112_A3_Part2B_S21_S22_20230054_20230220_20230358.cpp
Purpose     :   Make an application that takes a photo and apply a filter to it.
Version     :   3.0

                              Authors                   |           Filters         |                   Contributions
---> 1: Esraa Emary Abd Elsalam.          ID: 20230054  |   Merge - Lighten/Darken  |   how_to_save() - Main menu - Output formatting
---> 2: Abdelrahman Yasser Ali.           ID: 20230220  |     Black/White - Flip    |            load() - Filters adjustments
---> 2: Mohamed Nabil Elsaied Ali.        ID: 20230358  |      Rotate - Invert      |                  Resizing algorithm


Professor           :   Dr.Mohamed ElRamly
Teaching Assistant  :   Eng.Rana Abdelkader
Section Number      :   S21-S22
GitHub repository   :   https://github.com/esraa-emary/Assignment-3
System Diagram      :   https://drive.google.com/file/d/1Ajg6YGb8BwUtIZscLoIEWw0Hn7NWumuT/view?usp=sharing
*/
//========================================================================================================================================//

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <regex>
#include "Image_Class.h"
using namespace std;

// Save the effect in a new photo or the same one.
void how_to_save(Image &image, string &photo){
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Do you want to save the effect in a new photo or replace the base ?\n[1] New photo.\n[2] Replace the base.\nChoice: ";
    while (true)
    {
        string choice;
        getline(cin, choice);

        // Save the effect in a new photo.
        if(choice == "1"){
            string new_name;
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Remember that:" << endl;
            cout << "The new file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "Please enter the new file name:\n--> ";
            getline(cin, new_name);

            // Check the validity of the new file name.
            while(new_name.size() < 5 || ((new_name.substr(new_name.size() - 5 , 5) != ".jpeg") && (new_name.substr(new_name.size() - 4 , 4) != ".jpg") && (new_name.substr(new_name.size() - 4 , 4) != ".png") && (new_name.substr(new_name.size() - 4 , 4) != ".bmp"))){
                cout << "\n----------------------------------------------------------------------" << endl << endl;
                cout << "Invalid new file name.\n";
                cout << "\n----------------------------------------------------------------------" << endl << endl;
                cout << "Remember that:" << endl;
                cout << "The new file name must be one of the following format.\n";
                cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
                cout << "Please enter a valid new file name:\n--> ";
                getline(cin, new_name);
            }
            image.saveImage(new_name);
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Photo has been saved successfully." << endl;
            break;
        }
        
        // Save the effect in the same photo.
        else if(choice == "2"){
            image.saveImage(photo);
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Photo has been saved successfully." << endl;
            break;
        }
        
        // Invalid choice.
        else{
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please enter a valid choice:\n-->" << endl;   
            continue;
        }
    }
}

// Save the effect in a new photo only.
void how_to_save2(Image &image){
    string new_name;
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Remember that:" << endl;
    cout << "The new file name must be one of the following format.\n";
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    cout << "Please enter the new file name:\n--> ";
    getline(cin, new_name);

    // Check the validity of the new file name.
    while(new_name.size() < 5 || ((new_name.substr(new_name.size() - 4 , 4) != "jpeg") && (new_name.substr(new_name.size() - 3 , 3) != "jpg") && (new_name.substr(new_name.size() - 3 , 3) != "png") && (new_name.substr(new_name.size() - 3 , 3) != "bmp"))){
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "Remember that:" << endl;
        cout << "The new file name must be one of the following format.\n";
        cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
        cout << "Please enter a valid new file name:\n--> ";
        getline(cin, new_name);
    }
    image.saveImage(new_name);
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Photo has been saved successfully." << endl;
}

// Get the image from the user to apply the filter.
string load(string &name){
    while (true) {
        cout << endl;
        try {
        Image image(name);
        cout << "----------------------------------------------------------------------" << endl << endl;
        cout << "Photo Loaded Successfuly.\n";
        return name;
        }
        catch (invalid_argument) {
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please enter a valid file name:\n--> ";
            getline(cin, name);
        }
    }
}

// Validate input as numbers (digits only) then check it's within the specified dimension range.
// Called in Crop_Image()
string validateDimension(string num, int max_dimension) {
    regex digits ("\\d+");

    while (!(regex_match(num, digits))) {
        cout << "\n- Wrong Input! Please enter a valid number\n--> ";
        getline(cin, num);
    }

    while (stoi(num) <= max_dimension) {
        cout << "\n- Wrong Input! Dimension should not exceed (" << max_dimension << ") !\n"
             << "- Please enter a valid dimension\n--> ";
        getline(cin, num);
        return validateDimension(num, max_dimension);
    }

    return num;
}


// ========================================================== Main Functions ========================================================== //

// ========================================================== Filter 1 (Grayscale Conversion) ========================================================== //
Image Grayscale_Conversion(Image &image){
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
    return image;
}

// ========================================================== Filter 2 (Black and White) ========================================================== //
Image Black_n_White(Image &image) {
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
    return image;
}

// ========================================================== Filter 3 (Invert Image) ========================================================== //
Image Invert_Image(Image &image){
    for(int i=0; i<image.width; i++){
        for(int j=0; j<image.height; j++){
            for(int k=0; k<3; k++){
                image(i,j,k) = 255 - image(i,j,k);                               // Change pixel values.
            }
        }  
    }
    return image;
}

// ========================================================== Filter 4 (Merge Images) ========================================================== //
Image Merge_Images(Image &photo11, Image &photo22){
    // Declare minimum width and minimum height to unify dimensions for both photos
    string choice ;
    int width ,height ;
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "What do you want to do ?\n" << "[1] Resize images to the biggest width height.\n" << "[2] Resize images to the biggest width height.\n" << "[3] Back.\nChoice: ";
    getline(cin, choice);
    while (true){
        if (choice=="1"){
            width = max(photo11.width, photo22.width);
            height = max(photo11.height, photo22.height);
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
            return photo_result;
        }

        else if (choice=="2"){
            width = min(photo11.width, photo22.width);
            height = min(photo11.height, photo22.height);
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
            return photo_result;
        }

        // Back to the main menu.
        else if (choice == "3"){
            return photo11;
            break;
        }
            
        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
}

// ========================================================== Filter 5 (Flip) ========================================================== //
Image Flip_Image(Image &image) {
    while (true) {
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "Do you want to flip horizontally or vertically ?\n"<< "[1] Horizontally\n"
            << "[2] Vertically\n"<< "[3] Back.\n"<< "Choice: ";
        string choice;
        getline(cin, choice);

        // Flip horizontally
        if (choice == "1") {
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
            return image;
        }

        // Flip vertically
        else if (choice == "2") {
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
            return image;
        }

        // Back to the main menu.
        else if (choice == "3") 
            break;
        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    return image;
}

// ========================================================== Filter 6 (Rotate Image) ========================================================== //
Image Rotate_Image(Image &image){
    while (true)
    {
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "What rotation do you want ?\n[1] Rotate 90.\n[2] Rotate 180.\n[3] Rotate 270.\n[4] Back.\nChoice: ";
        string choice2;
        getline(cin, choice2);

        // Rotate 90°.
        if (choice2 ==  "1"){
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
            return rotate;
            break;
        }

        // Rotate 180°.
        else if(choice2 == "2"){
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
            return rotate;
        }

        // Rotate 270°.
        else if(choice2 == "3"){
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
            return rotate;
        }

        // Back to the main menu.
        else if (choice2 =="4")
            break;

        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    return image;
}

// ========================================================== Filter 7 (Darken and Lighten Image) ========================================================== //
Image Darken_and_Lighten(Image &image){
    while (true)
    {
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "Do you want to darken or lighten the image ?\n[1] Darken The Image.\n[2] Lighten The Image.\n[3] Back.\nChoice: ";
        string choice2;
        getline(cin, choice2);

        // Darken The Image.
        if (choice2 ==  "1"){
            float darken = 0.5;                                                   // Initialize darken value.
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k) *= darken;                                 // Change pixel values.
                    }
                }
            }
            return image;
        }

        // Lighten The Image.
        else if(choice2 == "2"){
            float lighten = 1.5;                                                // Initialize lighten value.
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        int val = image(i, j, k) * lighten;                     // Change pixel values.
                        if (val > 255)                                          // Check if channel value exceeds 255.
                            (image(i, j, k) = 255);
                        else
                            image(i, j, k) = val;
                    }
                }
            }
            return image;
        }

        // Back to the main menu.
        else if (choice2 =="3")
            break;

        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    return image;
}

// ========================================================== Filter 8 (Crop Image) ========================================================== //
Image Crop_Image(Image &image){
    cout << "\n----------------------------------------------------------------------" << endl << endl;

    // Get starting dimension
    cout << "\n- Enter the dimensions to start cropping from:\n";
    string start_w, start_h;
    cout << "\n- Width --> ";
    getline(cin, start_w);
    start_w = validateDimension(start_w, image.width);

    cout << "\n- Height --> ";
    getline(cin, start_h);
    start_w = validateDimension(start_h, image.height);


    // Get new dimensions
    cout << "\n- Enter the new dimensions:\n";
    string width, height;
    cout << "\n- Width --> ";
    getline(cin, width);
    width = validateDimension(width, image.width - stoi(start_w));

    cout << "\n- Height --> ";
    getline(cin, height);
    height = validateDimension(height, image.height - stoi(start_h));

    // Assigning dimensions as integer types
    int w = stoi(width), h = stoi(height);
    int w_start = stoi(start_w), h_start = stoi(start_h);

    Image result(w, h);

    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            for(int k = 0; k < 3; k++){
                result(i, j, k) = image(w_start + i, w_start + j, k);
            }
        }  
    }

    return result;
}

// ========================================================== Filter 9 (Adding a Frame to the Picture) ========================================================== //
Image Frame_Image(Image &image){
    while (true)
    {
        int width , height , minimum;
        width = image.width; 
        height = image.height;
        minimum = min(width , height);
        
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "What type of frame do you want ?\n[1] Simple.\n[2] Fancy.\n[3] Back.\nChoice: ";
        string choice2;
        getline(cin,choice2);

        // Apply a Simple frame.
        if (choice2 == "1"){
            for (int x = 0 ; x < width ; x++){
                for(int y = 0 ; y < height ; y++){
                    for(int k = 0 ; k < 3 ; k++){
                        if((x > (minimum * 0.01) && x < (minimum * 0.025)) || (x < width - (minimum * 0.01) && x > width - (minimum * 0.025)) ||
                        (y > (minimum * 0.01) && y < (minimum * 0.025)) || (y < height - (minimum * 0.01) && y > height - (minimum * 0.025))){
                            if((y>(minimum*0.01) &&y<height-(minimum*0.01) )&&(x>(minimum*0.01) &&x<width-(minimum*0.01) )){
                                image(x,y,0)=13;                           //left, right, top, bottom,blue.
                                image(x,y,1)=60;
                                image(x,y,2)=250;
                            }
                        }

                        if((x < (minimum * 0.01) || x > width - (minimum * 0.01) || y < (minimum * 0.01) || y > height - (minimum * 0.01))){
                            image(x,y,k)=245;                               //left, right, top, bottom.
                        }
                    }
                }
            }
            return image;
        }
        
        // Apply a Fancy frame.
        if (choice2 == "2"){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Which frame do you want ?\n[1] Frame 1.\n[2] Frame 2.\n[3] Back.\nChoice: ";
            string choice_frame;
            getline(cin, choice_frame);

            while (true)
            {
                // Apply frame 1.
                if (choice_frame == "1"){
                    for (int x = 0 ; x < width ; x++){
                        for(int y = 0; y < height ; y++){
                            for(int k = 0 ; k < 3 ; k++){
                            
                                if(( x > (minimum * 0.03) && x < (minimum * 0.034)) || (x < width - (minimum * 0.03) && x > width - (minimum * 0.034))){
                                    if((y > (minimum * 0.03) && y < height - (minimum * 0.03))){
                                        image(x,y,k) = 245;                    //y-axis.
                                    }
                                }

                                if((y>(minimum*0.028)&&y< (minimum*0.032) )||(y<height-(minimum*0.028) && y>height-(minimum*0.032))){
                                    if((x> (minimum*0.028) &&x<width-(minimum *0.028))){
                                        image(x,y,k)=245;                    //x-axis.
                                    }
                                }
            

                                if((x>(minimum*0.02)&&x<(minimum*0.024))|| (x<width-(minimum*0.02) && x>width-(minimum*0.024)) ||
                                (y>(minimum*0.02)&&y< (minimum*0.024) )||(y<height-(minimum*0.02) && y>height-(minimum*0.024))){
                                    image(x,y,k)=245; 
                    
                                }

                                if((x> (minimum*0.008) &&x< (minimum*0.02) )|| (x<width-(minimum*0.008)&&x>width-(minimum*0.02)) ||                              
                                (y>(minimum*0.008)&&y<(minimum*0.02))||(y<height-(minimum*0.008) && y>height-(minimum*0.02))){
                                    if((y>(minimum*0.008)&&y<height-(minimum*0.008))&&(x>(minimum*0.008)&&x<width-(minimum*0.008))){
                                        image(x,y,0)=13;                    //left, right, top, bottom, blue.
                                        image(x,y,1)=60;
                                        image(x,y,2)=250;
                                    }
                                }
                            
                                if((x<(minimum*0.008)|| x>width-(minimum*0.008)||y<(minimum*0.008)||y>height-(minimum*0.008))){
                                    image(x,y,k)=245;                       //left, right, top, bottom.
                                }  
                            }
                        }
                    }
                    return image;
                }

                // Apply frame 2.
                else if(choice_frame == "2"){
                    for (int x=0; x<width ; x++){
                        for(int y=0; y<height; y++){
                            for(int k=0;k<3;k++){
                                if((x<(minimum*0.005)|| x>width-(minimum*0.005)||y<(minimum*0.005)||y>height-(minimum*0.005))){
                                    image(x,y,k)=245;                        //left, right, top, bottom.
                                }
                            
                                else if((x> (minimum*0.005) &&x< (minimum*0.018) )|| (x<width-(minimum*0.005)&&x>width-(minimum*0.018)) ||      
                                (y>(minimum*0.005)&&y<(minimum*0.018))||(y<height-(minimum*0.005) && y>height-(minimum*0.018))){
                                    if((y>(minimum*0.005)&&y<height-(minimum*0.005))&&(x>(minimum*0.005)&&x<width-(minimum*0.005))){
                                        image(x,y,0)=13;                     //left, right, top, bottom,blue
                                        image(x,y,1)=60;
                                        image(x,y,2)=250;
                                    }
                                }
                                   
                                    
                                else if((x> (minimum*0.018) &&x< (minimum*0.03) )|| (x<width-(minimum*0.018)&&x>width-(minimum*0.03)) ||
                                (y>(minimum*0.018)&&y<(minimum*0.03))||(y<height-(minimum*0.018) && y>height-(minimum*0.03))){
                                    if(((y>(minimum*0.018)&&y<height-(minimum*0.018))&&(x>(minimum*0.018)&&x<width-(minimum*0.018)))){
                                        image(x,y,k)=245;                    //left, right, top, bottom,blue
                                    }
                                }

                                //squares
                                else if(((x> (minimum*0.03) &&x< (minimum*0.045) )|| (x<width-(minimum*0.03)&&(x>width-(minimum*0.045))))
                                && ((y>(minimum*0.03) && y<(minimum*0.045))||(y<height-(minimum*0.03) && y>height-(minimum*0.045)))){
                                    image(x,y,k)=245;
                                }

                                //square2//width
                                if((((x> (minimum*0.03) &&x< (minimum*0.065) ))|| (x<width-(minimum*0.03)&&(x>width-(minimum*0.065))))
                                && ((y>(minimum*0.06) && y < (minimum*0.063)||(y<height-(minimum*0.06) && y>height-(minimum*0.063))))){
                                    image(x,y,k)=245;
                                }

                                //square2//height
                                else if((((x> (minimum*0.06) &&x< (minimum*0.063) ))|| (x<width-(minimum*0.06)&&(x>width-(minimum*0.063))))
                                && ((y>(minimum*0.03) && y<(minimum*0.065)||(y<height-(minimum*0.03) && y>height-(minimum*0.065))))){
                                    image(x,y,k)=245;  
                                }

                                //square3//width               
                                if((((x> (minimum*0.03) &&x< (minimum*0.085) ))|| (x<width-(minimum*0.03)&&(x>width-(minimum*0.085))))
                                && ((y>(minimum*0.075) && y<(minimum*0.085)||(y<height-(minimum*0.075) && y>height-(minimum*0.085))))){
                                    image(x,y,k)=245;
                                }

                                //square3//height
                                else if((((x> (minimum*0.075) &&x< (minimum*0.085) ))|| (x<width-(minimum*0.075)&&(x>width-(minimum*0.085))))
                                && ((y>(minimum*0.03) && y<(minimum*0.085)||(y<height-(minimum*0.03) && y>height-(minimum*0.085))))){
                                    image(x,y,k)=245;
                                }
                            }
                        }
                    }
                    return image;
                }

                // Back to the menu.
                else if (choice_frame == "3")
                    break;

                else{
                    cout << "Please enter a valid choice." << endl;   
                    continue;
                }
            }
        }
          
        // Back to the main menu.
        else if (choice2 =="3")
            break;

        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    return image;
}

// ========================================================== Filter 10 (Detect_Image_Edges) ========================================================== //
Image Detect_Image_Edges(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;  // Initialize average value.
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);  // Accumulate pixel values.
            }

            avg /= 3;  // Calculate average.
            int val;

            if (avg > 127) {
                val = 255;
            } else {
                val = 0;
            }

            // Set all channels to either 0 or 255 (to obtain black and white only)
            image(i, j, 0) = val;
            image(i, j, 1) = val;
            image(i, j, 2) = val;
        }
    }

    for (int i = 0; i < image.width; i++) {
        bool flag = false;
        bool flag2 = false;
        for (int j = 1; j < image.width; j++) {        
            if (j > 0 && image(i, j - 1, 0) == 255 && image(i, j, 0) == 0 && !flag) {
                flag2 = false;
                flag = true;
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }

            else if (j < image.width - 1 && image(i, j, 0) == 0 && image(i, j + 1, 0) == 255 && !flag2){
                flag = false;
                flag2 = true;
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }

            else{
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    return image;
}            

// ========================================================== Filter 11 (Resizing Images) ========================================================== //
Image Resizing_Image(Image &image){
    float width, height;
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Please enter the width you want:\n--> ";                               // Read the width.
    cin >>  width;
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Please enter the height you want:\n--> ";                              // Read the height.
    cin >> height;
    cin.ignore();

    Image image_result(width,height);
    float step_width1 = image.width/width;
    float step_height1 = image.height/height;

    for(int i =0 ;i<width;i++){
        for(int j=0;j<height;j++){
            for(int k=0;k<3;k++){
                image_result(i,j,k) = image((i*step_width1) , (j*step_height1),k);   // Change pixel values. 
            }
        }
    }
    image = image_result;
    return image;
}

// ========================================================== Filter 12 (Blur Image) ========================================================== //
Image Blur_Image(Image &image){

    return image;
}

// ========================================================== Filter 13 (Natural sunlight) ========================================================== //
Image Natural_sunlight(Image &image){
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            if (image(i, j, 1) <= 220) image(i, j, 1) += 35;  // Check for underflow
            else image(i, j, 1) = 255;

            if (image(i, j, 0) <= 220) image(i, j, 0) += 35;  // Check for underflow
            else image(i, j, 0) = 255;

            if (image(i, j, 2) >= 20) image(i, j, 2) -= 20;  // Check for underflow
            else image(i, j, 2) = 0;
        }
    }
    return image;
}

// ========================================================== Filter 14 (Purple Image) ========================================================== //
Image Purple_Image(Image &image){
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            if (image(i, j, 0) <= 240) image(i, j, 0) += 15;  // Check for overflow
            else image(i, j, 0) = 255;
            
            if (image(i, j, 2) <= 230) image(i, j, 2) += 25;  // Check for overflow
            else image(i, j, 2) = 255;
            
            if (image(i, j, 1) >= 40) image(i, j, 1) -= 40;  // Check for underflow
            else image(i, j, 1) = 0;
        }
    }
    return image;
}

// ========================================================== Filter 15 (Infrared Photography) ========================================================== //
Image Infrared_Photography(Image &image){
    for(int i=0; i<image.width; i++){
        for(int j=0; j<image.height; j++){
            for(int k=0; k<3; k++){
                image(i, j, k) = 255 - image(i, j, k);                          // Change pixel values.
                image(i, j, 0) = 255;
            }
        }  
    }
    return image;
}

//================================================================= Main Program ==============================================================//

int main(){
    // Welcome message and brief lines about our application.
    cout << "#==================== Welcome to our application ====================#" << endl << endl;
    cout << "---> This application takes any photo and applies some filters in it." << endl;
    cout << "---> To apply filters in a photo it must be in one of these formats:" << endl;
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    
    int count = 0;
    string name;
    Image image;
    bool flag = false;
    while (true){
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "What do you want to do ?\n"<< "[1]  Load a new image.\n" << "[2]  Grayscale Conversion.\n" << "[3]  Black and White.\n" << "[4]  Invert Image.\n" << "[5]  Merge Images.\n" 
             << "[6]  Flip Image.\n" << "[7]  Rotate Image.\n" << "[8]  Darken and Lighten Image.\n" << "[9]  Crop Image.\n" << "[10] Adding a Frame to the Picture.\n" << "[11] Detect Image Edges.\n" 
             << "[12] Resizing Image.\n" << "[13] Blur Image.\n" << "[14] Natural sunlight.\n" << "[15] Purple Image.\n" << "[16] Infrared Photography.\n" <<"[17] Save the image.\n" << "[18] Exit.\n"<< "Choice: ";
        string choice1;
        getline(cin, choice1);

        // Check that the user enrered an image at first.
        if (count == 0 && (choice1 == "2" || choice1 == "3" || choice1 == "4" || choice1  == "5" || choice1  == "6" || choice1  == "7" || 
            choice1  == "8" || choice1  == "9" || choice1  == "10" || choice1  == "11" || choice1  == "12" || choice1  == "13" || 
            choice1  == "14" || choice1  == "15" || choice1  == "16" || choice1  == "17")){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please load an image at first.\n";
            continue;
        }

        // Loading the image.
        if (choice1 == "1"){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Remember that:" << endl;
            cout << "The file name must be at one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "Please enter the file name:\n--> ";
            string photo_name;
            getline(cin, photo_name);
            name = photo_name;
            name = load(name);
            Image image1 (name);
            image = image1;
            count ++;
        }

        // Applying filter 1 (Grayscale Conversion).
        else if (choice1 == "2"){
            image = Grayscale_Conversion(image);
        }

        // Applying filter 2 (Black and White Image).
        else if (choice1 == "3"){
            image = Black_n_White(image);
        }

        // Applying filter 3 (Invert Image).
        else if (choice1 == "4"){
            image = Invert_Image(image);
        }

        // Applying filter 4 (Merge Images).
        else if (choice1 == "5"){
            flag = true;
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Enter the second image to merge with:\n--> ";
            string name2;
            getline(cin, name2);
            name2 = load(name2);
            Image image2(name2);
            image = Merge_Images(image, image2);
        }

        // Applying filter 5 (Flip Image).
        else if (choice1 == "6"){
            image = Flip_Image(image);
        }

        // Applying filter 6 (Rotate Image).
        else if (choice1 == "7"){
            image = Rotate_Image(image);
        }

        // Applying filter 7 (Darken and Lighten Image).
        else if (choice1 == "8"){
            image = Darken_and_Lighten(image);
        }

        // Applying filter 8 (Crop Image).
        else if (choice1 == "9"){
            image = Crop_Image(image);
        }

        // Applying filter 9 (Adding a Frame to the Picture).
        else if (choice1 == "10"){
            image = Frame_Image(image);
        }

        // Applying filter 10 (Detect Image Edges).
        else if (choice1 == "11"){
            image = Detect_Image_Edges(image);
        }

        // Applying filter 11 (Resizing Images).
        else if (choice1 == "12"){
            image = Resizing_Image(image);
        }

        // Applying filter 12 (Blur Image).
        else if (choice1 == "13"){
            image = Blur_Image(image);
        }
       
        // Applying filter 13 (Natural sunlight).
        else if (choice1 == "14"){
            image = Natural_sunlight(image);
        }

        // Applying filter 14 (Purple Image).
        else if (choice1 == "15"){
            image = Purple_Image(image);
        }

        // Applying filter 15 (Infrared Photography).
        else if (choice1 == "16"){
            image = Infrared_Photography(image);
        }

        // Save the image.
        else if (choice1 == "17"){
            if (flag){
                how_to_save2(image);
                flag = false;
            }
            else
                how_to_save(image, name);
        }

        // Exit the application.
        else if (choice1 =="18")
            break;

        // Invalid choice.
        else{
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "#===== Thanks for using our application =====#" << endl;
    return 0;
}
