#include <cstdlib>
#include <iostream>
#include <string>
#include <wrmath/math.h>
#include <wrmath/geom/quaternion.h>

using namespace std;
using namespace wr;


static void
usage(ostream& outs)
{
	outs << "Print conversions between Euler angles and quaternions." << endl;
	outs << "Usage: euler2quat yaw pitch roll" << endl;
	outs << "       euler2quat x y z w" << endl;
}


static void
convertEulerToQuat(char **argv)
{
	double		yaw = math::DegreesToRadiansD(stod(string(argv[0])));
	double		pitch = math::DegreesToRadiansD(stod(string(argv[1])));
	double		roll = math::DegreesToRadiansD(stod(string(argv[2])));

	geom::Vector3d	euler {yaw, pitch, roll};
	auto		quaternion = geom::quaterniond_from_euler(euler);

	cout << "Quaternion: " << quaternion.asVector() << endl;
}


static void
convertQuatToEuler(char **argv)
{
	double	x = stod(string(argv[0]));
	double	y = stod(string(argv[1]));
	double	z = stod(string(argv[1]));
	double	w = stod(string(argv[1]));

	geom::Quaterniond	quaternion {x, y, z, w};
	auto			euler = quaternion.euler() * (180.0 / M_PI);

	cout << "Euler ZYX: " << euler << endl;
}


int
main(int argc, char **argv)
{
	if ((argc != 4) && (argc != 5)) {
		usage(cerr);
		return EXIT_FAILURE;
	}

	argv++;
	if (argc == 4) {
		convertEulerToQuat(argv);
	}
	else {
		convertQuatToEuler(argv);
	}
}