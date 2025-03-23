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

See it running [here](https://www.youtube.com/watch?v=zwNiKpuN-D0&list=PLoexzHtl62yWyu0h-OItQpDZCHwT4CqGm&index=12)
