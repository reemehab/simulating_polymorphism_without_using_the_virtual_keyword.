#include <iostream>

using namespace std;
struct ShapeVtable;
struct Shape {
    ShapeVtable *vtable;
};

struct ShapeVtable {
    double (*GetArea)(Shape *);  // the virtual function GetArea that the children will implement
    void (*PrintInfo)(Shape *);
    void (*Destroy)(Shape *); //the virtual destructor
};

double GetArea(Shape *shape) {
    shape->vtable->GetArea(shape);
}

void PrintInfo(Shape *shape) {
    shape->vtable->PrintInfo(shape);

}

void ShapeDestroy(Shape *shape) {
    shape->vtable->Destroy(shape);
}

struct Circle {
    Shape parent;
    double radius;
};

double CircleGetArea(Circle *circle) {
    return ((circle->radius) * (circle->radius) * (3.14));
}

void circlePrintInfo(Circle *circle) {
    cout << "circle with radius = " << circle->radius << endl;
}

void CircleDestroy(Circle *circle) {
    delete circle;
}

ShapeVtable CircleVtable =
        {
                (double (*)(Shape *)) CircleGetArea,
                (void (*)(Shape *)) circlePrintInfo,
                (void (*)(Shape *)) CircleDestroy
        };

void CircleInitialize(Circle *circle, double r) {
    circle->parent.vtable = &CircleVtable;
    circle->radius = r;
}

struct Rectangle {
    Shape parent;
    double width, height;
};

double RectangleGetArea(Rectangle *rectangle) {
    return (rectangle->width * rectangle->height);
}

void RectanglePrintInfo(Rectangle *rectangle) {
    cout <<"rectangle with width = " << rectangle->width << " and height = " << rectangle->height << endl;
}

void RectangleDestroy(Rectangle *rectangle) {
    delete rectangle;
}

ShapeVtable RectangleVtable =
        {
                (double (*)(Shape *)) RectangleGetArea,
                (void (*)(Shape *)) RectanglePrintInfo,
                (void (*)(Shape *)) RectangleDestroy
        };

void RectangleInitialize(Rectangle *rectangle, double w, double h) {
    rectangle->parent.vtable = &RectangleVtable;
    rectangle->width = w;
    rectangle->height = h;
}

struct Ellipse {
    Shape parent;
    double R1,R2;
};
double elipseGetArea(Ellipse *elipse){
 return  elipse->R1*elipse->R2*3.14;
}

void elipsePrintInfo(Ellipse *elipse) {
    cout <<"ellipse with R1= " << elipse->R1 << " and R2 = " << elipse->R2 << endl;
}

void elipseDestroy(Ellipse *elipse) {
    delete elipse;
}

ShapeVtable ellipseVtable =
        {
                (double (*)(Shape *)) elipseGetArea,
                (void (*)(Shape *)) elipsePrintInfo,
                (void (*)(Shape *)) elipseDestroy
        };

void EllipseInitialize(Ellipse *elipse, double R1, double R2) {
    elipse->parent.vtable = &ellipseVtable;
    elipse->R1 = R1;
    elipse->R2 = R2;
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