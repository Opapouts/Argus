 gcc src/data_ingestion/*.c src/utils/*.c vendor/cJSON/cJSON.c -I./includes -I./vendor/cJSON -I./vendor/local_curl/include -L./vendor/local_curl/lib -lcurl -o argus

