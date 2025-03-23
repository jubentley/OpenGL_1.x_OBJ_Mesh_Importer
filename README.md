# OpenGL 1.x .OBJ Mesh Importer

.obj Mesh Importer for OpenGL 1.x 

Reads in a .obj and .mtl file and renders it in OpenGL 1.x using glut.h

uses glut.h

Call as such:<br>
#include "MeshImp.h"<br>
MeshImp *ABot;<br>
ABot = new MeshImp("../MeshData//Dojo");<br>
ABot->Render(105,1,102,0,0,0);<br>
delete ABot;<br>
