/*************************************************************************/
/*  godot_linuxbsd.cpp                                                   */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include <limits.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>

#include "main/main.h"
#include "os_linuxbsd.h"

#define ML_TEST 4
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/avstring.h>
#include <libavutil/time.h>
#include <libavutil/opt.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <av_rational.h>

#define SDL_AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIO_FRAME_SIZE 192000


int main(int argc, char *argv[]) {
	std::cerr << "Hello ffmpeg link test\n";
//	auto rat =     av_d2q(3, 6);
//	std::cerr << "rat:  " << rat.num << " / " << rat.den << "\n";

	av::Rational r (3,6);
	r.dump();
	std::cout << std::endl;

//	std::cerr << "fixme_mult(7, 5): " << fixme_mult(7, 5) << "\n";
//	auto rat =     av_d2q(3, 6);

//	std::cerr << "rat:  " << rat.num << " / " << rat.den << "\n";
	int ret = -1;

	// file I/O context: demuxers read a media file and split it into chunks of data (packets)
	AVFormatContext * pFormatCtx = NULL;
	ret = avformat_open_input(&pFormatCtx, argv[1], NULL, NULL);
	if (ret < 0)
	{
		printf("Could not open file %s.\n", argv[1]);
		return -1;
	}

	// read packets of a media file to get stream information
	ret = avformat_find_stream_info(pFormatCtx, NULL);
	if (ret < 0)
	{
		printf("Could not find stream information %s.\n", argv[1]);
		return -1;
	}

	// print detailed information about the input or output format
	av_dump_format(pFormatCtx, 0, argv[1], 0);


	return 0;
}

#if (ML_TEST == 4)
#elif (ML_TEST == 3)
#include "../../../modules/wrapffmpeg/example/api2-samples/api2-dict-basic.cpp"
//#include "../../../modules/wrapffmpeg/example/api2-samples/api2-decode-audio.cpp"
//#include "../../../modules/wrapffmpeg/example/api2-samples/api2-timestamp.cpp"
#elif (ML_TEST == 2)
#include <av_rational.h>
int main(int argc, char *argv[]) {
	std::cerr << "Hello Rational\n";
//	auto rat =     av_d2q(3, 6);
//	std::cerr << "rat:  " << rat.num << " / " << rat.den << "\n";

	av::Rational r (3,6);
	r.dump();
	std::cout << std::endl;

//	std::cerr << "fixme_mult(7, 5): " << fixme_mult(7, 5) << "\n";
//	auto rat =     av_d2q(3, 6);

//	std::cerr << "rat:  " << rat.num << " / " << rat.den << "\n";


	return 0;
}
#elif (ML_TEST == 1)
#include <iostream>
extern "C" {
#include <libavutil/rational.h>
}
int main(int argc, char *argv[]) {
	std::cerr << "Hello Martin\n";
	std::cerr << "fixme_mult(7, 5): " << fixme_mult(7, 5) << "\n";
	auto rat =     av_d2q(3, 6);

	std::cerr << "rat:  " << rat.num << " / " << rat.den << "\n";


	return 0;
}

#else
int main(int argc, char *argv[]) {
	OS_LinuxBSD os;

	setlocale(LC_CTYPE, "");

	// We must override main when testing is enabled
	TEST_MAIN_OVERRIDE

	char *cwd = (char *)malloc(PATH_MAX);
	ERR_FAIL_COND_V(!cwd, ERR_OUT_OF_MEMORY);
	char *ret = getcwd(cwd, PATH_MAX);

	Error err = Main::setup(argv[0], argc - 1, &argv[1]);
	if (err != OK) {
		free(cwd);
		return 255;
	}

	if (Main::start()) {
		os.run(); // it is actually the OS that decides how to run
	}
	Main::cleanup();

	if (ret) { // Previous getcwd was successful
		if (chdir(cwd) != 0) {
			ERR_PRINT("Couldn't return to previous working directory.");
		}
	}
	free(cwd);

	return os.get_exit_code();
}
#endif
