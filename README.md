# Basic-Ray-Tracing
Basic Ray Tracing program for 3 spheres using the Blinn-Phong shading model

This project uses a total of six (6) classes to perform a simple, yet complete in 
theory, scene raytracing.

## Breakdown of these classes used to perform ray tracing

These are all the classes that were used to perform ray tracing for this project (header and
implementation files):

1. Camera
2. Color
3. Vectormath
4. Ray
5. Shape
6. Image

## End Result - Output

By using this program, you should be able to obtain a ray traced image like this:

![alt text](https://github.com/konoha71/Basic-Ray-Tracing/blob/master/Screenshot_raytracing.png)

## Details about the classes used in this project (credits to Hillsoft)

The Camera class would take care of defining a camera object as a Perspective Camera.  Additional
information is added to this camera object such as it's origin and up vector. See class for details.

The Color class is just a shorthand (convenient) class to deal with color math operations such as 
color addition as well as color multiplication (either by a K factor or by another color).  It also
provides some extra functionalities to deal with color value clamping (when a pixel value exceeds
255 for instance).

The Vectormath class was designed to represent vectors as objects and also provide several methods 
to do math with these.  An example of this, that is used quite often throughout the ray tracing
application is the method "dot" which performs a dot product between two vectors.  Yet another one
is "Normalize" which is used very often to normalize a vector.

The Ray class is one of the most important classes that contribute to this project as it pretty much
represents a Ray object *and* also includes some methods to compute ray intersections.  As we know
for this project, for each pixel a ray will be traced and then be computed for intersections.  This
class, also, interacts very closely with the Shape class briefly discussed next.

The Shape class is also one important class that contributes directly to this project as it defines
some default figures (shapes).  The shapes that are supported for this project are just spheres 
although planes (2d planes) are supported they are not being used as extensively as spheres.

Last but not least, the Image class is the last class tha contributes to this project.  The purpose
of this class is just to store the ray traced data into an image object so that it can be used to 
display the ray traced scene by OpenGL DrawPixel function.

## End notes

Finally, the Blinn-Phong model was used to perform the ray tracing of the scene.  This means that
the project code allows the 3 default spheres to have specular texture (coloring).  Shadows were 
implemented as part of the ray tracing application but the color is used as shadow is just the 
ambient color.

## Credits
Many thanks and credits to [Hillsoft](https://github.com/Hillsoft) for making such a [good tutorial for Ray Tracing](https://youtu.be/RIgc5J_ZGu8).  All the classes that were previously mentioned were cloned from his Ray Tracing project.
Visit his GitHub profile for more details!
