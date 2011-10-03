/*
 * it6000e.h
 *
 *  Created on: Sep 25, 2011
 *      Author: ferd
 */

#ifndef IT6000E_H_
#define IT6000E_H_

/**
 * soft keys
 */
#define FN_KEY_1	1
#define FN_KEY_2	2
#define FN_KEY_3	3
#define FN_KEY_4	4
#define FN_KEY_5	5
#define FN_KEY_6	6

/**
 * display functions
 */
#define DISPLAY_WIDTH 		320
#define DISPLAY_HEIGHT 		240
#define APP_DISPLAY_HEIGHT 	129
#define FN_KEY_BAR_HEIGHT 	16

/**
 * color definitions
 * RTC WIN Programmer's reference p63
 */
#define COLOR_BLACK			56
#define COLOR_RED			88
#define COLOR_DARK_RED		72
#define COLOR_GREEN			63
#define COLOR_DARK_GREEN	60
#define COLOR_YELLOW		95
#define COLOR_DARK_YELLOW	76
#define COLOR_BLUE			216
#define COLOR_DARK_BLUE		136
#define COLOR_MAGENTA		248
#define COLOR_DARK_MAGENTA	152
#define COLOR_CYAN			223
#define COLOR_DARK_CYAN		140
#define COLOR_WHITE			255

#define COLOR_GREY_MAX		32
#define COLOR_GREY_MIN		55

/**
 * fonts
 */
#define FONT_HELVETICA	0
#define FONT_COURIER	4
#define FONT_RTC		16
#define FONT_RTC_MONO	20

/**
 * font style
 * should be added to selected font
 */
#define FONT_STYLE_NORMAL	0
#define FONT_STYLE_BOLD		1
#define FONT_STYLE_ITALIC	2


/**
 * box styles
 */
#define BOX_STYLE_NONE				0
#define BOX_STYLE_FLAT				1
#define BOX_STYLE_EMBOSS			2
#define BOX_STYLE_ENGRAVED			3
#define BOX_STYLE_EMBOSSED_FRAME_1	4
#define BOX_STYLE_ENGRAVED_FRAME_1	5
#define BOX_STYLE_EMBOSSED_THIN_1	6
#define BOX_STYLE_ENGRAVED_THIN_1	7
#define BOX_STYLE_EMBOSSED_THIN_2	8
#define BOX_STYLE_ENGRAVED_THIN_2	9
#define BOX_STYLE_ENGRAVED_BOX		10
#define BOX_STYLE_EMBOSSED_BOX		11
#define BOX_STYLE_ENGRAVED_FRAME_2	12
#define BOX_STYLE_EMBOSSED_FRAME_2	13
#define BOX_STYLE_THIN_BLACK		14

/**
 * arrow styles
 */
#define ARROW_STYLE_RIGHT	1
#define ARROW_STYLE_DOWN	2
#define ARROW_STYLE_LEFT	3
#define ARROW_STYLE_UP		4

/*
 * polygon draw modes
 */
#define POLYGON_DRAW_START	0
#define POLYGON_DRAW_END	1

/**
 * file functions
 */
#define FILE_HANDLE_MIN 0
#define FILE_HANDLE_MAX 7

#define FOPEN_SUCCESS 0

#define FWRITE_ERROR 0

#endif /* IT6000E_H_ */
