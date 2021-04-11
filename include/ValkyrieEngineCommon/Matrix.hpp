#ifndef VLK_MATRIX_HPP
#define VLK_MATRIX_HPP

#include "ValkyrieEngine/ValkyrieDefs.hpp"
#include "ValkyrieEngineCommon/Vector.hpp"
#include "ValkyrieEngineCommon/Quaternion.hpp"
#include <limits>
#include <type_traits>

namespace vlk
{
	template <Size N, Size M, typename Val>
	class MatrixBase
	{
		public:
		typedef MatrixBase<N, M, Val> SelfType;
		typedef VectorBase<M, Val> ColType;
		typedef ColType DataType[N];
		DataType data;

		VLK_STATIC_ASSERT_MSG(std::is_arithmetic<Val>::value, "Val must be an arithmetic type");

		VLK_CXX14_CONSTEXPR inline MatrixBase<N, M, Val>()
		{
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					data[n][m] = 0.0;
				}
			}
		}

		VLK_CXX14_CONSTEXPR inline MatrixBase<N, M, Val>(const DataType& dat)
		{
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					data[n][m] = dat[n][m];
				}
			}
		}

		VLK_CXX14_CONSTEXPR inline MatrixBase<N, M, Val>(const SelfType&) = default;
		VLK_CXX14_CONSTEXPR inline MatrixBase<N, M, Val>(SelfType&&) = default;
		VLK_CXX14_CONSTEXPR inline SelfType& operator=(const SelfType&) = default;
		VLK_CXX14_CONSTEXPR inline SelfType& operator=(SelfType&&) = default;
		VLK_CXX20_CONSTEXPR inline ~MatrixBase<N, M, Val>() = default;

		VLK_CXX14_CONSTEXPR inline SelfType operator+(const SelfType& rhs) const
		{
			DataType tmp;
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					tmp[n][m] = data[n][m] + rhs[n][m];
				}
			}
			return SelfType(tmp);
		}

		VLK_CXX14_CONSTEXPR inline SelfType operator-(const SelfType& rhs) const
		{
			DataType tmp;
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					tmp[n][m] = data[n][m] - rhs[n][m];
				}
			}
			return SelfType(tmp);
		}

		VLK_CXX14_CONSTEXPR inline SelfType operator+(const Val& rhs) const
		{
			DataType tmp;
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					tmp[n][m] = data[n][m] + rhs;
				}
			}
			return SelfType(tmp);
		}

		VLK_CXX14_CONSTEXPR inline SelfType operator-(const Val& rhs) const
		{
			DataType tmp;
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					tmp[n][m] = data[n][m] - rhs;
				}
			}
			return SelfType(tmp);
		}

		VLK_CXX14_CONSTEXPR inline SelfType operator*(const Val& rhs) const
		{
			DataType tmp;
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					tmp[n][m] = data[n][m] * rhs;
				}
			}
			return SelfType(tmp);
		}

		VLK_CXX14_CONSTEXPR inline SelfType operator/(const Val& rhs) const
		{
			DataType tmp;
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					tmp[n][m] = data[n][m] / rhs;
				}
			}
			return SelfType(tmp);
		}

		VLK_CXX14_CONSTEXPR inline SelfType& operator+=(const SelfType& rhs)
		{
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					data[n][m] += rhs[n][m];
				}
			}
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline SelfType& operator-=(const SelfType& rhs)
		{
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					data[n][m] -= rhs[n][m];
				}
			}
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline SelfType& operator+=(const Val& rhs)
		{
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					data[n][m] += rhs;
				}
			}
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline SelfType& operator-=(const Val& rhs)
		{
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					data[n][m] -= rhs;
				}
			}
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline SelfType& operator*=(const Val& rhs)
		{
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					data[n][m] *= rhs;
				}
			}
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline SelfType& operator/=(const Val& rhs)
		{
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					data[n][m] /= rhs;
				}
			}
			return *this;
		}

		/*!
		 * \brief Matrix-matrix multiplication
		 */
		template <Size L>
		VLK_CXX14_CONSTEXPR inline MatrixBase<L, M, Val> operator*(const MatrixBase<L, N, Val>& rhs) const
		{
			MatrixBase<L, M, Val> tmp;
			for (Size n = 0; n < N; n++)
			{
				for (Size l = 0; l < L; l++)
				{
					//tmp[n][l] = 0.f;
					for (Size m = 0; m < M; m++)
					{
						tmp[l][m] += data[n][m] * rhs[l][n];
					}
				}
			}
			return tmp;
		}

		/*!
		 * \brief Matrix-vector multiplication
		 */
		VLK_CXX14_CONSTEXPR inline ColType operator*(const ColType& rhs) const
		{
			ColType col;
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					col[n] += rhs[m] * data[m][n];
				}
			}
			return col;

			/*
			return Vector3(
				data[0][0] * rhs[0] + data[1][0] * rhs[1] + data[2][0] * rhs[2],
				data[0][1] * rhs[0] + data[1][1] * rhs[1] + data[2][1] * rhs[2],
				data[0][2] * rhs[0] + data[1][2] * rhs[1] + data[2][2] * rhs[2]);*/
		}

		VLK_CXX14_CONSTEXPR inline bool operator==(const SelfType& rhs) const
		{
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					if (data[n][m] != rhs[n][m]) return false;
				}
			}

			return true;
		}

		VLK_CXX14_CONSTEXPR inline bool operator!=(const SelfType& rhs) const
		{
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					if (data[n][m] != rhs[n][m]) return true;
				}
			}

			return false;
		}

		VLK_CXX14_CONSTEXPR inline ColType* Data() { return data; }
		VLK_CXX14_CONSTEXPR inline const ColType* Data() const { return data; }

		VLK_CXX14_CONSTEXPR inline ColType& operator[](Size i) { return data[i]; }
		VLK_CXX14_CONSTEXPR inline const ColType& operator[](Size i) const { return data[i]; }

		//Variadic template at the beginning prevents default parmeters X and Y being
		//overriden by user.
		/*!
		 * \brief Returns the determinant of a matrix.
		 *
		 * Non-square matricies do not have a determinant defined and will return <tt>NaN</tt>.
		 */
		template <typename..., Size X = N, Size Y = M, std::enable_if_t<X != Y, Int> = 0>
		VLK_CXX14_CONSTEXPR inline Val Determinant() const 
		{
			return std::numeric_limits<Val>::signaling_NaN();
		}

		template <typename..., Size X = N, Size Y = M, std::enable_if_t<X == Y & X == 1, Int> = 1>
		VLK_CXX14_CONSTEXPR inline Val Determinant() const
		{
			return data[0][0];
		}

		template <typename..., Size X = N, Size Y = M, std::enable_if_t<X == Y & X == 2, Int> = 2>
		VLK_CXX14_CONSTEXPR inline Val Determinant() const
		{
			return data[0][0] * data[1][1] - data[0][1] * data[1][0];
		}

		template <typename..., Size X = N, Size Y = M, std::enable_if_t<(X == Y) & (X > 2), Int> = 3>
		VLK_CXX14_CONSTEXPR inline Val Determinant() const
		{
			VLK_CXX14_CONSTEXPR Size S = X;
			Val det = 0.0;
			Val mod = 1.0;

			for (Size n = 0; n < S; n++)
			{
				VectorBase<S - 1, Val> subMatrix[S - 1];
				Size x1 = 0;

				for (Size x = 0; x < S; x++)
				{
					//Ignore current column
					if (x == n) continue;

					for (Size y = 1; y < S; y++)
					{
						subMatrix[x1][y - 1] = data[x][y];
					}

					x1++;
				}

				//Recursive call to Determinant here
				det += mod * data[n][0] * MatrixBase<S - 1, S - 1, Val>(subMatrix).Determinant();

				//Mod is alternated between addition and subtraction every iteration
				mod *= static_cast<Val>(-1.0);
			}

			return det;
		}

		/*!
		 * \brief Returns the inverse of a matrix such that <tt>mat * mat.Inverse()</tt> is an identity matrix.
		 *
		 * Non-square matrices do not have an inverse and thus will return a NxM matrix of <tt>NaN</tt> values.
		 */
		template <typename..., Size X = N, Size Y = M, std::enable_if_t<X != Y, Int> = 0>
		VLK_CXX14_CONSTEXPR inline SelfType Inverse() const
		{
			SelfType mat;
			for (Size n = 0; n < N; n++)
			{
				for (Size m = 0; m < M; m++)
				{
					mat[n][m] = std::numeric_limits<Val>::signaling_NaN();
				}
			}
			return mat;
		}

		//1x1
		template <typename..., Size X = N, Size Y = M, std::enable_if_t<X == Y & X == 1, Int> = 1>
		VLK_CXX14_CONSTEXPR inline SelfType Inverse() const
		{
			return SelfType({VectorBase<1, Val>({1.0 / data[0][0]})});
		}

		
		//2x2
		template <typename..., Size X = N, Size Y = M, std::enable_if_t<X == Y & X == 2, Int> = 2>
		VLK_CXX14_CONSTEXPR inline SelfType Inverse() const
		{
			return SelfType({(*this) * (1.0 / data.Determinant())});
		}

		template <typename..., Size X = N, Size Y = M, std::enable_if_t<(X == Y) & (X > 2), Int> = 3>
		VLK_CXX14_CONSTEXPR inline SelfType Inverse() const
		{
			SelfType minors;
			SelfType mat;
			MatrixBase<N - 1, M - 1, Float> subMatrix;

			//Assemble minor matrix
			for (Size x = 0; x < N; x++)
			{
				for (Size y = 0; y < M; y++)
				{
					Int n = 0; //X index to write to subMatrix
					Int m = 0; //Y index to write to subMatrix

					//Assemble subMatrix
					for (Size xx = 0; xx < N; xx++)
					{
						if (xx == x) continue; //Ignore current row
						m = 0;

						for (Size yy = 0; yy < M; yy++)
						{
							if (yy == y) continue; //Ignore current colum
							subMatrix[n][m] = data[xx][yy];
							m++;
						}
						n++;
					}

					minors[x][y] = subMatrix.Determinant();
				}
			}

			Val determinant = 0.0;
			Val mod = 1.0;

			for (Size x = 0; x < N; x++)
			{
				for (Size y = 0; y < M; y++)
				{
					// Apply cofactor and transpose here
					//
					// Expression forms a checkerboard of + and -
					// + - + -
					// - + - +
					// + - + -
					// - + - +
					if ( ( ((x % 2) != 0) & ((y % 2) == 0) ) | ( ((x % 2) == 0) & ((y % 2) != 0) ) )
						mat[y][x] = -minors[x][y];
					else
						mat[y][x] =  minors[x][y];
				}

				//Top row of minors matrix can form the determinant without calculating twice.
				determinant += mod * data[x][0] * minors[x][0];
				mod *= -1.0;
			}

			return mat * (1.0 / determinant);
		}
	};

	/*!
	 * \brief Column-major 3x3 transformation matrix.
	 *
	 * Used to store and apply transformations in 2d space
	 */
	class Matrix3
	{
		public:
		typedef MatrixBase<3, 3, Float> DataType;
		typedef DataType::ColType ColType;

		private:
		DataType data;

		public:
		/*!
		 * \brief Creates a 3x3 identity matrix
		 */
		VLK_CXX14_CONSTEXPR inline Matrix3() : 
			data({ ColType({ 1.f, 0.f, 0.f }),
			       ColType({ 0.f, 1.f, 0.f }),
			       ColType({ 0.f, 0.f, 1.f }) })
			{ }

		VLK_CXX14_CONSTEXPR inline Matrix3(const DataType& d) : data(d) { }

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
		VLK_CXX14_CONSTEXPR inline Matrix3(
			Float x0, Float x1, Float x2,
			Float y0, Float y1, Float y2,
			Float z0, Float z1, Float z2) :
			data({ ColType({x0, y0, z0}), 
			       ColType({x1, y1, z1}), 
			       ColType({x2, y2, z2}) })
			{ }

		/*!
		 * \brief Initialize a matrix with three Vector3
		 * \param v0 The first column of the matrix
		 * \param v1 The second column of the matrix
		 * \param v2 The third column of the matrix
		 */
		VLK_CXX14_CONSTEXPR inline Matrix3(
			Vector3 v0,
			Vector3 v1,
			Vector3 v2) :
			data({	ColType({v0[0], v0[1], v0[2]}), 
					ColType({v1[0], v1[1], v1[2]}), 
					ColType({v2[0], v2[1], v2[2]}) })
		{ };

		VLK_CXX14_CONSTEXPR inline Matrix3(const Matrix3&) = default;
		VLK_CXX14_CONSTEXPR inline Matrix3(Matrix3&&) = default;
		VLK_CXX14_CONSTEXPR inline Matrix3& operator=(const Matrix3&) = default;
		VLK_CXX14_CONSTEXPR inline Matrix3& operator=(Matrix3&&) = default;
		VLK_CXX20_CONSTEXPR inline ~Matrix3() = default;

		VLK_CXX14_CONSTEXPR inline ColType& operator[](Size s) { return data[s]; }
		VLK_CXX14_CONSTEXPR inline const ColType& operator[](Size s) const { return data[s]; }

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
		VLK_CXX14_CONSTEXPR inline Matrix3 operator+(const Float f) const { return Matrix3(data + f); }

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
		VLK_CXX14_CONSTEXPR inline Matrix3 operator-(const Float f) const { return Matrix3(data - f); }

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
		VLK_CXX14_CONSTEXPR inline Matrix3 operator*(const Float f) const { return Matrix3(data * f); }

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
		VLK_CXX14_CONSTEXPR inline Matrix3 operator/(const Float f) const { return Matrix3(data / f); }

		/*!
		 * \brief Adds corresponding cells of two matrices
		 */
		VLK_CXX14_CONSTEXPR inline Matrix3 operator+(const Matrix3& rhs) const { return Matrix3(data + rhs.data); }

		/*!
		 * \brief Subtracts corresponding cells of two matricies
		 */
		VLK_CXX14_CONSTEXPR inline Matrix3 operator-(const Matrix3& rhs) const { return Matrix3(data - rhs.data); }

		/*!
		 * \copydoc vlk::Matrix3::operator+(const Float) const
		 */
		VLK_CXX14_CONSTEXPR inline Matrix3& operator+=(const Float f) { data += f; return *this; }

		VLK_CXX14_CONSTEXPR inline Matrix3& operator-=(const Float f) { data -= f; return *this; }

		VLK_CXX14_CONSTEXPR inline Matrix3& operator*=(const Float f) { data *= f; return *this; }

		VLK_CXX14_CONSTEXPR inline Matrix3& operator/=(const Float f) { data /= f; return *this; }

		VLK_CXX14_CONSTEXPR inline Matrix3 operator+=(const Matrix3& rhs) { data += rhs.data; return *this; }

		VLK_CXX14_CONSTEXPR inline Matrix3 operator-=(const Matrix3& rhs) { data -= rhs.data; return *this; }
	
		VLK_CXX14_CONSTEXPR inline bool operator==(const Matrix3& rhs) const { return data == rhs.data; }

		VLK_CXX14_CONSTEXPR inline bool operator!=(const Matrix3& rhs) const { return data != rhs.data; }

		//Multiply functions are MASSIVE, are we sure these should be inline?
		
		/*!
		 * \brief multiplies a matrix by a vector
		 */
		VLK_CXX14_CONSTEXPR inline Vector3 operator*(const Vector3& rhs) const
		{
			return Vector3(data * ColType({rhs[0], rhs[1], rhs[2]}));
		}

		/*!
		 * \brief multiplies two matricies
		 */
		VLK_CXX14_CONSTEXPR inline Matrix3 operator*(const Matrix3& rhs) const
		{
			return Matrix3(data * rhs.data);
		}

		/*!
		 * \brief Returns the inverse of this matrix so that <tt>m * !m</tt> is an identity matrix
		 */
		VLK_CXX14_CONSTEXPR inline Matrix3 operator!() const
		{
			return data.Inverse();
		}

		VLK_CXX14_CONSTEXPR inline Float Determinant() const
		{
			return data.Determinant();
		}

		VLK_CXX14_CONSTEXPR inline Matrix3 Transpose() const
		{
			Matrix3 mat;
			for (int n = 0; n < 3; n++)
			{
				for (int m = 0; m < 3; m++)
				{
					mat[n][m] = data[m][n];
				}
			}
			return mat;
		}

		/*! 
		 * \brief Creates a matrix equivelant to the translation represented by \c v
		 */
		static VLK_CXX14_CONSTEXPR inline Matrix3 CreateTranslation(const Vector2& v)
		{
			return Matrix3(
				1.0f, 0.0f, v[0],
				0.0f, 1.0f, v[1],
				0.0f, 0.0f, 1.0f);
		}

		/*!
		 * \brief Creates a matrix representing a rotation of \c angle radians
		 */
		static inline Matrix3 CreateRotation(const Float angle)
		{
			const Float cosA = Cos(angle);
			const Float sinA = Sin(angle);
			return Matrix3(
				 cosA, -sinA,	0.0f,
				 sinA,	cosA,	0.0f,
				 0.0f,	0.0f,	1.0f);
		}

		/*!
		 * \copydoc vlk::Matrix3::CreateRotation(const Float)
		 *
		 * \remark Constexpr-compatible overload. Do not use in runtime code.
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Matrix3> CreateRotation(ConstexprWrapper<Float> angle)
		{
			const Float cosA = Cos(angle);
			const Float sinA = Sin(angle);
			return ForceCXPR(Matrix3(
				 cosA, -sinA, 0.0f,
				 sinA,  cosA, 0.0f,
				 0.0f,  0.0f, 1.0f));
		}

		/*!
		 * \brief Creates a matrix that scales by the amount specified in \c v
		 */
		static VLK_CXX14_CONSTEXPR inline Matrix3 CreateScale(const Vector2& v)
		{
			return Matrix3(
				 v[0], 0.0f, 0.0f,
				 0.0f, v[1], 0.0f,
				 0.0f, 0.0f, 1.0f);
		}

		/*!
		 * \brief Creates a matrix that reflects along the X-axis
		 */
		static VLK_CXX14_CONSTEXPR inline Matrix3 CreateReflectionX()
		{
			return Matrix3(
			  	-1.0f,  0.0f, 0.0f,
				 0.0f,  1.0f, 0.0f,
				 0.0f,  0.0f, 1.0f);
		}

		/*!
		 * \brief Creates a matrix that reflects along the Y-axis
		 */
		static VLK_CXX14_CONSTEXPR inline Matrix3 CreateReflectionY()
		{
			return Matrix3(
				  1.0f,  0.0f, 0.0f,
				  0.0f, -1.0f, 0.0f,
				  0.0f,  0.0f, 1.0f);
		}
	};

	/*!
	 * \brief Column-major 4x4 transformation matrix.
	 *
	 * Used to store and apply transformations in 3d space
	 */
	class Matrix4
	{
		typedef MatrixBase<4, 4, Float> DataType;
		typedef DataType::ColType ColType;
		DataType data;

		public:

		/*!
		 * \brief Creates a 4x4 identity matrix
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4() :
			data({ ColType({1.f, 0.f, 0.f, 0.f}),
			       ColType({0.f, 1.f, 0.f, 0.f}),
				   ColType({0.f, 0.f, 1.f, 0.f}),
				   ColType({0.f, 0.f, 0.f, 1.f}) })
		{ }

		VLK_CXX14_CONSTEXPR inline Matrix4(DataType d): data(d) { }
		VLK_CXX14_CONSTEXPR inline Matrix4(const Matrix4&) = default;
		VLK_CXX14_CONSTEXPR inline Matrix4(Matrix4&&) = default;
		VLK_CXX14_CONSTEXPR inline Matrix4& operator=(const Matrix4&) = default;
		VLK_CXX14_CONSTEXPR inline Matrix4& operator=(Matrix4&&) = default;
		VLK_CXX20_CONSTEXPR inline ~Matrix4() = default;

		/*!
		 * \brief Initialize individual values of a matrix
		 *
		 * \code
		 *
		 * //  |----|----|----|----|
		 * //  | x0 | x1 | x2 | x3 |
		 * //  |----|----|----|----|
		 * //  | y0 | y1 | y2 | y3 |
		 * //  |----|----|----|----|
		 * //  | z0 | z1 | z2 | z3 |
		 * //  |----|----|----|----|
		 * //  | w0 | w1 | w2 | w3 | 
		 * //  |----|----|----|----|
		 *
		 * \endcode
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4(
			Float x0, Float x1, Float x2, Float x3,
			Float y0, Float y1, Float y2, Float y3,
			Float z0, Float z1, Float z2, Float z3,
			Float w0, Float w1, Float w2, Float w3) :
			data({	ColType({x0, y0, z0, w0}), 
					ColType({x1, y1, z1, w1}), 
					ColType({x2, y2, z2, w2}), 
					ColType({x3, y3, z3, w3}) })
			{ };

		/*!
		 * \brief Initialize a matrix with four Vector4
		 * \param v0 The first column of the matrix
		 * \param v1 The second column of the matrix
		 * \param v2 The third column of the matrix
		 * \param v3 The fourth column of the matrix
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4(
			Vector4 v0,
			Vector4 v1,
			Vector4 v2,
			Vector4 v3) :
			data({	ColType({v0[0], v0[1], v0[2], v0[3]}),
					ColType({v1[0], v1[1], v1[2], v1[3]}),
				  	ColType({v2[0], v2[1], v2[2], v2[3]}),
					ColType({v3[0], v3[1], v3[2], v3[3]}) })
		{ };

		VLK_CXX14_CONSTEXPR inline ColType& operator[](Size s) { return data[s]; }
		VLK_CXX14_CONSTEXPR inline const ColType& operator[](Size s) const { return data[s]; }

		/*!
		 * \brief Performs an addition to every cell of a matrix
		 *
		 * \code
		 *
		 * m = m + 3.0f;
		 *
		 * //  Before:               After:
		 * //  |---|---|---|---|     |---|---|---|---|
		 * //  |1.0|0.0|0.0|0.0|     |4.0|3.0|3.0|3.0|
		 * //  |---|---|---|---|     |---|---|---|---|
		 * //  |0.0|1.0|0.0|0.0|     |3.0|4.0|3.0|3.0|
		 * //  |---|---|---|---| ->  |---|---|---|---|
		 * //  |0.0|0.0|1.0|0.0|     |3.0|3.0|4.0|3.0|
		 * //  |---|---|---|---|     |---|---|---|---|
		 * //  |0.0|0.0|0.0|1.0|     |3.0|3.0|3.0|4.0|
		 * //  |---|---|---|---|     |---|---|---|---|
		 *
		 * \endcode
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4 operator+(const Float f) const 
		{ 
			return Matrix4(data + f); 
		}

		/*!
		 * \brief Performs a subtraction to every cell of a matrix
		 *
		 * \code
		 *
		 * m = m - 3.0f;
		 *
		 * //  Before:               After:
		 * //  |---|---|---|---|     |----|----|----|----|
		 * //  |1.0|0.0|0.0|0.0|     |-2.0|-3.0|-3.0|-3.0|
		 * //  |---|---|---|---|     |----|----|----|----|
		 * //  |0.0|1.0|0.0|0.0|     |-3.0|-2.0|-3.0|-3.0|
		 * //  |---|---|---|---| ->  |----|----|----|----|
		 * //  |0.0|0.0|1.0|0.0|     |-3.0|-3.0|-2.0|-3.0|
		 * //  |---|---|---|---|     |----|----|----|----|
		 * //  |0.0|0.0|0.0|1.0|     |-3.0|-3.0|-3.0|-2.0|
		 * //  |---|---|---|---|     |----|----|----|----|
		 *
		 * \endcode
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4 operator-(const Float f) const
		{
			return Matrix4(data - f);
		}

		/*!
		 * \brief Performs a scalar multiplication to every cell of a matrix
		 *
		 * \code
		 *
		 * m = m * 3.0f;
		 *
		 * //  Before:               After:
		 * //  |---|---|---|---|     |---|---|---|---|
		 * //  |1.0|0.0|0.0|0.0|     |3.0|0.0|0.0|0.0|
		 * //  |---|---|---|---|     |---|---|---|---|
		 * //  |0.0|1.0|0.0|0.0|     |0.0|3.0|0.0|0.0|
		 * //  |---|---|---|---| ->  |---|---|---|---|
		 * //  |0.0|0.0|1.0|0.0|     |0.0|0.0|3.0|0.0|
		 * //  |---|---|---|---|     |---|---|---|---|
		 * //  |0.0|0.0|0.0|1.0|     |0.0|0.0|0.0|3.0|
		 * //  |---|---|---|---|     |---|---|---|---|
		 *
		 * \endcode
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4 operator*(const Float f) const
		{
			return Matrix4(data * f);
		}

		/*!
		 * \brief Performs a scalar division to every cell of a matrix
		 *
		 * \code
		 *
		 * m = m / 2.0f;
		 *
		 * //  Before:               After:
		 * //  |---|---|---|---|     |---|---|---|---|
		 * //  |1.0|0.0|0.0|0.0|     |0.5|0.0|0.0|0.0|
		 * //  |---|---|---|---|     |---|---|---|---|
		 * //  |0.0|1.0|0.0|0.0|     |0.0|0.5|0.0|0.0|
		 * //  |---|---|---|---| ->  |---|---|---|---|
		 * //  |0.0|0.0|1.0|0.0|     |0.0|0.0|0.5|0.0|
		 * //  |---|---|---|---|     |---|---|---|---|
		 * //  |0.0|0.0|0.0|1.0|     |0.0|0.0|0.0|0.5|
		 * //  |---|---|---|---|     |---|---|---|---|
		 *
		 * \endcode
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4 operator/(const Float f) const
		{
			return Matrix4(data / f);
		}

		/*!
		 * \brief Adds corresponding cells of two matrices
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4 operator+(const Matrix4& rhs) const
		{
			return Matrix4(data + rhs.data);
		}

		/*!
		 * \brief Subtracts corresponding cells of two matricies
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4 operator-(const Matrix4& rhs) const
		{
			return Matrix4(data - rhs.data);
		}

		VLK_CXX14_CONSTEXPR inline Matrix4& operator+=(const Float f)
		{
			data += f;
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline Matrix4& operator-=(const Float f)
		{
			data -= f;
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline Matrix4& operator*=(const Float f)
		{
			data *= f;
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline Matrix4& operator/=(const Float f)
		{
			data /= f;
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline Matrix4 operator+=(const Matrix4& rhs)
		{
			data += rhs.data;
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline Matrix4 operator-=(const Matrix4& rhs)
		{
			data -= rhs.data;
			return *this;
		}
	
		VLK_CXX14_CONSTEXPR inline bool operator==(const Matrix4& rhs) const { return data == rhs.data; }
		VLK_CXX14_CONSTEXPR inline bool operator!=(const Matrix4& rhs) const {return data != rhs.data; }

		/*!
		 * \brief multiplies a matrix by a vector
		 */
		VLK_CXX14_CONSTEXPR inline Vector4 operator*(const Vector4& rhs) const
		{
			return Vector4(data * ColType({rhs[0], rhs[1], rhs[2], rhs[3]}));
		}

		/*!
		 * \brief multiplies two matricies
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4 operator*(const Matrix4& rhs) const
		{
			return data * rhs.data;
		}

		/*!
		 * \brief Returns the inverse of this matrix so that <tt>m * !m</tt> is an identity matrix
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4 operator!() const
		{
			return data.Inverse();
		}

		VLK_CXX14_CONSTEXPR inline Float Determinant() const
		{
			return data.Determinant();
		}

		VLK_CXX14_CONSTEXPR inline Matrix4 Transpose() const
		{
			Matrix4 m;
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					m[x][y] = data[y][x];
				}
			}
			return m;
		}

		/*! 
		 * \brief Creates a matrix equivelant to the translation represented by \c v
		 */
		static VLK_CXX14_CONSTEXPR inline Matrix4 CreateTranslation(const Vector3& v)
		{
			return ForceCXPR(Matrix4(
				1.0f, 0.0f, 0.0f, v[0],
				0.0f, 1.0f, 0.0f, v[1],
				0.0f, 0.0f, 1.0f, v[2],
				0.0f, 0.0f, 0.0f, 1.0f ));
		}

		/*!
		 * \brief Creates a matrix representing a rotation of \c angle radians around the X-axis
		 */
		static inline Matrix4 CreateRotationX(const Float angle)
		{
			const Float cosA = Cos(angle);
			const Float sinA = Sin(angle);
			return Matrix4(
				 1.0f,  0.0f,  0.0f,  0.0f,
				 0.0f,  cosA, -sinA,  0.0f,
				 0.0f,  sinA,  cosA,  0.0f,
				 0.0f,  0.0f,  0.0f,  1.0f );
		}

		/*!
		 * \copydoc vlk::Matrix4::CreateRotationX(const Float)
		 *
		 * \remark Constexpr-compatible overload. Do not use in runtime code.
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Matrix4> CreateRotationX(ConstexprWrapper<Float> angle)
		{
			const Float cosA = Cos(angle);
			const Float sinA = Sin(angle);
			return ForceCXPR(Matrix4(
				 1.0f,  0.0f,  0.0f,  0.0f,
				 0.0f,  cosA, -sinA,  0.0f,
				 0.0f,  sinA,  cosA,  0.0f,
				 0.0f,  0.0f,  0.0f,  1.0f ));
		}

		/*!
		 * \brief Creates a matrix representing a rotation of \c angle radians around the Y-axis
		 */
		static inline Matrix4 CreateRotationY(const Float angle)
		{
			const Float cosA = Cos(angle);
			const Float sinA = Sin(angle);
			return Matrix4(
				 cosA,  0.0f,  sinA,  0.0f,
				 0.0f,  1.0f,  0.0f,  0.0f,
				-sinA,  0.0f,  cosA,  0.0f,
				 0.0f,  0.0f,  0.0f,  1.0f );
		}

		/*!
		 * \copydoc vlk::Matrix4::CreateRotationY(const Float)
		 *
		 * \remark Constexpr-compatible overload. Do not use in runtime code.
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Matrix4> CreateRotationY(ConstexprWrapper<Float> angle)
		{
			const Float cosA = Cos(angle);
			const Float sinA = Sin(angle);
			return ForceCXPR(Matrix4(
				 cosA,  0.0f,  sinA,  0.0f,
				 0.0f,  1.0f,  0.0f,  0.0f,
				-sinA,  0.0f,  cosA,  0.0f,
				 0.0f,  0.0f,  0.0f,  1.0f ));
		}

		/*!
		 * \brief Creates a matrix representing a rotation of \c angle radians around the Z-axis
		 */
		static inline Matrix4 CreateRotationZ(const Float angle)
		{
			const Float cosA = Cos(angle);
			const Float sinA = Sin(angle);
			return Matrix4(
				 cosA, -sinA, 0.0f, 0.0f,
				 sinA,  cosA, 0.0f, 0.0f,
				 0.0f,  0.0f, 1.0f, 0.0f,
				 0.0f,  0.0f, 0.0f, 1.0f );
		}

		/*!
		 * \copydoc vlk::Matrix4::CreateRotationZ(const Float)
		 *
		 * \remark Constexpr-compatible overload. Do not use in runtime code.
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Matrix4> CreateRotationZ(ConstexprWrapper<Float> angle)
		{
			const Float cosA = Cos(angle);
			const Float sinA = Sin(angle);
			return ForceCXPR(Matrix4(
				 cosA, -sinA, 0.0f, 0.0f,
				 sinA,  cosA, 0.0f, 0.0f,
				 0.0f,  0.0f, 1.0f, 0.0f,
				 0.0f,  0.0f, 0.0f, 1.0f ));
		}

		/*!
		 * \brief Creates a matrix representing a rotation equivelant to the given euler axis values.
		 *
		 * \param euler A Vector3 where every element represents the number of radians to turn around the respective axis.
		 */
		static inline Matrix4 CreateRotation(const Vector3& euler)
		{
			const Float sinX = Sin(euler.X());
			const Float sinY = Sin(euler.Y());
			const Float sinZ = Sin(euler.Z());
			const Float cosX = Cos(euler.X());
			const Float cosY = Cos(euler.Y());
			const Float cosZ = Cos(euler.Z());

			return Matrix4(
				 cosY * cosZ, -cosY * sinZ * cosX + sinY * sinX,  cosY * sinZ * sinX + sinY * cosX, 0.0f,
				 sinZ,         cosZ * cosX,                      -cosZ * sinX,                      0.0f,
				-sinY * cosZ,  sinY * sinZ * cosX + cosY * sinX, -sinY * sinZ * sinX + cosY * cosX, 0.0f,
				 0.0f,         0.0f,                              0.0f,                             1.0f );
		}
		/*!
		 * \copydoc vlk::Matrix4::CreateRotation(const Vector3&)
		 *
		 * \remark Constexpr-compatible overload. Do not use in runtime code.
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Matrix4> CreateRotation(ConstexprWrapper<Vector3> euler)
		{
			const Float sinX = Sin(ForceCXPR(euler->X()));
			const Float sinY = Sin(ForceCXPR(euler->Y()));
			const Float sinZ = Sin(ForceCXPR(euler->Z()));
			const Float cosX = Cos(ForceCXPR(euler->X()));
			const Float cosY = Cos(ForceCXPR(euler->Y()));
			const Float cosZ = Cos(ForceCXPR(euler->Z()));

			return ForceCXPR(Matrix4(
				 cosY * cosZ, -cosY * sinZ * cosX + sinY * sinX,  cosY * sinZ * sinX + sinY * cosX, 0.0f,
				 sinZ,         cosZ * cosX,                      -cosZ * sinX,                      0.0f,
				-sinY * cosZ,  sinY * sinZ * cosX + cosY * sinX, -sinY * sinZ * sinX + cosY * cosX, 0.0f,
				 0.0f,         0.0f,                              0.0f,                             1.0f ));
		}

		/*!
		 * \brief Creates a matrix representing a rotation of <tt>angle</tt> radians around the normalized axis <tt>axis</tt>
		 */
		static inline Matrix4 CreateRotation(Float angle, const Vector3& axis)
		{
			Float cosA = Cos(angle);
			Float sinA = Sin(angle);
			Float t = 1.0f - cosA;
			Float x = axis[0];
			Float y = axis[1];
			Float z = axis[2];

			return ForceCXPR(Matrix4(
				 t * x * x + cosA,     t * x * y - z * sinA, t * x * z + y * sinA, 0.0f,
				 t * x * y + z * sinA, t * y * y + cosA,     t * y * z + x * sinA, 0.0f,
				 t * x * z + y * sinA, t * y * z + x * sinA, t * z * z + cosA,     0.0f,
				 0.0f,                 0.0f,                 0.0f,                 1.0f ));
		}

		/*!
		 * \copydoc vlk::Matrix4::CreateRotation(Float, const Vector3&)
		 *
		 * \remark Constexpr-compatible overload. Do not use in runtime code.
		 */
		static inline ConstexprWrapper<Matrix4> CreateRotation(ConstexprWrapper<Float> angle, ConstexprWrapper<Vector3> axis)
		{
			Float cosA = Cos(angle);
			Float sinA = Sin(angle);
			Float t = 1.0f - cosA;
			Float x = axis->X();
			Float y = axis->Y();
			Float z = axis->Z();

			return ForceCXPR(Matrix4(
				 t * x * x + cosA,     t * x * y - z * sinA, t * x * z + y * sinA, 0.0f,
				 t * x * y + z * sinA, t * y * y + cosA,     t * y * z + x * sinA, 0.0f,
				 t * x * z + y * sinA, t * y * z + x * sinA, t * z * z + cosA,     0.0f,
				 0.0f,                 0.0f,                 0.0f,                 1.0f ));
		}

		/*!
		 * \brief Creates a matrix representing an equivelant roatation to quaternion <tt>q</tt>.
		 */
		static VLK_CXX14_CONSTEXPR inline Matrix4 CreateRotation(const Quaternion& q)
		{
			Float xx = q[0] * q[0];
			Float yy = q[1] * q[1];
			Float zz = q[2] * q[2];
			Float xy = q[0] * q[1];
			Float xz = q[0] * q[2];
			Float xw = q[0] * q[3];
			Float yz = q[1] * q[2];
			Float yw = q[1] * q[3];
			Float zw = q[2] * q[3];

			return Matrix4(
				1.f - 2.f * (yy + zz),	//0 0
				      2.f * (xy - zw),	//1 0
				      2.f * (xz + yw),	//2 0
					  0.f,				//3 0

				      2.f * (xy + zw),	//0 1
				1.f - 2.f * (xx + zz),	//1 1
					  2.f * (yz - xw),	//2 1
					  0.f,				//3 1

				      2.f * (xz - yw),	//0 2
				      2.f * (yz + xw),	//1 2
				1.f - 2.f * (xx + yy),	//2 2
				      0.f,

				0.f, 0.f, 0.f, 1.f);
		}

		/*!
		 * \brief Creates a matrix that scales by the amount specified in \c v
		 */
		static VLK_CXX14_CONSTEXPR inline Matrix4 CreateScale(const Vector3& v)
		{
			return Matrix4(
				 v[0], 0.0f, 0.0f, 0.0f,
				 0.0f, v[1], 0.0f, 0.0f,
				 0.0f, 0.0f, v[2], 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f );
		}

		/*!
		 * \brief Creates a matrix that reflects along the X-axis
		 */
		static VLK_CXX14_CONSTEXPR inline Matrix4 CreateReflectionX()
		{
			return Matrix4(
				-1.0f,  0.0f,  0.0f,  0.0f,
				 0.0f,  1.0f,  0.0f,  0.0f,
				 0.0f,  0.0f,  1.0f,  0.0f,
				 0.0f,  0.0f,  0.0f,  1.0f );
		}

		/*!
		 * \brief Creates a matrix that reflects along the Y-axis
		 */
		static VLK_CXX14_CONSTEXPR inline Matrix4 CreateReflectionY()
		{
			return Matrix4(
				 1.0f,  0.0f,  0.0f,  0.0f,
				 0.0f, -1.0f,  0.0f,  0.0f,
				 0.0f,  0.0f,  1.0f,  0.0f,
				 0.0f,  0.0f,  0.0f,  1.0f );
		}
		
		/*!
		 * \brief Creates a matrix that reflects along the Z-axis
		 */
		static VLK_CXX14_CONSTEXPR inline Matrix4 CreateReflectionZ()
		{
			return Matrix4(
				 1.0f,  0.0f,  0.0f,  0.0f,
				 0.0f,  1.0f,  0.0f,  0.0f,
				 0.0f,  0.0f, -1.0f,  0.0f,
				 0.0f,  0.0f,  0.0f,  1.0f );
		}
	};
}

#endif
