#pragma once
#include <iostream>

namespace nu::math {

    //#define MY_DEBUG
    template<typename T, int N, int M>
    struct MasWrapper{
        T mas[N][M];
    };

    template<typename T, int N, int M>
    class Matrix{
    public:
        Matrix(){
#ifdef MY_DEBUG
            std::cout << "Constructor" << std::endl;
#endif
            m_n = N;
            m_m = M;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = 0;
        }
        Matrix(const MasWrapper<T, N, M>& mas){
#ifdef MY_DEBUG
            std::cout << "Constructor" << std::endl;
#endif
            m_n = N;
            m_m = M;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mas.mas[i][j];
        }
        Matrix(const Matrix<T, N, M>& mat){
#ifdef MY_DEBUG
            std::cout << "Copy constructor" << std::endl;
#endif
            m_n = mat.m_n;
            m_m = mat.m_m;

            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mat.m_mat[i][j];
        }

        int getN() const { return m_n; }
        int getM() const { return m_m; }
        T get(int i, int j) const { return m_mat[i][j]; }
        void set(int i, int j, T data) { m_mat[i][j] = data; }

        template<typename U, int H, int W>
        Matrix<U, H, W>& operator=(const Matrix<U, H, W>& mat){
#ifdef MY_DEBUG
            std::cout << "Operator =" << std::endl;
#endif
            m_n = mat.getN();
            m_m = mat.getM();

            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mat.get(i, j);

            return *this;
        }

        template<typename U, int H, int W>
        Matrix<U, H, W> operator+(const Matrix<U, H, W>& mat){
#ifdef MY_DEBUG
            std::cout << "operator+" << std::endl;
#endif
            Matrix<U, H, W> tmp;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
            return tmp;
        }
        template<typename U, int H, int W>
        Matrix<U, H, W> operator-(const Matrix<U, H, W>& mat){
#ifdef MY_DEBUG
            std::cout << "operator-" << std::endl;
#endif
            Matrix<U, H, W> tmp;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
            return tmp;
        }
        template<typename U, int H, int W>
        Matrix<U, H, W> operator*(const Matrix<U, H, W>& mat){
#ifdef MY_DEBUG
            std::cout << "operator*" << std::endl;
#endif
            Matrix<U, H, W> tmp;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < mat.getM(); j++){
                    U sum = 0;
                    for (int k = 0; k < m_m; k++)
                        sum += m_mat[i][k] * mat.get(k, j);
                    tmp.set(i, j, sum);
                }
            return tmp;
        }
        Matrix<T, N, M> trans(){
            double tmp;
            Matrix<T, N, M> second_m;
            for (int i = 0; i < m_n; i++)
                for (int j=i; j < m_m; j++){
                    if((i==0 && j==0) || (i==m_n-1 && j==m_m-1)) {
                        second_m.set(i, j, m_mat[i][j]);
                        continue;
                    }
                    second_m.set(i, j, m_mat[j][i]);
                    second_m.set(j, i, m_mat[i][j]);
                }
            return second_m;
        }
        T det(){
            double result = 0;
            if(m_n == 2 && m_m == 2)
                return m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
            else if(m_n == 3 && m_m == 3) {
                result = (m_mat[0][0] * m_mat[1][1] * m_mat[2][2]) + (m_mat[0][1] * m_mat[1][2] * m_mat[2][0]) + (m_mat[1][0] * m_mat[2][1] * m_mat[0][2])
                         - (m_mat[2][0] * m_mat[1][1] * m_mat[0][2]) - (m_mat[0][1] * m_mat[1][0] * m_mat[2][2]) - (m_mat[1][2] * m_mat[2][1] * m_mat[0][0]);
                return result;
            } else {
                std::cout << "Det only for 2x2 or 3x3!!!" << std::endl;
                return 0;
            }
        }
        Matrix<T, N, M> reverse(){
            double det = this->det();
            if (det == 0) {
                throw std::runtime_error("Det equally zero!!!");
            }
            det=1/det;
            Matrix<T, N, M> second_m;
            if(N == 2 && M == 2) {
                second_m.set(0, 0, m_mat[1][1] * det);
                second_m.set(0, 1, (-1) * m_mat[1][0] * det);
                second_m.set(1, 0, (-1) * m_mat[0][1] * det);
                second_m.set(1, 1, m_mat[0][0] * det);
                second_m = second_m.trans();
                return second_m;
            } else if(m_n == 3 && m_m == 3) {
                second_m.set(0, 0, (m_mat[1][1] * m_mat[2][2] - m_mat[1][2] * m_mat[2][1]) * det);
                second_m.set(0, 1, (-1) * (m_mat[1][0] * m_mat[2][2] - m_mat[1][2] * m_mat[2][0]) * det);
                second_m.set(0, 2, (m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0]) * det);
                second_m.set(1, 0, (-1) * (m_mat[0][1] * m_mat[2][2] - m_mat[0][2] * m_mat[2][1]) * det);
                second_m.set(1, 1, (m_mat[0][0] * m_mat[2][2] - m_mat[0][2] * m_mat[2][0]) * det);
                second_m.set(1, 2, (-1) * (m_mat[0][0] * m_mat[2][1] - m_mat[0][1] * m_mat[2][0]) * det);
                second_m.set(2, 0, (m_mat[0][1] * m_mat[1][2] - m_mat[0][2] * m_mat[1][1]) * det);
                second_m.set(2, 1, (-1) * (m_mat[0][0] * m_mat[1][2] - m_mat[0][2] * m_mat[1][0]) * det);
                second_m.set(2, 2, (m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0]) * det);
                second_m = second_m.trans();
                return second_m;
            } else
                throw std::runtime_error("Det only for 2x2 or 3x3!!!");
        }
        ~Matrix(){
#ifdef MY_DEBUG
            std::cout << "Destructor" << std::endl;
#endif
        }

        template<typename U, int H, int W>
        friend std::istream& operator>>(std::istream& os, Matrix<U, H, W>& mat);

        template<typename U, int H, int W>
        friend std::ostream& operator<<(std::ostream& os, const Matrix<U, H, W>& mat);

    private:
        int m_n, m_m;
        T m_mat[N][M];
    };
    template<typename T, int N, int M>
    std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat){
        for (int i = 0; i < mat.m_n; i++)
            for (int j = 0; j < mat.m_m; j++)
                in >> mat.m_mat[i][j];
        return in;
    }

    template<typename T, int N, int M>
    std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat){
        out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
        for (int i = 0; i < mat.m_n; i++) {
            for (int j = 0; j < mat.m_m; j++)
                out << mat.m_mat[i][j] << " ";
            out << std::endl;
        }
        return out;
    }

    using Vec2i = Matrix<int, 2, 1>;
    using Vec2d = Matrix<double, 2, 1>;
    using Mat22i = Matrix<int, 2, 2>;
    using Mat22d = Matrix<double, 2, 2>;
    using Mat33i = Matrix<int, 3, 3>;
    using Mat33d = Matrix<double, 3, 3>;
}