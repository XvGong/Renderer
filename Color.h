#pragma once

class Color {
	using BYTE = unsigned char;
	using DWORD = unsigned long;
public:

	Color() = default;

	Color(float r, float g, float b, float a = 1.0f)
	{
		argb = DWORD((DWORD(BYTE(a * 0xff)) << 24) | (DWORD(BYTE(r * 0xff)) << 16) | (DWORD(BYTE(g * 0xff) << 8)) | (DWORD(BYTE(b * 0xff))));
	}

	Color(BYTE r, BYTE g, BYTE b, BYTE a = 0xff)
	{
		argb = DWORD((DWORD(a) << 24) | (DWORD(r) << 16) | (DWORD(g) << 8) | (DWORD(b)));
	}

	inline BYTE a()const {
		return BYTE((argb >> 24) & 0xff);
	}

	inline BYTE r()const {
		return BYTE((argb >> 16) & 0xff);
	}

	inline BYTE g()const {
		return BYTE((argb >> 8) & 0xff);
	}

	inline BYTE b()const {
		return BYTE(argb & 0xff);
	}

	DWORD abgr()const {
		return DWORD((DWORD(a()) << 24) | (DWORD(b()) << 16) | (DWORD(g()) << 8) | (DWORD(r())));
	}

	DWORD mix(const DWORD& bgr) {
		float alpha = static_cast<float>(a()) / 255;
		BYTE R = BYTE(r() * alpha) + BYTE((BYTE(bgr) & 0xff) * (1 - alpha));
		BYTE G = BYTE(g() * alpha) + BYTE((BYTE(bgr>>8) & 0xff) * (1 - alpha));
		BYTE B = BYTE(b() * alpha) + BYTE((BYTE(bgr>>16) & 0xff) * (1 - alpha));
		return DWORD(R | (G << 8) | (B << 16));
	}

private:
	DWORD argb = 0;
};