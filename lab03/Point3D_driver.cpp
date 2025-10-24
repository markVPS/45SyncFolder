#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Point3D {
  int x;
  int y;
  int z;
};

extern "C" Point3D* Point3D_add(Point3D* p1, Point3D* p2);

int main() {
  srand(time(0));

  // create two Point3Ds with random values
  Point3D a = {rand() % 201 - 100, rand() % 201 - 100, rand() % 201 - 100};
  Point3D b = {rand() % 201 - 100, rand() % 201 - 100, rand() % 201 - 100};

  // add them together
  Point3D* sum = Point3D_add(&a, &b);

  cout << a.x << " " << a.y << " " << a.z << endl;
  cout << b.x << " " << b.y << " " << b.z << endl;
  cout << sum->x << " " << sum->y << " " << sum->z << endl;
  cout << endl;

  // check that they were added correctly
  if (sum->x == a.x + b.x && sum->y == a.y + b.y && sum->z == a.z + b.z) {
    free(sum); // make sure it was made on the heap
    cout << "PASSED: Point3D_add" << endl;
  } else {
    cout << "FAILED: Point3D_add" << endl;
  }

  return 0;
}
