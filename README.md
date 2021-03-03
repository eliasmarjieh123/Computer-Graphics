# Computer Graphics 203.3710
## Students Team data

Name: 'Elias Marjieh'  




### Lecturer
*Roi Poranne*

[roiporanne@cs.haifa.ac.il](mailto:roiporanne@cs.haifa.ac.il)

URL: [https://www.inf.ethz.ch/personal/poranner/](https://www.inf.ethz.ch/personal/poranner/)



## Course Description

This course provides an introduction to the foundations of Computer Graphics. We will cover the basic mathematical concepts, such as 2D and 3D transformations, shading models, and rendering techniques. The ultimate goal of this course is to develop a basic model viewer.

Students will experiment with modern graphics programming and build a renderer using C++ and OpenGL.

By the end of the course, you will be able to:

* Explain and apply the fundamental mathematical concepts used in rendering.
* Implement a basic graphics pipeline based on rasterization.
* Develop simple graphics programs in C++ using OpenGL and GLSL.

*Textbook*:
Interactive Computer Graphics: A Top-Down Approach with Shader-Based OpenGL ,6th Edition

# Assignment 1:

Computer Graphics 203.3710 Assignment #1
Wireframe Viewer
Introduction
In this assignment you will develop the first stage of a modeling software. Your program will
render models in wire-frame (edges only). The emphasis in this assignment is the correct
application of transformations and the design of a GUI.
The Skeleton
You are given a code skeleton for your program. Please view the skeleton mainly as a suggestion.
It is a good starting point, but you are allowed and even should change its structure. The
skeleton includes a cmake script that builds a visual studio solution and consists of five projects:
• MeshViewer: This is the main part of the code and where you will implement your
program. The project relies on ImGui to create a user interface.
• ImGui: An easy to use GUI creation library.
• nfd: Small library for a cross platform file opening dialog.
• glfw: Handles events and window creation (in multiple operating systems).
• glad: Handles the openGL interface.
General Requirements
Some of the requirements below involve developing some user interactions. Design it in a way
that you find reasonable, using the mouse and menu, or just the keyboard. More detail appears
below.
Note: Some of the requirements are not specific, and this is done on purpose. It is encouraged
that you to make your own decisions on how to design the code and the interface. In many
cases, there is no right or wrong. If you have two ways in which you can implement something
and you can’t decide, go with the simpler approach first. If you have time, implement the other
approach as well.
In this assignment, the following features should be implemented:
• Renderer:
1. Render models as wireframe (only the edges of the triangles should be drawn).
2. Render the normals of the models (see point 8 and fig. 1). Normals should be
drawn as line segments, where one end point is at the triangle barycenter (in case
of triangle normal) or on the vertex that the normal is associated with (in case of
vertex normal), and the other endpoint is located some distance away from the other
end point, in the normal direction.
1
Figure 1: Wireframe rendering with normals per face and per vertex (blue lines) and bounding
box (in green)
3. Render the bounding box of each model (point 10).
4. For pairs only: Use camera.obj file to render cameras.
• Model:
5. Load an OBJ file.
6. Store the transformations of the model in both local and world frames. The transformation from local to world frame should be
T “ TwTm
where Tm and Tw are the local and world transformation respectively.
7. Implement methods for updating the transformations of the model in both the model
and world frames.
8. Compute the normal per triangle, using the cross product of two edge vectors and
store them.
9. If the OBJ file contains normal-per-vertex data, store them as well.
10. Compute the bounding box of the model in model frame. Each face of the box
should correspond to a the mix/min values of each coordinate x,y,z, over all of the
vertices.
11. Ensure that the normals and the bounding box are correctly transformed with the
model.
• Camera:
12. Store the transformations of the camera in both local and world frames. The transformation from local to world frame should be
C “ CwCm
where Cm and Cw are the local and world transformation respectively.
13. Implement methods for updating the transformations of the camera in both the
model and world frames.
14. Implement methods for updating the projection (perspective, orthographic) and its
parameters (z near,z far, aspect ratio, etc)
15. Implement a method for specifying the camera transformation using LookAt.
• Scene:
16. For pairs only: Allow several models and cameras simultaneously in the scene.
17. For pairs only: Allow the user to select the active model or camera. The active
model or camera will be the ones controlled and transformed by the user.
2
18. For pairs only: Allow the user to select the current camera. The renderer will render
the scene using the current camera transformation and projection. The current
camera can be the same as the active camera.
19. Allow the user to rotate the active camera to look at the on the active model (use
LookAt).
20. Allow the user to control the camera’s zoom.
21. Bonus: Allow the user to control the active camera as an ’orbit camera’, by dragging
the mouse while holding one of its buttons down. Orbit camera is the ability to move
the camera around the surface of an imaginary sphere. Here is an example.
22. Bonus: Implement a dolly effect feature.
• User Interface:
23. Allow the user to move, scale, and rotate objects using ImGui sliders using.
24. Allow the user to move, and rotate cameras using ImGui sliders.
25. For pairs only: Allow control of transformations using the mouse.
26. Allow the user to set the step size of incremental transformation.
27. When the user resizes the window, re-render the scene correctly, while maintaining
aspect ratio.
28. In general, the UI should be easy to use, and you should be able to set the position
of models and cameras quickly.




# Assigment1-part1

## Image of the Bresenham's Algorithim test:
![](https://github.com/eliasmarjieh123/Computer-Graphics/blob/feedback/linesCreatingCircle.JPG)
## Image of 16 circles in each other:
![](https://github.com/eliasmarjieh123/Computer-Graphics/blob/feedback/16circles.JPG)

### Assignment1-Part2

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
Translate in local 175 towards X, 175 towards Y, then Rotation in world with 50 degree in Y axis:
![Translate in local 175 towards X, 175 towards Y, then Rotation in
world with 50 degree in Y
axis](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/TLRW175-50.JPG)

Translate in world 175 towards X, 175 towards Y, then Rotation in local with 50 degree in Y axis:
![Translate in world 175 towards X, 175 towards Y, then Rotation in
local with 50 degree in Y
axis](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SubAssignment2-Images/TWRL175-50.JPG)

### Assignment1-Part3

# Phase 1:
==========

Transformation on the cow: Scale 0.8 - translate By X 700 - rotate By Y
45
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase1/Scale0.8-translateByX700-rotateByY45.JPG)

Transformation on the cow: Scale 0.8 - translate By X 700 - rotate By Y
90
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase1/Scale0.8-translateByX700-rotateByY90.JPG)

Transformation on the cow: Scale 0.8 - translate By X 700 - rotate By Y
135
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase1/Scale0.8-translateByX700-rotateByY135.JPG)

Transformation on the cow: Scale 0.8 - translate By X 700 - rotate By Y
180
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase1/Scale0.8-translateByX700-rotateByY180.JPG)

Transformation on the cow: Scale 0.8 - translate By X 700 - rotate By Y
225
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase1/Scale0.8-translateByX700-rotateByY225.JPG)

Transformation on the cow: Scale 0.8 - translate By X 700 - rotate By Y
270
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase1/Scale0.8-translateByX700-rotateByY270.JPG)

Transformation on the cow: Scale 0.8 - translate By X 700 - rotate By Y
315
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase1/Scale0.8-translateByX700-rotateByY315.JPG)

Transformation on the cow: Scale 0.8 - translate By X 700 - rotate By Y
360
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase1/Scale0.8-translateByX700-rotateByY360.JPG)

# Phase 2:
==========

T1=Scale 0.8 Translate By X 600 By Y 80 Rotate by X 30 Rotate By Y 60

T2=Scale 0.7 Translate By X 300 By Y 90 Rotate By Z 45 Rotate By X 45

T1 in Local T2 in World:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase2/T1LT2W.JPG)

T1 in World T2 in Local:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase2/T1WT2LWithNoExtra.JPG)

T1 in World T2 in Local and translated in order to see the model:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase2/T1WT2LWith700Translate%20inLocal.JPG)

# Phase 3:
==========

![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase3/LoadedModel.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase3/ModelWithVertexNormals.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase3/ModelWithFaceAndVertexNormals.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase3/ModelWithFaceAndVertexNormalsAndBoundingBox.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase3/ModelWithFaceAndVertexNormalsAndBoundingBoxGUI-Included.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase3/ModelWithFaceAndVertexNormalsAndBoundingBoxTranslatedGUI-Included.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase3/ModelWithFaceAndVertexNormalsAndBoundingBoxTranslatedInX.JPG)

# Phase 4:
==========

Orthographic Mode:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase4/Cow-Orthographic.JPG)
Orthographic mode Rotation By Y in 75:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase4/Cow-Orthographic-RotatedByY75.JPG)
Orthographic mode Rotation By Y in 285:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase4/Cow-Orthographic-RotatedByY285.JPG)
Perspective Mode:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase4/Cow-Perspective.JPG)
Perspective mode Rotation By Y in 75:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase4/Cow-Perspective-RotatedByY75.JPG)
Perspective mode Rotation By Y in 285:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase4/Cow-Perspective-RotatedByY285.JPG)

# Phase 5:
==========

fovy=50:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase5/Cow-FOV50.JPG)

fovy=70:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase5/Cow-FOV70.JPG)

fovy=100:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase5/Cow-FOV100.JPG)

translate by Z 4.5:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase5/Cow-CamtranslateByZ4.5.JPG)

translate by Z -4.5:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase5/Cow-CamtranslateByZ-4.5.JPG)

# Phase 6:
==========

Rotate by Y 78 in Local:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase6/CowRotateLocal78.JPG)

Rotate by Y 96 in World:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase6/CowRotateWorld96.JPG)

# Phase 7:
==========

LookAt at(5,5,5):
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase7/Cow-LookAt-(5%2C5%2C5).JPG)

# Phase 9:
==========

![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase9/WindowResize1.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase9/WindowResize2.JPG)

# Phase 10:
===========

Maximum GUI:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/SuibAssignment3/Assignment1-SubAssignment3-Phase10/GUI.JPG)



