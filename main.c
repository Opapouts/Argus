#include "vendor/raylib/src/raylib.h"
#include "includes/graphics_engine.h"
#include "includes/data_ingestion.h"

int  main(void)
{
	t_central central;
// 1. Setup the Camera (Before the while loop)
	Camera3D camera = {0};
	graph_setup(&camera);

	Mesh		earthMesh = GenMeshSphere(4.0f, 32, 32);
	Model		earthModel = LoadModelFromMesh(earthMesh);
	Texture2D	earthTexture = LoadTexture("src/graphics_engine/assets/2k_earth.png");
	earthModel.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = earthTexture;

	while (!WindowShouldClose())
	{
		update_camera(&camera);
		BeginDrawing();
		ClearBackground(BLACK);

		BeginMode3D(camera);
    
		DrawModel(earthModel, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
		plane_setup(central.planes);
		EndMode3D();
		DrawText("Live 3D Global Radar", 20, 20, 20, LIGHTGRAY);
		EndDrawing();
	}
	UnloadTexture(earthTexture);
	UnloadModel(earthModel);
	CloseWindow();
	return (0);
}
