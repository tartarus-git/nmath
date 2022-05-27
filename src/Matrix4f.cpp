#include "../include/nmath/matrices/Matrix4f.h"

#include "../include/nmath/vectors/Vector3f.h"

#include <cmath>

nmath::Matrix4f nmath::Matrix4f::createRotation(float x, float y, float z) noexcept {
	nmath::Matrix4f yzMat = { };

	float cosX = cos(x);
	float sinX = sin(x);

	float cosY = cos(y);
	float sinY = sin(y);

	float cosZ = cos(z);
	float sinZ = sin(z);
	
	yzMat(0, 0) = 1;
	yzMat(1, 1) = cosY;
	yzMat(1, 2) = sinY;
	yzMat(2, 1) = -sinY;
	yzMat(2, 2) = cosY;
	yzMat(3, 3) = 1;

	nmath::Matrix4f xzMat = { };
	xzMat(0, 0) = cosX;
	xzMat(0, 2) = sinX;
	xzMat(2, 0) = -sinX;
	xzMat(2, 2) = cosX;
	xzMat(1, 1) = 1;
	xzMat(3, 3) = 1;

	nmath::Matrix4f xyMat = { };
	xyMat(0, 0) = cosZ;
	xyMat(0, 1) = sinZ;
	xyMat(1, 0) = -sinZ;
	xyMat(1, 1) = cosZ;
	xyMat(2, 2) = 1;
	xyMat(3, 3) = 1;

	return xyMat * xzMat * yzMat;
}

nmath::Matrix4f nmath::Matrix4f::createRotation(nmath::Vector3f rot) noexcept { return createRotation(rot.x, rot.y, rot.z); }
