/* Student name           ===>    ID
 * Anas Amin Mohamed      ===> [20220069]
 * Mohamed Mahmoud Hassan ===> [20220307]
 * Hassan Mohamed Ismail  ===> [20220114]
 */

#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include "bmplib.h"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char shrunkimage[SIZE][SIZE];


void loadImage();
void loadImage2(); // Added this for loading a second image to use it in merge function.
void saveImage();
void doSomethingForImage();

int main()
{
    loadImage(); // Load the initial image.
    doSomethingForImage(); // Perform some operations on the image.
    saveImage(); // Save the modified image.
    return 0;
}
//========================================================================================
void ShrunkImage(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            shrunkimage[i][j] = 255;
        }
    }
}

//========================================================================================

// Function to load an image.
void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Adding ".bmp" extension and load the image using a function from the BMP library.
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//========================================================================================

// Function to load a second image (added for merging operation).
void loadImage2() {
    char image2FileName[100];

    // Get gray scale image file name for the second image.
    cout << "Enter the second source image file name: ";
    cin >> image2FileName;

    // Adding ".bmp" extension and load the second image using a function from the BMP library.
    strcat(image2FileName, ".bmp");
    readGSBMP(image2FileName, image2);
}

//========================================================================================

// Function to save the modified image.
void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Adding ".bmp" extension and save the image using a function from the BMP library.
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//========================================================================================

// Function to convert the image to black and white.
void BW()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

//========================================================================================

// Function to invert the colors of the image.
void invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] == 255)
                image[i][j] = 0;
            else if (image[i][j] == 0)
                image[i][j] = 255;
            else
                image[i][j] = 255 - image[i][j];
        }
    }
}

//========================================================================================

// Function to darken the image.
void darken() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image[i][j] / 2;
        }
    }
}

//========================================================================================

// Function to lighten the image.
void lighten() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image[i][j] + ((255 - image[i][j]) / 2);
        }
    }
}

//========================================================================================

// Function to flip the image horizontally.
void fliph() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            swap(image[i][j], image[i][SIZE - j - 1]);
        }
    }
}

//========================================================================================

// Function to flip the image vertically.
void flipv() {
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE; j++) {
            swap(image[i][j], image[SIZE - i - 1][j]);
        }
    }
}

//========================================================================================

// Function to rotate the image 270 degrees.
void rotate270() {
    unsigned char rot[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            rot[i][j] = image[j][SIZE - i - 1];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = rot[i][j];
        }
    }
}

//========================================================================================

// Function to rotate the image 180 degrees.
void rotate180() {
    unsigned char rot[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            rot[i][j] = image[SIZE - i - 1][SIZE - j - 1];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = rot[i][j];
        }
    }
}

//========================================================================================

// Function to rotate the image 90 degrees.
void rotate90() {
    unsigned char rot[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            rot[i][j] = image[SIZE - j - 1][i];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = rot[i][j];
        }
    }
}

//========================================================================================

// Function to merge two images.
void merge() {
    loadImage2(); // Load the second image.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

//========================================================================================

// Function to Shrink image.
void shrinktoHalf() {
    unsigned char newImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = 255;
        }
    }

    unsigned char shrunk[SIZE / 2][SIZE / 2];
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            shrunk[i][j] = (image[2 * i][2 * j] + image[2 * i][2 * j + 1] + image[2 * i + 1][2 * j] + image[2 * i + 1][2 * j + 1]) / 4;
        }
    }

    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            newImage[i][j] = shrunk[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = newImage[i][j];
        }
    }
}



void shrinktoOnethird() {
    unsigned char newImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = 255;
        }
    }

    unsigned char shrunk[SIZE / 3][SIZE / 3];
    for (int i = 0; i < SIZE / 3; i++) {
        for (int j = 0; j < SIZE / 3; j++) {
            int sum = 0;
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    sum += image[3 * i + x][3 * j + y];
                }
            }
            shrunk[i][j] = sum / 9;
        }
    }

    for (int i = 0; i < SIZE / 3; i++) {
        for (int j = 0; j < SIZE / 3; j++) {
            newImage[i][j] = shrunk[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = newImage[i][j];
        }
    }
}

void shrinktoQuarter() {
    unsigned char newImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = 255; // White background
        }
    }

    unsigned char shrunk[SIZE / 4][SIZE / 4];
    for (int i = 0; i < SIZE / 4; i++) {
        for (int j = 0; j < SIZE / 4; j++) {
            int sum = 0;
            for (int x = 0; x < 4; x++) {
                for (int y = 0; y < 4; y++) {
                    sum += image[4 * i + x][4 * j + y];
                }
            }
            shrunk[i][j] = sum / 16;
        }
    }

    for (int i = 0; i < SIZE / 4; i++) {
        for (int j = 0; j < SIZE / 4; j++) {
            newImage[i][j] = shrunk[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = newImage[i][j];
        }
    }
}

//========================================================================================
// Function to blur image.
void blur() {
    unsigned char newImage[SIZE][SIZE];

    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            int sum = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    sum += image[i + x][j + y];
                }
            }
            newImage[i][j] = sum / 9; // 9 is the total number of pixels in the 3x3 array.
        }
    }

    // Copy the blurred image back to the original image array.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = newImage[i][j];
        }
    }
}

//========================================================================================


void mirror_right(){

    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE /2 ; j++) {
            image[i][j] = image[i][SIZE -j -1] ;

        }

    }

}

//========================================================================================

void mirror_left(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE/2; j < SIZE  ; j++) {
            image[i][j] = image[i][SIZE - j -1] ;

        }

    }

}

//========================================================================================


void mirror_up(){

    for (int i = SIZE /2; i < SIZE  ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            image[i][j] = image[SIZE -i -1][j] ;

        }

    }

}

//========================================================================================


void mirror_down(){

    for (int i = 0; i < SIZE /2 ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            image[i][j] = image[SIZE -i -1][j] ;

        }

    }

}



//========================================================================================


// Function to detect edges using Sobel operator
void detectEdges() {
    // Sobel operator kernels for horizontal and vertical gradients
    int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Create a new image array to store the edge-detected image
    unsigned char newImage[SIZE][SIZE];

    // Loop through the image pixels (excluding the border pixels)
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            int gradientX = 0;
            int gradientY = 0;

            // Apply Sobel operator to the 3x3 neighborhood of the current pixel
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    gradientX += image[i + x][j + y] * sobelX[x + 1][y + 1];
                    gradientY += image[i + x][j + y] * sobelY[x + 1][y + 1];
                }
            }

            // Calculate the gradient magnitude
            int gradientMagnitude = sqrt(gradientX * gradientX + gradientY * gradientY);

            // Apply a threshold to detect edges
            if (gradientMagnitude > 127) {
                newImage[i][j] = 0; // Set edge pixels to black
            } else {
                newImage[i][j] = 255; // Set non-edge pixels to white
            }
        }
    }

    // Copy the edge-detected image back to the original image array
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            image[i][j] = newImage[i][j];
        }
    }
}

//========================================================================================


void cropImage(int x, int y, int l, int w) {
    if (x < 0 || y < 0 || x + l >= SIZE || y + w >= SIZE) {//Check if the crop area exceeds the boundaries

        cout << "Error, Crop area exceeds image boundaries" << endl;
    }

    unsigned char newImage[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i >= x && i < x + l && j >= y && j < y + w) {
                newImage[i][j] = image[i][j];
            } else {
                newImage[i][j] = 255; // Set the area outside the cropped region to white.
            }
        }
    }

    // Copy the cropped image back to the original image array.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = newImage[i][j];
        }
    }
}


//========================================================================================


void skewH()
{


            unsigned char image2[SIZE][SIZE];
            unsigned char image3[SIZE][SIZE];
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image2[i][j] = 255;
                    image3[i][j] = 255;
                }
            }

            cout << "Please enter degree to skew Up : ";
            double degree;
            cin >> degree;
            double rad = degree * (M_PI / 180.0);
            double tangent = tan(rad);
            int x = 256 / (1 + (1 / tangent));

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image2[(i*x)/SIZE][j] = image[i][j];
                }
            }

            double begin= 256.0 - x;
            double move = begin / 256.0;
            for (int i = 0; i < SIZE; i++) {
                for (int j = int(begin); j < begin+x; j++){
                    image3[j][i]=image2[int(j-begin)][i];
                }
                begin-=move;
            }
            for(int i = 0 ; i < SIZE ;i++)
            {
                for(int  j = 0 ; j < SIZE ; j++)
                {
                    image[i][j] = image3[i][j];
                }
            }
        }



//========================================================================================


void skewV(){
            unsigned char image2[SIZE][SIZE];
            unsigned char image3[SIZE][SIZE];
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image2[i][j] = 255;
                    image3[i][j] = 255;
                }
            }

            cout << "Please enter degree to skew Up : ";
            double degree;
            cin >> degree;
            double rad = degree * (M_PI / 180.0);
            double tangent = tan(rad);
            int x = 256 / (1 + (1 / tangent));

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image2[i][(j*x)/SIZE] = image[i][j];
                }
            }

            double begin= 256.0 - x;
            double move = begin / 256.0;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++){
                    image3[i][j+int(begin)]=image2[i][j];
                }
                begin-=move;
            }
            for(int i = 0 ; i < SIZE ;i++)
            {
                for(int  j = 0 ; j < SIZE ; j++)
                {
                    image[i][j] = image3[i][j];
                }
            }



        }

//========================================================================================


void Shuffle() {
    int first,second,third,forth;
    cout <<"Please , enter the sequence of the parts  : \n";
    cin>>first>>second>>third>>forth;

    unsigned char upleft[SIZE/2][SIZE/2];
    unsigned char upright[SIZE/2][SIZE/2];
    unsigned char downleft[SIZE/2][SIZE/2];
    unsigned char downright[SIZE/2][SIZE/2];

    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            upleft[i][j] = image[i][j];
            upright[i][j] = image[i][j + SIZE / 2];
            downleft[i][j] = image[i + SIZE / 2][j];
            downright[i][j] = image[i + SIZE / 2][j + SIZE / 2];
        }
    }

    if (first==1){

            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j] = upleft[i][j];
                }
            }

        }
    else if (first==2){

            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j] = upright[i][j];
                }
            }


        }

    else if (first==3){

            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j] = downleft[i][j];
                }
            }

        }
    else if (first==4){

            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j] = downright[i][j];
                }
            }


        }



    if (second==1){


            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j+SIZE/2] = upleft[i][j];
                }
            }

        }
    else if (second==2){


            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j+SIZE/2] = upright[i][j];
                }
            }


        }

    else if (second==3){


            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j+SIZE/2] = downleft[i][j];
                }
            }


        }
    else if (second==4){

            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i][j+SIZE/2] = downright[i][j];
                }
            }


        }



    if (third==1){


            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j] = upleft[i][j];
                }
            }
        }
    else if (third==2){


            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j] = upright[i][j];
                }
            }

        }

    else if (third==3){

            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j] = downleft[i][j];
                }
            }


        }
    else if (third==4){

            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j] = downright[i][j];
                }
            }

        }





    if (forth==1){


            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j+SIZE/2] = upleft[i][j];
                }
            }
        }
    else if (forth==2){

            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j+SIZE/2] = upright[i][j];
                }
            }

        }

    else if (forth==3){

            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0;  j<SIZE / 2; j++) {
                    image[i+SIZE/2][j+SIZE/2] = downleft[i][j];
                }
            }

        }
    else if (forth==4){

            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j<SIZE / 2; j++) {
                    image[i+SIZE/2][j+SIZE/2] = downright[i][j];
                }
            }

        }



}


//========================================================================================


// Function to enlarge image
void enlarge_1(){
    unsigned char NewImage[SIZE][SIZE];
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            NewImage[i][j] = 255;
        }
    }
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            NewImage[i][j] = image[i / 2][j / 2];
        }
    }
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            image[i][j] = NewImage[i][j];
        }
    }
}

void enlarge_2(){
    unsigned char NewImage[SIZE][SIZE];
    for(int i = 0;i < SIZE ;i++){
        for(int j = 0;j < SIZE;j++){
            NewImage[i][j] = 255;
        }
    }
    for(int i = 0;i < SIZE ;i++){
        for(int j = 0;j < SIZE;j++){
            NewImage[i][j] = image[i / 2][j / 2+127];
        }
    }
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            image[i][j] = NewImage[i][j];
        }
    }
}

void enlarge_3(){
    unsigned char NewImage[SIZE][SIZE];
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE ;j++){
            NewImage[i][j] = 255;
        }
    }
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE ;j++){
            NewImage[i][j] = image[i / 2 + 127][j / 2];
        }
    }
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            image[i][j] = NewImage[i][j];
        }
    }
}

void enlarge_4(){
    unsigned char NewImage[SIZE][SIZE];
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            NewImage[i][j] = 255;
        }
    }
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            NewImage[i][j] = image[i / 2 + 127][j / 2 + 127];
        }
    }
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            image[i][j] = NewImage[i][j];
        }
    }
}

//========================================================================================

// Function to perform various operations on the loaded image based on user input.
void doSomethingForImage() {
    int filterNum, choice;
    cout << "Enter A Filter Number You Need: \n" << "1 ==> BW\n" << "2 ==> Invert\n" << "3 ==> Darken \n"
         << "4 ==> Lighten\n" << "5 ==> Flip\n" << "6 ==> Rotate\n" << "7 ==> Merge\n"
         << "8 ==> Shrink\n" << "9 ==> Blur\n" << "10 ==> Crop\n" << "11 ==> mirror\n" << "12 ==> detect edges\n"
         << "13 ==> skew\n" << "14 ==> Shuffle\n" << "15 ==> Enlarge \n";

    cin >> filterNum;
    switch (filterNum) {
        case 1:
            BW();
            break;
        case 2:
            invert();
            break;
        case 3:
            darken();
            break;
        case 4:
            lighten();
            break;

        case 5:
            cout << "1 ==> vertical\n" << "2 ==> horizontal\n";
            cin >> choice;
            if (choice == 1)
                flipv();
            else if (choice == 2)
                fliph();
            break;

        case 6:
            cout << "1 ==> for 270 deg \n " << "2 ==> for 180 deg \n " << "3 ==> for 90 deg \n";
            cin >> choice;
            if (choice == 1)
                rotate270();
            else if (choice == 2)
                rotate180();
            else if (choice == 3)
                rotate90();

            break;

        case 7:

            merge();
            break;

        case 8:
            cout << "Choose one from the next options: " << endl;
            cout << "1 ==> Shrink to 1/2\n" << "2 ==> Shrink to 1/3\n" << "3 ==> Shrink to 1/4\n";
            cin >> choice;
            if (choice == 1)
                shrinktoHalf();
            else if (choice == 2)
                shrinktoOnethird();
            else if (choice == 3)
                shrinktoQuarter();
            break;

        case 9:
            blur();
            blur();
            blur();
            blur();
            blur();
            blur();
            break;


        case 10:
            int x, y, l, w;
            cout << "Enter the x, y coordinates of the top-left corner of the crop area: ";
            cin >> x >> y;
            cout << "Enter the length and width of the crop area: ";
            cin >> l >> w;
            cropImage(x, y, l, w);
            break;

        case 11:
            cout << "Choose one from the next options: " << endl;
            cout << "1 ==> mirror_right \n" << "2 ==> mirror_left\n" << "3 ==> mirror_up\n" << "4 ==> mirror_down\n";
            cin >> choice;
            if (choice == 1)
                mirror_right();
            else if (choice == 2)
                mirror_left();
            else if (choice == 3)
                mirror_up();
            else
                mirror_down();
            break;

        case 12:
            detectEdges();
            break;

        case 13:
            cout << "Please , enter the type of the skewing : 1-Horizontal  2-Virtical \n";
            cin >> choice;
            if (choice == 1)
                skewH();
            else if (choice == 2)
                skewV();

            break;

        case 14:
            Shuffle();
            break;

        case 15:
            cout << "Enter the quarter you want to enlarge: ";
            int choice;
            cin >> choice;
            if (choice == 1)
                enlarge_1();
            else if (choice == 2)
                enlarge_2();
            else if (choice == 3)
                enlarge_3();
            else if (choice == 4)
                enlarge_4();
            break;
    }
}