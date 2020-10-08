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
#include <type_traits>

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

	enum class EDmxType
	{
		BadType = 0,
		Bool,
		Int,
		Int16,
		UInt16,
		Int32,
		UInt32,
		Int64,
		UInt64,
		Float,
		Double,
		String,
		ElementId,
		Vector2,
		Vector3,
		Vector4,
		Color,
		QAngle,
		Array
	};

	template<class T>
	constexpr EDmxType TypeOfT()
	{
		if(std::is_same<T, DmxBool>::value) return EDmxType::Bool;
		else if(std::is_same<T, DmxInt>::value) return EDmxType::Int;
		else if(std::is_same<T, DmxInt16>::value) return EDmxType::Int16;
		else if(std::is_same<T, DmxUInt16>::value) return EDmxType::UInt16;
		else if(std::is_same<T, DmxInt32>::value) return EDmxType::Int32;
		else if(std::is_same<T, DmxUInt32>::value) return EDmxType::UInt32;
		else if(std::is_same<T, DmxInt64>::value) return EDmxType::Int64;
		else if(std::is_same<T, DmxUInt64>::value) return EDmxType::UInt64;
		else if(std::is_same<T, DmxFloat>::value) return EDmxType::Float;
		else if(std::is_same<T, DmxDouble>::value) return EDmxType::Double;
		else if(std::is_same<T, DmxString>::value) return EDmxType::String;
		else if(std::is_same<T, DmxElementId>::value) return EDmxType::ElementId;
		else if(std::is_same<T, DmxVector2>::value) return EDmxType::Vector2;
		else if(std::is_same<T, DmxVector3>::value) return EDmxType::Vector3;
		else if(std::is_same<T, DmxVector4>::value) return EDmxType::Vector4;
		else if(std::is_same<T, DmxQAngle>::value) return EDmxType::QAngle;
		else if(std::is_same<T, DmxColor>::value) return EDmxType::Color;
		return EDmxType::BadType;
	}

	class IDmxBaseElement
	{
	public:

		virtual EDmxType Type() const = 0;

		virtual bool IsArray() const { return false; }
	};

	template<class T>
	class CDmxElement : public IDmxBaseElement
	{
	protected:
		T m_value;
		EDmxType m_type;

		/* Defines all of the constructors */
		CDmxElement() :
			m_type(libkv::TypeOfT<T>())
		{

		}

	public:
		CDmxElement(const T& value) :
			CDmxElement()
		{
		}


		EDmxType Type() const override { return m_type; };

		const T& Value() const { return m_value; };
		T& Value() { return m_value; };

		void Set(const T& v) { m_value = v; }

		template<class _T>
		bool IsA(const _T& unused)
		{
			return m_type == TypeOfT<_T>();
		}

		template<class _T>
		bool IsA()
		{
			return m_type == TypeOfT<_T>();
		}
	};

	template<class T>
	class CDmxArray : public IDmxBaseElement
	{
	protected:
		EDmxType m_arrayType;
		std::vector<T> m_array;

		CDmxArray() :
			m_arrayType(libkv::TypeOfT<T>())
		{

		}

	public:
		explicit CDmxArray(size_t length) :
			CDmxArray(),
			m_array(length)
		{

		}

		explicit CDmxArray(std::initializer_list<T> list) :
			CDmxArray(),
			m_array(list)
		{

		}

		template<class _T>
		bool IsArrayOf(const _T& unused)
		{
			return m_arrayType == TypeOfT<_T>();
		}

		template<class _T>
		bool IsArrayOf()
		{
			return m_arrayType == TypeOfT<_T>();
		}

		EDmxType Type() const override { return m_arrayType; };

		bool IsArray() const override { return true; };
	};

	/* Array type definitions */
	using DmxBoolArray            = CDmxArray<DmxBool>;
	using DmxIntArray             = CDmxArray<DmxInt>;
	using DmxInt16Array           = CDmxArray<DmxInt16>;
	using DmxUInt16Array          = CDmxArray<DmxUInt16>;
	using DmxInt32Array           = CDmxArray<DmxInt32>;
	using DmxUInt32Array          = CDmxArray<DmxUInt32>;
	using DmxInt64Array           = CDmxArray<DmxInt64>;
	using DmxUInt64Array          = CDmxArray<DmxUInt64>;
	using DmxFloatArray           = CDmxArray<DmxFloat>;
	using DmxDoubleArray          = CDmxArray<DmxDouble>;
	using DmxStringArray          = CDmxArray<DmxString>;
	using DmxElementIdArray       = CDmxArray<DmxElementId>;
	using DmxVector3Array         = CDmxArray<DmxVector3>;
	using DmxQAngleArray          = CDmxArray<DmxQAngle>;
	using DmxColorArray           = CDmxArray<DmxColor>;
	using DmxVector2Array         = CDmxArray<DmxVector2>;
	using DmxVector4Array         = CDmxArray<DmxVector4>;
}
