# Ocean Simulation

### Overview

We present a procedural method for sea surface simulation. Our model is based on a superposition of many different waves generated according to some physical rules to reproduce natural phenomena. More precisely, we choose a wave spectrum approach to create the wave’s main structure and Perlin noise for small scale details. Then, we use a layered BRDF with a diffuse term, a specular term using a microfacet model based on the GGX distribution and a global illumination term, for the rendering procedure to get a satisfying visual result.

![Final_scene1](https://user-images.githubusercontent.com/76222299/161565694-ccf6f9e0-ff9a-4c18-acfa-d52ac4537d57.png)
![final_result2](https://user-images.githubusercontent.com/76222299/161565703-f0af7abd-0a5f-48f5-8f48-afc193e4f3d3.PNG)
![waves](https://user-images.githubusercontent.com/76222299/161565711-ad5755f8-d04f-46f7-a047-6c4eb31a09f2.PNG)
![seafoam](https://user-images.githubusercontent.com/76222299/161565705-878549f6-a357-4217-bc61-8eaf9119f391.PNG)

### To Run
'''
make ..
./pgm
'''
