#include <lxvmath.h>

//http://modo.sdk.thefoundry.co.uk/index.php?title=Vmath_(lxvmath.h)&redirect=no#C2

// in place multiplications
void  mul_point2d_by_matrix(double &x, double &y, double matrix[3][3]);
void  mulPtByMatrix(double pt[3], double matrix[][4]);
void  mulPtByMatrix(float pt[3], double matrix[][4]);
void  mulPtByMatrix(LXtVector &pt, LXtMatrix4 matrix[][4]);

// store multiplication in another point
void  mulPtByMatrix(double pt[3], double matrix[][4], double result[3]);
void  mulPtByMatrix(LXtFVector pt, LXtMatrix4 matrix, LXtFVector &result);

void  copyDMatrix4(double ma[][4], double mb[][4]);
void  copyMatrix4(LXtMatrix4 ma, LXtMatrix4 &mb);
void  copyMatrix4(const LXtMatrix4 ma, LXtMatrix4 &mb);
void  copyMatrix3_to4(LXtMatrix ma, LXtVector pos, LXtMatrix4 &mb);

bool isIdentity3(LXtMatrix xfrm);
bool isIdentity4(LXtMatrix4 xfrm);

void transpose4(LXtMatrix4 a, LXtMatrix4 &res);

void product4(LXtMatrix4 a, LXtMatrix4 b, LXtMatrix4 &res);

// Determinant and Inverse methods are ported from this C code :
// http ://www.ccodechamp.com/c-program-to-find-inverse-of-matrix/
// This function is recursive and private, as it is called by det determinant,
// which properly initializes this method with the proper input matrix.
// k is the number of columns of the matrix (?)
float determinant(LXtMatrix4 a, float k = 4);

// La matrice dei cofattori puo' essere trova solo per matrici quadrate    
void cofactor4(LXtMatrix4 a, LXtMatrix4 &fac);

bool inverse(LXtMatrix4 ma, LXtMatrix4 &mb);

void rotation_matrix3(double angle, double rot_mat[3][3]);
void scale_matrix3(double scaleX, double scaleY, double scale_mat[3][3]);
void cross3(double ma[3][3], double mb[3][3], double result[3][3]);
void set_matrix_translation3(double x, double y, double matrix[3][3]);
void get_scale_from_matrix4(double xfrm[4][4], double scale[3]);
void get_scale_matrix4(double xfrm[4][4], double result[4][4]);
void get_rotation_matrix4(double xfrm[4][4], double result[4][4]);

//void rotationMatrixY4(double angle, double rot_matrix[][4]);
void rotationMatrixY4(double angle, LXtMatrix4 &rot_matrix);
void rotationMatrixX4(double angle, LXtMatrix4 &rot_matrix);


void cross4(double ma[4][4], double mb[4][4], double result[4][4]);

void makeIdentity3(double ma[3][3]);
void makeIdentity4(double ma[4][4]);
