#ifndef MUPDF_FITZ_SEPARATION_H
#define MUPDF_FITZ_SEPARATION_H

#include "mupdf/fitz/system.h"
#include "mupdf/fitz/context.h"

/*
	A fz_separation structure holds details of a set of separations
	(such as might be used on within a page of the document).

	The app might control the separations by enabling/disabling them,
	and subsequent renders would take this into account.
*/

enum
{
	FZ_MAX_SEPARATIONS = 64
};

typedef struct fz_separations_s fz_separations;

typedef enum
{
	/* "Composite" separations are rendered using process
	 * colors using the equivalent colors */
	FZ_SEPARATION_COMPOSITE = 0,
	/* Spot colors are rendered into their own spot plane. */
	FZ_SEPARATION_SPOT = 1,
	/* Disabled colors are not rendered at all in the final
	 * output. */
	FZ_SEPARATION_DISABLED = 2
} fz_separation_behavior;

/* Create a new separations structure (initially empty) */
fz_separations *fz_new_separations(fz_context *ctx, int controllable);

/* Keep a reference */
fz_separations *fz_keep_separations(fz_context *ctx, fz_separations *sep);

/* Drop a reference */
void fz_drop_separations(fz_context *ctx, fz_separations *sep);

/* Add a separation (null terminated name, colorspace) */
void fz_add_separation(fz_context *ctx, fz_separations *sep, const char *name, fz_colorspace *cs, int cs_channel);

/* Add a separation with equivalents (null terminated name, colorspace) (old, deprecated) */
void fz_add_separation_equivalents(fz_context *ctx, fz_separations *sep, uint32_t rgba, uint32_t cmyk, const char *name);

/* Control the rendering of a given separation */
void fz_set_separation_behavior(fz_context *ctx, fz_separations *sep, int separation, fz_separation_behavior behavior);

/* Test for the current behavior of a separation */
fz_separation_behavior fz_separation_current_behavior(fz_context *ctx, const fz_separations *sep, int separation);

/* Quick test for all separations composite (the common case) */
int fz_separations_all_composite(fz_context *ctx, const fz_separations *sep);

/* Read separation name */
const char *fz_separation_name(fz_context *ctx, const fz_separations *sep, int separation);

/* Count the number of separations */
int fz_count_separations(fz_context *ctx, const fz_separations *sep);

/* Find out if separations are controllable. */
int fz_separations_controllable(fz_context *ctx, const fz_separations *seps);

/* Return the number of active separations. */
int fz_count_active_separations(fz_context *ctx, const fz_separations *seps);

/* If the separations selection is unsuitable for overprint,
 * clone it to produce one that is, otherwise return NULL. */
fz_separations *fz_clone_separations_for_overprint(fz_context *ctx, fz_separations *seps);

/* Convert a color given in terms of one colorspace,
 * to a color in terms of another colorspace/separations. */
void fz_convert_separation_colors(fz_context *ctx, const fz_color_params *color_params, const fz_colorspace *dst_cs, const fz_separations *dst_sep, float *dst_color, const fz_colorspace *src_cs, const float *src_color);

/* Get the equivalent separation color in a given colorspace. */
void fz_separation_equivalent(fz_context *ctx, const fz_separations *seps, int i, const fz_color_params *color_params, const fz_colorspace *dst_cs, const fz_colorspace *prf, float *convert);

#endif
