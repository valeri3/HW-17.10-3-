#include <iostream>
#include <string>
using namespace std;

class Exception 
{
protected:
    string message;
public:
    Exception(string m) : message(m) {}
    virtual string GetMessage() 
    {
        return message;
    }
};

class ArraySizeException : public Exception 
{
public:
    ArraySizeException(string m) : Exception(m) {}
};

class ArrayDataException : public Exception 
{
public:
    ArrayDataException(string m) : Exception(m) {}
};

class ArrayValueCalculator 
{
    int rows;
    int cols;
public:
    ArrayValueCalculator(int r, int c) : rows(r), cols(c) {}
    int doCalc(string** arr) 
    {
        int sum = 0;
        if (rows != cols) throw ArraySizeException("Invalid array size, rows must be equal cols");
        try {
            for (int i = 0; i < rows; i++) 
            {
                for (int j = 0; j < cols; j++)
                {
                    int val = 0;
                    for (char n : arr[i][j])
                    {
                        if (isdigit(n)) 
                        {
                            val = val * 10 + (n - '0');
                            sum += val;
                        }
                        else 
                        {
                            throw ArrayDataException("Invalid data at cell [" + to_string(i) + "," + to_string(j) + "]");
                        }
                    }
                }
            }
        }
        catch (ArrayDataException exception)
        {
            cout << exception.GetMessage() << endl;
        }
        catch (ArraySizeException exception) 
        {
            cout << exception.GetMessage() << endl;
        }
        return sum;
    }
};

int main() 
{
    const int M = 4;
    const int N = 4;
    string array[M][N] = {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"}
    };

    string** arrayPtr = new string * [M];
    for (int i = 0; i < N; i++) 
    {
        arrayPtr[i] = array[i];
    }

    ArrayValueCalculator calc(M, N);
    int result = calc.doCalc(arrayPtr);
    delete[] arrayPtr;
    cout << result;
}