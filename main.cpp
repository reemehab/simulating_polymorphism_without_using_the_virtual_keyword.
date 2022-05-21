#include <iostream>

using namespace std;
struct ShapeVtable; // we dclared ShapeVtable here without implementation sp Shape struct can see it
//struct shape
struct Shape {
    ShapeVtable *vtable; // a pointer from shapeVtable struct
};
//shape virtual table
struct ShapeVtable {
    double (*GetArea)(Shape *);  // the virtual function GetArea that the children will implement
    void (*PrintInfo)(Shape *); // the virtual function GetArea that the children will implement
    void (*Destroy)(Shape *); //the virtual destructor
};

//function to Get the Area of a shape calling the vTable
double GetArea(Shape *shape) {
   return shape->vtable->GetArea(shape);
}

//function to print the information of any shape by calling the vTable
void PrintInfo(Shape *shape) {
    shape->vtable->PrintInfo(shape);

}
//the Virtual destructor that is used to destroy the object
void ShapeDestroy(Shape *shape) {
    shape->vtable->Destroy(shape);
}

//circle struct that  inherits from class Shape and has radius as attribute
struct Circle {
    Shape parent;
    double radius;
};

//function to get the area of the circle by taking an object form circle as a parameter and return the area equation
double CircleGetArea(Circle *circle) {
    return ((circle->radius) * (circle->radius) * (3.14));
}

//function to print the Circle's Radius
void circlePrintInfo(Circle *circle) {
    cout << "circle with radius = " << circle->radius << endl;
}

//the destructor of the circle struct
void CircleDestroy(Circle *circle) {
    delete circle;
}
// the circle's Virtual Table
ShapeVtable CircleVtable =
        {
                (double (*)(Shape *)) CircleGetArea, //implementing GetArea of a shape here as Circle Get Area
                (void (*)(Shape *)) circlePrintInfo, //implementing print info of a shape here as circlePrintInfo
                (void (*)(Shape *)) CircleDestroy  //implementing the destructor of a shape here as circleDestructor
        };

//function that initializes the Circle object with its Virtual Table and radius
void CircleInitialize(Circle *circle, double r) {
    circle->parent.vtable = &CircleVtable;
    circle->radius = r;
}

//Rectangle struct that inherits from shape struct and has attributes width and height
struct Rectangle {
    Shape parent;
    double width, height;
};
//function to get the area of the rectangle by taking an object form rectangle as a parameter and return the area equation
double RectangleGetArea(Rectangle *rectangle) {
    return (rectangle->width * rectangle->height);
}

//function to print the rectangle's height and width
void RectanglePrintInfo(Rectangle *rectangle) {
    cout <<"rectangle with width = " << rectangle->width << " and height = " << rectangle->height << endl;
}

//Destructor for rectangle that deletes the object at the end
void RectangleDestroy(Rectangle *rectangle) {
    delete rectangle;
}

//Rectangle virtual table that says that these functions are the implementation for the functions in shape vTable that allows inheritance
ShapeVtable RectangleVtable =
        {
                (double (*)(Shape *)) RectangleGetArea, //implementing GetArea of a shape here as Rectangle Get Area
                (void (*)(Shape *)) RectanglePrintInfo, //implementing print info of a shape here as Rectangle print info
                (void (*)(Shape *)) RectangleDestroy//implementing the destructor of a shape here as Rectangle destructor
        };

//function that initializes the rectangle object with its Virtual Table and height and width
void RectangleInitialize(Rectangle *rectangle, double w, double h) {
    rectangle->parent.vtable = &RectangleVtable;
    rectangle->width = w;
    rectangle->height = h;
}

//ellipse struct that inherites from shape class
struct Ellipse {
    Shape parent; //aggregation
    double radius1,radius2; //attributes
};

//function to get the area of the ellipse by taking an object form ellipse as a parameter and return the area equation
double elipseGetArea(Ellipse *elipse){
 return  elipse->radius1*elipse->radius2*3.14;
}

//function to print the elipe's info as radius 1 and radius 2
void elipsePrintInfo(Ellipse *elipse) {
    cout <<"ellipse with R1= " << elipse->radius1 << " and R2 = " << elipse->radius2 << endl;
}

//elipse destructor to delete the elipse object after termination
void elipseDestroy(Ellipse *elipse) {
    delete elipse;
}

ShapeVtable ellipseVtable =
        {
                (double (*)(Shape *)) elipseGetArea, //implementing GetArea of a shape here as ellipse Get Area
                (void (*)(Shape *)) elipsePrintInfo, //implementing print info of a shape here as ellipsePrintInfo
                (void (*)(Shape *)) elipseDestroy  //implementing the destructor of a shape here as ellipse Destructor
        };

//function that initializes the elipse object with its Virtual Table and radius1 and radius2
void EllipseInitialize(Ellipse *elipse, double radius1, double radius2) {
    elipse->parent.vtable = &ellipseVtable;
    elipse->radius1 = radius1;
    elipse->radius2 = radius2;
}


int main() {
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10
    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5
    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12
    Shape *shapes[3];
    shapes[0] = (Shape *) &circle;
    shapes[1] = (Shape *) &rectangle;
    shapes[2] = (Shape *) &ellipse;
    double total_area = 0;
    int i;
    for (i = 0; i < 3; i++) {
        double d = GetArea(shapes[i]);
        total_area += d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }

    cout << total_area << endl; // check if the value is correct
    return 0;
}