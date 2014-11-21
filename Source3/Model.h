/*
 * .obj Model Loader
 * By: Mitchell Andrews (Wobbier) / Robert Evola (RelishZombie)
 * November 11, 2013
 * Loads a .obj file into faces and vertices and then renders the model.
 *
 #pragma once

 #include "imageloader.h"
 #include <iostream>
 #include <list>
 #include <string>
 #include <fstream>
 #include <tchar.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <Windows.h>
 #include <gl/gl.h>
 #include <gl/glu.h>
 template <typename V3T>
 struct Vector3 {
 V3T x;
 V3T y;
 V3T z;
 Vector3() {}
 Vector3(V3T X, V3T Y, V3T Z) {
 x = X;
 y = Y;
 z = Z;
 }
 Vector3 operator+(Vector3<V3T> v) {
 return Vector3(x + v.x, y + v.y, z + v.z);
 }
 Vector3 operator-(Vector3<V3T> v) {
 return Vector3(x - v.x, y - v.y, z - v.z);
 }
 /*V3T operator[] (int index) const
 {
 switch (index)
 {
 case 0:
 return x;
 case 1:
 return y;
 case 2:
 return z;
 }
 }
 V3T& operator[] (int index)
 {
 switch (index)
 {
 case 0:
 return x;
 case 1:
 return y;
 case 2:
 return z;
 }
 }*
 };
 template <typename V2T>
 struct Vector2 {
 V2T x;
 V2T y;
 Vector2() {}
 Vector2(V2T X, V2T Y) {
 x = X;
 y = Y;
 }
 Vector2 operator+(Vector2<V2T> v) {
 return Vector2(x + v.x, y + v.y);
 }
 Vector2 operator-(Vector2<V2T> v) {
 return Vector2(x - v.x, y - v.y);
 }
 };
 class Image;
 class Model {
 public:
 Model(const char * filename);
 Model(const char * filename, const char * texture);
 ~Model();
 void Render();
 private:
 void init(const char * filename);
 void init(const char * filename, const char * texture);
 unsigned int loadTexture(Image* image);
 Vector3<float>* vertices;
 Vector3<int>* faces;
 Vector3<float>* normals;
 Vector3<int>* texturePointers;
 Vector2<float>* textureCoords;
 int* normPointers;
 int vertSize, faceSize;
 std::string currentString;
 void addPoint(int currentPoint);
 void addFace(int currentFace);
 void addNorm(int currentNorm);
 void addTextureCoord(int currentNorm);
 bool fileLoaded = false;
 bool supportsNorms = false;
 bool supportsTextures = false;
 unsigned int texture;
 };
 */