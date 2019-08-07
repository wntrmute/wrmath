#include <cstdlib>
#include <iostream>
#include <string>
#include <wrmath/geom/vector.h>
#include <wrmath/geom/quaternion.h>

using namespace std;
using namespace wr::geom;


int
main(int argc, char **argv)
{
	if (argc != 5) {
		cerr << "Usage: quaternion w x y z" << endl;
		return EXIT_FAILURE;
	}

	double w = stod(string(argv[1]));
	double x = stod(string(argv[2]));
	double y = stod(string(argv[3]));
	double z = stod(string(argv[4]));

	Vector3d	frame {x, y, z};
	Quaterniond	quat = quaternion(frame, w);

	cout << quat << endl;
}