#pragma once

// report position of train to console
void logTrainPos(double x, double y, double dx, double dy, int train);
//void logCollision(double x, double y, int train1, int train2);

double determinant(double num1, double num2, double num3, double num4);
bool intersect(double x1, double y1, double destX1, double destY1, double x2, double y2, double destX2, double destY2);