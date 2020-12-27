/*------------------------------------------------------------------
 File:  CylinderVolume.c  (Lab 5)
 Author: Gilbert Arbez, Fall 2016
 Description: Calculates how the volume changes for different depths
              in a horizontal cylinder.
------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define symbolic constant
#define N       50    // number of points to compute
#define H_IX    0   // Index to row with depth, h, values
#define VOL_IX  1   // Index to row with volume values
#define NUM_ROWS 2  // number of rows in 2D array
#define TRUE    1
#define FALSE   0

// Definition of a structure type for user input
typedef struct
{
    double radius;  // in m
    double length;    // in m
} CYLINDER;

// Prototypes
void getDimensions(CYLINDER *);
void computeVolume(CYLINDER *, int n, double [][n]);
/*--------------------------------------------------------------------
Function: main
Description:  Calls getDimensions to get cylinder dimensions from the user,
              computeVolume to fill in the matrix containing depth/volume pairs,
              and displays the contents of the matrix in a table.
----------------------------------------------------------------------*/
void main()
{
    // Variable declarations
    CYLINDER cyl;  // structure variable fo cylinder
    double points[NUM_ROWS][N];  // N points of depth/volume
    int ix;   // for indexing the columns in the 2D array
    // Get input from user, the cylinder radius and length
    getDimensions(cyl);
    // Compute depth/volume points
    computeVolume(&cyl, N, points);  // no & for the points array
    // Display results (could have used a function to display the results)
    // Setup the start of the table
    printf("The change in liquid volume of the cylinder with radius %.2f \nand length %.2f as depth changes is as follows.\n",
            cyl.radius, cyl.length);
    printf("%10s    %10s\n","Depth", "Volume");
    printf("------------------------\n");
    // Loop to display each column of the table.
    for(ix = 0; ix <= N; ix = ix + 1)
       printf("%10.2f    %10.2f\n", points[H_IX][ix], points[VOL_IX][ix]);
}
/*------------------------------------------------------------------------
Function: getDimensions
Parameter
    cylPtr - pointer to a CYLINDER structure variable
Description: Prompts the user for the dimensions of the
             cylinder.  Ensures the values are > 0.
------------------------------------------------------------------------*/
void getDimensions(CYLINDER *cylPtr)
{
    int flag;
    do
    {
         flag = TRUE;
         printf("Please enter the values for the cylinder radius and length: ");
          scanf("%lf %lf",&cylPtr->radius, &cylPtr->length);
          if( cylPtr.radius <= 0.0 || cylPtr->length <= 0.0)
          {
              printf("Both values must be greater than zero.\n");
              flag = FALSE;
          }
    } while(flag == FALSE);
}
/*------------------------------------------------------------------------
Function: computeVolume
Parameter
    cylPtr - pointer to a CYLINDER structure variable
    n      - number of points (note that using this parameter makes
                               the function independent of the symbolic
                               constant and generalizes the function)
    dataPoints - depth/volume points stored in a 2D array
                 Row H_IX contains the depth values
                 Row VOL_IX contains the volume values
Description: Computes a number of depth/volume data points that varies
             the depth of the liquid from 0 to the cylinder diameter.
             n such data points are computed (i.e. the increment in the
                                              value of h is 2r/n).
------------------------------------------------------------------------*/
void computeVolume(CYLINDER *cylPtr, int n, double dataPoints[][n])
{
    // Declaration of variables
    double increment;   // how to increment the depth
    double h;           // depth value
    int ix;             // loop counter and column index in the 2D array
    double term1, term2;  // for computing terms of the equation
    // setup the variables
    increment = cylPtr->radius/n;
    ix = 0;
    h = 0.0;
    // Loop for calculating each of the n depth/volume points.
    while(ix < n)   // Can also use a for loop
    {
       dataPoints[H_IX][ix] = h;
       term1 = pow(cylPtr->radius,2)*acos((cylPtr->radius-h)/cylPtr->radius);
       term2 = (cylPtr->radius - h)*sqrt(2.0*cylPtr->radius*h - pow(h,2));
       dataPoints[VOL_IX][ix] = (term1 - term2)*cylPtr->length;
       // increment variables for next point
       ix = ix +1;
    }
}
