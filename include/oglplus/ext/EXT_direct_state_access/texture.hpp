/**
 *  @file oglplus/ext/EXT_direct_state_access/texture.hpp
 *  @brief Texture object wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_DSA_1107121519_HPP
#define OGLPLUS_TEXTURE_DSA_1107121519_HPP

#include <oglplus/texture.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Wrapper for texture and texture unit-related operations
/** @note Do not use this class directly, use Texture instead.
 *
 *  @glsymbols
 *  @glfunref{GenTextures}
 *  @glfunref{DeleteTextures}
 *  @glfunref{IsTexture}
 */
class DSATextureEXTOps
 : public Named
 , public BaseObject<true>
 , public FriendOf<BufferOps>
{
public:
	/// Texture bind and image specification targets
	/** @note Not all of the values enumerated here are valid
	 *  bind targets. Some of them are just image specification
	 *  targets.
	 */
	typedef TextureTarget Target;
	Target target;
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenTextures)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenTextures));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteTextures)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsTexture)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_TEXTURE
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::Texture;
	}
#endif

	friend class FriendOf<DSATextureEXTOps>;
public:
	/// Types related to Texture
	struct Property
	{
		/// Depth texture comparison mode
		typedef TextureCompareMode CompareMode;

		/// Maginification filter
		typedef TextureMagFilter MagFilter;

		/// Minification filter
		typedef TextureMinFilter MinFilter;

		/// Texture swizzle coordinate
		typedef TextureSwizzleCoord SwizzleCoord;

		/// Texture swizzle value
		typedef TextureSwizzle Swizzle;

		/// Texture wrap mode for coordinate
		typedef TextureWrapCoord WrapCoord;

		/// Texture wrap mode value
		typedef TextureWrap Wrap;
	};

	/// Specify active texture unit for subsequent commands
	/**
	 *  @throws Error
	 *
	 *  @see Bind
	 *
	 *  @glsymbols
	 *  @glfunref{ActiveTexture}
	 */
	static void Active(TextureUnitSelector index)
	{
		OGLPLUS_GLFUNC(ActiveTexture)(
			GLenum(GL_TEXTURE0 + GLuint(index))
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ActiveTexture));
	}

	/// Returns active texture unit
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{ACTIVE_TEXTURE}
	 */
	static GLint Active(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_ACTIVE_TEXTURE, &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		return GL_TEXTURE0 - result;
	}

	/// Bind this texture to this->target
	void Bind(void)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindTexture)(GLenum(target), _name);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindTexture,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	GLint GetIntParam(GLenum query) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetTextureParameterivEXT)(
			_name,
			GLenum(target),
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return result;
	}

	GLfloat GetFloatParam(GLenum query) const
	{
		GLfloat result = 0;
		OGLPLUS_GLFUNC(GetTextureParameterfvEXT)(
			_name,
			GLenum(target),
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterfvEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return result;
	}

	GLint GetIntParam(GLint level, GLenum query) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetTextureLevelParameterivEXT)(
			_name,
			GLenum(target),
			level,
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureLevelParameterivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return result;
	}

	GLfloat GetFloatParam(GLint level, GLenum query) const
	{
		GLfloat result = 0;
		OGLPLUS_GLFUNC(GetTextureLevelParameterfvEXT)(
			_name,
			GLenum(target),
			level,
			query,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureLevelParameterfvEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return result;
	}

	/// Returns the width of the texture as it was specified by *Image*D
	/**
	 *  @see Height
	 *  @see Depth
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_WIDTH}
	 */
	GLsizei Width(GLint level = 0) const
	{
		return GLsizei(GetIntParam(level, GL_TEXTURE_WIDTH));
	}

	/// Returns the height of the texture as it was specified by *Image*D
	/**
	 *  @see Width
	 *  @see Depth
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_HEIGHT}
	 */
	GLsizei Height(GLint level = 0) const
	{
		return GLsizei(GetIntParam(level, GL_TEXTURE_HEIGHT));
	}

	/// Returns the depth of the texture as it was specified by *Image*D
	/**
	 *  @see Width
	 *  @see Height
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_DEPTH}
	 */
	GLsizei Depth(GLint level = 0) const
	{
		return GLsizei(GetIntParam(level, GL_TEXTURE_DEPTH));
	}

	/// Returns the data type used to store the RED component
	/**
	 *  @see GreenType
	 *  @see BlueType
	 *  @see AlphaType
	 *  @see DepthType
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_RED_TYPE}
	 */
	PixelDataType RedType(GLint level = 0) const
	{
		return PixelDataType(GetIntParam(
			level,
			GL_TEXTURE_RED_TYPE
		));
	}

	/// Returns the data type used to store the GREEN component
	/**
	 *  @see RedType
	 *  @see BlueType
	 *  @see AlphaType
	 *  @see DepthType
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_GREEN_TYPE}
	 */
	PixelDataType GreenType(GLint level = 0) const
	{
		return PixelDataType(GetIntParam(
			level,
			GL_TEXTURE_GREEN_TYPE
		));
	}

	/// Returns the data type used to store the BLUE component
	/**
	 *  @see RedType
	 *  @see GreenType
	 *  @see AlphaType
	 *  @see DepthType
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_BLUE_TYPE}
	 */
	PixelDataType BlueType(GLint level = 0) const
	{
		return PixelDataType(GetIntParam(
			level,
			GL_TEXTURE_BLUE_TYPE
		));
	}

	/// Returns the data type used to store the ALPHA component
	/**
	 *  @see RedType
	 *  @see GreenType
	 *  @see BlueType
	 *  @see DepthType
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_ALPHA_TYPE}
	 */
	PixelDataType AlphaType(GLint level = 0) const
	{
		return PixelDataType(GetIntParam(
			level,
			GL_TEXTURE_ALPHA_TYPE
		));
	}

	/// Returns the data type used to store the DEPTH component
	/**
	 *  @see RedType
	 *  @see GreenType
	 *  @see BlueType
	 *  @see AlphaType
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_DEPTH_TYPE}
	 */
	PixelDataType DepthType(GLint level = 0) const
	{
		return PixelDataType(GetIntParam(
			level,
			GL_TEXTURE_DEPTH_TYPE
		));
	}

	/// Returns the actual resolution of the RED component
	/**
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_RED_SIZE}
	 */
	GLsizei RedSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_RED_SIZE
		));
	}

	/// Returns the actual resolution of the GREEN component
	/**
	 *  @see RedSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_GREEN_SIZE}
	 */
	GLsizei GreenSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_GREEN_SIZE
		));
	}

	/// Returns the actual resolution of the BLUE component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_BLUE_SIZE}
	 */
	GLsizei BlueSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_BLUE_SIZE
		));
	}

	/// Returns the actual resolution of the ALPHA component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_ALPHA_SIZE}
	 */
	GLsizei AlphaSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_ALPHA_SIZE
		));
	}

	/// Returns the actual resolution of the DEPTH component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_DEPTH_SIZE}
	 */
	GLsizei DepthSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_DEPTH_SIZE
		));
	}

	/// Returns the actual resolution of the STENCIL component
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_STENCIL_SIZE}
	 */
	GLsizei StencilSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_STENCIL_SIZE
		));
	}

	/// Returns the size of all texture components
	/**
	 *  @see RedSize
	 *  @see GreenSize
	 *  @see BlueSize
	 *  @see AlphaSize
	 *  @see DepthSize
	 *  @see StencilSize
	 *
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_SHARED_SIZE}
	 */
	GLsizei SharedSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_SHARED_SIZE
		));
	}

	/// Returns the size (in bytes) of the image array if it is compressed
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_COMPRESSED_IMAGE_SIZE}
	 */
	GLsizei CompressedImageSize(GLint level = 0) const
	{
		return GLsizei(GetIntParam(
			level,
			GL_TEXTURE_COMPRESSED_IMAGE_SIZE
		));
	}

	/// Returns the internal data format of the image array
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexLevelParameter}
	 *  @gldefref{TEXTURE_INTERNAL_FORMAT}
	 */
	PixelDataInternalFormat InternalFormat(GLint level = 0) const
	{
		return PixelDataInternalFormat(GetIntParam(
			level,
			GL_TEXTURE_INTERNAL_FORMAT
		));
	}

/*
	template <typename T>
	static void GetImage(
		Target target,
		GLint level,
		PixelDataFormat format,
		std::vector<T>& dest
	)
	{
		dest.resize(...); TODO (see ReadPixel &co.)
		and/or ARB_robustness
		OGLPLUS_GLFUNC(GetTexImage)(
			GLenum(target),
			level,
			GLenum(format),
			GLenum(GetDataType<T>()),
			dest.data()
		);
	}
*/

	/// Allows to obtain the texture image in compressed form
	/** This function stores the image of the texture bound to
	 *  the specified texture @p target with the specified @p level
	 *  of detail in compressed form into the @p dest buffer.
	 *  This function automatically resizes the buffer so that
	 *  it can accomodate the texture data.
	 *
	 *  @glsymbols
	 *  @glfunref{GetCompressedTexImage}
	 */
	void GetCompressedImage(
		GLint level,
		std::vector<GLubyte>& dest
	) const
	{
		dest.resize(CompressedImageSize(level));
		OGLPLUS_GLFUNC(GetCompressedTextureImageEXT)(
			_name,
			GLenum(target),
			level,
			dest.data()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetCompressedTextureImageEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a three dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage3D}
	 */
	void Image3D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureImage3DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			height,
			depth,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a three dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage3D}
	 */
	void Image3D(
		const images::Image& image,
		GLint level = 0,
		GLint border = 0
	)
	{
		OGLPLUS_GLFUNC(TextureImage3DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(image.InternalFormat()),
			image.Width(),
			image.Height(),
			image.Depth(),
			border,
			GLenum(image.Format()),
			GLenum(image.Type()),
			image.RawData()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a three dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage3D}
	 */
	void SubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage3DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			zoffs,
			width,
			height,
			depth,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a three dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage3D}
	 */
	void SubImage3D(
		const images::Image& image,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint level = 0
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage3DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			zoffs,
			image.Width(),
			image.Height(),
			image.Depth(),
			GLenum(image.Format()),
			GLenum(image.Type()),
			image.RawData()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a two dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage2D}
	 */
	void Image2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureImage2DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			height,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a two dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage2D}
	 */
	void Image2D(
		const images::Image& image,
		GLint level = 0,
		GLint border = 0
	)
	{
		OGLPLUS_GLFUNC(TextureImage2DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(image.InternalFormat()),
			image.Width(),
			image.Height(),
			border,
			GLenum(image.Format()),
			GLenum(image.Type()),
			image.RawData()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a two dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage2D}
	 */
	void SubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLsizei width,
		GLsizei height,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage2DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			width,
			height,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a two dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage2D}
	 */
	void SubImage2D(
		const images::Image& image,
		GLint xoffs,
		GLint yoffs,
		GLint level = 0
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage2DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			image.Width(),
			image.Height(),
			GLenum(image.Format()),
			GLenum(image.Type()),
			image.RawData()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a one dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage1D}
	 */
	void Image1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureImage1DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			border,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a one dimensional texture image
	/**
	 *  @glsymbols
	 *  @glfunref{TexImage1D}
	 */
	void Image1D(
		const images::Image& image,
		GLint level = 0,
		GLint border = 0
	)
	{
		OGLPLUS_GLFUNC(TextureImage1DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(image.InternalFormat()),
			image.Width(),
			border,
			GLenum(image.Format()),
			GLenum(image.Type()),
			image.RawData()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a one dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage1D}
	 */
	void SubImage1D(
		GLint level,
		GLint xoffs,
		GLsizei width,
		PixelDataFormat format,
		PixelDataType type,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage1DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			width,
			GLenum(format),
			GLenum(type),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a two dimensional texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{TexSubImage1D}
	 */
	void SubImage1D(
		const images::Image& image,
		GLint xoffs,
		GLint level = 0
	)
	{
		OGLPLUS_GLFUNC(TextureSubImage1DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			image.Width(),
			GLenum(image.Format()),
			GLenum(image.Type()),
			image.RawData()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureSubImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Copies a two dimensional texture image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexImage2D}
	 */
	void CopyImage2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height,
		GLint border
	)
	{
		OGLPLUS_GLFUNC(CopyTextureImage2DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			x,
			y,
			width,
			height,
			border
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Copies a one dimensional texture image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexImage1D}
	 */
	void CopyImage1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLint x,
		GLint y,
		GLsizei width,
		GLint border
	)
	{
		OGLPLUS_GLFUNC(CopyTextureImage1DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			x,
			y,
			width,
			border
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Copies a three dimensional texture sub image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexSubImage3D}
	 */
	void CopySubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(CopyTextureSubImage3DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			zoffs,
			x,
			y,
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureSubImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Copies a two dimensional texture sub image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexSubImage2D}
	 */
	void CopySubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(CopyTextureSubImage2DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			x,
			y,
			width,
			height
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureSubImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Copies a one dimensional texture sub image from the framebuffer
	/**
	 *  @glsymbols
	 *  @glfunref{CopyTexSubImage1D}
	 */
	void CopySubImage1D(
		GLint level,
		GLint xoffs,
		GLint x,
		GLint y,
		GLsizei width
	)
	{
		OGLPLUS_GLFUNC(CopyTextureSubImage1DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			x,
			y,
			width
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CopyTextureSubImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a three dimensional compressed texture image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexImage3D}
	 */
	void CompressedImage3D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLint border,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureImage3DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			height,
			depth,
			border,
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a two dimensional compressed texture image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexImage2D}
	 */
	void CompressedImage2D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLsizei height,
		GLint border,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureImage2DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			height,
			border,
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a one dimensional compressed texture image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexImage1D}
	 */
	void CompressedImage1D(
		GLint level,
		PixelDataInternalFormat internal_format,
		GLsizei width,
		GLint border,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureImage1DEXT)(
			_name,
			GLenum(target),
			level,
			GLint(internal_format),
			width,
			border,
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a three dimensional compressed texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexSubImage3D}
	 */
	void CompressedSubImage3D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLint zoffs,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		PixelDataFormat format,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureSubImage3DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			zoffs,
			width,
			height,
			depth,
			GLint(format),
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureSubImage3DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a two dimensional compressed texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexSubImage2D}
	 */
	void CompressedSubImage2D(
		GLint level,
		GLint xoffs,
		GLint yoffs,
		GLsizei width,
		GLsizei height,
		PixelDataFormat format,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureSubImage2DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			yoffs,
			width,
			height,
			GLint(format),
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureSubImage2DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Specifies a one dimensional compressed texture sub image
	/**
	 *  @glsymbols
	 *  @glfunref{CompressedTexSubImage1D}
	 */
	void CompressedSubImage1D(
		GLint level,
		GLint xoffs,
		GLsizei width,
		PixelDataFormat format,
		GLsizei image_size,
		const void* data
	)
	{
		OGLPLUS_GLFUNC(CompressedTextureSubImage1DEXT)(
			_name,
			GLenum(target),
			level,
			xoffs,
			width,
			GLint(format),
			image_size,
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompressedTextureSubImage1DEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1
	/// Assigns a buffer storing the texel data to the texture
	/**
	 *  @glverreq{3,1}
	 *  @glsymbols
	 *  @glfunref{TexBuffer}
	 */
	void Buffer(
		PixelDataInternalFormat internal_format,
		const BufferOps& buffer
	)
	{
		OGLPLUS_GLFUNC(TextureBufferEXT)(
			_name,
			GLenum(target),
			GLenum(internal_format),
			FriendOf<BufferOps>::GetName(buffer)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureBufferEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY ||GL_VERSION_4_3 ||GL_ARB_texture_view
	/// References and reinteprets a subset of the data of another texture
	/**
	 *  @glvoereq{4,3,ARB,texture_view}
	 *  @glsymbols
	 *  @glfunref{TextureView}
	 */
	void View(
		const DSATextureEXTOps& orig_texture,
		PixelDataInternalFormat internal_format,
		GLuint min_level,
		GLuint num_levels,
		GLuint min_layer,
		GLuint num_layers
	)
	{
		OGLPLUS_GLFUNC(TextureView)(
			_name,
			GLenum(target),
			orig_texture._name,
			GLenum(internal_format),
			min_level,
			num_levels,
			min_layer,
			num_layers
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureView,
			Texture,
			EnumValueName(target),
			_name
		));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY ||GL_VERSION_4_2 ||GL_ARB_shader_image_load_store
	/// Binds a @p level of this texture to an image @p unit
	/**
	 *  @glvoereq{4,2,ARB,shader_image_load_store}
	 *  @glsymbols
	 *  @glfunref{BindImageTexture}
	 */
	void BindImage(
		ImageUnitSelector unit,
		GLint level,
		bool layered,
		GLint layer,
		AccessSpecifier access,
		ImageUnitFormat format
	)
	{
		OGLPLUS_GLFUNC(BindImageTexture)(
			GLuint(unit),
			_name,
			level,
			layered? GL_TRUE : GL_FALSE,
			layer,
			GLenum(access),
			GLenum(format)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			BindImageTexture,
			Texture,
			nullptr,
			_name
		));
	}
#endif

	/// Returns the texture base level (TEXTURE_BASE_LEVEL)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BASE_LEVEL}
	 */
	GLuint BaseLevel(void) const
	{
		return GetIntParam(GL_TEXTURE_BASE_LEVEL);
	}

	/// Sets the texture base level (TEXTURE_BASE_LEVEL)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BASE_LEVEL}
	 */
	void BaseLevel(GLuint level)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BASE_LEVEL,
			level
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	Vector<GLfloat, 4> BorderColor(TypeTag<GLfloat>) const
	{
		GLfloat result[4];
		OGLPLUS_GLFUNC(GetTextureParameterfvEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterfvEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return Vector<GLfloat, 4>(result, 4);
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	void BorderColor(Vector<GLfloat, 4> color)
	{
		OGLPLUS_GLFUNC(TextureParameterfvEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterfvEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	Vector<GLint, 4> BorderColor(TypeTag<GLint>) const
	{
		GLint result[4];
		OGLPLUS_GLFUNC(GetTextureParameterIivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterIivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return Vector<GLint, 4>(result, 4);
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	void BorderColor(Vector<GLint, 4> color)
	{
		OGLPLUS_GLFUNC(TextureParameterIivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterIivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	Vector<GLuint, 4> BorderColor(TypeTag<GLuint>) const
	{
		GLuint result[4];
		OGLPLUS_GLFUNC(GetTextureParameterIuivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			result
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTextureParameterIuivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
		return Vector<GLuint, 4>(result, 4);
	}

	/// Sets the texture border color (TEXTURE_BORDER_COLOR)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_BORDER_COLOR}
	 */
	void BorderColor(Vector<GLuint, 4> color)
	{
		OGLPLUS_GLFUNC(TextureParameterIuivEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_BORDER_COLOR,
			Data(color)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterIuivEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets the compare mode (TEXTURE_COMPARE_MODE)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_COMPARE_MODE}
	 */
	TextureCompareMode CompareMode(void) const
	{
		return TextureCompareMode(GetIntParam(
			GL_TEXTURE_COMPARE_MODE
		));
	}

	/// Sets the compare mode (TEXTURE_COMPARE_MODE)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_COMPARE_MODE}
	 */
	void CompareMode(TextureCompareMode mode)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_COMPARE_MODE,
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Sets the compare function (TEXTURE_COMPARE_FUNC)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_COMPARE_FUNC}
	 */
	CompareFunction CompareFunc(void) const
	{
		return CompareFunction(GetIntParam(
			GL_TEXTURE_COMPARE_FUNC
		));
	}

	/// Sets the compare function (TEXTURE_COMPARE_FUNC)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_COMPARE_FUNC}
	 */
	void CompareFunc(CompareFunction func)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_COMPARE_FUNC,
			GLenum(func)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets the LOD bias value (TEXTURE_LOD_BIAS)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_LOD_BIAS}
	 */
	GLfloat LODBias(void) const
	{
		return GetFloatParam(GL_TEXTURE_LOD_BIAS);
	}

	/// Sets the LOD bias value (TEXTURE_LOD_BIAS)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_LOD_BIAS}
	 */
	void LODBias(GLfloat value)
	{
		OGLPLUS_GLFUNC(TextureParameterfEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_LOD_BIAS,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterfEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets the magnification filter (TEXTURE_MAG_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MAG_FILTER}
	 */
	TextureMagFilter MagFilter(void) const
	{
		return TextureMagFilter(GetIntParam(
			GL_TEXTURE_MAG_FILTER
		));
	}

	/// Sets the magnification filter (TEXTURE_MAG_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MAG_FILTER}
	 */
	void MagFilter(TextureMagFilter filter)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MAG_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets the minification filter (TEXTURE_MIN_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MIN_FILTER}
	 */
	TextureMinFilter MinFilter(void) const
	{
		return TextureMinFilter(GetIntParam(
			GL_TEXTURE_MIN_FILTER
		));
	}

	/// Sets the minification filter (TEXTURE_MIN_FILTER)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MIN_FILTER}
	 */
	void MinFilter(TextureMinFilter filter)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MIN_FILTER,
			GLenum(filter)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets minimal LOD value (TEXTURE_MIN_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MIN_LOD}
	 */
	GLfloat MinLOD(void) const
	{
		return GetFloatParam(GL_TEXTURE_MIN_LOD);
	}

	/// Sets minimal LOD value (TEXTURE_MIN_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MIN_LOD}
	 */
	void MinLOD(GLfloat value)
	{
		OGLPLUS_GLFUNC(TextureParameterfEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MIN_LOD,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterfEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets maximum LOD value (TEXTURE_MAX_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MAX_LOD}
	 */
	GLfloat MaxLOD(void) const
	{
		return GetFloatParam(GL_TEXTURE_MAX_LOD);
	}

	/// Sets maximum LOD value (TEXTURE_MAX_LOD)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MAX_LOD}
	 */
	void MaxLOD(GLfloat value)
	{
		OGLPLUS_GLFUNC(TextureParameterfEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MAX_LOD,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterfEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets maximum level value (TEXTURE_MAX_LEVEL)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MAX_LEVEL}
	 */
	GLint MaxLevel(void) const
	{
		return GetIntParam(GL_TEXTURE_MAX_LEVEL);
	}

	/// Sets maximum level value (TEXTURE_MAX_LEVEL)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MAX_LEVEL}
	 */
	void MaxLevel(GLint value)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MAX_LEVEL,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets the maximum anisotropy level
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{MAX_TEXTURE_MAX_ANISOTROPY_EXT}
	 */
	GLfloat MaxAnisotropy(void) const
	{
#ifdef  GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
		return GetFloatParam(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT);
#else
		return Glfloat(1);
#endif
	}

	/// Gets the current anisotropy level
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_MAX_ANISOTROPY_EXT}
	 */
	GLfloat Anisotropy(void) const
	{
#ifdef  GL_TEXTURE_MAX_ANISOTROPY_EXT
		return GetFloatParam(GL_TEXTURE_MAX_ANISOTROPY_EXT);
#else
		return Glfloat(1);
#endif
	}

	/// Sets the anisotropy level
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_MAX_ANISOTROPY_EXT}
	 */
	void Anisotropy(GLfloat value)
	{
#ifdef  GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
		OGLPLUS_GLFUNC(TextureParameterfEXT)(
			_name,
			GLenum(target),
			GL_TEXTURE_MAX_ANISOTROPY_EXT,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameterfEXT,
			Texture,
			EnumValueName(target),
			_name
		));
#else
		OGLPLUS_FAKE_USE(value);
#endif
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_3 || GL_ARB_texture_swizzle
	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_*)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 */
	TextureSwizzle Swizzle(TextureSwizzleCoord coord) const
	{
		return TextureSwizzle(GetIntParam(
			GLenum(coord)
		));
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_*)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 */
	void Swizzle(
		TextureSwizzleCoord coord,
		TextureSwizzle mode
	)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GLenum(coord),
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_R)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_R}
	 */
	TextureSwizzle SwizzleR(void) const
	{
		return Swizzle(TextureSwizzleCoord::R);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_R)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_R}
	 */
	void SwizzleR(TextureSwizzle mode)
	{
		Swizzle(TextureSwizzleCoord::R, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_G)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_G}
	 */
	TextureSwizzle SwizzleG(void) const
	{
		return Swizzle(TextureSwizzleCoord::G);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_G)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_G}
	 */
	void SwizzleG(TextureSwizzle mode)
	{
		Swizzle(TextureSwizzleCoord::G, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_B)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_B}
	 */
	TextureSwizzle SwizzleB(void) const
	{
		return Swizzle(TextureSwizzleCoord::B);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_B)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_B}
	 */
	void SwizzleB(TextureSwizzle mode)
	{
		Swizzle(TextureSwizzleCoord::B, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_A)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_A}
	 */
	TextureSwizzle SwizzleA(void) const
	{
		return Swizzle(TextureSwizzleCoord::A);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_A)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_A}
	 */
	void SwizzleA(TextureSwizzle mode)
	{
		Swizzle(TextureSwizzleCoord::A, mode);
	}

	/// Gets the swizzle parameter (TEXTURE_SWIZZLE_RGBA)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_RGBA}
	 */
	TextureSwizzle SwizzleRGBA(void) const
	{
		return Swizzle(TextureSwizzleCoord::RGBA);
	}

	/// Sets the swizzle parameter (TEXTURE_SWIZZLE_RGBA)
	/**
	 *  @glvoereq{3,3,ARB,texture_swizzle}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_SWIZZLE_RGBA}
	 */
	void SwizzleRGBA(TextureSwizzle mode)
	{
		Swizzle(TextureSwizzleCoord::RGBA, mode);
	}
#endif // texture swizzle

	/// Gets the wrap parameter (TEXTURE_WRAP_*)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 */
	TextureWrap Wrap(TextureWrapCoord coord) const
	{
		return TextureWrap(GetIntParam(GLenum(coord)));
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_*)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 */
	void Wrap(
		TextureWrapCoord coord,
		TextureWrap mode
	)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GLenum(coord),
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	/// Gets the wrap parameter (TEXTURE_WRAP_S)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_WRAP_S}
	 */
	TextureWrap WrapS(void) const
	{
		return Wrap(TextureWrapCoord::S);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_S)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_WRAP_S}
	 */
	void WrapS(TextureWrap mode)
	{
		Wrap(TextureWrapCoord::S, mode);
	}

	/// Gets the wrap parameter (TEXTURE_WRAP_T)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_WRAP_T}
	 */
	TextureWrap WrapT(void) const
	{
		return Wrap(TextureWrapCoord::T);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_T)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_WRAP_T}
	 */
	void WrapT(TextureWrap mode)
	{
		Wrap(TextureWrapCoord::T, mode);
	}

	/// Gets the wrap parameter (TEXTURE_WRAP_R)
	/**
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{TEXTURE_WRAP_R}
	 */
	TextureWrap WrapR(void) const
	{
		return Wrap(TextureWrapCoord::R);
	}

	/// Sets the wrap parameter (TEXTURE_WRAP_R)
	/**
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{TEXTURE_WRAP_R}
	 */
	void WrapR(TextureWrap mode)
	{
		Wrap(TextureWrapCoord::R, mode);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
	/// Gets the depth stencil mode parameter (DEPTH_STENCIL_TEXTURE_MODE)
	/**
	 *  @glverreq{4,3}
	 *  @glsymbols
	 *  @glfunref{GetTexParameter}
	 *  @gldefref{DEPTH_STENCIL_TEXTURE_MODE}
	 */
	PixelDataFormat DepthStencilMode(void) const
	{
		return PixelDataFormat(GetIntParam(
			GL_DEPTH_STENCIL_TEXTURE_MODE
		));
	}

	/// Sets the swizzle parameter (DEPTH_STENCIL_TEXTURE_MODE)
	/**
	 *  @glverreq{4,3}
	 *  @glsymbols
	 *  @glfunref{TexParameter}
	 *  @gldefref{DEPTH_STENCIL_TEXTURE_MODE}
	 */
	void DepthStencilMode(PixelDataFormat mode)
	{
		OGLPLUS_GLFUNC(TextureParameteriEXT)(
			_name,
			GLenum(target),
			GL_DEPTH_STENCIL_TEXTURE_MODE,
			GLenum(mode)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			TextureParameteriEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}
#endif

	/// Generate mipmap for the texture bound to the specified target
	/**
	 *  @glsymbols
	 *  @glfunref{GenerateMipmap}
	 */
	void GenerateMipmap(void)
	{
		OGLPLUS_GLFUNC(GenerateTextureMipmapEXT)(
			_name,
			GLenum(target)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GenerateTextureMipmapEXT,
			Texture,
			EnumValueName(target),
			_name
		));
	}

	// Utility functions:

	/// Returns the target for the i-th cube map @p face (0-5)
	/** This functions returns one of the values for cube map faces
	 *  from the Target enumeration. The value of @p face must
	 *  be between 0 and 5 with the following meaning:
	 *  0 = Target::CubeMapPositiveX,
	 *  1 = Target::CubeMapNegativeX,
	 *  2 = Target::CubeMapPositiveY,
	 *  3 = Target::CubeMapNegativeY,
	 *  4 = Target::CubeMapPositiveZ,
	 *  5 = Target::CubeMapNegativeZ.
	 */
	static Target CubeMapFace(GLuint face)
	{
		assert(face <= 5);
		return Target(GL_TEXTURE_CUBE_MAP_POSITIVE_X+face);
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL DSA texture functionality
/**
 *  @ingroup oglplus_objects
 */
class DSATextureEXT
 : public DSATextureEXTOps
{ };
#else
typedef Object<DSATextureEXTOps> DSATextureEXT;

#endif

#endif // GL_EXT_direct_state_access

} // namespace oglplus

#endif // include guard
