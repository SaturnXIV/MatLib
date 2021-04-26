#ifndef MATRIX_H
#define	MATRIX_H

#include <iostream>

class matrix
{
public:
    matrix(); //Default constructor
    matrix(int m, int n); //Overloaded constructor that takes in matrix dimensions and sets up 2D double array
    ~matrix(); //Destructor
    int ReturnM(); //Returns matrix's M dimension
    int ReturnN(); //Returns matrix's N dimension
    void SetDimensions(int m, int n); //Sets up matrix's 2D double array
    void GetMat(); //Uses std::cout and std::cin to prompt the user to select matrix dimensions and sets up 2D double array
    double& Data(int m, int n); //Returns reference to matrix e
    long double Det(); //Returns the determinant of the matrix
    matrix Transpose(); //Returns the transpose of the matrix
    matrix Inverse(); //Returns the inverse of the matrix
    void DisplayMat(); //Prints out the contents of the matrix
    bool isSquare(); //Return true is matrix is square, otherwise returns false
    bool isInvertible(); //Returns true if the matrix is invertible, otherwise returns false
    void Clear(); //Deletes matrix elements and sets dimensions to 0
    void AdjustZero(double e); //Converts very small numbers to zero
    void AdjustZero(); //Overloaded AdjustZero with default margin value

    double* operator[](int i); //Overloaded [] operator to return pointer to double within matrix, allows M1[i][j] notation

    matrix& operator+=(matrix a); //Overloaded += operator
    matrix& operator-=(matrix a); //Overloaded -= operator
    matrix& operator*=(double c); //Overloaded *= operator (only supports scalar multiplication)

    friend matrix Addition(matrix a, matrix b); //Returns the sum of two matrices of equal dimensions
    friend matrix operator+(matrix a, matrix b); //Overloaded + operator

    friend matrix Subtraction(matrix a, matrix b); //Returns the difference of two matrices of equal dimensions
    friend matrix operator-(matrix a, matrix b); //Overloaded - operator

    friend bool areMultiplicable(matrix a, matrix b); //Returns true if matrices a and can be multiplied together, otherwise returns false
    friend matrix MatrixMultiplication(matrix a, matrix b); //Returns the product of matrices a and b
    friend matrix operator*(matrix a, matrix b); //Overloaded * operator for matrix multiplication

    friend matrix ScalarMultiplication(double c, matrix base); //Returns product of scalar c and matrix base
    friend matrix operator*(double c, matrix base); //Overloaded * operator for scalar multiplication, scalar in front of matrix
    friend matrix operator*(matrix base, double c); //Overloaded * operator for scalar multiplication, matrix in front of scalar

    matrix* next; //Pointer to next matrix in order to operate as a list
private:
    int m, n; //Matrix dimensions
    double** data; //2D double array storing data
};
#endif

matrix::matrix()
{
    next = nullptr; //Sets next matrix pointer to null
    m = 0; //M dimension set to 0
    n = 0; //N dimension set to 0
    data = nullptr; //Data double* pointer set to null
}
matrix::matrix(int m, int n)
{
    next = nullptr; //Sets next matrix pointer to null
    this->SetDimensions(m, n); //Sets up the matrix's m by n 2D double matrix
}
matrix::~matrix()
{
}
int matrix::ReturnM()
{
    return this->m;
}
int matrix::ReturnN()
{
    return this->n;
}
void matrix::SetDimensions(int m, int n)
{
    this->m = m;
    this->n = n;

    data = new double* [m]; //Creates array of double pointers of size m
    for (int i = 0; i < m; i++)
    {
        data[i] = new double[n]; //Each pointer points to a series of n doubles
    }
}
void matrix::GetMat()
{
    int m, n; //Variable to be substituted for matrix dimensions

    std::cout << "\nEnter matrix dimensions(m and n seperated by a space): ";
    std::cin >> m >> n; //Reads user inputs for matrix dimensions

    SetDimensions(m, n); //Sets up the matrix's 2D double array

    std::cout << "\nEnter matrix data (i entries seperated by spaces and j entries seperated by new lines): \n\n";
    for (int i = 0; i < this->m; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            std::cin >> this->data[i][j]; //Each element input by user is read and placed in the matrix data array
        }
    }
}
double& matrix::Data(int i, int j)
{
    return data[i][j]; //Returns element at location ij
}
long double matrix::Det()
{
    matrix* sub; //Pointer to current minor of matrix
    long double result = 0; //Result that will be constructed and returned

    if (this->n == 1) //If 1x1 matrix (matrix must be square for determinant to exist)
    {
        return **data; //Return the singular element
    }
    if (this->n == 2) //If 2x2 matrix (matrix must be square for determinant to exist)
    {
        return (data[0][0] * data[1][1]) - (data[0][1] * data[1][0]); //Returns the determinant of the 2x2 matrix
    }
    else //If the matrix is not a single element 
    {
        for (int j = 0; j < this->n; j++)
        {
            //Sets up minor matrix (sub)
            sub = new matrix;
            sub->SetDimensions(this->m - 1, this->n - 1);

            int r = 0;

            for (int x = 1; x < this->m; x++)
            {
                r = 0;

                for (int y = 0; y < this->n; y++)
                {
                    if (y == j)
                        continue;
                    else
                    {
                        sub->data[x - 1][r] = data[x][y];
                        r++;
                    } 
                }
            }

            //Adds the current cofactor multiplied by the current element (taking into account the + and - matrix checkboard) to the final result
            result += pow(-1, j) * data[0][j] * sub->Det();

            delete sub;
        }
        return result;
    }
}
matrix matrix::Transpose()
{
    matrix out(this->n, this->m); //Output matrix of switched dimensions m and n

    for (int i = 0; i < this->m; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            out.Data(j, i) = data[i][j]; //Components ij replaced by components ji
        }
    }

    return out;
}
matrix matrix::Inverse()
{
    matrix out(this->m, this->n); //Output matrix
    matrix minor((this->m) - 1, (this->n) - 1); //Minor matrix at each index whose determinant will be calculated

    //Step 1: Matrix of Minors
    int k = 0, l = 0;

    for (int i = 0; i < this->m; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            //Creates minor
            for (int x = 0; x < this->m; x++)
            {
                if (x == i)
                    continue;

                else
                {
                    for (int y = 0; y < this->n; y++)
                    {
                        if (y == j)
                            continue;

                        else
                        {
                            minor.Data(k, l) = this->data[x][y];
                            l++;
                        }
                    }

                    l = 0;
                    k++;
                }

            }//Minor created

            k = 0;

            out.Data(i, j) = minor.Det(); //Element ij replaced by the determinant of its minor
        }
    }

    //Step 2: Matrix of Cofactors
    for (int i = 0; i < out.ReturnM(); i++)
    {
        for (int j = 0; j < out.ReturnN(); j++)
        {
            out.Data(i, j) *= pow(-1, i + j);
        }
    }

    //Step 3: Adjugate
    out = out.Transpose();

    //Step 4: 1/Determinant
    out = (1 / this->Det()) * out;

    return out;
}
void matrix::DisplayMat()
{
    std::cout << "\n";

    for (int i = 0; i < this->m; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            std::cout << data[i][j] << " "; //Elements of single row seperated by space
        }

        std::cout << "\n"; //Different rows seperated by newline
    }
}
bool matrix::isSquare()
{
    return this->m == this->n;
}
bool matrix::isInvertible()
{
    if (this->isSquare())
        return !(this->Det() == 0);
    else
        return false;
}
void matrix::Clear()
{
    this->m = 0;
    this->n = 0;

    for (int i = 0; i < m; i++)
    {
        delete[] data[i]; //Deletes pointers to doubles
    }
    delete[] data; //Deletes pointer to double pointer

    data = nullptr;
}
void matrix::AdjustZero(double e)
{
    for (int i = 0; i < this->m; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            if (abs(this->data[i][j]) < e) //If element is smaller than e
                this->data[i][j] = 0; //Set element equal to 0
        }
    }
}
void matrix::AdjustZero()
{
    double epsilon = 1.0e-15; //Default threshold value

    for (int i = 0; i < this->m; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            if (abs(this->data[i][j]) < epsilon) //If element is smaller than e
                this->data[i][j] = 0; //Set element equal to 0
        }
    }
}

double* matrix::operator[](int i)
{
    return data[i];
}

matrix& matrix::operator+=(matrix a)
{
    *this = *this + a;
    return *this;
}
matrix& matrix::operator-=(matrix a)
{
    *this = *this - a;
    return *this;
}
matrix& matrix::operator*=(double c)
{
    *this = c * *this;
    return *this;
}

matrix Addition(matrix a, matrix b)
{
    matrix out(a.m, a.n); //Output matrix

    for (int i = 0; i < out.m; i++)
    {
        for (int j = 0; j < out.n; j++)
        {
            out.Data(i, j) = a.Data(i, j) + b.Data(i, j); //Each element is the sum of elements from a and b
        }
    }

    return out;
}
matrix operator+(matrix a, matrix b)
{
    return Addition(a, b);
}

matrix Subtraction(matrix a, matrix b)
{
    matrix out(a.m, a.n); //Output matrix

    for (int i = 0; i < out.m; i++)
    {
        for (int j = 0; j < out.n; j++)
        {
            out.Data(i, j) = a.Data(i, j) - b.Data(i, j); //Each element is the sum of elements from a and b
        }
    }

    return out;
}
matrix operator-(matrix a, matrix b)
{
    return Subtraction(a, b);
}

bool areMultiplicable(matrix a, matrix b)
{
    return (a.n == b.m);
}
matrix MatrixMultiplication(matrix a, matrix b)
{
    matrix out(a.m, b.n); //Output matrix
    double entry = 0; //Entry at each element in out

    for (int i = 0; i < out.m; i++)
    {
        for (int j = 0; j < out.n; j++)
        {
            for (int k = 0; k < a.n; k++) //b.m also works since a.n must equal b.m for matrix multiplication to be possible
            {
                entry += a.data[i][k] * b.data[k][j]; //Adds product of elements from a and b and adds it the sum of that element in out
            }

            out.data[i][j] = entry;
            entry = 0; //Entry reset to 0 for next entry in out
        }
    }

    return out;
}
matrix operator*(matrix a, matrix b)
{
    return MatrixMultiplication(a, b);
}

matrix ScalarMultiplication(double c, matrix base)
{
    matrix out(base.m, base.n);

    for (int i = 0; i < base.m; i++)
    {
        for (int j = 0; j < base.n; j++)
        {
            out.data[i][j] = c * base.data[i][j]; //Multipies each element in base by the scalar c and puts in out
        }
    }

    return out;
}
matrix operator*(double c, matrix base)
{
    return ScalarMultiplication(c, base);
}
matrix operator*(matrix base, double c)
{
    return ScalarMultiplication(c, base);
}