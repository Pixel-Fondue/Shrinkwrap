#include "modo_matrix.h"

//http://modo.sdk.thefoundry.co.uk/index.php?title=Vmath_(lxvmath.h)&redirect=no#C2




void mul_point2d_by_matrix(double &x, double &y, double matrix[3][3]){
	// This function multiplies this vector by a matrix, resulting in a new
	// vector.This is useful for applying a transform to a position in 3D
	// space.
	double result_x = x * matrix[0][0] + y * matrix[1][0] + matrix[2][0];
	double result_y = x * matrix[0][1] + y * matrix[1][1] + matrix[2][1];

	x = result_x;
	y = result_y;

}


// Multiply pt by matrix in place.
void  mulPtByMatrix(double pt[3], double matrix[][4]){
	double result[3];
	result[0] = pt[0] * matrix[0][0] + pt[1] * matrix[1][0] + pt[2] * matrix[2][0] + matrix[3][0];
	result[1] = pt[0] * matrix[0][1] + pt[1] * matrix[1][1] + pt[2] * matrix[2][1] + matrix[3][1];
	result[2] = pt[0] * matrix[0][2] + pt[1] * matrix[1][2] + pt[2] * matrix[2][2] + matrix[3][2];
	pt[0] = result[0];
	pt[1] = result[1];
	pt[2] = result[2];
}
/*
void  mulPtByMatrix(float pt[3], LXtMatrix4 matrix){
	float result[3];
	result[0] = pt[0] * matrix[0][0] + pt[1] * matrix[1][0] + pt[2] * matrix[2][0] + matrix[3][0];
	result[1] = pt[0] * matrix[0][1] + pt[1] * matrix[1][1] + pt[2] * matrix[2][1] + matrix[3][1];
	result[2] = pt[0] * matrix[0][2] + pt[1] * matrix[1][2] + pt[2] * matrix[2][2] + matrix[3][2];
	pt[0] = result[0];
	pt[1] = result[1];
	pt[2] = result[2];
}
*/

// Matrix multiplication in place
void  mulPtByMatrix(float pt[3], double matrix[][4]){
	// This function multiplies this vector by a matrix, resulting in a new
	// vector.This is useful for applying a transform to a position in 3D
	// space.
	LXtVector result;
	result[0] = pt[0] * matrix[0][0] + pt[1] * matrix[1][0] + pt[2] * matrix[2][0] + matrix[3][0];
	result[1] = pt[0] * matrix[0][1] + pt[1] * matrix[1][1] + pt[2] * matrix[2][1] + matrix[3][1];
	result[2] = pt[0] * matrix[0][2] + pt[1] * matrix[1][2] + pt[2] * matrix[2][2] + matrix[3][2];
	pt[0] = result[0];
	pt[1] = result[1];
	pt[2] = result[2];
}

// Matrix multiplication in place
void  mulPtByMatrix(LXtVector &pt, LXtMatrix matrix){
	// This function multiplies this vector by a matrix, resulting in a new
	// vector.This is useful for applying a transform to a position in 3D
	// space.
	LXtVector result;
	result[0] = pt[0] * matrix[0][0] + pt[1] * matrix[1][0] + pt[2] * matrix[2][0] + matrix[3][0];
	result[1] = pt[0] * matrix[0][1] + pt[1] * matrix[1][1] + pt[2] * matrix[2][1] + matrix[3][1];
	result[2] = pt[0] * matrix[0][2] + pt[1] * matrix[1][2] + pt[2] * matrix[2][2] + matrix[3][2];
	pt[0] = result[0];
	pt[1] = result[1];
	pt[2] = result[2];
}


// store multiplication in another point
void  mulPtByMatrix(double pt[3], double matrix[][4], double result[3]){
	result[0] = pt[0] * matrix[0][0] + pt[1] * matrix[1][0] + pt[2] * matrix[2][0] + matrix[3][0];
	result[1] = pt[0] * matrix[0][1] + pt[1] * matrix[1][1] + pt[2] * matrix[2][1] + matrix[3][1];
	result[2] = pt[0] * matrix[0][2] + pt[1] * matrix[1][2] + pt[2] * matrix[2][2] + matrix[3][2];
}
void  mulPtByMatrix(LXtFVector pt, LXtMatrix4 matrix, LXtFVector &result){
	result[0] = pt[0] * matrix[0][0] + pt[1] * matrix[1][0] + pt[2] * matrix[2][0] + matrix[3][0];
	result[1] = pt[0] * matrix[0][1] + pt[1] * matrix[1][1] + pt[2] * matrix[2][1] + matrix[3][1];
	result[2] = pt[0] * matrix[0][2] + pt[1] * matrix[1][2] + pt[2] * matrix[2][2] + matrix[3][2];
}



// Copy mb in ma

void  copyDMatrix4(double ma[][4], double mb[][4]){
	mb[0][0] = ma[0][0]; mb[0][1] = ma[0][1]; mb[0][2] = ma[0][2]; mb[0][3] = ma[0][3];
	mb[1][0] = ma[1][0]; mb[1][1] = ma[1][1]; mb[1][2] = ma[1][2]; mb[1][3] = ma[1][3];
	mb[2][0] = ma[2][0]; mb[2][1] = ma[2][1]; mb[2][2] = ma[2][2]; mb[2][3] = ma[2][3];
	mb[3][0] = ma[3][0]; mb[3][1] = ma[3][1]; mb[3][2] = ma[3][2]; mb[3][3] = ma[3][3];
}

void  copyMatrix4(LXtMatrix4 ma, LXtMatrix4 &mb){
	mb[0][0] = ma[0][0]; mb[0][1] = ma[0][1]; mb[0][2] = ma[0][2]; mb[0][3] = ma[0][3];
	mb[1][0] = ma[1][0]; mb[1][1] = ma[1][1]; mb[1][2] = ma[1][2]; mb[1][3] = ma[1][3];
	mb[2][0] = ma[2][0]; mb[2][1] = ma[2][1]; mb[2][2] = ma[2][2]; mb[2][3] = ma[2][3];
	mb[3][0] = ma[3][0]; mb[3][1] = ma[3][1]; mb[3][2] = ma[3][2]; mb[3][3] = ma[3][3];
}

void  copyMatrix4(const LXtMatrix4 ma, LXtMatrix4 &mb){
	mb[0][0] = ma[0][0]; mb[0][1] = ma[0][1]; mb[0][2] = ma[0][2]; mb[0][3] = ma[0][3];
	mb[1][0] = ma[1][0]; mb[1][1] = ma[1][1]; mb[1][2] = ma[1][2]; mb[1][3] = ma[1][3];
	mb[2][0] = ma[2][0]; mb[2][1] = ma[2][1]; mb[2][2] = ma[2][2]; mb[2][3] = ma[2][3];
	mb[3][0] = ma[3][0]; mb[3][1] = ma[3][1]; mb[3][2] = ma[3][2]; mb[3][3] = ma[3][3];
}

void  copyMatrix3_to4(LXtMatrix ma, LXtVector pos, LXtMatrix4 &mb){
	mb[0][0] = ma[0][0]; mb[0][1] = ma[0][1]; mb[0][2] = ma[0][2]; mb[0][3] = 0.0;
	mb[1][0] = ma[1][0]; mb[1][1] = ma[1][1]; mb[1][2] = ma[1][2]; mb[1][3] = 0.0;
	mb[2][0] = ma[2][0]; mb[2][1] = ma[2][1]; mb[2][2] = ma[2][2]; mb[2][3] = 0.0;
	mb[3][0] = pos[0];   mb[3][1] = pos[1];   mb[3][2] = pos[2];   mb[3][3] = 1.0;

}

// Matrix 3X3
bool isIdentity3(LXtMatrix xfrm){
	if (xfrm[0][0] == 1.0 && xfrm[0][1] == 0.0 && xfrm[0][2] == 0.0)
		if (xfrm[1][0] == 0.0 && xfrm[1][1] == 1.0 && xfrm[1][2] == 0.0)
			if (xfrm[2][0] == 0.0 && xfrm[2][1] == 0.0 && xfrm[2][2] == 1.0)
				return true;
	return false;
}

bool isIdentity4(LXtMatrix4 xfrm){
	if (xfrm[0][0] == 1.0 && xfrm[0][1] == 0.0 && xfrm[0][2] == 0.0 && xfrm[0][3] == 0.0)
		if (xfrm[1][0] == 0.0 && xfrm[1][1] == 1.0 && xfrm[1][2] == 0.0 && xfrm[1][3] == 0.0)
			if (xfrm[2][0] == 0.0 && xfrm[2][1] == 0.0 && xfrm[2][2] == 1.0 && xfrm[2][3] == 0.0)
				if (xfrm[3][0] == 0.0 && xfrm[3][1] == 0.0 && xfrm[3][2] == 0.0 && xfrm[3][3] == 1.0)
					return true;
	return false;
}






// Il prodotto tra matrici si puo' fare solamente quando 
// il numero di colonne della prima matrice e' uguale al numero di righe della seconda
// Per questo motivo e' sempre possibile ad esempio moltiplicare una matrice per la sua trasposta
// Se la prima matrice e' n*m e la seconda e' n1*m1, la matrice risultante avra' n righe e m1 colonne
void product4(LXtMatrix4 a, LXtMatrix4 b, LXtMatrix4 &res) {
	double sum = 0;
	for (unsigned int i = 0; i < 4; i++){
		for (unsigned int j = 0; j < 4; j++){
			for (unsigned int k = 0; k < 4; k++){
				sum += a[i][k] * b[k][j];
			}
			res[i][j] = sum;
			sum = 0;
		}
	}
}




void transpose4(LXtMatrix4 a, LXtMatrix4 &res) {
	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			res[i][j] = a[j][i];
}



// Determinant and Inverse methods are ported from this C code :
// http ://www.ccodechamp.com/c-program-to-find-inverse-of-matrix/
// This function is recursive and private, as it is called by det determinant,
// which properly initializes this method with the proper input matrix.
// k is the number of columns of the matrix (?)
float determinant(LXtMatrix4 a, float k)
{
	float s = 1, det = 0;
	LXtMatrix4 b;
	int i, j, m, n, c;
	if (k == 1)
	{
		return (a[0][0]);
	}
	else
	{
		det = 0;
		for (c = 0; c<k; c++)
		{
			m = 0;
			n = 0;
			for (i = 0; i<k; i++)
			{
				for (j = 0; j<k; j++)
				{
					b[i][j] = 0;
					if (i != 0 && j != c)
					{
						b[m][n] = a[i][j];
						if (n<(k - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}
			det = det + s * (a[0][c] * determinant(b, k - 1));
			s = -1 * s;
		}
	}

	return (det);
}



// La matrice dei cofattori puo' essere trova solo per matrici quadrate    
void cofactor4(LXtMatrix4 a, LXtMatrix4 &fac) {
	// The matrix of cofactor can be found for square matrices only
	int f = 4;
	LXtMatrix4 b;

	int p, q, m, n, i, j;
	for (q = 0; q < 4; q++) {
		for (p = 0; p < 4; p++) {
			m = 0;
			n = 0;
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					if (i != q && j != p) {
						b[m][n] = a[i][j];
						if (n < (f - 2))
							n += 1;
						else {
							n = 0;
							m += 1;
						}
					}
				}
			}
			fac[q][p] = pow(-1.0, q + p) * determinant(b, f - 1);
		}
	}
}


bool inverse(LXtMatrix4 ma, LXtMatrix4 &mb) {
	// First of all, the matrix must be square to be able to be inverted
	// The inverse of a matrix, is its transpose diveded by its determinnt
	// For this reason, determinant != 0, or the matrix cannot be inverted.
	//
	// transpose(A) / determinant(a)     where determinant(A) != 0

	double	det = determinant(ma, 4);
	if (det != 0) {
		double one_divide_det = 1.0 / det;

		// I need to find
		// The matrix of minor
		// The matrix of cofactors from the matrix of minor
		// The transpose matrix of the matrix of cofactor
		// Then divide the transposed matrix by the determinant
		LXtMatrix4 fac;
		cofactor4(ma, fac);

		transpose4(fac, mb);
		for (unsigned int i = 0; i < 4; i++){
			for (unsigned int j = 0; j < 4; j++){
				mb[i][j] = mb[i][j] * one_divide_det;
			}
		}
		return true;
	}
	return false;
}






void rotation_matrix3(double angle, double rot_mat[3][3]) {

	rot_mat[0][0] = cos(angle);
	rot_mat[0][1] = -sin(angle);
	rot_mat[0][2] = 0.0;

	rot_mat[1][0] = sin(angle);
	rot_mat[1][1] = cos(angle);
	rot_mat[1][2] = 0.0;

	rot_mat[2][0] = 0.0;
	rot_mat[2][1] = 0.0;
	rot_mat[2][2] = 1.0;
}

void scale_matrix3(double scaleX, double scaleY, double scale_mat[3][3]) {

	scale_mat[0][0] = scaleX;
	scale_mat[0][1] = 0.0;
	scale_mat[0][2] = 0.0;

	scale_mat[1][0] = 0.0;
	scale_mat[1][1] = scaleY;
	scale_mat[1][2] = 0.0;

	scale_mat[2][0] = 0.0;
	scale_mat[2][1] = 0.0;
	scale_mat[2][2] = 1.0;
}

void cross3(double ma[3][3], double mb[3][3], double result[3][3]) {
	double  matrixTmp[3][3];

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			matrixTmp[i][j] = 0.0;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 3; k++){
				matrixTmp[i][j] += ma[i][k] * mb[k][j];
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++){
			result[i][j] = matrixTmp[i][j];
		}
	}

}
void set_matrix_translation3(double x, double y, double matrix[3][3]){
	matrix[2][0] = x;
	matrix[2][1] = y;
}

void makeIdentity3(double ma[3][3]){
	ma[0][0] = 1.0; ma[0][1] = 0.0; ma[0][2] = 0.0;
	ma[1][0] = 0.0; ma[1][1] = 1.0; ma[1][2] = 0.0;
	ma[2][0] = 0.0; ma[2][1] = 0.0; ma[2][2] = 1.0;
}


/*
void _rotationMatrixY4(double angle, double rot_matrix[][4]){
	
	//double rmat[4][4] = { { cos(angle), 0.0, sin(angle), 0.0 },
	//{ 0.0, 1.0, 0.0, 0.0 },
	//{ sin(angle), 0.0, cos(angle), 0.0 },
	//{0.0, 0.0, 0.0, 1.0 }};
	
	rot_matrix[0][0] = cos(angle);
	rot_matrix[0][1] = 0.0;
	rot_matrix[0][2] = -sin(angle);
	rot_matrix[0][3] = 0.0;

	rot_matrix[1][0] = 0.0;
	rot_matrix[1][1] = 1.0;
	rot_matrix[1][2] = 0.0;
	rot_matrix[1][3] = 0.0;

	rot_matrix[2][0] = sin(angle);
	rot_matrix[2][1] = 0.0;
	rot_matrix[2][2] = cos(angle);
	rot_matrix[2][3] = 0.0;

	rot_matrix[3][0] = 0.0;
	rot_matrix[3][1] = 0.0;
	rot_matrix[3][2] = 0.0;
	rot_matrix[3][3] = 1.0;
}
*/

//This can be used with double[4][4] as well.
void rotationMatrixY4(double angle, LXtMatrix4 &rot_matrix){

	rot_matrix[0][0] = cos(angle);
	rot_matrix[0][1] = 0.0;
	rot_matrix[0][2] = -sin(angle);
	rot_matrix[0][3] = 0.0;

	rot_matrix[1][0] = 0.0;
	rot_matrix[1][1] = 1.0;
	rot_matrix[1][2] = 0.0;
	rot_matrix[1][3] = 0.0;

	rot_matrix[2][0] = sin(angle);
	rot_matrix[2][1] = 0.0;
	rot_matrix[2][2] = cos(angle);
	rot_matrix[2][3] = 0.0;

	rot_matrix[3][0] = 0.0;
	rot_matrix[3][1] = 0.0;
	rot_matrix[3][2] = 0.0;
	rot_matrix[3][3] = 1.0;
}

void rotationMatrixX4(double angle, LXtMatrix4 &rot_matrix){

	rot_matrix[0][0] = 1.0;
	rot_matrix[0][1] = 0.0;
	rot_matrix[0][2] = 0.0;
	rot_matrix[0][3] = 0.0;

	rot_matrix[1][0] = 0.0;
	rot_matrix[1][1] = cos(angle);
	rot_matrix[1][2] = sin(angle);
	rot_matrix[1][3] = 0.0;

	rot_matrix[2][0] = 0.0;
	rot_matrix[2][1] = -sin(angle);
	rot_matrix[2][2] = cos(angle);
	rot_matrix[2][3] = 0.0;

	rot_matrix[3][0] = 0.0;
	rot_matrix[3][1] = 0.0;
	rot_matrix[3][2] = 0.0;
	rot_matrix[3][3] = 1.0;
}


void cross4(double ma[4][4], double mb[4][4], double result[4][4]) {
	double  matrixTmp[4][4];

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			matrixTmp[i][j] = 0.0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 4; k++){
				matrixTmp[i][j] += ma[i][k] * mb[k][j];
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++){
			result[i][j] = matrixTmp[i][j];
		}
	}

}


void makeIdentity4(double ma[4][4]){
	ma[0][0] = 1.0; ma[0][1] = 0.0; ma[0][2] = 0.0; ma[0][3] = 0.0;
	ma[1][0] = 0.0; ma[1][1] = 1.0; ma[1][2] = 0.0; ma[1][3] = 0.0;
	ma[2][0] = 0.0; ma[2][1] = 0.0; ma[2][2] = 1.0; ma[2][3] = 0.0;
	ma[3][0] = 0.0; ma[3][1] = 0.0; ma[3][2] = 0.0; ma[3][3] = 1.0;
}


void get_scale_from_matrix4(double xfrm[4][4], double scale[3]){

	// scale X
	if (xfrm[0][0] != 0.0 || xfrm[0][1] != 0.0 || xfrm[0][2] != 0.0){
		scale[0] = sqrt((xfrm[0][0] * xfrm[0][0]) + (xfrm[0][1] * xfrm[0][1]) + (xfrm[0][2] * xfrm[0][2]));
	}
	else {
		scale[0] = 0.0;
	}
	// scale Y
	if (xfrm[1][0] != 0.0 || xfrm[1][1] != 0.0 || xfrm[1][2] != 0.0){
		scale[1] = sqrt((xfrm[1][0] * xfrm[1][0]) + (xfrm[1][1] * xfrm[1][1]) + (xfrm[1][2] * xfrm[1][2]));
	}
	else {
		scale[1] = 0.0;
	}
	// scale Z
	if (xfrm[2][0] != 0.0 || xfrm[2][1] != 0.0 || xfrm[2][2] != 0.0){
		scale[2] = sqrt((xfrm[2][0] * xfrm[2][0]) + (xfrm[2][1] * xfrm[2][1]) + (xfrm[2][2] * xfrm[2][2]));
	}
	else {
		scale[2] = 0.0;
	}
}

// Decompose Matrix to find scale matrix only
void get_scale_matrix4(double xfrm[4][4], double result[4][4]){
	double sc[3];
	get_scale_from_matrix4(xfrm, sc);

	result[0][0] = sc[0];
	result[0][1] = 0.0;
	result[0][2] = 0.0;
	result[0][3] = 0.0;

	result[1][0] = 0.0;
	result[1][1] = sc[1];
	result[1][2] = 0.0;
	result[1][3] = 0.0;

	result[2][0] = 0.0;
	result[2][1] = 0.0;
	result[2][2] = sc[2];
	result[2][3] = 0.0;

	result[3][0] = 0.0;
	result[3][1] = 0.0;
	result[3][2] = 0.0;
	result[3][3] = 1.0;
}

void get_rotation_matrix4(double xfrm[4][4], double result[4][4]){
	double sc[3];
	get_scale_from_matrix4(xfrm, sc);

	double factorX = 0.0;
	double factorY = 0.0;
	double factorZ = 0.0;

	if (sc[0] != 0.0)
		factorX = 1.0 / sc[0];

	if (sc[1] != 0.0)
		factorY = 1.0 / sc[1];

	if (sc[2] != 0.0)
		factorZ = 1.0 / sc[2];

	result[0][0] = xfrm[0][0] * factorX;
	result[0][1] = xfrm[0][1] * factorX;
	result[0][2] = xfrm[0][2] * factorX;
	result[0][3] = 0.0;

	result[1][0] = xfrm[1][0] * factorY;
	result[1][1] = xfrm[1][1] * factorY;
	result[1][2] = xfrm[1][2] * factorY;
	result[1][3] = 0.0;

	result[2][0] = xfrm[2][0] * factorZ;
	result[2][1] = xfrm[2][1] * factorZ;
	result[2][2] = xfrm[2][2] * factorZ;
	result[2][3] = 0.0;

	result[3][0] = 0.0;
	result[3][1] = 0.0;
	result[3][2] = 0.0;
	result[3][3] = 1.0;
}