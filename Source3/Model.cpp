/*
* .obj Model Loader
* By: Mitchell Andrews (Wobbier) / Robert Evola (RelishZombie)
* November 11, 2013
* Loads a .obj file into faces and vertices and then renders the model.
*
#include "Model.h"
int stringPos;
std::string tempString;

Model::Model(const char * filename) {
init(filename);
}
Model::Model(const char * filename, const char * texture) {
init(filename, texture);
}
Model::~Model() {
delete[] vertices;
delete[] faces;
}

void Model::init(const char * filename) {
int tempVerts = 0;
int tempFaces = 0;
int tempNorms = 0;
int tempTexCoords = 0;
std::ifstream fileStream;
fileStream.open(filename);
if (fileStream.is_open()) {
while (std::getline(fileStream, currentString)) {
switch (currentString[1]) {
case 'n':
tempNorms++;
supportsNorms = true;
continue;
case 't':
tempTexCoords++;
supportsTextures = true;
continue;
}
switch (currentString[0]) {
case 'v':
tempVerts++;
std::cout << "Read Vert" << std::endl;
break;
case 'f':
tempFaces++;
std::cout << "Read Face" << std::endl;
break;
}
}
vertices = new Vector3<float>[tempVerts];
faces = new Vector3<int>[tempFaces];
normals = new Vector3<float>[tempNorms];
normPointers = new int[tempFaces];
texturePointers = new Vector3<int>[tempFaces];
textureCoords = new Vector2<float>[tempTexCoords];
tempVerts = 0;
tempFaces = 0;
tempNorms = 0;
tempTexCoords = 0;
fileStream.clear();
fileStream.seekg(0, std::ios::beg);
while (std::getline(fileStream, currentString)) {
switch (currentString[1]) {
case 'n':
addNorm(tempNorms);
tempNorms++;
continue;
case 't':
addTextureCoord(tempTexCoords);
tempTexCoords++;
continue;
}
switch (currentString[0]) {
case 'v':
addPoint(tempVerts);
tempVerts++;
break;
case 'f':
addFace(tempFaces);
tempFaces++;
break;
}
}
fileStream.close();
fileLoaded = true;
vertSize = tempVerts;
faceSize = tempFaces;
//std::cout << texturePointers[0].z;
//std::cout << textureCoords[texturePointers[0].x].x << textureCoords[texturePointers[0].x].y << std::endl;
//std::cout << textureCoords[texturePointers[0].y].x << textureCoords[texturePointers[0].y].y << std::endl;
//std::cout << textureCoords[texturePointers[0].z].x << textureCoords[texturePointers[0].z].y << std::endl;
//std::cout << vertices[faces[0].x].x;
}
}

void Model::init(const char * filename, const char * textureName) {
init(filename);
Image* image = loadBMP(textureName);
texture = loadTexture(image);
delete image;
//texture = LoadTexture(filename, 1024, 1024);
}

void Model::Render() {
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
glPushMatrix();
//std::cout << "render";
glRotatef(-90, 0, 1, 0);
if (fileLoaded) {
for (int i = 0; i < faceSize; ++i) {
glBegin(GL_POLYGON);
if (supportsNorms)
glNormal3f(normals[normPointers[i]].x, normals[normPointers[i]].y, normals[normPointers[i]].z);

if (supportsTextures)
glTexCoord2f(textureCoords[texturePointers[i].x].x, textureCoords[texturePointers[i].x].y);
glVertex3f(vertices[faces[i].x].x, vertices[faces[i].x].y, vertices[faces[i].x].z);

if (supportsTextures)
glTexCoord2f(textureCoords[texturePointers[i].y].x, textureCoords[texturePointers[i].y].y);
glVertex3f(vertices[faces[i].y].x, vertices[faces[i].y].y, vertices[faces[i].y].z);

if (supportsTextures)
glTexCoord2f(textureCoords[texturePointers[i].z].x, textureCoords[texturePointers[i].z].y);
glVertex3f(vertices[faces[i].z].x, vertices[faces[i].z].y, vertices[faces[i].z].z);
glEnd();
}
}
glPopMatrix();
glDisable(GL_TEXTURE_2D);
}

void Model::addPoint(int currentVert) {
for (int i = 2; i >= 0; --i) {
stringPos = currentString.find_last_of(" ");
tempString = currentString.substr(stringPos + 1);
if (i == 0) vertices[currentVert].x = std::stof(tempString.c_str());
if (i == 1) vertices[currentVert].y = std::stof(tempString.c_str());
if (i == 2) vertices[currentVert].z = std::stof(tempString.c_str());
currentString = currentString.erase(stringPos, currentString.length());
}
}

void Model::addFace(int currentFace) {
for (int i = 2; i >= 0; --i) {
if (supportsNorms) {
stringPos = currentString.find_last_of("/");
tempString = currentString.substr(stringPos + 1);
normPointers[currentFace] = std::stoi(tempString.c_str()) - 1;
if (currentString[stringPos - 1] == '/') {
currentString = currentString.erase(stringPos - 1, currentString.length());
}
else {
currentString = currentString.erase(stringPos, currentString.length());
stringPos = currentString.find_last_of("/");
tempString = currentString.substr(stringPos + 1);
if (i == 0)texturePointers[currentFace].x = std::stof(tempString.c_str()) - 1;
if (i == 1)texturePointers[currentFace].y = std::stof(tempString.c_str()) - 1;
if (i == 2)texturePointers[currentFace].z = std::stof(tempString.c_str()) - 1;
currentString = currentString.erase(stringPos, currentString.length());
}
}
stringPos = currentString.find_last_of(" ");
tempString = currentString.substr(stringPos + 1);
if (i == 0) faces[currentFace].x = std::stoi(tempString.c_str()) - 1;
if (i == 1) faces[currentFace].y = std::stoi(tempString.c_str()) - 1;
if (i == 2) faces[currentFace].z = std::stoi(tempString.c_str()) - 1;
currentString = currentString.erase(stringPos, currentString.length());
}
}
void Model::addNorm(int currentIndex) {
for (int i = 2; i >= 0; --i) {
stringPos = currentString.find_last_of(" ");
tempString = currentString.substr(stringPos + 1);
if (i == 0)normals[currentIndex].x = std::stof(tempString.c_str());
if (i == 1)normals[currentIndex].y = std::stof(tempString.c_str());
if (i == 2)normals[currentIndex].z = std::stof(tempString.c_str());
currentString = currentString.erase(stringPos, currentString.length());
}
}
void Model::addTextureCoord(int currentIndex) {
for (int i = 0; i < 2; ++i) {
stringPos = currentString.find_last_of(" ");
tempString = currentString.substr(stringPos + 1);
if (i == 1) textureCoords[currentIndex].x = std::stof(tempString.c_str());
if (i == 0) textureCoords[currentIndex].y = std::stof(tempString.c_str());
currentString = currentString.erase(stringPos, currentString.length());
}
}
unsigned int Model::loadTexture(Image *image) {
GLuint textureId;
glGenTextures(1, &textureId); //Make room for our texture
glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
//Map the image to the texture
glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
0,                            //0 for now
GL_RGB,                       //Format OpenGL uses for image
image->width, image->height,  //Width and height
0,                            //The border of the image
GL_RGB, //GL_RGB, because pixels are stored in RGB format
GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
//as unsigned numbers
image->pixels);               //The actual pixel data
return textureId; //Returns the id of the texture
}*/