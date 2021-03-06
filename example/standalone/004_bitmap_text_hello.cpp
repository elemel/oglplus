/**
 *  @example standalone/004_bitmap_text_hello.cpp
 *  @brief Shows the usage of OGLplus' text rendering utilities
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "glut_glew_example.hpp"

#include <oglplus/all.hpp>
#include <oglplus/images/png.hpp>

#include <oglplus/text/bitmap_glyph.hpp>


class BitmapGlyphExample
 : public oglplus::StandaloneExample
{
private:
	oglplus::Context gl;

	typedef oglplus::text::BitmapGlyphRendering TextRendering;

	TextRendering tr;

	TextRendering::Font font;

	TextRendering::Layout layout;

	TextRendering::Renderer rndr;

	oglplus::ProgramUniform<oglplus::Vec3f> rndr_color;
	oglplus::ProgramUniform<GLfloat> rndr_opacity;

	int prev_interval;
	std::size_t current_line;
public:
	BitmapGlyphExample(int argc, const char** argv)
	 : gl()
	 , tr(0, 1, 2)
	 , font(tr.LoadFont((argc>1)?argv[1]:"Sans"))
	 , layout(tr.MakeLayout(font, 128))
	 , rndr(tr.GetRenderer(
			oglplus::FragmentShader(
				oglplus::ObjectDesc("Pixel color"),
				oglplus::StrLit("#version 330\n"
				"uniform vec3 Color;"
				"uniform float Opacity;"
				"vec4 PixelColor("
				"	vec4 TexelColor,"
				"	vec3 GlyphPosition,"
				"	float GlyphXOffset,"
				"	vec2 GlyphExtent,"
				"	vec2 GlyphCoord,"
				"	float LayoutWidth"
				")"
				"{"
				"	return vec4(Color, TexelColor.r*Opacity);"
				"}")
			)
		)
	), rndr_color(rndr.GetUniform<oglplus::Vec3f>("Color"))
	 , rndr_opacity(rndr.GetUniform<GLfloat>("Opacity"))
	 , prev_interval(-1)
	 , current_line(0)
	{
		using namespace oglplus;

		rndr.Use();

		gl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		gl.Enable(Capability::Blend);
		gl.BlendFunc(
			BlendFunction::SrcAlpha,
			BlendFunction::DstAlpha
		);

		rndr.SetAlignment(text::Alignment::Center);
	}

	void LoadNext(void)
	{
		typedef oglplus::text::Direction Dir;
		struct {
			Dir direction;
			const char* text;
		} lines[] = {
			{Dir::LeftToRight, u8"Hello world"},
			{Dir::LeftToRight, u8"Nazdar svet"},
			{Dir::LeftToRight, u8"Γεια σας κόσμο"},
			{Dir::LeftToRight, u8"Привет мир"},
			{Dir::LeftToRight, u8"Witaj świecie"},
			{Dir::LeftToRight, u8"Здравей свят"},
			{Dir::LeftToRight, u8"Ahoj světe"},
			{Dir::LeftToRight, u8"Moi maailma"},
			{Dir::LeftToRight, u8"Bonjour tout le monde"},
			{Dir::LeftToRight, u8"Hallo welt"},
			{Dir::LeftToRight, u8"Բարեւ աշխարհ"},
			{Dir::LeftToRight, u8"Hej världen"},
			{Dir::LeftToRight, u8"Прывітанне свет"},
			{Dir::LeftToRight, u8"Olá mundo"},
			{Dir::LeftToRight, u8"Здраво свете"},
			{Dir::LeftToRight, u8"Zdravo svet"},
			{Dir::LeftToRight, u8"Hola mundo"},
			{Dir::LeftToRight, u8"Merhaba dünya"},
			{Dir::LeftToRight, u8"Привіт світ"},
			{Dir::LeftToRight, u8"Pozdrav svijetu"},
			{Dir::LeftToRight, u8"Hello világ"},
			{Dir::RightToLeft, u8"مرحبا العالم"},
			{Dir::LeftToRight, u8"Ciao mondo"},
			{Dir::LeftToRight, u8"Здраво светот"},
			{Dir::RightToLeft, u8"שלום עולם"},
			{Dir::LeftToRight, u8"Hei verden"}
		};
		const std::size_t line_count = sizeof(lines)/sizeof(lines[0]);

		layout.Set(lines[current_line].text);

		rndr.SetDirection(lines[current_line].direction);
		rndr_color.Set(
			0.1f+GLfloat(0.8f*std::rand())/RAND_MAX,
			0.3f+GLfloat(0.7f*std::rand())/RAND_MAX,
			0.1f+GLfloat(0.8f*std::rand())/RAND_MAX
		);

		if(++current_line >= line_count)
			current_line = 0;
	}

	void Reshape(void)
	{
		using namespace oglplus;

		gl.Viewport(Width(), Height());

		rndr.SetProjection(
			CamMatrixf::PerspectiveX(
				Degrees(60),
				Width()/Height(),
				1, 60
			)
		);
	}

	void Render(void)
	{
		using namespace oglplus;

		GLfloat t = GLfloat(FrameTime());
		GLfloat i = t*0.3f;
		int interval = int(i);
		GLfloat f = i - GLfloat(interval);
		if(prev_interval < interval)
		{
			LoadNext();
			prev_interval = interval;
		}

		gl.Clear().ColorBuffer().DoIt();

		rndr_opacity.Set(SineWave(f*0.5f));

		rndr.SetLayoutTransform(ModelMatrixf::TranslationZ(-20.0f+16.0f*f));
		rndr.Render(layout);
	}
};

int main(int argc, char* argv[])
{
	return oglplus::GlutGlewMain<BitmapGlyphExample>(
		"Example of usage of OGLplus' bitmap glyph text rendering",
		argc, argv
	);
}

