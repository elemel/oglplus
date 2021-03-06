/*
 *  .file oglplus/enums/compare_function_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/compare_function.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	CompareFunction
> _ValueRange(CompareFunction*)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_COMPAREFUNCTION)
#define OGLPLUS_IMPL_EVR_COMPAREFUNCTION
{
static const GLenum _values[] = {
#if defined GL_LEQUAL
GL_LEQUAL,
#endif
#if defined GL_GEQUAL
GL_GEQUAL,
#endif
#if defined GL_LESS
GL_LESS,
#endif
#if defined GL_GREATER
GL_GREATER,
#endif
#if defined GL_EQUAL
GL_EQUAL,
#endif
#if defined GL_NOTEQUAL
GL_NOTEQUAL,
#endif
#if defined GL_ALWAYS
GL_ALWAYS,
#endif
#if defined GL_NEVER
GL_NEVER,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	CompareFunction
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

