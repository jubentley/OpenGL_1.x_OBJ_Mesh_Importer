/*############################################################################
##																			##
##	MeshImp																	##
##																			##
##	Imports and Renders .obj and .mtl Mesh Files							##
##																			##
##	Author:		Justin Bentley												##
##	Date:		2018 >> 2019			              ###### ######  ###### ##
##	Version:	1.1 (Mat Support)		            ###     ##  ##  ##  ##  ##
##	GLfloat variables using "glut.h"	           ##      ######  ######   ##
##										        #   ##### ##      ##        ##
#############################################################################*/

//In Maya; 
//Prefferable to Combine
//Only Triangles, so Triangulate
//RGB Color 0-1

#ifndef MeshImp_def 
#define MeshImp_def 
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include "glut.h"
//#include "OPGLDraw.h"

#define LINELEN 100 //LINE OF FILE MAX LEN
#define MATNAMELEN 50	//SIZE OF MATERIAL NAME
#define MAXMATS 100		//AMOUNT OF DIFFERENT MATERIALS
#define DIRLEN 50	//DIRECTORY NAME LENGTH
#define KEYLEN 80 //vt vx usemtl etc
#define MATCHANGES 1000 //AMOUNT OF TIMES MATERIALS CHANGE

//VLA ALTERNATIVE
//MAX VALUES
#define VERTEX 2000000	//MUST BE DONE MANUALLY (SORRY)
#define NORMALS 2000000	//MAKE SURE U PLUS 1 AS TXT ARRAY START AT 1
#define FACES 2000000

class MeshImp
{
public:
	void MeshImp::Render(GLfloat X, GLfloat Y, GLfloat Z, GLfloat YAW, GLfloat PITCH, GLfloat ROLL);	
	MeshImp::MeshImp(char* dir);
	~MeshImp();
protected:
private:
	void MeshImp::LoadMeshData(char* dirobj);
	void MeshImp::LoadMattData(char* dirmtl);
	//.TXT READER/SORTER/ARRAY ELEMENT ALLOCATOR
	void MeshImp::PrecalculateElements(FILE *infile, char *line, char *var);

	int facepoint = 1;	//.OBJ ARRAYS START FROM ONE
	char MatIDObj[MAXMATS][MATNAMELEN];	//
	char MatIDMtl[MATCHANGES][MATNAMELEN];	//
	int MatChangeMarker[MATCHANGES];	//FACE NUM TO CHANGE MAT
	int MatChangeMarkerID[MATCHANGES];	//Kd Ka Ks TO USE
	int MatChangeMarkerPoint = 0;	//INCREMENTER
	int MatPointObj = 0;
	int MatPointMtl = -1;//BEING A PRE-INCREMENTER
	GLfloat Kd[MAXMATS][4];	//DIFFUSE
	GLfloat Ka[MAXMATS][4];	//AMBIENT
	GLfloat Ks[MAXMATS][4];	//SPECULAR
	GLint Ns[MAXMATS];		//SPECULAR EXPONENT		//TYPE BLINN NOT PRESENT

	//VLA'S
	//GLfloat **vertex;
	//GLfloat **normals;
	//int ***face;

	//	VLA ALTERNATIVE
	GLfloat vertex[VERTEX][3];
	GLfloat normals[NORMALS][3];
	int face[FACES][3][3];
};
#endif
