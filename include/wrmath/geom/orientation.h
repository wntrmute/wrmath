//
// Created by kyle on 8/3/19.
//

#ifndef __WRMATH_GEOM_ORIENTATION_H
#define __WRMATH_GEOM_ORIENTATION_H


#include <wrmath/geom/vector.h>


namespace wr {
namespace geom {


float	RadiansToDegreesF(float rads);
double	RadiansToDegreesD(double rads);
float	DegreesToRadiansF(float degrees);
double	DegreesToRadiansD(double degrees);


constexpr uint8_t Basis_i = 0;
constexpr uint8_t Basis_j = 1;
constexpr uint8_t Basis_k = 2;


static const Vector2d Basis2d[] = {
	Vector2d{1, 0},
	Vector2d{0, 1},
};


static const Vector2f Basis2f[] = {
	Vector2f{1, 0},
	Vector2f{0, 1},
};


static const Vector3d Basis3d[] = {
	Vector3d{1, 0, 0},
	Vector3d{0, 1, 0},
	Vector3d{0, 0, 1},
};


static const Vector3f Basis3f[] = {
	Vector3f{1, 0, 0},
	Vector3f{0, 1, 0},
	Vector3f{0, 0, 1},
};



float	Heading2f(Vector2f vec);
double	Heading2d(Vector2d vec);
float	Heading3f(Vector3f vec);
double	Heading3d(Vector3d vec);

} // namespace geom
} // namespace wr


#endif // __WRMATH_ORIENTATION_H
