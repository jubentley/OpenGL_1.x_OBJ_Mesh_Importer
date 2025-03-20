# OpenGL_1.x_OBJ_Mesh_Importer

.obj Mesh Importer for OpenGL 1.x 

uses glut.h

Call as such:<br>
#include "MeshImp.h"<br>
MeshImp *ABot;<br>
ABot = new MeshImp("../MeshData//Dojo");<br>
ABot->Render(105,1,102,0,0,0);<br>
delete ABot;<br>
