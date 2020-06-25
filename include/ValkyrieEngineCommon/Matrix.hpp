#include "ValkyrieEngine/ValkyrieDefs.hpp"
#include "ValkyrieEngineCommon/Vector.hpp"
#include <array>

namespace vlk
{
	/*!
	 * \brief Column-major 3x3 matrix.
	 * Used to store and apply transformations in 2d space
	 */
	class Matrix3
	{
		typedef std::array<Float, 3> colType;
		std::array<colType, 3> data;

		public:

		/*!
		 * \brief Creates a matrix with all values initialized to 0.0
		 */
		constexpr inline Matrix3() {}

		constexpr inline Matrix3(const Matrix3&) = default;
		constexpr inline Matrix3(Matrix3&&) = default;
		constexpr inline Matrix3& operator=(const Matrix3&) = default;
		constexpr inline Matrix3& operator=(Matrix3&&) = default;
		constexpr inline ~Matrix3() = default;

		/*!
		 * \brief Initialize individual values of a matrix
		 *
		 * \code
		 *
		 * //  |----|----|----|
		 * //  | x0 | x1 | x2 |
		 * //  |----|----|----|
		 * //  | y0 | y1 | y2 |
		 * //  |----|----|----|
		 * //  | z0 | z1 | z2 |
		 * //  |----|----|----|
		 *
		 * \endcode
		 */
		constexpr inline Matrix3(
			Float x0, Float y0, Float z0,
			Float x1, Float y1, Float z1,
			Float x2, Float y2, Float z2) :
			data { { {x0, y0, z0}, {x1, y1, z1}, {x2, y2, z1} } }
		{ };

		/*!
		 * \brief Initialize a matrix with three Vector3
		 * \param v0 The first column of the matrix
		 * \param v1 The second column of the matrix
		 * \param v2 The third column of the matrix
		 */
		constexpr inline Matrix3(
			Vector3 v0,
			Vector3 v1,
			Vector3 v2) :
			data { { {v0.x, v0.y, v0.z}, {v1.x, v1.y, v1.z}, {v2.x, v2.y, v2.z}} }
		{ };

		constexpr inline std::array<Float, 3>& operator[](Size s) { return data[s]; }
		constexpr inline const std::array<Float, 3>& operator[](Size s) const { return data[s]; }

		/*!
		 * \brief Performs an addition to every cell of a matrix
		 *
		 * \code
		 *
		 * m = m + 3.0f;
		 *
		 * //  Before:           After:
		 * //  |---|---|---|     |---|---|---|
		 * //  |1.0|0.0|0.0|     |4.0|3.0|3.0|
		 * //  |---|---|---|     |---|---|---|
		 * //  |0.0|1.0|0.0|  -> |3.0|4.0|3.0|
		 * //  |---|---|---|     |---|---|---|
		 * //  |0.0|0.0|1.0|     |3.0|3.0|4.0|
		 * //  |---|---|---|     |---|---|---|
		 *
		 * \endcode
		 */
		constexpr inline Matrix3 operator+(const Float f) const
		{
			return Matrix3(
				data[0][0] + f, data[0][1] + f, data[0][2] + f,
				data[1][0] + f, data[1][1] + f, data[1][2] + f,
				data[2][0] + f, data[2][1] + f, data[2][2] + f);
		}

		/*!
		 * \brief Performs a subtraction to every cell of a matrix
		 *
		 * \code
		 *
		 * m = m - 3.0f;
		 *
		 * //  Before:           After:
		 * //  |---|---|---|     |----|----|----|
		 * //  |1.0|0.0|0.0|     |-2.0|-3.0|-3.0|
		 * //  |---|---|---|     |----|----|----|
		 * //  |0.0|1.0|0.0|  -> |-3.0|-2.0|-3.0|
		 * //  |---|---|---|     |----|----|----|
		 * //  |0.0|0.0|1.0|     |-3.0|-3.0|-2.0|
		 * //  |---|---|---|     |----|----|----|
		 *
		 * \endcode
		 */
		constexpr inline Matrix3 operator-(const Float f) const
		{
			return Matrix3(
				data[0][0] - f, data[0][1] - f, data[0][2] - f,
				data[1][0] - f, data[1][1] - f, data[1][2] - f,
				data[2][0] - f, data[2][1] - f, data[2][2] - f);
		}

		/*!
		 * \brief Performs a scalar multiplication to every cell of a matrix
		 *
		 * \code
		 *
		 * m = m * 3.0f;
		 *
		 * //  Before:           After:
		 * //  |---|---|---|     |---|---|---|
		 * //  |1.0|0.0|0.0|     |3.0|0.0|0.0|
		 * //  |---|---|---|     |---|---|---|
		 * //  |0.0|1.0|0.0|  -> |0.0|3.0|0.0|
		 * //  |---|---|---|     |---|---|---|
		 * //  |0.0|0.0|1.0|     |0.0|0.0|3.0|
		 * //  |---|---|---|     |---|---|---|
		 *
		 * \endcode
		 */
		constexpr inline Matrix3 operator*(const Float f) const
		{
			return Matrix3(
				data[0][0] * f, data[0][1] * f, data[0][2] * f,
				data[1][0] * f, data[1][1] * f, data[1][2] * f,
				data[2][0] * f, data[2][1] * f, data[2][2] * f);
		}

		/*!
		 * \brief Performs a scalar division to every cell of a matrix
		 *
		 * \code
		 *
		 * m = m / 2.0f;
		 *
		 * //  Before:           After:
		 * //  |---|---|---|     |---|---|---|
		 * //  |1.0|0.0|0.0|     |0.5|0.0|0.0|
		 * //  |---|---|---|     |---|---|---|
		 * //  |0.0|1.0|0.0|  -> |0.0|0.5|0.0|
		 * //  |---|---|---|     |---|---|---|
		 * //  |0.0|0.0|1.0|     |0.0|0.0|0.5|
		 * //  |---|---|---|     |---|---|---|
		 *
		 * \endcode
		 */
		constexpr inline Matrix3 operator/(const Float f) const
		{
			return Matrix3(
				data[0][0] / f, data[0][1] / f, data[0][2] / f,
				data[1][0] / f, data[1][1] / f, data[1][2] / f,
				data[2][0] / f, data[2][1] / f, data[2][2] / f);
		}

		constexpr inline Matrix3 operator+(const Matrix3& rhs) const
		{
			return Matrix3(
				data[0][0] + rhs[0][0], data[0][1] + rhs[0][1], data[0][2] + rhs[0][2],
				data[1][0] + rhs[1][0], data[1][1] + rhs[1][1], data[1][2] + rhs[1][2],
				data[2][0] + rhs[2][0], data[2][1] + rhs[2][1], data[2][2] + rhs[2][2]);
		}

		constexpr inline Matrix3 operator-(const Matrix3& rhs) const
		{
			return Matrix3(
				data[0][0] - rhs[0][0], data[0][1] - rhs[0][1], data[0][2] - rhs[0][2],
				data[1][0] - rhs[1][0], data[1][1] - rhs[1][1], data[1][2] - rhs[1][2],
				data[2][0] - rhs[2][0], data[2][1] - rhs[2][1], data[2][2] - rhs[2][2]);
		}

		//Multiply functions are bloody MASSIVE, are we sure these should be inline?

		/*!
		 * \brief multiplies two matricies
		 */
		constexpr inline Matrix3 operator*(const Matrix3& rhs) const
		{
			Matrix3 result;

			result[0][0] = data[0][0] * rhs[0][0] + data[1][0] * rhs[0][1] + data[2][0] * rhs[0][2];
			result[0][1] = data[0][1] * rhs[0][0] + data[1][1] * rhs[0][1] + data[2][1] * rhs[0][2];
			result[0][2] = data[0][2] * rhs[0][0] + data[1][2] * rhs[0][1] + data[2][2] * rhs[0][2];
			result[1][0] = data[0][0] * rhs[1][0] + data[1][0] * rhs[1][1] + data[2][0] * rhs[1][2];
			result[1][1] = data[0][1] * rhs[1][0] + data[1][1] * rhs[1][1] + data[2][1] * rhs[1][2];
			result[1][2] = data[0][2] * rhs[1][0] + data[1][2] * rhs[1][1] + data[2][2] * rhs[1][2];
			result[2][0] = data[0][0] * rhs[2][0] + data[1][0] * rhs[2][1] + data[2][0] * rhs[2][2];
			result[2][1] = data[0][1] * rhs[2][0] + data[1][1] * rhs[2][1] + data[2][1] * rhs[2][2];
			result[2][2] = data[0][2] * rhs[2][0] + data[1][2] * rhs[2][1] + data[2][2] * rhs[2][2];

			return result;
		}

		/*!
		 * \brief Returns the inverse of this matrix so that \code m * !m \endcode is an identity matrix
		 */
		constexpr inline Matrix3 operator!() const
		{
			return *this * (1 / Determinant());
		}

		constexpr inline Float Determinant() const
		{
			return	data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2]) -
					data[1][0] * (data[0][1] * data[2][2] - data[2][1] * data[0][2]) +
					data[2][0] * (data[0][1] * data[1][2] - data[1][1] * data[0][2]);
		}
		
		constexpr inline bool operator==(const Matrix3& rhs) const
		{
			return	data[0][0] == rhs[0][0] && data[0][1] == rhs[0][1] && data[0][2] == rhs[0][2] &&
					data[1][0] == rhs[1][0] && data[1][1] == rhs[1][1] && data[1][2] == rhs[1][2] &&
					data[2][0] == rhs[2][0] && data[2][1] == rhs[2][1] && data[2][2] == rhs[2][2];
		}

		constexpr inline bool operator!=(const Matrix3& rhs) const
		{
			return	data[0][0] != rhs[0][0] || data[0][1] != rhs[0][1] || data[0][2] != rhs[0][2] ||
					data[1][0] != rhs[1][0] || data[1][1] != rhs[1][1] || data[1][2] != rhs[1][2] ||
					data[2][0] != rhs[2][0] || data[2][1] != rhs[2][1] || data[2][2] != rhs[2][2];
		}

		/*!
		 * \brief Translates this matrix by a given vector
		 * \return A reference to \c this
		 */
		constexpr inline Matrix3& Translate(const Vector2& v)
		{
			data[2][0] += v.x;
			data[2][1] += v.y;
			return *this;
		}

		/*!
		 * \brief Translates this matrix parallel to the x-axis by the given amount
		 * \return A reference to \c this 
		 */
		constexpr inline Matrix3& TranslateX(Float amount)
		{
			data[2][0] += amount;
			return *this;
		}

		/*!
		 * \brief Translates this matrix paralell to the y-axis by the given amount
		 * \return A reference to \c this
		 */
		constexpr inline Matrix3& TranslateY(Float amount)
		{
			data[2][1] += amount;
			return *this;
		}

		/*!
		 * \brief Scales this matrix by the given vector
		 * \return A reference to \c this
		 */
		constexpr inline Matrix3& Scale(const Vector2& v)
		{
			data[0][0] *= v.x;
			data[1][1] *= v.y;
			return *this;
		}

		/*!
		 * \brief Scales this matrix paralell to the x-axis by the given amount
		 * \return A reference to \c this
		 */
		constexpr inline Matrix3& ScaleX(const Float amount)
		{
			data[0][0] *= amount;
			return *this;
		}

		/*!
		 * \brief Scales this matrix paralell to the y-axis by the given amount
		 * \return A reference to \c this
		 */
		constexpr inline Matrix3& ScaleY(const Float amount)
		{
			data[1][1] *= amount;
			return *this;
		}

		/*!
		 * \brief Reflects this matrix about the X-axis
		 * \return A reference to \c this
		 */
		constexpr inline Matrix3& ReflectX()
		{
			data[1][1] *= -1.0f;
			return *this;
		}

		/*!
		 * \brief Reflects this matrix about the Y-axis
		 * \return A reference to \c this
		 */
		constexpr inline Matrix3& ReflectY()
		{
			data[0][0] *= -1.0f;
			return *this;
		}

		/*!
		 * \brief Creates an identity matrix
		 *
		 *
		 */
		static constexpr inline Matrix3 Identity()
		{
			return Matrix3(
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f);
		}

		/*! 
		 * \brief Creates a matrix equivelant to the translation represented by \c v
		 */
		static constexpr inline Matrix3 Translation(const Vector2& v)
		{
			return Matrix3(
				1.0f, 0.0f, v.x,
				0.0f, 1.0f, v.y,
				0.0f, 0.0f, 1.0f);
		}
	};

	class Matrix4
	{

	};
}
