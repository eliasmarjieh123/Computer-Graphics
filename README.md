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


# Assignment 2:

# Computer Graphics Assignment #2
Lighting and Shading
Introduction
In this assignment you will continue to develop your modeling software. The goal of this
assignment is to render solid, shaded objects.
General Requirements
As in the previous assignment, some of the requirements involve developing a user interface.
Design it however you like, using the mouse and menu, or just the keyboard, as long as you can
manipulate the scene in a reasonable amount of effort. The assignment is to add the following
elements to your program.
Note: Some of the requirements are not specific, and this is done on purpose. It is encouraged
that you to make your own decisions on how to design the code and the interface. In many
cases, there is no right or wrong. If you have two ways in which you can implement something
and you can’t decide, go with the simpler approach first. If you have time, implement the other
approach as well.
In this assignment, the following features should be implemented:
• Models materials:
1. Allow specifying a uniform material for each model. The material should consist of
ambient, diffuse and specular colors. Allow the user to change the different colors
(RGB).
2. Procedurally generate one non-uniform material. Use the slides on texture generation
for inspiration. There are many different options here, and no incorrect answer, so
be creative!
3. For pairs only: Enable texture mapping. Load an image and use texture coordinates
to apply to modulate the color. Allow the user to decide to which lighting model
(ambient, diffuse, or specular) to apply the texture to.
• Lights:
4. Allow the user to add a point light source, and specify its position.
5. Allow the user to add a parallel light source, and specify its direction.
6. for both light types, let the user pick the color (RGB) for the ambient, diffuse and
specular components.
7. Show the position and orientation of the light sources in an intuitive way.
8. For pairs only: Allow the user to add several light sources of the same type
• Renderer:
1
9. Implement a scan conversion algorithm to draw solid triangles.
10. Implement the z-buffer algorithm to allow hidden surface removal.
11. Implement flat, Gouraud and Phong shading and allow the user to switch between
them.
• Postprocessing: Implement one (For pairs only: two) of the following
12. Gaussian blurring and Bloom.
13. Multisample antialiasing.
14. Fog effect.

# Assignment 2- Part 1


## Phase 1:
--------

Model with random color for each triangle:
==========================================

![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part1/color-buufer.JPG)

## Phase 2:
--------

Showing the difference betweeen color-buffer and z-buffer:
==========================================================

![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part1/color-buffer-z-buffer.jpg)

Gray Scale in orthographic:
===========================

![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part1/Z-Buffer-GrayScale.JPG)

Gray Scale in Perspective:
==========================

![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part1/Z-Buffer-GrayScale-Perspective.JPG)



# Assignment 2- Part 2


Few Explenations:
=================

The user can add as much lights as they want, there is the abillity to
turn on/off any light, decide if its a point or parallel source, rotate,
translate and specify colors and to choose direction when in parallel.
Lights are shown as a star that presents a light when its turned on, and
it's color is the same as the light's ambient color. The user can choose
the 3 colors(R,G,B) for the model. All those actions can be done beside
the other options built in previous assignments.

Cow model with 2 point light sources in Flat shading abd both lights are translated:
=======================================================

Colors:
---------

Light Ambient Color= (224,42,42) Light Diffuse Color= (255,0,0) Light
SpecularColor= (214,44,44) Model Ambient Color= (70,162,165) Model
Diffuse Color= (55,169,20) Model Specular Color= (35,149,156)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/Cow-FlatShading-2PointLights.JPG)

Cow model with 1 point light source and 1 parallel light source in Flat shading and the point light is translated:
=========================================================================

Colors:
------------

Light Ambient Color= (224,42,42) Light Diffuse Color= (255,0,0) Light
SpecularColor= (214,44,44) Model Ambient Color= (70,162,165) Model
Diffuse Color= (55,169,20) Model Specular Color= (35,149,156)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/Cow-FlatShading-1PointLights-1ParallelLight.JPG)

Cow Model with 2 point light sources in Gouraud shading and both lights are translated:
===========================================================

Colors:
---------

Light Ambient Color= (224,42,42) Light Diffuse Color= (255,0,0) Light
SpecularColor= (214,44,44) Model Ambient Color= (70,162,165) Model
Diffuse Color= (55,169,20) Model Specular Color= (35,149,156)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/Cow-GouraudShading-2PointLights.JPG)

Cow model with 1 point light source and 1 parallel light source in Gouraud shading and the point light is translated:
=============================================================================

Colors:
----------

Light Ambient Color= (224,42,42) Light Diffuse Color= (255,0,0) Light
SpecularColor= (214,44,44) Model Ambient Color= (70,162,165) Model
Diffuse Color= (55,169,20) Model Specular Color= (35,149,156)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/Cow-GouraudShading-1PointLights-1ParallelLight.JPG)

Cow modelk with 3 parallel light sources in different colors and different directions:
=======================================================

![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/Cow-3ParallelLights.JPG)

Showing the difference between Gouraud shading and Phong shading:
==============================================

Gouraud Shading:
------------------

![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/Cow-GouraudShading-PointLights.JPG)
Phong Shading:
--------------------
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/Cow-PhongShading-PointLights.JPG)

Linear fog on the teapot:
---------------------------
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/LinearFog.JPG)

Fog with density 40:
---------------------
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/Fog-Density40.JPG)

Fog with density 62:
-----------------------
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/Fog-Density62.JPG)

Extra Photos:
===========

Flat shading with 2 light sources:
--------------------------------------

![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/GUI-Cow.JPG)

Phong shading with 2 light sources:
------------------------------------------
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/GUI-Cow-Phong.JPG)

Beethoven with 4 light sources with Phong shading:
--------------------------------------------------------
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment2/Part2/Beethoven.JPG)




# Assignment 3:

Computer Graphics Assignment #3
OpenGL renderer
In the third assignment you will replace the software renderer you implemented in the
first two assignment by an OpenGL renderer. There are several steps that are necessary in
order to do that, and unfortunately you will not be able to see anything on screen before you
accomplish all of them. Before you start, please study the example OpenGL project posted on
the website and plan the necessary steps. The main goal of this assignment is to focus on the
implementation of Phong shading only. There is no requirement to implement the wire frame
rendering or flat and Goroud shading.
For this part please create a markdown file ’Assignment3Report/Assignment3Report.md’, and
do the following:
1. The software renderer was built on top of OpenGL. The Renderer::SwapBuffer() function
loads color buffer into a texture on the GPU. Read the function Renderer::InitOpenGLRendering()
and explain in the report how this texture is displayed. Remove all the now irrelevant
code from the renderer.
2. Update the MeshModel class to load the mesh on the GPU. Use the example OpenGL
project as a reference.
3. Write a vertex shader that applies all the transformations. Use the reference code, but
pay attention to the differences between your code and the reference code. Copy the code
the the report.
4. Write a fragment shader that only outputs a constant color and paste it in the report.
The goal for now is to ensure that the pipeline works. Lights will be added later.
5. In the renderer, update all the relevant vertex attributes and uniforms, and paste the
relevant piece of code to the report. If everything was done correctly, you should be able
to view the mesh in your application.
6. Implement Phong shading in the fragment shader. To demonstrate that the performance
has now improved a lot, load one of the meshes from
https://github.com/alecjacobson/common-3d-test-models and display it from several viewpoint and different lighting.
7. Implement texture mapping. Use the example OpenGL project as reference. Enable
at least one type of canonical project (for pairs: three): plane, cylinder or sphere. In
addition, find a mesh with texture coordinates and use them. Show your results in the
report.
8. Implement one (for pairs: all) of the following
(a) Normal mapping
(b) Environment mapping
(c) Toon shading (without the silhouette)


# Assignment 3 Report:

# Assignment 3
### Name: Elias Marjieh
### ID No. 318386646
#
#
#
#
#### Phase 1:
Renderer::InitOpenGLRendering()
This function gets our screen ready to render models on it. 
glGenTextures(1, &gl_screen_tex_); this instruction prepares the texture's identifier in order to use textures.
glGenVertexArrays(1, &gl_screen_vtc_); Arrays (Buffers) that describes the objects that will be rendered on the screen.

The function creates to triangles that contains the content that will be stretched over the screen, basically it replaces our buffers from the previous assignments and GL will make sure everything is rendered correctly and the Z-buffer algorithm is activated.
#### Phase 2:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/MeshModelConstructor.JPG)
The MeshModel constructor now creates a list of vertexes that contains for each vertex its position, normal and texture coordinates (if there is any texture coordinates or normals for the model).
It also prepares the GL buffers, VAO, VBO, vertices and all the data that is needed by the GPU in order to render the models correctly on the screen.

#### Phase 3:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/vshader.JPG)

# vshader code:
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

// The model/view/projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 LightTransformation;
uniform int lightType;
uniform bool VT;
// These outputs will be available in the fragment shader as inputs
out vec3 orig_fragPos;
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;

void main()
{
	// Apply the model transformation to the 'position' and 'normal' properties of the vertex,
	// so the interpolated values of these properties will be available for usi n the fragment shader
	orig_fragPos = vec3(vec4(pos, 1.0f));
	fragPos = vec3(model * vec4(pos, 1.0f));
	fragNormal =  normal;

	// Pass the vertex texture coordinates property as it is. Its interpolated value
	// will be avilable for us in the fragment shader
	if(VT){fragTexCoords = texCoords;}
	else{
	fragTexCoords = orig_fragPos.xy;
	}
	gl_Position = projection * view *  model * vec4(pos, 1.0f);
}

The vshader prepares the data (inputs) for the fragment shader in order to use it for to impolement the shaders.

#### Phase 4:
###### The fragment shader that gives the model a constant color which can be contorled by the ambient color
#version 330 core
#define PHONGSHADING 999
#define WIREFRAME 990
#define TEXTURED 900
#define REFLECTION 909

struct Material
{
	sampler2D textureMap;
	vec3 diffuseColor;
	vec3 specularColor;
	vec3 ambientColor;

	// You can add more fields here...
	// Such as:
	//		1. diffuse/specular relections constants
	//		2. specular alpha constant
	//		3. Anything else you find relevant
};

// We set this field's properties from the C++ code
uniform Material material;
uniform int LightsCount;
uniform vec3 AmbientColor[10];
uniform vec3 DiffuseColor[10];
uniform vec3 SpecularColor[10];
uniform vec3 lightsPositions[10];
uniform mat4x4 lightTransformations[10];
uniform vec3 LightsDirections[10];
uniform int LightsTypes[10];
uniform vec3 eye;
uniform int Method;
uniform int Alpha[10];
// Inputs from vertex shader (after interpolation was applied)
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;
// The final color of the fragment (pixel)
out vec4 color;

void main()
{
	// Sample the texture-map at the UV coordinates given by 'fragTexCoords'
	vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));
	vec3 I,FinalAmbient,FinalDiffuse,FinalSpecular;
	color=vec4(material.ambientColor,1.f);
}
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/OneColor.JPG)

#### All fragment shader code:


#version 330 core
#define PHONGSHADING 999
#define WIREFRAME 990
#define TEXTURED 900
#define REFLECTION 909



struct Material
{
	sampler2D textureMap;
	vec3 diffuseColor;
	vec3 specularColor;
	vec3 ambientColor;

	// You can add more fields here...
	// Such as:
	//		1. diffuse/specular relections constants
	//		2. specular alpha constant
	//		3. Anything else you find relevant
};

// We set this field's properties from the C++ code
uniform Material material;
uniform int LightsCount;
uniform vec3 AmbientColor[10];
uniform vec3 DiffuseColor[10];
uniform vec3 SpecularColor[10];
uniform vec3 lightsPositions[10];
uniform mat4x4 lightTransformations[10];
uniform vec3 LightsDirections[10];
uniform int LightsTypes[10];
uniform vec3 eye;
uniform int Method;
uniform int Alpha[10];
// Inputs from vertex shader (after interpolation was applied)
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;
// The final color of the fragment (pixel)
out vec4 color;

void main()
{
	// Sample the texture-map at the UV coordinates given by 'fragTexCoords'
	vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));
	vec3 I,FinalAmbient,FinalDiffuse,FinalSpecular;
		if(Method==2)	
	     {
		    color=vec4(0.f,0.f,0.f,1.f);
			for(int i=0;i<LightsCount;i++)
			{
				if(LightsTypes[i]==1){I=normalize(fragPos-vec3(lightTransformations[i]* vec4(lightsPositions[i],1.f)));}
				else {I=LightsDirections[i];}
				FinalAmbient=vec3(AmbientColor[i].x*material.ambientColor.x,AmbientColor[i].y*material.ambientColor.y,AmbientColor[i].z*material.ambientColor.z);
				FinalDiffuse=vec3(DiffuseColor[i].x * material.diffuseColor.x, DiffuseColor[i].y * material.diffuseColor.y, DiffuseColor[i].z * material.diffuseColor.z)*dot((-fragNormal), I);
				FinalSpecular = vec3(SpecularColor[i].x * material.specularColor.x, SpecularColor[i].y * material.specularColor.y, SpecularColor[i].z * material.specularColor.z);
				vec3 r = (2.f * dot(-fragNormal, I) * fragNormal - I);
				float Power = pow(max(0.0f, dot((r), (eye))), Alpha[i]);
				FinalSpecular*=Power;
			    color += vec4((FinalSpecular+FinalDiffuse+FinalAmbient),0.f);
			}
		}
		else if(Method==0)
		{
			color=vec4(material.ambientColor,1.f);
		}
		else if(Method==1){
		color=vec4(textureColor,1.f);
		}
		else if(Method==3){
		color=vec4(material.ambientColor.x,material.ambientColor.y,material.ambientColor.z,1.f);
		}
		else{
		   color=vec4(0.f,0.f,0.f,1.f);
           for(int i=0;i<LightsCount;i++)
			{
			if(LightsTypes[i]==1){I=normalize(fragPos-vec3(lightTransformations[i]* vec4(lightsPositions[i],1.f)));}
			else {I=LightsDirections[i];}
			   float intensity = dot(I, fragNormal);
               if(intensity < 0)
                  intensity = 0;
               // Calculate what would normally be the final color, including texturing and diffuse lighting
               vec3 color1 = vec3(fragTexCoords,1.f) * DiffuseColor[i]*  material.diffuseColor;
                // Discretize the intensity, based on a few cutoff points
                if (intensity > 0.95)
                    color1 = vec3(1.0,1,1) * color1;
                else if (intensity > 0.5)
                    color1 = vec3(0.7,0.7,0.7) * color1;
                else if (intensity > 0.05)
                    color1 = vec3(0.35,0.35,0.35) * color1;
                else
                    color1 = vec3(0.1,0.1,0.1) * color1;
              color+=vec4(color1,0.f);
            }
       }
}

#### Phase 5:
void Renderer::Render(Scene& scene)
{
	int cameraCount = scene.GetCameraCount();
	int LightsCount=scene.GetLightCount();
	glm::vec3 AmbientColor[10];
	glm::vec3 DiffuseColor[10];
	glm::vec3 SpecularColor[10];
	glm::vec3 lightsPositions[10];
	glm::mat4x4 lightTransformations[10];
	glm::vec3 lightsDirections[10];
	int lightTypes[10];
	int Alpha[10];
	if (cameraCount > 0)
	{
		int modelCount = scene.GetModelCount();
		const Camera& camera = scene.GetActiveCamera();
		for (int i = 0; i < scene.GetLightCount(); i++)
		{
			Light currentLight = scene.GetLight(i);
			if (currentLight.IsActive()) {
				AmbientColor[i] = currentLight.GetAmbientColor();
				DiffuseColor[i] = currentLight.GetDiffuseColor();
				SpecularColor[i] = currentLight.GetSpecularColor();
				lightsPositions[i] = currentLight.GetPosition();
				lightTransformations[i] = currentLight.GetTransformation();
				lightsDirections[i] = normalize(currentLight.GetDirection());
				lightTypes[i] = currentLight.GetIfPoint();
				Alpha[i] = currentLight.GetAlpha();
			}
			else {
				LightsCount--;
			}
		}
		for (int currentModelIndex = 0; currentModelIndex < modelCount; currentModelIndex++)
		{
			MeshModel& currentModel = scene.GetModel(currentModelIndex);

			// Activate the 'colorShader' program (vertex and fragment shaders)
			colorShader.use();

			//colorShader.setUniform("reflection", false);
			colorShader.setUniform("AmbientColor", AmbientColor, LightsCount);
			colorShader.setUniform("DiffuseColor", DiffuseColor, LightsCount);
			colorShader.setUniform("SpecularColor", SpecularColor, LightsCount);
			colorShader.setUniform("lightsPositions", lightsPositions, LightsCount);
			colorShader.setUniform("lightTransformations", lightTransformations, LightsCount);
			colorShader.setUniform("LightsTypes", lightTypes, LightsCount);
			colorShader.setUniform("LightsDirections", lightsDirections, LightsCount);
			colorShader.setUniform("LightsCount", LightsCount);
			colorShader.setUniform("eye", normalize(camera.GetEye()));
			colorShader.setUniform("material.diffuseColor", currentModel.GetDiffuseColor());
			colorShader.setUniform("material.specularColor", currentModel.GetSpecularColor());
			colorShader.setUniform("material.ambientColor", currentModel.GetAmbientColor());
			colorShader.setUniform("Alpha", Alpha, scene.GetLightCount());
			colorShader.setUniform("Method", currentModel.GetMethod());
			colorShader.setUniform("model", currentModel.GetWorldTransformation() * currentModel.GetModelTransformation());
			colorShader.setUniform("view", camera.GetViewTransformation());
			colorShader.setUniform("projection", camera.GetProjectionTransformation());
			colorShader.setUniform("material.textureMap", 0);
			colorShader.setUniform("VT", currentModel.GetIfThereIsVT());

			if (currentModel.GetMethod() == 0)
			{
				// Drag our model's faces (triangles) in line mode (wireframe)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glBindVertexArray(currentModel.GetVAO());
				glDrawArrays(GL_TRIANGLES, 0, currentModel.GetModelVertices().size());
				glBindVertexArray(0);
			}
			else if (currentModel.GetMethod() == 2|| currentModel.GetMethod() == 4) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBindVertexArray(currentModel.GetVAO());
				glDrawArrays(GL_TRIANGLES, 0, currentModel.GetModelVertices().size());
				glBindVertexArray(0);
			}
			else if(currentModel.GetMethod() == 1){
				texture1.bind(0);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBindVertexArray(currentModel.GetVAO());
				glDrawArrays(GL_TRIANGLES, 0, currentModel.GetModelVertices().size());
				glBindVertexArray(0);
				texture1.unbind(0);
			}
			else if (currentModel.GetMethod() == 3) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBindVertexArray(currentModel.GetVAO());
				glDrawArrays(GL_TRIANGLES, 0, currentModel.GetModelVertices().size());
				glBindVertexArray(0);
			}
		}
	}
}	
In this function we send all the model's properties to the fragment shader in order to render the model in the correct way.
Then we specefy what method we want and according to the method we give the instructions

#### Phase 6:
Demonstrating Phong shading
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/BeetlePhong.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/ManyModels.JPG)
In the last picture beethoven and the cow are rendered with phong shading.

#### Phase 7:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/CowWearingBoots.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/TeaPotBlackAndWithe.JPG)
#### Here Beethoven and the cow are phong shaded and watermelons are toon shaded
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/ThoseAreMyWaterMelons.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/CrateTextured.JPG)
Those are models with Texture coordinates (The beetle with no texture coordinates).
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/Beetle.JPG)

#### Phase 8:
##### I decided to implement toon shading:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/CrateInToonShading.JPG)
#### Here we can see that part of the models are toon shaded
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/ManyModels.JPG)
#### Beethoven, crate and watermelon toon shaded:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/ToonShading.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/BeethovenToonShading.jpeg)
## Extras:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/WireFrame.JPG)

### Although sometimes it was hard to understand the background calculations and implementations, it was so fun to do this cousre, thank you.
