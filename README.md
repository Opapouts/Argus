gcc main.c src/graphics_engine/*.c src/data_ingestion/*.c src/utils/*.c vendor/cJSON/cJSON.c -I./includes -I./vendor/cJSON -I./vendor/local_curl/include -I./vendor/raylib/src -L./vendor/local_curl/lib -L./vendor/raylib/src -lcurl -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o argus

