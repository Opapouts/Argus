#include <stdio.h>
#include <curl/curl.h>

int main(void) {
    /* Initialize libcurl globally */
    curl_global_init(CURL_GLOBAL_DEFAULT);

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize curl handle\n");
        return 1;
    }

    printf("libcurl version: %s\n\n", curl_version());

    /* Set the URL to fetch -- a simple, lightweight endpoint */
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");

    /* Follow redirects if any */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    /* Perform the request */
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        printf("Request succeeded! libcurl is working correctly.\n");
    }

    /* Cleanup */
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return (res == CURLE_OK) ? 0 : 1;
}
