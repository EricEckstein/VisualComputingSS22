# Visual Computing - Lecture WS 2022/2023
## Eric Eckstein - ai21m041

## Git repository:
    https://github.com/EricEckstein/VisualComputingSS22/

## Projects
- FirstOpenCLProgram: Test program, welches am Anfang der Vorlesung zum aufbau einfacher OpenCL - Auslagerung von Berechnungen
auf die Grafikkarte genutzt wurde
- MarchingCubes: // Alter Stand welcher nicht zum Laufen bekommen wurde
- OpenGl: Anfangsproject, welches einen funktionierenden Stand der OpenGL implementierung hatte - in diesem wurde der MarchingCubes Algorithmus implementiert. Auf eine Umbenennung wurde auf Grund von Abhängigkeiten verzichtet
- PointCloudRendering: Begonnenes PointCloud Rendering Project - wurde nicht weitergeführt, als die Abgabe entfernt wurde
- Raytracing: Abgabe für das Raytracing Project
- Shadertoy: Shadertoy Abgabe Implementierung



# Abgabe a) - Marching Cubes
## Enthalten in Ordner: "VirtualComputing.OpenGL"

### Shader
Es existieren drei Shader
- Fragment.glsl
- Vetex.glsl
- Geometry.glsl

### Hilfsklassen
Die "Shader" Klasse abstrahiert das Auslesen und Kompilieren aus den .glsl Dateien. 
Die PerlinNoise.hpp stellt random noise Daten zur Verfügung welche genutzt werden um den MarchingCube Algorithmus an den Enden weiter auszuführen

### Daten
Die tri_table.h gibt einen eindimensionalen Datensatz vor, auf welchem die ersten MarchingCube Triangles gebaut werden.

### Main in HelloWindow.cpp:
- Open GL wird initialisiert
- Shader werden ausgelesen und kompiliert
- Noise mit mit PerlinNoise Klasse initialisiert
- Buffer für Texture der perlinNoise wird generiert
- Vertex Daten werden erstellt und in Buffer geschrieben
- Rendering Loop:
    - Abfrage über Input
    - Color für Background wird gesetzt
    - Buffer werden gebunden
    - Shader wird mit Projection, View und Model Daten gesetzt
    - Shader programm wird gestartet
- Buffer und Shader werden gelöscht
- OpenGL Window wird terminiert

## Auführen:
- Verschiedene Verzeichnis müsen im Include Verzeichnis ersetzt werden:
- KHR, GLFW, glad und glm Verzeichnisse müssen gesetzt werden
    C:\Technikum\include\KHR
    C:\Technikum\include\GLFW
    C:\Technikum\include\glad
    C:\Technikum\include\glm
    C:\Technikum\include


# Abgabe b) - Raytracing 
## Enthaten in Ordner: "Raytracing\HelloTriangle"

Das Raytracing Hello Triangle wurde erweitert um den geforderten Würfel + Schatten und Ebene darzustellen

# Was funktioniert:
- Es wird die Ebene und der Würfel dargestellt (Würfel selbst mit Trianglen gerendert)
- Die Ebene wird unter dem Würfel dargestellt

# Was nicht funktioniert:
- Der Schattenwurf wird nicht dargestellt. Ich bin dem Raytracing Example häufig gefolgt, aber ich bekomme den Schattenwurf nicht zum Laufen.
(Sowohl ShadowRay.hlsl und Hit.hlsl wurden angepasst.)

# Ausführen:
- Das Projekt wurde in VS 2019 bearbeitet und hat keine externen Abhängigkeiten. Ein Ausführen müsste mit eine Nvidia raytracing-fähigen Grafikkarte ausführbar sein.
- Mit der "Leertaste" kann zwischen Raster-Berechnung und Raytracing umgeschalten werden

