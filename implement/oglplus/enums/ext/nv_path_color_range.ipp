/*
 *  .file oglplus/enums/ext/nv_path_color_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_color.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	PathNVColor
> _ValueRange(PathNVColor*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_PATHNVCOLOR)
#define OGLPLUS_IMPL_EVR_PATHNVCOLOR
{
static const GLenum _values[] = {
#if defined GL_PRIMARY_COLOR_NV
GL_PRIMARY_COLOR_NV,
#endif
#if defined GL_SECONDARY_COLOR_NV
GL_SECONDARY_COLOR_NV,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	PathNVColor
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

