#include "MeshImp.h"

void MeshImp::Render(GLfloat X,GLfloat Y,GLfloat Z,GLfloat YAW, GLfloat PITCH, GLfloat ROLL) {
	glFrontFace(GL_CCW);	//PREFER NOT TO BE HERE
//	glPolygonMode(GL_FRONT, GL_FILL);
//	glPolygonMode(GL_BACK, GL_LINE);
//	glEnable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(X,Y,Z);
	glRotatef(YAW, 0, 1, 0);
	if (PITCH != 0) { glRotatef(PITCH, 0, 0, 1); }
	if (ROLL != 0) { glRotatef(ROLL, 1, 0, 0); }
	glBegin(GL_TRIANGLES);
	//REF 4295/6019/8570 4297/5987/8486 4296/5984/8480 VT/TX/NR
	MatChangeMarkerPoint = 0;
	for (int i = 1; i < facepoint; i++) {
		if (MatChangeMarker[MatChangeMarkerPoint] == i) {
			glEnd();
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, 
				&Ka[MatChangeMarkerID[MatChangeMarkerPoint]][0]);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, 
				&Ks[MatChangeMarkerID[MatChangeMarkerPoint]][0]);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, 
				&Kd[MatChangeMarkerID[MatChangeMarkerPoint]][0]);
			glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, ((int)128 * 0.5));

			glBegin(GL_TRIANGLES);
			MatChangeMarkerPoint++;
		}
		glNormal3f(
			normals[face[i][0][2]] [0],
			normals[face[i][0][2]] [1],
			normals[face[i][0][2]] [2]	);
		glVertex3f(
			vertex[face[i][0][0]] [0],
			vertex[face[i][0][0]] [1],
			vertex[face[i][0][0]] [2]);
		glNormal3f(
			normals[face[i][1][2]] [0],
			normals[face[i][1][2]] [1],
			normals[face[i][1][2]] [2]);
		glVertex3f(
			vertex[face[i][1][0]] [0],
			vertex[face[i][1][0]] [1],
			vertex[face[i][1][0]] [2]);
		glNormal3f(
			normals[face[i][2][2]] [0],
			normals[face[i][2][2]] [1],
			normals[face[i][2][2]] [2]);
		glVertex3f(
			vertex[face[i][2][0]] [0],
			vertex[face[i][2][0]] [1],
			vertex[face[i][2][0]] [2]);
	}	
	glEnd();
	glPopMatrix();
}
void MeshImp::PrecalculateElements(FILE *infile, char *line, char *key) {

	int verticesct = 2, normalsct = 2, facesct = 2;
	while (fgets(line, LINELEN, infile) > 0) {
		sscanf(line, "%s", key);
		if (strcmp(key, "v")) { verticesct++; }
		if (strcmp(key, "vn")) { normalsct++; }
		if (strcmp(key, "vn")) { facesct++; } //(key[0] == 'f')
	}
	printf("Vertices = %d, Normals = %d, Faces = %d\n", verticesct, normalsct, facesct);
	fseek(infile, 0, SEEK_SET);	//BREAK HERE FOR VERTS READOUT

	//verticesct = 200000;
	//normalsct = 200000;
	//facesct = 200000;


	//// VLA'S
	//vertex = new GLfloat*[verticesct];
	//for (int i = 0; i < verticesct; i++) {
	//	vertex[i] = new GLfloat[3];
	//}
	//normals = new GLfloat*[normalsct];
	//for (int i = 0; i < normalsct; i++) {
	//	normals[i] = new GLfloat[3];
	//}
	//face = new int**[facesct];
	//for (int x = 0; x < facesct; ++x) {
	//	face[x] = new int*[3];
	//	for (int y = 0; y < 3; ++y) {
	//		face[x][y] = new int[3];
	//	}
	//}
}

void MeshImp::LoadMattData(char* dirmtl) {
	FILE *infile;
	char line[LINELEN], key[KEYLEN], inputmatname[MATNAMELEN];

	infile = fopen(dirmtl, "rb");//READ/BINARY

	while (fgets(line, LINELEN, infile) > 0) {
		sscanf(line, "%s", key);
		if (strcmp(key, "newmtl") == 0) {
			MatPointMtl++;
			sscanf(line, "%s %s", key, inputmatname);
			strcpy(MatIDMtl[MatPointMtl], inputmatname);//STACKS MATERIAL NAMES IN .MTL
		}
		if (strcmp(key, "Kd") == 0) {
			sscanf(line, "%s %f %f %f", key,
				&Kd[MatPointMtl][0],
				&Kd[MatPointMtl][1],
				&Kd[MatPointMtl][2]);
			Kd[MatPointMtl][3] = 1.0;
		}
		if (strcmp(key, "Ka") == 0) {
			sscanf(line, "%s %f %f %f", key,
				&Ka[MatPointMtl][0],
				&Ka[MatPointMtl][1],
				&Ka[MatPointMtl][2]);
			Ka[MatPointMtl][3] = 1.0;
		}
		if (strcmp(key, "Ks") == 0) {
			sscanf(line, "%s %f %f %f", key,
				&Ks[MatPointMtl][0],
				&Ks[MatPointMtl][1],
				&Ks[MatPointMtl][2]);
			Ks[MatPointMtl][3] = 1.0;


		}
	}
	fclose(infile);
}
void MeshImp::LoadMeshData(char* dirobj) {

	FILE *infile;
	char line[LINELEN], key[KEYLEN], inputmatname[MATNAMELEN];
	int vertexpoint = 0, normalpoint = 0;

	infile = fopen(dirobj, "rb");//READ/BINARY

	MeshImp::PrecalculateElements(infile, line, key);

	while (fgets(line, LINELEN, infile) > 0) {
		sscanf(line, "%s", key);
		if (strcmp(key, "usemtl") == 0) {//change material
			sscanf(line, "%s %s", key, inputmatname);
//			strcpy(MatIDObj[MatPointObj], inputmatname);//?
			MatChangeMarker[MatChangeMarkerPoint] = facepoint;
			for (int i = 0; i <= MatPointMtl; i++) {
				if (strcmp(inputmatname, MatIDMtl[i]) == 0) {
					MatChangeMarkerID[MatChangeMarkerPoint] = i;
					break;
				}				
			}
			MatPointObj++;
			MatChangeMarkerPoint++;

		}
		if (strcmp(key, "v") == 0) {//vertex
			vertexpoint++;
			sscanf(line, "%s %f %f %f",
				key, &vertex[vertexpoint][0],
				&vertex[vertexpoint][1], &vertex[vertexpoint][2]);
		}
		if (strcmp(key, "vn") == 0) {//normal
			normalpoint++;
			sscanf(line, "%s %f %f %f",
				key, &normals[normalpoint][0],
				&normals[normalpoint][1], &normals[normalpoint][2]);
		}
		if (strcmp(key, "f") == 0) {//face, triangle, v,vt,vn v,vt,vn v,vt,vn
			for (int i = 0; i < strlen(line); i++) {
				if (line[i] == '/') { line[i] = ' '; }
			}
			sscanf(line, "%s %d %d %d %d %d %d %d %d %d",
				key,
				&face[facepoint][0][0], &face[facepoint][0][1],
				&face[facepoint][0][2], &face[facepoint][1][0],
				&face[facepoint][1][1], &face[facepoint][1][2],
				&face[facepoint][2][0], &face[facepoint][2][1],
				&face[facepoint][2][2]);
			facepoint++;
		}
	}
	fclose(infile);
}
MeshImp::MeshImp(char* dir)
{
	char dirobj[DIRLEN], dirmtl[DIRLEN];
	strcpy(dirobj, dir); strcat(dirobj, ".obj");
	strcpy(dirmtl, dir); strcat(dirmtl, ".mtl");

	MeshImp::LoadMattData(dirmtl);
	MeshImp::LoadMeshData(dirobj);

}
MeshImp::~MeshImp()
{
	// DELETE VLA
//	delete[] vertex, normals, face;
}









//int **arr = new int*[sizeX];
//for (int i = 0; i < sizeX; i++)
//	arr[i] = new int[sizeY];