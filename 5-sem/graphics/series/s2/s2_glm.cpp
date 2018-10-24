// cg_s2_glm.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include <iostream>
#include <glm/glm.hpp>

#define PRINT_M2X3(mat) std::cout << \
                        mat[0][0] << "\t" << mat[1][0] << std::endl << \
                        mat[0][1] << "\t" << mat[1][1] << std::endl << \
                        mat[0][2] << "\t" << mat[1][2] << std::endl;


#define PRINT_V3(v) std::cout << v[0] << "\n" << v[1] << "\n" << v[2] << std::endl;

#define PRINT_M3X3(mat) std::cout << mat[0][0] << "\t" << mat[1][0] << "\t" << mat[2][0] << std::endl \
						 << mat[0][1] << "\t" << mat[1][1] << "\t" << mat[2][1] << std::endl \
						 << mat[0][2] << "\t" << mat[1][2] << "\t" << mat[2][2] << std::endl;

#define printLine() std::cout << "------------" << std::endl;

int main()
{
    // a)
    {
        std::cout << "a)" << std::endl;
        glm::mat2x3 mat1{ 1, 2, 0,
                          0, 3, 1};
        glm::mat2x3 mat2{ 3.0, 0.5, -0.5,
                          0.5, 2.0, 1.0};
        std::cout << "Mat1: " << std::endl;
        PRINT_M2X3(mat1);
        std::cout << "Mat2: " << std::endl;
        PRINT_M2X3(mat2);

        std::cout << "Mat1 + Mat2:" << std::endl;
        glm::mat2x3 r1 = mat1 + mat2;
        PRINT_M2X3(r1);
    }
    printLine();

    // b)
    {
        std::cout << "b)" << std::endl;
        glm::mat3x3 mat1{ 0.5, 1.0, 2.0,
                          -1.0, 0.5, 1.0,
                          -2.0, -1.0, -0.5};

        std::cout << "M1: " << std::endl;
        PRINT_M3X3(mat1);
        std::cout << "R1: " << std::endl;
        glm::mat3x3 r1 = glm::transpose(glm::transpose(glm::transpose(mat1)));
        PRINT_M3X3(r1);
    }

    printLine();
    // c)
    {
        std::cout << "c)" << std::endl;
        glm::mat3x3 mat1{1, 0, 0,
                         0, 1, 0,
                         30, 15, 1};
        glm::vec3 v1{1, 1, 0};

        std::cout << "M1: " << std::endl;
        PRINT_M3X3(mat1);
        std::cout << "V1: " << std::endl;
        PRINT_V3(v1);
        std::cout << "M1 * V1: " << std::endl;
        glm::vec3 r1 = mat1 * v1;
        PRINT_V3(r1);
    }

    printLine();

    // d)
    {
        std::cout << "d)" << std::endl;
        glm::mat3x3 mat1{ 1, -1, 0,
                          -1, 1, 0,
                          0, 0, 1};
        glm::mat3x3 mat2{ 1, 0, 0,
                          0, 1, 0,
                          30, 15, 1};

        std::cout << "M1: " << std::endl;
        mat1 = glm::transpose(mat1);
        PRINT_M3X3(mat1);
        std::cout << "M2: " << std::endl;
        PRINT_M3X3(mat2);
        std::cout << "M1 * M2: " << std::endl;
        glm::mat3x3 r1 = mat1 * mat2;
        PRINT_M3X3(r1);
    }

    // 4)
    {
        // Vertices
        glm::vec3 a{-15, 0, -50};
        glm::vec3 b{15, 0, -50};
        glm::vec3 c{0, 15, -50};
    }


}