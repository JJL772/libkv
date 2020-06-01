/*
 *
 * dmx.h
 *
 * Data Model eXchange format used by Source 1 and Source 2. Also known as "KeyValues2".
 * Support for both binary and text formats is planned.
 *
 */
#pragma once

#include <string>
#include <vector>

/*
 * Native DMX Types.
 * These cant currently be exchanged by anythings. I will think up a system for this in the future.
 *
 */

namespace libkv
{
	struct ElementId
	{
		union {
			std::uint8_t u8[16];
			std::uint16_t u16[8];
			std::uint32_t u32[4];
			std::uint64_t u64[2];
		};
	};

	struct Vector2
	{
		float x,y;

		float X() const { return x; };
		float Y() const { return y; };

		void SetX(float f) { x = f; };
		void SetY(float f) { y = f; };
	};

	struct Vector3
	{
		float x,y,z;

		float X() const { return x; };
		float Y() const { return y; };
		float Z() const { return z; };

		void SetX(float f) { x = f; };
		void SetY(float f) { y = f; };
		void SetZ(float f) { z = f; };
	};

	struct Vector4
	{
		float x,y,z,m;

		float X() const { return x; };
		float Y() const { return y; };
		float Z() const { return z; };
		float M() const { return m; };

		void SetX(float f) { x = f; };
		void SetY(float f) { y = f; };
		void SetZ(float f) { z = f; };
		void SetM(float f) { m = f; };
	};

	struct QAngle
	{
		float pitch, yaw, roll;

		float Pitch() const { return pitch; };
		float Yaw() const { return yaw; };
		float Roll() const { return roll; }

		void SetPitch(float f) { pitch = f; };
		void SetYaw(float f) { yaw = f; };
		void SetRoll(float f) { roll = f; };
	};

	struct Color
	{
		unsigned char r, g, b, a;

		unsigned char R() const { return r; };
		unsigned char G() const { return g; };
		unsigned char B() const { return b; };
		unsigned char A() const { return a; };

		void SetR(unsigned char c) { r = c; };
		void SetG(unsigned char c) { g = c; };
		void SetB(unsigned char c) { b = c; };
		void SetA(unsigned char c) { a = c; };
	};

	/* Basic types */
	using DmxBool = bool;
	using DmxInt = int;
	using DmxInt16 = std::int16_t;
	using DmxUInt16 = std::uint16_t;
	using DmxInt32 = std::int32_t;
	using DmxUInt32 = std::uint32_t;
	using DmxInt64 = std::int64_t;
	using DmxUInt64 = std::uint64_t;
	using DmxFloat = float;
	using DmxDouble = double;
	using DmxString = std::string;
	using DmxElementId = ElementId;

	/* Slightly more complex types */
	using DmxVector3 = Vector3;
	using DmxQAngle = QAngle;
	using DmxColor = Color;
	using DmxVector2 = Vector2;
	using DmxVector4 = Vector4;

	/* Array types */
	using DmxIntArray = std::vector<DmxInt>;
	using DmxStringArray = std::vector<DmxString>;
	using DmxVector3Array = std::vector<DmxVector3>;
	using DmxVector2Array = std::vector<DmxVector2>;
	using DmxColorArray = std::vector<DmxColor>;
	using DmxFloatArray = std::vector<DmxFloat>;
	using DmxVector4Array = std::vector<DmxVector4>;
}
