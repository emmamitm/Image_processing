#include <iostream>
#include "header.h"
#include <iostream>
#include "fstream"
#include "ostream"
#include "vector"
#include "sstream"
#include "string"
using namespace std;

///write and read output
void openFile(string FileName, header& headerobject, vector<Image>& image){
    ifstream inFile(FileName, ios_base:: binary);
    if(inFile.is_open())
        cout<< "open";
    inFile.read(&headerobject.idlength, sizeof(headerobject.idlength));
    inFile.read(&headerobject.colorMapType, sizeof(headerobject.colorMapType));
    inFile.read(&headerobject.dataTypeCode, sizeof(headerobject.dataTypeCode));
    inFile.read((char*)&headerobject.colorMapOrigin, sizeof(headerobject.colorMapOrigin));
    inFile.read((char*)&headerobject.coloraMapLength, sizeof(headerobject.coloraMapLength));
    inFile.read(&headerobject.colorMapDepth, sizeof(headerobject.colorMapDepth));
    inFile.read((char*)&headerobject.xOrigin, sizeof(headerobject.xOrigin));
    inFile.read((char*)&headerobject.yOrigin, sizeof(headerobject.yOrigin));
    inFile.read((char*)&headerobject.width, sizeof(headerobject.width));
    inFile.read((char*)&headerobject.height, sizeof(headerobject.height));
    inFile.read(&headerobject.bitsPerPixel, sizeof(headerobject.bitsPerPixel));
    inFile.read(&headerobject.imageDescriptor, sizeof(headerobject.imageDescriptor));

    Image image1;
    image1.headerObj = headerobject;
    unsigned long pixelNum = headerobject.width * headerobject.height;
    for (int i = 0; i < pixelNum; ++i) {
        colorsNode c;
        inFile.read((char*)&c.blue, sizeof(c.blue));
        inFile.read((char*)&c.green, sizeof(c.green));
        inFile.read((char*)&c.red, sizeof(c.red));

        image1.colorsInImage.push_back(c);
    }

    image.push_back(image1);
    inFile.close();

}
void writeFile(string filePath, Image& image){
    //write the header to the file and then follow with image data
    ofstream newFileOutput(filePath, ios_base::binary);

    newFileOutput.write(&image.headerObj.idlength, sizeof(image.headerObj.idlength));
    newFileOutput.write(&image.headerObj.colorMapType, sizeof(image.headerObj.colorMapType));
    newFileOutput.write(&image.headerObj.dataTypeCode, sizeof(image.headerObj.dataTypeCode));
    newFileOutput.write((char*)&image.headerObj.colorMapOrigin, sizeof(image.headerObj.colorMapOrigin));
    newFileOutput.write((char *)&image.headerObj.coloraMapLength, sizeof(short));
    newFileOutput.write(&image.headerObj.colorMapDepth, sizeof(image.headerObj.colorMapDepth));
    newFileOutput.write((char*)&image.headerObj.xOrigin, sizeof(image.headerObj.xOrigin));
    newFileOutput.write((char *)&image.headerObj.yOrigin, sizeof(image.headerObj.yOrigin));
    newFileOutput.write((char*)&image.headerObj.width, sizeof(image.headerObj.width));
    newFileOutput.write((char *)&image.headerObj.height, sizeof(image.headerObj.height));
    newFileOutput.write(&image.headerObj.bitsPerPixel, sizeof(image.headerObj.bitsPerPixel));
    newFileOutput.write(&image.headerObj.imageDescriptor, sizeof(image.headerObj.imageDescriptor));

    unsigned long pixelNum =image.headerObj.width * image.headerObj.height;
    for (int i = 0; i < pixelNum; ++i) {
        newFileOutput.write((char*)&image.colorsInImage.at(i).blue, sizeof(image.colorsInImage.at(i).blue));
        newFileOutput.write((char*)&image.colorsInImage.at(i).green, sizeof(image.colorsInImage.at(i).green));
        newFileOutput.write((char*)&image.colorsInImage.at(i).red, sizeof(image.colorsInImage.at(i).red));
    }

    newFileOutput.close();

}

///math operations to pixels
unsigned char mult(unsigned char A, unsigned char B){
    const float total = 255.0f;
    float multiplier1= A/total;
    float multiplier2= B/total;
    float totalMult = ((multiplier1*multiplier2)*total)+0.5f;

    return (int)totalMult;

}
unsigned char sub(unsigned char A, unsigned char B){
    const float total = 255.0f;
    float multiplier1= A/total;
    float multiplier2= B/total;
    float totalSub = ((multiplier2-multiplier1)*total)+0.5f;
    if(totalSub<=0){
        totalSub=0.0f;
    }
    return (int)totalSub;

}
unsigned char screen(unsigned char A, unsigned char B){
    const float total = 255.0f;
    float multiplier1= A/total;
    float multiplier2= B/total;
    float totalScreen = (1.0-(1.0-multiplier1)*(1.0-multiplier2))*total +0.5f;
    return (int )totalScreen;

}
unsigned char over(unsigned char A, unsigned char B){
    const float total = 255.0f;
    float multiplier1= A/total;
    float multiplier2= B/total;

    if(multiplier2<= 0.5f){
        float totalOver = (2*multiplier2*multiplier1);
        return (unsigned char) (totalOver*total+0.5f);
    }
    else{
        float totalOver = 1- 2*(1-multiplier1)*(1-multiplier2);
        return (unsigned char) (totalOver*total +0.5f);
    }

}
void forLoop(Image& A, Image& B, Image& newImage){
    unsigned long pixelNum = newImage.headerObj.width* newImage.headerObj.height;
    unsigned long halfnum =newImage.headerObj.height/2;
    for (int i = 0; i < halfnum ; ++i) {
        for (int secondloop = 0; secondloop < halfnum; ++secondloop) {
            //bottomleft corner
            int factor= halfnum*i;
            newImage.colorsInImage.push_back(A.colorsInImage.at(secondloop+(factor) ));
        }
        for (int thirdloop = 0; thirdloop < halfnum; ++thirdloop) {
            int factor= halfnum*i;
            newImage.colorsInImage.push_back(B.colorsInImage.at(thirdloop+(factor)));
        }
    }
}

///void files that run the tests
void multiply(vector<Image> &image){
    Image A = image.at(0);
    Image B = image.at(1);
    Image newImage;
    newImage.headerObj.height=A.headerObj.height;
    newImage.headerObj.width=A.headerObj.width;
    newImage.headerObj.idlength= A.headerObj.idlength;
    newImage.headerObj.colorMapType= A.headerObj.colorMapType;
    newImage.headerObj.dataTypeCode= A.headerObj.dataTypeCode;
    newImage.headerObj.colorMapOrigin= A.headerObj.colorMapOrigin;
    newImage.headerObj.coloraMapLength= A.headerObj.coloraMapLength;
    newImage.headerObj.colorMapDepth= A.headerObj.colorMapDepth;
    newImage.headerObj.xOrigin= A.headerObj.xOrigin;
    newImage.headerObj.yOrigin= A.headerObj.yOrigin;
    newImage.headerObj.bitsPerPixel= A.headerObj.bitsPerPixel;
    newImage.headerObj.imageDescriptor= A.headerObj.imageDescriptor;

    unsigned long pixelNum = newImage.headerObj.height * newImage.headerObj.width;

    for (int i = 0; i < pixelNum ; ++i) {
        colorsNode c;
        c.blue= mult(A.colorsInImage.at(i).blue, B.colorsInImage.at(i).blue);

        c.green = mult(A.colorsInImage.at(i).green, B.colorsInImage.at(i).green);

        c.red = mult(A.colorsInImage.at(i).red, B.colorsInImage.at(i).red);

        newImage.colorsInImage.push_back(c);

    }
    image.push_back(newImage);

}
void Subtract(vector<Image> &image){
    Image A = image.at(0);
    Image B = image.at(1);
    Image newImage;
    newImage.headerObj.height=A.headerObj.height;
    newImage.headerObj.width=A.headerObj.width;
    newImage.headerObj.idlength= A.headerObj.idlength;
    newImage.headerObj.colorMapType= A.headerObj.colorMapType;
    newImage.headerObj.dataTypeCode= A.headerObj.dataTypeCode;
    newImage.headerObj.colorMapOrigin= A.headerObj.colorMapOrigin;
    newImage.headerObj.coloraMapLength= A.headerObj.coloraMapLength;
    newImage.headerObj.colorMapDepth= A.headerObj.colorMapDepth;
    newImage.headerObj.xOrigin= A.headerObj.xOrigin;
    newImage.headerObj.yOrigin= A.headerObj.yOrigin;
    newImage.headerObj.bitsPerPixel= A.headerObj.bitsPerPixel;
    newImage.headerObj.imageDescriptor= A.headerObj.imageDescriptor;

    unsigned long pixelNum = newImage.headerObj.height * newImage.headerObj.width;

    for (int i = 0; i < pixelNum ; ++i) {
        colorsNode c;
        c.blue= sub(A.colorsInImage.at(i).blue, B.colorsInImage.at(i).blue);

        c.green = sub(A.colorsInImage.at(i).green, B.colorsInImage.at(i).green);

        c.red = sub(A.colorsInImage.at(i).red, B.colorsInImage.at(i).red);

        newImage.colorsInImage.push_back(c);

    }
    image.push_back(newImage);

}
void Screen(vector<Image> &image){
    Image A = image.at(0);
    Image B = image.at(1);
    Image newImage;
    newImage.headerObj.height=A.headerObj.height;
    newImage.headerObj.width=A.headerObj.width;
    newImage.headerObj.idlength= A.headerObj.idlength;
    newImage.headerObj.colorMapType= A.headerObj.colorMapType;
    newImage.headerObj.dataTypeCode= A.headerObj.dataTypeCode;
    newImage.headerObj.colorMapOrigin= A.headerObj.colorMapOrigin;
    newImage.headerObj.coloraMapLength= A.headerObj.coloraMapLength;
    newImage.headerObj.colorMapDepth= A.headerObj.colorMapDepth;
    newImage.headerObj.xOrigin= A.headerObj.xOrigin;
    newImage.headerObj.yOrigin= A.headerObj.yOrigin;
    newImage.headerObj.bitsPerPixel= A.headerObj.bitsPerPixel;
    newImage.headerObj.imageDescriptor= A.headerObj.imageDescriptor;

    unsigned long pixelNum = newImage.headerObj.height * newImage.headerObj.width;

    for (int i = 0; i < pixelNum ; ++i) {
        colorsNode c;
        c.blue= screen(A.colorsInImage.at(i).blue, B.colorsInImage.at(i).blue);

        c.green = screen(A.colorsInImage.at(i).green, B.colorsInImage.at(i).green);

        c.red = screen(A.colorsInImage.at(i).red, B.colorsInImage.at(i).red);

        newImage.colorsInImage.push_back(c);

    }
    image.push_back(newImage);
}
void Overlay(vector<Image> &image){
    Image A = image.at(0);
    Image B = image.at(1);
    Image newImage;
    newImage.headerObj.height=A.headerObj.height;
    newImage.headerObj.width=A.headerObj.width;
    newImage.headerObj.idlength= A.headerObj.idlength;
    newImage.headerObj.colorMapType= A.headerObj.colorMapType;
    newImage.headerObj.dataTypeCode= A.headerObj.dataTypeCode;
    newImage.headerObj.colorMapOrigin= A.headerObj.colorMapOrigin;
    newImage.headerObj.coloraMapLength= A.headerObj.coloraMapLength;
    newImage.headerObj.colorMapDepth= A.headerObj.colorMapDepth;
    newImage.headerObj.xOrigin= A.headerObj.xOrigin;
    newImage.headerObj.yOrigin= A.headerObj.yOrigin;
    newImage.headerObj.bitsPerPixel= A.headerObj.bitsPerPixel;
    newImage.headerObj.imageDescriptor= A.headerObj.imageDescriptor;

    unsigned long pixelNum = newImage.headerObj.height * newImage.headerObj.width;

    for (int i = 0; i < pixelNum ; ++i) {
        colorsNode c;
        c.blue= over(A.colorsInImage.at(i).blue, B.colorsInImage.at(i).blue);

        c.green = over(A.colorsInImage.at(i).green, B.colorsInImage.at(i).green);

        c.red = over(A.colorsInImage.at(i).red, B.colorsInImage.at(i).red);

        newImage.colorsInImage.push_back(c);

    }
    image.push_back(newImage);

}
void Add( vector<Image> &image){

    Image A = image.at(0);

    Image newImage;
    newImage.headerObj.height=A.headerObj.height;
    newImage.headerObj.width=A.headerObj.width;
    newImage.headerObj.idlength= A.headerObj.idlength;
    newImage.headerObj.colorMapType= A.headerObj.colorMapType;
    newImage.headerObj.dataTypeCode= A.headerObj.dataTypeCode;
    newImage.headerObj.colorMapOrigin= A.headerObj.colorMapOrigin;
    newImage.headerObj.coloraMapLength= A.headerObj.coloraMapLength;
    newImage.headerObj.colorMapDepth= A.headerObj.colorMapDepth;
    newImage.headerObj.xOrigin= A.headerObj.xOrigin;
    newImage.headerObj.yOrigin= A.headerObj.yOrigin;
    newImage.headerObj.bitsPerPixel= A.headerObj.bitsPerPixel;
    newImage.headerObj.imageDescriptor= A.headerObj.imageDescriptor;

    unsigned long pixelNum = newImage.headerObj.height * newImage.headerObj.width;

    for (int i = 0; i < pixelNum ; ++i) {
        colorsNode c;
        c.blue= A.colorsInImage.at(i).blue;

        if(A.colorsInImage.at(i).green+200.0> 255){
            c.green=255;
        }
        else{
            c.green = A.colorsInImage.at(i).green+200.0;
        }

        c.red = A.colorsInImage.at(i).red;

        newImage.colorsInImage.push_back(c);

    }
    image.push_back(newImage);

}
void Scale( vector<Image> &image){

    Image A = image.at(0);

    Image newImage;
    newImage.headerObj.height=A.headerObj.height;
    newImage.headerObj.width=A.headerObj.width;
    newImage.headerObj.idlength= A.headerObj.idlength;
    newImage.headerObj.colorMapType= A.headerObj.colorMapType;
    newImage.headerObj.dataTypeCode= A.headerObj.dataTypeCode;
    newImage.headerObj.colorMapOrigin= A.headerObj.colorMapOrigin;
    newImage.headerObj.coloraMapLength= A.headerObj.coloraMapLength;
    newImage.headerObj.colorMapDepth= A.headerObj.colorMapDepth;
    newImage.headerObj.xOrigin= A.headerObj.xOrigin;
    newImage.headerObj.yOrigin= A.headerObj.yOrigin;
    newImage.headerObj.bitsPerPixel= A.headerObj.bitsPerPixel;
    newImage.headerObj.imageDescriptor= A.headerObj.imageDescriptor;

    unsigned long pixelNum = newImage.headerObj.height * newImage.headerObj.width;

    for (int i = 0; i < pixelNum ; ++i) {
        colorsNode c;
        c.blue= 0;

        c.green = A.colorsInImage.at(i).green;

        if(A.colorsInImage.at(i).red*4 >255){
            c.red=255;
        }
        else{
           c.red = A.colorsInImage.at(i).red*4;
        }

        newImage.colorsInImage.push_back(c);

    }
    image.push_back(newImage);

}
void ChangeChannel( vector<Image> &image){

    Image A = image.at(0);

    Image newImage;
    Image newImage2;
    Image newImage3;

    newImage.headerObj.height=A.headerObj.height;
    newImage.headerObj.width=A.headerObj.width;
    newImage.headerObj.idlength= A.headerObj.idlength;
    newImage.headerObj.colorMapType= A.headerObj.colorMapType;
    newImage.headerObj.dataTypeCode= A.headerObj.dataTypeCode;
    newImage.headerObj.colorMapOrigin= A.headerObj.colorMapOrigin;
    newImage.headerObj.coloraMapLength= A.headerObj.coloraMapLength;
    newImage.headerObj.colorMapDepth= A.headerObj.colorMapDepth;
    newImage.headerObj.xOrigin= A.headerObj.xOrigin;
    newImage.headerObj.yOrigin= A.headerObj.yOrigin;
    newImage.headerObj.bitsPerPixel= A.headerObj.bitsPerPixel;
    newImage.headerObj.imageDescriptor= A.headerObj.imageDescriptor;

    newImage2=newImage;
    newImage3=newImage;

    unsigned long pixelNum = newImage.headerObj.height * newImage.headerObj.width;

    for (int i = 0; i < pixelNum ; ++i) {
        colorsNode c,c2,c3;

        c.blue= A.colorsInImage.at(i).red;
        c.green = A.colorsInImage.at(i).red;
        c.red= A.colorsInImage.at(i).red;
        newImage.colorsInImage.push_back(c);

        c2.blue=A.colorsInImage.at(i).green;
        c2.green= A.colorsInImage.at(i).green;
        c2.red =A.colorsInImage.at(i).green;
        newImage2.colorsInImage.push_back(c2);

        c3.blue=A.colorsInImage.at(i).blue;
        c3.green = A.colorsInImage.at(i).blue;
        c3.red = A.colorsInImage.at(i).blue;
        newImage3.colorsInImage.push_back(c3);

    }
    image.push_back(newImage);
    image.push_back(newImage2);
    image.push_back(newImage3);

}
void CombineThreeChannels(vector<Image> &image)
{

    Image A = image.at(0);//red
    Image B = image.at(1);//green
    Image C = image.at(2);//blue
    Image newImage;

    newImage.headerObj.height=A.headerObj.height;
    newImage.headerObj.width=A.headerObj.width;
    newImage.headerObj.idlength= A.headerObj.idlength;
    newImage.headerObj.colorMapType= A.headerObj.colorMapType;
    newImage.headerObj.dataTypeCode= A.headerObj.dataTypeCode;
    newImage.headerObj.colorMapOrigin= A.headerObj.colorMapOrigin;
    newImage.headerObj.coloraMapLength= A.headerObj.coloraMapLength;
    newImage.headerObj.colorMapDepth= A.headerObj.colorMapDepth;
    newImage.headerObj.xOrigin= A.headerObj.xOrigin;
    newImage.headerObj.yOrigin= A.headerObj.yOrigin;
    newImage.headerObj.bitsPerPixel= A.headerObj.bitsPerPixel;
    newImage.headerObj.imageDescriptor= A.headerObj.imageDescriptor;

    unsigned long pixelNum = newImage.headerObj.width* newImage.headerObj.height;

    for (int i = 0; i < pixelNum ; ++i) {
        colorsNode c;
        c.red= A.colorsInImage.at(i).red;
        c.green = B.colorsInImage.at(i).green;
        c.blue= C.colorsInImage.at(i).blue;

        newImage.colorsInImage.push_back(c);

    }
    image.push_back(newImage);

}
void rotate180(vector<Image> &image){
    Image A = image.at(0);
    Image newImage;

    newImage.headerObj.height=A.headerObj.height;
    newImage.headerObj.width=A.headerObj.width;
    newImage.headerObj.idlength= A.headerObj.idlength;
    newImage.headerObj.colorMapType= A.headerObj.colorMapType;
    newImage.headerObj.dataTypeCode= A.headerObj.dataTypeCode;
    newImage.headerObj.colorMapOrigin= A.headerObj.colorMapOrigin;
    newImage.headerObj.coloraMapLength= A.headerObj.coloraMapLength;
    newImage.headerObj.colorMapDepth= A.headerObj.colorMapDepth;
    newImage.headerObj.xOrigin= A.headerObj.xOrigin;
    newImage.headerObj.yOrigin= A.headerObj.yOrigin;
    newImage.headerObj.bitsPerPixel= A.headerObj.bitsPerPixel;
    newImage.headerObj.imageDescriptor= A.headerObj.imageDescriptor;

    unsigned long pixelNum = newImage.headerObj.width* newImage.headerObj.height;
    long val = pixelNum;
    for (int i = 0; i < pixelNum ; ++i) {
        colorsNode c;
        c.red= A.colorsInImage.at( pixelNum-1-i).red;
        c.green = A.colorsInImage.at( pixelNum -1-i).green;
        c.blue= A.colorsInImage.at( pixelNum-1 -i).blue;

        newImage.colorsInImage.push_back(c);

    }
    image.push_back(newImage);

}
void extraCredit(vector<Image> &image){

    Image A = image.at(0); //text
    Image B = image.at(1); //pattern
    Image C = image.at(2); //car
    Image D = image.at(3); //circles
    Image newImage;

    newImage.headerObj.height=A.headerObj.height*2;
    newImage.headerObj.width=A.headerObj.width*2;
    newImage.headerObj.idlength= A.headerObj.idlength;
    newImage.headerObj.colorMapType= A.headerObj.colorMapType;
    newImage.headerObj.dataTypeCode= A.headerObj.dataTypeCode;
    newImage.headerObj.colorMapOrigin= A.headerObj.colorMapOrigin;
    newImage.headerObj.coloraMapLength= A.headerObj.coloraMapLength;
    newImage.headerObj.colorMapDepth= A.headerObj.colorMapDepth;
    newImage.headerObj.xOrigin= A.headerObj.xOrigin;
    newImage.headerObj.yOrigin= A.headerObj.yOrigin;
    newImage.headerObj.bitsPerPixel= A.headerObj.bitsPerPixel;
    newImage.headerObj.imageDescriptor= A.headerObj.imageDescriptor;

    forLoop(A, B, newImage);

    forLoop(C, D, newImage);

    image.push_back(newImage);



}


///tester
bool compareImages(vector<Image> &image){
    Image A = image.at(0);
    Image B = image.at(1);

    unsigned long size=  A.headerObj.height * B.headerObj.width;
    for (int i = 0; i < size; ++i) {
        if((A.colorsInImage.at(i).green == B.colorsInImage.at(i).green)&&(A.colorsInImage.at(i).blue == B.colorsInImage.at(i).blue) &&(A.colorsInImage.at(i).red == B.colorsInImage.at(i).red)){
            continue;
        } else{
            return false;
        }
    }

    return true;
}

///main --> will call the test cases
int main() {


    string input, output, example;

    input = "input/";
    output = "output/";
    example= "examples/";
    int testCase=1;

    if(testCase==1){
        //correct
        vector<Image> images;

        header headerObj;
        header headerObj2;

        openFile(input+ "layer1.tga", headerObj, images);
        openFile(input+ "pattern1.tga", headerObj2,images);
        multiply(images);
        writeFile(output+ "part1.tga", images.at(2));

        vector<Image> comparison;
        header headerObj3;
        openFile(example+ "EXAMPLE_part1.tga",headerObj3, comparison);

        comparison.push_back(images.at(2));

        if(compareImages(comparison) == true){
            cout<< "Test 1 completed successfully";
        }
        else{
            cout<< "Test 1 failed";
        }
        cout<<endl;
        testCase =2;

    }
    if (testCase==2){
        vector<Image> images;

        header headerObj;
        header headerObj2;

        openFile(input+ "layer2.tga", headerObj, images);
        openFile(input+ "car.tga", headerObj2,images);
        Subtract(images);
        writeFile(output+"part2.tga", images.at(2));

        vector<Image> comparison;
        header headerObj3;
        openFile(example+"EXAMPLE_part2.tga",headerObj3, comparison);
        comparison.push_back(images.at(2));

        if(compareImages(comparison) == true){
            cout<< "Test 2 completed successfully";
        }
        else{
            cout<< "Test 2 failed";
        }
        cout<<endl;

        testCase =3;


    }
    if (testCase ==3){
        //CORRECT
        vector<Image> images;

        header headerObj;
        header headerObj2;
        openFile(input+ "layer1.tga", headerObj, images);
        openFile(input+ "pattern2.tga", headerObj2,images);
        multiply(images);

        writeFile("extraNeededFile.tga", images.at(2));

        vector<Image> images2;
        images2.push_back(images.at(2));
        header headerObj3;
        openFile(input+ "text.tga", headerObj3,images2);

        Screen(images2);
        writeFile(output+"part3.tga", images2.at(2));

        vector<Image> comparison;
        header headerObj4;
        openFile(example+"EXAMPLE_part3.tga",headerObj4, comparison);
        comparison.push_back(images2.at(2));

        if(compareImages(comparison) == true){
            cout<< "Test 3 completed successfully";
        }
        else{
            cout<< "Test 3 failed";
        }
        cout<<endl;
        testCase =4;



    }
    if (testCase==4){
        //CORRECT
        vector<Image> images;

        header headerObj;
        header headerObj2;

        openFile(input+"layer2.tga", headerObj, images);
        openFile(input+"circles.tga", headerObj2,images);
        multiply(images);

        writeFile("test4first.tga", images.at(2));

        vector<Image> images2;

        header headerObj3;
        openFile(input+"pattern2.tga", headerObj3,images2);

        images2.push_back(images.at(2));


        Subtract(images2);
        writeFile(output+"test4.tga", images2.at(2));

        vector<Image> comparison;
        header headerObj4;
        openFile(example+"EXAMPLE_part4.tga",headerObj4, comparison);
        comparison.push_back(images2.at(2));

        if(compareImages(comparison) == true){
            cout<< "Test 4 completed successfully";
        }
        else{
            cout<< "Test 4 failed";
        }
        cout<<endl;
        testCase =5;


    }
    if(testCase==5){
        //CORRECT
        vector<Image> images;

        header headerObj;
        header headerObj2;

        openFile(input+"layer1.tga", headerObj, images);
        openFile(input+"pattern1.tga", headerObj2,images);


        Overlay(images);

        writeFile(output+"test5.tga", images.at(2));

        vector<Image> comparison;
        header headerObj4;
        openFile(example+"EXAMPLE_part5.tga",headerObj4, comparison);
        comparison.push_back(images.at(2));

        if(compareImages(comparison) == true){
            cout<< "Test 5 completed successfully";
        }
        else{
            cout<< "Test 5 failed";
        }
        cout<<endl;
        testCase =6;

    }
    if(testCase==6){
        //CORRECT
        vector<Image> images;

        header headerObj;

        openFile(input+"car.tga", headerObj, images);


        Add(images);

        writeFile(output+"test6.tga", images.at(1));

        vector<Image> comparison;
        header headerObj4;
        openFile(example+"EXAMPLE_part6.tga",headerObj4, comparison);
        comparison.push_back(images.at(1));

        if(compareImages(comparison) == true){
            cout<< "Test 6 completed successfully";
        }
        else{
            cout<< "Test 6 failed";
        }
        cout<<endl;
        testCase =7;
    }
    if(testCase ==7){
        //CORRECT
        vector<Image> images;

        header headerObj;

        openFile(input+"car.tga", headerObj, images);


        Scale(images);

        writeFile(output+"test7.tga", images.at(1));

        vector<Image> comparison;
        header headerObj4;
        openFile(example+"EXAMPLE_part7.tga",headerObj4, comparison);
        comparison.push_back(images.at(1));

        if(compareImages(comparison) == true){
            cout<< "Test 7 completed successfully";
        }
        else{
            cout<< "Test 7 failed";
        }
        cout<<endl;

        testCase =8;

    }
    if(testCase ==8){
        //CORRECT
        vector<Image> images;

        header headerObj;

        openFile(input+"car.tga", headerObj, images);

        ChangeChannel(images);

        writeFile(output+"part8_r.tga", images.at(1));
        writeFile(output+"part8_g.tga", images.at(2));
        writeFile(output+"part8_b.tga", images.at(3));

        vector<Image> comparison;
        header headerObj4;
        openFile(example+"EXAMPLE_part8_r.tga",headerObj4, comparison);
        comparison.push_back(images.at(1));

        if(compareImages(comparison) == true){
            cout<< "Test 8 red completed successfully";
        }
        else{
            cout<< "Test 8 red failed";
        }
        cout<<endl;

        vector<Image> comparison2;
        openFile(example+"EXAMPLE_part8_g.tga",headerObj4, comparison2);
        comparison2.push_back(images.at(2));

        if(compareImages(comparison2) == true){
            cout<< "Test 8 green completed successfully";
        }
        else{
            cout<< "Test 8 green failed";
        }
        cout<<endl;

        vector<Image> comparison3;
        openFile(example+"EXAMPLE_part8_b.tga",headerObj4, comparison3);
        comparison3.push_back(images.at(3));

        if(compareImages(comparison3) == true){
            cout<< "Test 8 blue completed successfully";

        }
        else{
            cout<< "Test 8 blue failed";
        }
        cout<<endl;
        testCase =9;

    }
    if(testCase ==9){
        //CORRECT
        vector<Image> images;

        header headerObj;
        header headerObj2;
        header headerObj3;


        openFile(input+"layer_red.tga", headerObj, images);
        openFile(input+"layer_green.tga", headerObj2, images);
        openFile(input+"layer_blue.tga", headerObj3, images);

        CombineThreeChannels(images);

        writeFile(output+"part9.tga", images.at(3));

        vector<Image> comparison;
        header headerObj4;
        openFile(example+"EXAMPLE_part9.tga",headerObj4, comparison);
        comparison.push_back(images.at(3));

        if(compareImages(comparison) == true){
            cout<< "Test 9 completed successfully";
        }
        else{
            cout<< "Test 9 failed";
        }
        cout<<endl;

        testCase =10;

    }
    if(testCase ==10){
        //CORRECT
        vector<Image> images;

        header headerObj;


        openFile(input+"text2.tga", headerObj, images);


        rotate180(images);

        writeFile(output+"part10.tga", images.at(1));

        vector<Image> comparison;
        header headerObj4;
        openFile(example+"EXAMPLE_part10.tga",headerObj4, comparison);
        comparison.push_back(images.at(1));

        if(compareImages(comparison) == true){
            cout<< "Test 10 completed successfully";
        }
        else{
            cout<< "Test 10 failed";
        }
        cout<<endl;

        testCase =11;

    }else if(testCase ==11){
        ///extra credit
        //CORRECT
        vector<Image> images;

        header headerObj;


        openFile("text.tga", headerObj, images); //bottom left
        openFile("pattern1.tga", headerObj, images); //bottom right
        openFile("car.tga", headerObj, images); //top left
        openFile("circles.tga", headerObj, images); //top right

        extraCredit(images);

        writeFile("EXTRACREDIT.tga", images.at(4));


    }
    cout<< "done";




}

//a .TGA file with image data is stared in a contiguous block of pixels equal to image width times image height
//each pixel contains 8 bits for red, 8 for green and 8 for blue
//each of these will contain a value 0-255 and will be stored with an unsigned char
//stored in order blue, green, red
//the first pixel in the image file represents the bottom left corner of the image
//the last pixel represents the top right corener of the image
/*
 *
 * cout<< "new stuff";
    cout<<endl;
    cout<<(int)newImage.idlength;
    cout<<endl;
    cout<< (int)newImage.colorMapType;
    cout<<endl;
    cout<< (int)newImage.dataTypeCode;
    cout<<endl;
    cout<< newImage.colorMapOrigin;
    cout<<endl;
    cout<< newImage.coloraMapLength;
    cout<<endl;
    cout<< (int)newImage.colorMapDepth;
    cout<<endl;
    cout<<  newImage.xOrigin;
    cout<<endl;
    cout<<newImage.yOrigin;
    cout<<endl;
    cout<< newImage.width;
    cout<<endl;
    cout<< newImage.height;
    cout<<endl;
    cout<< (int)newImage.bitsPerPixel;
    cout<<endl;
    cout<<(int) newImage.imageDescriptor;
    cout<<endl;


 *
 */