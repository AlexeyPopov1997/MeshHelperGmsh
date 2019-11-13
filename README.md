# MeshHelperGMSH

MeshHelperGMSH is a dynamic link library (dll) for creating finite element models of bodies of revolution.

> When creating a library, the API of an open source 3D finite element mesh generator GMSH is actively used [![GMSH](https://github.com/AlexeyPopov1997/MeshHelperGMSH/blob/master/figures/gmsh_logo.png)](http://gmsh.info)

## MeshHelperGMSH.dll and exported function

MeshHelperGMSH.dll contains an exported function:

```sh
bool сreateRotationBodyMesh (const WCHAR * IniFileName, const WCHAR * BodySectionName)
```

which accepts the name of an .ini file with radial section coordinates of various bodies of rotation and a section with data about a specific body under study as input parameter.

An example of the .ini file used:

```sh
[Body1]

ContourNodesSection=Nods1
RotateAxeBeginPoint=0.0  0.0  0.0
RotateAxeEndPoint=0.0  1.0  0.0
MeshStep=0.5
VolumeMeshFile=Body1.msh
 
[Nods1]
 
P1=0  0  0
P2=2  0  0
P3=6  1  0
P4=8  2  0
P5=7  2  0
P6=6  2  0
P7=2  1  0
P8=0  1  0
```

- Examples of inifiles are in the directory https://github.com/AlexeyPopov1997/MeshHelperGMSH/tree/master/inifiles_test


This function returns the name generated during its operation, the file of the finite element mesh (VolumeMeshFile).

An example of the .msh file received: 

* viewing a file in post processor mode in GMSH

![alt text](https://github.com/AlexeyPopov1997/MeshHelperGMSH/blob/master/figures/Body1_postproc.png) 


* view a file in a text editor

```sh
$MeshFormat
4 0 8
$EndMeshFormat
$Entities
27 52 28 1
1 0 0 0 0 0 0 0 
2 2 0 0 2 0 0 0 
3 6 1 0 6 1 0 0 
...
111 -2.693795529522258e-10 1 0 2 1 2 0 3 -7 -107 83 
1 -8 0 -8 8 2 8 0 28 10 14 18 22 26 30 33 36 40 44 48 52 56 59 62 66 70 74 78 82 85 88 92 96 100 104 108 111 
$EndEntities
$Nodes
108 4440
1 0 0 1
1 0 0 0
2 0 0 1
...
4584 -2.338138678685574 0.7671455966861047 -2.098601462465859
$EndNodes
$Elements
108 11689
1 0 15 1
1 1 
2 0 15 1
...
36167 2816 2955 2971 2859 
$EndElements
```

## Files of finite element mesh can be written to files of the following formats

| File type | File extension |
| ------ | ------ |
| Gmsh MSH | .msh |
| Abaqus INP | .inp |
| LSDYNA KEY | .key |
| CELUM | .celum |
| CGNS | .cgns |
| Diffpack 3D | .diff |
| I-deas Universal | .unv |
| Iridum | .ir3 |
| MED | .med  .mmed |
| INRIA Medit | .mesh |
| CEA Triangulation | .mail |
| Matlab | .m |
| Nastran Bulk Data File | .bdf  .nas |
| Plot3D Structured Mesh | .p3d |
| STL Surface | .stl |
| VTK | .vtk |
| VRML Surface | .wrl  .vrml |
| Tochnog | .dat |
| PLY2 Surface | .ply2 |
| SU2 | .su2 |
| GAMBIT Neutral File | .neu |

## Compilation and assembly
> The project was compiled and assembled using standard tools IDE Visual Studio 2019 Community [![VS2019](https://github.com/AlexeyPopov1997/MeshHelperGMSH/blob/master/figures/visual_studio_community_2019.png)](https://visualstudio.microsoft.com/ru/vs/)

## Current version of MeshHelperGMSH.dll
> Release version dynamic link library (dll) for Win32 configuration: 

[![MeshHelperGMSH](https://github.com/AlexeyPopov1997/MeshHelperGMSH/blob/master/figures/MeshHelperGMSH.dll.png)](https://github.com/AlexeyPopov1997/MeshHelperGMSH/tree/master/Bin)
