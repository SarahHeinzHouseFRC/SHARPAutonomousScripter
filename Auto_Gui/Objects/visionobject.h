#ifndef VISIONOBJECT_H
#define VISIONOBJECT_H
#include <opencv2/opencv.hpp>

using namespace cv;
class visionObject
{
public:
    visionObject(vector<Point> *contour);
    Mat* getBinaryImage();
    void drawBinaryImage();
    Rect* getBoundingBox();
    String getName();
    bool isOffScreen();
    vector<Point>* getContour();
    double getArea();
    double getRatio();
    //void setHSV();



private:
     Mat _binaryImage;
     int _hueLow;
     int _saturationLow;
     int _valueLow;
     int _hueHigh;
     int _saturationHigh;
     int _valueHigh;
     String _name;
     Rect _boundingBox;
     bool _offScreen;
     vector<Point> _contour;
     double _area;
     double height;
     double width;
     double _ratioHeightWidth;
     int _numberInStack;
};

#endif // VISIONOBJECT_H
