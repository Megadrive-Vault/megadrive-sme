Map composition
---------------

Map are done using Tiled : http://www.mapeditor.org/
The .tmx is the main file searched by the compiler, then it requires:
 <map_name>_plan_a_solid.tiles          the main collision tiles, 16 colors bmp, packed to 1bit (0=none, other= plain, usefull for grid helpers), angle will be automaticaly generated
 <map_name>_plan_a_solid.csv            the collision map, exported from the .tmx
 <map_name>_plan_a_graphics.tiles       the graphics tiles
 <map_name>_plan_a_graphics.csv         the plane A graphics map
 <map_name>_plan_b_solid.tiles          the additional collision tiles, usefull for separated game mode (vehicles vs pedestrians)
 <map_name>_plan_b_solid.csv            the additional collision map
 <map_name>_plan_b_graphics.tiles       the graphics tiles
 <map_name>_plan_b_graphics.csv         the plane B graphics map

 