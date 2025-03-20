# OpenGL_1.x_OBJ_Mesh_Importer

.obj Mesh Importer for OpenGL 1.x 

uses glut.h

Call as such:
#include "MeshImp.h"
MeshImp *ABot;
ABot = new MeshImp("../MeshData//Dojo");
ABot->Render(105,1,102,0,0,0);
delete ABot;
