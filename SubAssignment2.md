### Assignment1-Part2

Elias Marjieh
-------------

Phase 1:
========

![Screenshot of the printed
vertices](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/VerticesPrinting.JPG)
![Screenshot of the printed
faces](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/FacesPrinting.JPG)

Phase 2 explaination:
=====================

First I looked for the minimum value for all three axises and then if
negative turned to positive. After that values were multiplied by the
calculated factor (350/minimum) according to the axis. In order to make
the object visible I calculated the maximum value in each axis and then
multiplied each value with (350/max).

Phase 3:
========

![Cow](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/Cow.JPG)
![Beethoven](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/Beethoven.JPG)

phase 4:
========

![Translate
GUI](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/TranslateGUI.JPG)

![Rotation
GUI](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/RotationsGUI.JPG)

![Scaling
GUI](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/ScaleGUI.JPG)

How the transformations is done: I allocated 6 matrices, 3
transformations and 2 modes (Local, World). Every time a transformation
is executed the matrix is changed according to the methods learnt in the
lecture. and then the matrecies get multiplied: glm::mat4x4 m =
sWorldMatrix \* rWorldMatrix \* tWorldMatrix*sLocalMatrix * rLocalMatrix
\* tLocalMatrix;

Then the vertices get transformed to another list of vertices called
TransformedVertices\_ according to the result of m above.

Phase 5:
========

![Translate in local 175 towards X, 175 towards Y, then Rotation in
world with 50 degree in Y
axis](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/TLRW175-50.JPG)

![Translate in world 175 towards X, 175 towards Y, then Rotation in
local with 50 degree in Y
axis](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/TWRL175-50.JPG)
