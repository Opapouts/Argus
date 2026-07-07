#include "vendor/raylib/src/raylib.h"
#include "includes/data_ingestion.h"
#include "includes/graphics_engine.h"

int  main(void)
{
	t_central central = {0};
	Camera3D camera = {0};

	graph_setup(&camera);

	Mesh		earthMesh = GenMeshSphere(4.0f, 32, 32);
	Model		earthModel = LoadModelFromMesh(earthMesh);
	Texture2D	earthTexture = LoadTexture("src/graphics_engine/assets/day_earth.png");
	earthModel.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = earthTexture;

	//We need to webscrape once and parse in the central struct
	central.json_str = webscrape();
	if (central.json_str)
	{
		parse_opensky_data(central.json_str, &central);
		custom_free(central.json_str);
	}
	while (!WindowShouldClose())
	{
		update_camera(&camera);
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(camera);
		DrawModel(earthModel, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
		draw_planes(central.planes);
		EndMode3D();
		DrawText("Live 3D Global Radar", 20, 20, 20, LIGHTGRAY);
		EndDrawing();
	}
	UnloadTexture(earthTexture);
	UnloadModel(earthModel);
	CloseWindow();
	free_planes(central.planes);
	return (0);
}
