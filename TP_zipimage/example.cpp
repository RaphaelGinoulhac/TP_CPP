#include <Imagine/Graphics.h>
#include <algorithm>
#include <iostream>
#include "../quadtree/quadtree.h"

using namespace Imagine;
using namespace std;

#ifndef srcPath
#define srcPath(s) ("./" s)
#endif

int main(int argc, char **argv)
{
    // Get image file (defualt is running horse)
    const char *image_file =
	(argc > 1) ? argv[1] : srcPath("running-horse-square.png");
    // Load image
    byte* image;
    int width, height;
    cout << "Loading image: " << image_file << endl; 
    loadGreyImage(image_file, image, width, height);
    // Print statistics
    cout << "Image size: " << width << "x" << height << endl;
    cout << "Number of pixels: " << width*height << endl;
    // Display image
    Window window = openWindow(width, height);
    putGreyImage(IntPoint2(0,0), image, width, height);
    // Pause
    click();

    // Exit
    return 0;
}
