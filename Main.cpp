//by Hicham Ben Abdallah
//January 14,  2021
//Contact: hichamrise@gmail.com
//
//Resources:
//https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
//http://ee263.stanford.edu/notes/matrix-primer-lect2.pdf
//
//

#include <iostream>
#include <vector>
#include "Matrix.hpp"

void ListMatrices(matrix* mat); //Displays list of matrices mat
matrix* Selection(matrix* mat, int size); //Collects size amounts of matrices and returns pointer that can access them

matrix Addition(matrix* input); //Takes matrix pointer, prompts user to select matrices, and returns sum of selected matrices
matrix Subtraction(matrix* input); //Takes matrix pointer, prompts user to select matrices, and returns difference of selected matrices
matrix ScalarMultiplication(matrix* input); //Takes matrix pointer, prompts user to input a scalar and select a matrix, and returns the resulting matrix
matrix MatrixMultiplication(matrix* input); //Takes matrix pointer, prompts user to select matrices, and returns the resulting product matrix
double Determinant(matrix* input); //Takes matrix pointer, prompts user to select a matrix, and returns its determinant
matrix Inverse(matrix* input); //Takes matrix pointer, prompts user to select a matrix, and returns its inverse
matrix Transpose(matrix* input); //Takes matrix pointer, prompts user to select a matrix, and returns its transpose

int main()
{
    matrix m0; //First element in matrix list
    matrix* mat = &m0; //Pointer to matrices in list, initialized to point at m0
    char c; //Input char variable
    bool loop1 = true; //Condition for first loop
    bool loop2 = true; //Condition for second loop
    
    while (loop1)
    {
        mat->GetMat();

        do
        {
            std::cout << "\nWould you like to add a matrix to your database(Y/N)?: ";
            std::cin >> c;

            switch (c)
            {
            case 'y':
            case 'Y':
                mat->next = new matrix;
                mat = mat->next;
                break;
            case 'n':
            case 'N':
                mat = &m0;
                loop1 = false;
                break;
            default:
                std::cout << "Invalid selection, try again\n";
                continue;
            }
        } while (!((c == 'y' || c == 'Y') || (c == 'n' || c == 'N')));
    }
    while (loop2)
    {
        bool exit = false;
        matrix resultM;
        double resultS;

        do
        {
            std::cout << "\nWhat operation would you like to perform?:\n"
                << "[A] Addition\n"
                << "[B] Subtraction\n"
                << "[C] Scalar Multiplication\n"
                << "[D] Matrix Multiplication\n"
                << "[E] Determinant\n"
                << "[F] Inverse\n"
                << "[G] Transpose\n"
                << std::endl;

            std::cin >> c;

            switch (c)
            {
            case 'a':
            case 'A':
                resultM = Addition(mat);
                std::cout << "\nThe result is: \n";
                resultM.DisplayMat();
                exit = true;
                break;
            case 'b':
            case 'B':
                resultM = Subtraction(mat);
                std::cout << "\nThe result is: \n";
                resultM.DisplayMat();
                exit = true;
                break;
            case 'c':
            case 'C':
                resultM = ScalarMultiplication(mat);
                std::cout << "\nThe result is: \n";
                resultM.DisplayMat();
                exit = true;
                break;
            case 'd':
            case 'D':
                resultM = MatrixMultiplication(mat);
                std::cout << "\nThe result is: \n";
                exit = true;
                resultM.DisplayMat();
                break;
            case 'e':
            case 'E':
                resultS = Determinant(mat);
                std::cout << "\nThe result is " << resultS << "\n";
                exit = true;
                break;
            case 'f':
            case 'F':
                resultM = Inverse(mat);
                std::cout << "\nThe result is: \n";
                resultM.DisplayMat();
                exit = true;
                break;
            case 'g':
            case 'G':
                resultM = Transpose(mat);
                std::cout << "\nThe result is: \n";
                resultM.DisplayMat();
                exit = true;
                break;
            default:
                std::cout << "Invalid selection, try again\n";
                continue;
            }
        } while (!exit);

        do
        {
            mat = &m0;

            std::cout << "\nWould you like to add another matrix to your database(Y/N)?: ";
            std::cin >> c;

            switch (c)
            {
            case 'y':
            case 'Y':
                while (mat->next != nullptr)
                {
                    mat = mat->next;
                }
                mat->next = new matrix;
                mat = mat->next;
                mat->GetMat();
                break;
            case 'n':
            case 'N':
                mat = &m0;
                continue;
                break;
            default:
                std::cout << "Invalid selection, try again\n";
                continue;
            }
        } while (!(c == 'n' || c == 'N'));

        do
        {
            std::cout << "\nWould you like to perform another operation(Y/N)?: ";
            std::cin >> c;

            switch (c)
            {
            case 'y':
            case 'Y':
                break;
            case 'n':
            case 'N':
                loop2 = false;
                break;
            default:
                std::cout << "Invalid selection, try again\n";
                continue;
            }
        } while (!((c == 'y' || c == 'Y') || (c == 'n' || c == 'N')));
    }

    std::cin >> c;
    return 0;
}

void ListMatrices(matrix* mat)
{
    matrix* view = mat;

    int list = 1; //Numbering for matrix list

    while (view != nullptr)
    {
        std::cout << "\n[" << list << "]";
        for (int n = 0; n < view->ReturnN(); n++)
            std::cout << " " << view->Data(0, n);

        std::cout << "\n";

        for (int i = 1; i < view->ReturnM(); i++)
        {
            std::cout << "    ";

            for (int j = 0; j < view->ReturnN(); j++)
            {
                std::cout << view->Data(i, j) << " ";
            }

            std::cout << "\n";
        }

        view = view->next;
        list++;
    }
}
matrix* Selection(matrix* mat, int size)
{
    matrix* ref = mat;
    matrix* out = new matrix[size];
    int index;

    std::cout << "\n";

    for (int n = 0; n < size; n++)
    {
        std::cin >> index;
        for (int x = 1; x < index; x++)
        {
            ref = ref->next;
        }
        out[n] = *ref;
        ref = mat;
    }

    return out;
}

matrix Addition(matrix* input)
{
    matrix output;
    int size;

    std::cout << "\nADDITION\n" << "How many matrices would you like to add together?: ";
    std::cin >> size;

    std::cout << "\nSelect the matrices you would like to add together by entering their numeric labels sperated by spaces:\nMake sure selected matrices are of the same dimensions.\n";
    ListMatrices(input);

    matrix* selected = new matrix[size];
    selected = Selection(input, size);

    output.SetDimensions(selected->ReturnM(), selected->ReturnN());
    for (int i = 0; i < output.ReturnM(); i++)
    {
        for (int j = 0; j < output.ReturnN(); j++)
        {
            output.Data(i, j) = 0;
        }
    }

    for (int n = 0; n < size; n++)
    {
        output = output + selected[n];
    }

    delete[] selected;

    return output;
}
matrix Subtraction(matrix* input)
{
    matrix a, b;
    matrix output;

    std::cout << "\nSUBTRACTION\n" << "Select the matrices you would like to subtract by entering their numeric labels sperated by a space:\nMake sure selected matrices are of the same dimensions.\n";
    ListMatrices(input);

    matrix* selected = new matrix[2];
    selected = Selection(input, 2);

    a = selected[0];
    b = selected[1];

    output = a - b;

    return output;
}
matrix ScalarMultiplication(matrix* input)
{
    matrix output;
    int c;

    std::cout << "\nSCALAR MULTIPLICATION\n" << "Select matrix to multiply by a scalar:\n";
    ListMatrices(input);

    output = *Selection(input, 1);

    std::cout << "\nWhat scalar would you like to multiply this matrix by?: ";
    std::cin >> c;
    std::cout << "\n";

    output = c * output;

    return output;
}
matrix MatrixMultiplication(matrix* input)
{
    matrix a, b;
    matrix output;

    std::cout << "\nMATRIX MULTIPLICATION\n" << "Select two matrices to multiply together by entering their numeric labels sperated by a space:\n";
    ListMatrices(input);

    matrix* selected = new matrix[2];
    selected = Selection(input, 2);

    a = selected[0];
    b = selected[1];

    if (areMultiplicable(a, b))
    {
        output = a * b;
        return output;
    }
    else
        throw("Not multiplicable");
}
double Determinant(matrix* input)
{
    matrix temp;
    double output;

    std::cout << "\nDETERMINANT\n" << "Select the matrix whose determinant you would like to calculate by entering its numeric label:\n";
    ListMatrices(input);

    temp = *Selection(input, 1);

    if (temp.isSquare())
    {
        output = temp.Det();
        return output;
    }
    else
        throw("Matrix does not have a determinant");
}
matrix Inverse(matrix* input)
{
    matrix output;

    std::cout << "\nINVERSE\n" << "Select the matrix you would like to invert by entering its numeric label:\n";
    ListMatrices(input);

    output = *Selection(input, 1);
    output = output.Inverse();

    return output;
}
matrix Transpose(matrix* input)
{
    matrix output;

    std::cout << "\nTRANSPOSE\n" << "Select the matrix whose transpose you would like to calculate by entering its numeric label:\n";
    ListMatrices(input);

    output = *Selection(input, 1);
    output = output.Transpose();

    return output;
}