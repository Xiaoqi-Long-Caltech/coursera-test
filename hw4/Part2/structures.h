#ifndef STRUCTURE_H
#define STRUCTURE_H

/* A lot of this file is copied from the demo file, open_demo.cpp. */
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <eigen3/Eigen/Dense>
#define _USE_MATH_DEFINES

using namespace std;
using namespace Eigen;

/* The structures are created the way they are in the demo file */
struct Point_Light
{
    
    float position[4];
    float color[3];
    float attenuation_k;
    Point_Light(float x, float y, float z, float w,
            float r, float g, float b, float k) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
        position[3] = w;
        color[0] = r;
        color[1] = g;
        color[2] = b;
        attenuation_k = k;
    }
    Point_Light() {}
};

/* The following struct is used for representing points and normals in world
 * coordinates.
 *
 * Notice how we are using this struct to represent points, but the struct
 * lacks a w-coordinate. Fortunately, OpenGL will handle all the complications
 * with the homogeneous component for us when we have it process the points.
 * We do not actually need to keep track of the w-coordinates of our points
 * when working in OpenGL.
 */
struct Triple
{
    float x;
    float y;
    float z;
    Triple() {}
    Triple (float x_, float y_, float z_) 
       : x(x_), y(y_), z(z_) {}
    Vector3f GetTriple(){
       Vector3f triple(x, y, z);
       return triple;
    }
    void SetX(float new_x) {
       x = new_x;
    }
    void SetY(float new_y) {
       y = new_y;
    }
    void SetZ(float new_z) {
       z = new_z;
    }
};

/* The following struct is used for storing a set of transformations.
 *
 * Note that we do not need to use matrices this time to represent the
 * transformations. This is because OpenGL will handle all the matrix
 * operations for us when we have it apply the transformations. All we
 * need to do is supply the parameters.
 */
struct Transforms
{
    /* For each array below,
     * Index 0 has the x-component
     * Index 1 has the y-component
     * Index 2 has the z-component
     */
    float translation[3];
    float rotation[3];
    float scaling[3];

    /* Angle in degrees.
     */
    float rotation_angle;
    
    /* When we parse a Transform, with each type of transform, we parse in the other two types of transforms as identities */
    Transforms(string t, float x, float y, float z) {
        if (t.compare("t") == 0) {
           translation[0] = x;
           translation[1] = y;
           translation[2] = z;
           scaling[0] = 1;
           scaling[1] = 1;
           scaling[2] = 1;
           rotation[0] = 0;
           rotation[1] = 0;
           rotation[2] = 0;
           rotation_angle = 0;
        } else if (t.compare("s") == 0) {
           scaling[0] = x;
           scaling[1] = y;
           scaling[2] = z;
           translation[0] = 0;
           translation[1] = 0;
           translation[2] = 0;
           rotation[0] = 0;
           rotation[1] = 0;
           rotation[2] = 0;
           rotation_angle = 0;
        }
    }
    
    /* Rotation transform needs an additional function argument */
    Transforms(string t, float x, float y, float z, float angle) {
        if (t.compare("r") == 0) {
           rotation[0] = x;
           rotation[1] = y;
           rotation[2] = z;
           rotation_angle = angle;
           translation[0] = 0;
           translation[1] = 0;
           translation[2] = 0;
           scaling[0] = 1;
           scaling[1] = 1;
           scaling[2] = 1;
        }
    }
};

struct Object
{
    /* See the note above and the comments in the 'draw_objects' and
     * 'create_cubes' functions for details about these buffer vectors.
     */
    vector<Triple> vertex_buffer;
    vector<Triple> normal_buffer;

    vector<Transforms> transform_sets;

    /* Index 0 has the r-component
     * Index 1 has the g-component
     * Index 2 has the b-component
     */
    float ambient_reflect[3];
    float diffuse_reflect[3];
    float specular_reflect[3];

    float shininess;
    
    /* constructors */
    Object(vector<Triple> v, vector<Triple> n) : vertex_buffer(v),
            normal_buffer(n) {};
    Object() {};
    void SetAmbient(float r, float g, float b) {
        ambient_reflect[0] = r;
        ambient_reflect[1] = g;
        ambient_reflect[2] = b;
    }

    void SetDiffuse(float r, float g, float b) {
        diffuse_reflect[0] = r;
        diffuse_reflect[1] = g;
        diffuse_reflect[2] = b;
    }

    void SetSpecular(float r, float g, float b) {
        specular_reflect[0] = r;
        specular_reflect[1] = g;
        specular_reflect[2] = b;
    }
};

/* Scene struct as in last assignment */
struct Scene {
    Triple position_camera;
    Triple orientation_camera;
    float orientation_angle_cam;
    float near;
    float far;
    float left;
    float right;
    float top;
    float bottom;
    vector<Point_Light> lights;
    vector<Object> objects;
    int xres;
    int yres;
    Scene() {}
};

#endif
