/*--------------------------------------------------------------------------------
 * How to know the size of Content-Length header without downloading the contents.
 *
 * The following URL is very useful for example code using cURL.
 * 		https://curl.se/libcurl/c/example.html
 *
 * -------------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/* Definition of bool type */
#ifndef bool
typedef unsigned char bool;
#endif

#ifndef true
#define true	((bool) 1)
#endif

#ifndef false
#define false	((bool) 0)
#endif

/* Enable debug */
static bool enable_debug = false;

/* Example function */
static double get_response_size(char *url);

/*
 * get_response_size
 * 		Return the size of response withoud download it.
 */
static double
get_response_size(char *url)
{
	CURL		*curl;
	CURLcode	 res;
	double		 response_size = 0;

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);

		/* download a header without body */
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

		/* follow HTTP redirect location  */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		if (enable_debug)
		{
			/* output debug info */
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}

		/* do request */
		res = curl_easy_perform(curl);
		if (res == CURLE_OK)
		{
			/* get the size of response that will be downloaded */
			res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &response_size);
			if(res != CURLE_OK)
				goto error_exit;
		}
		else
			goto error_exit;
	}

	curl_easy_cleanup(curl);
	return response_size;

error_exit:
	fprintf(stderr, "ERROR: Failed to transfer the data(status_code:%d).\n", res);
	curl_easy_cleanup(curl);
	exit(1);
}

/*
 * Main routine.
 * - Arguments:
 * 		1st: request URL
 * 		2nd: showing the verbose information if specify "debug" string.
 */
int
main(int argc, char *argv[])
{
	char	*url;
	double	 response_size;

	if (argc > 1)
	{
		url = argv[1];
		if (argc > 2 && (strcmp(argv[2], "debug") == 0))
			enable_debug = true;
	}
	else
	{
		fprintf(stderr, "Please specify the request URL.\n");
		return 1;
	}

	/* get the response size */
	response_size = get_response_size(url);
	printf("Size of response: %.0f (Byte)\n", response_size);

	return 0;
}
