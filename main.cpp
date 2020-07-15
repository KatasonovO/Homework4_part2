#include <iostream>

using namespace std;

class Array{
private:
    int row;
    int column;
    int **arr;

    void create(int row, int column)
    {
        this->row = row;
        this->column = column;
        arr = new int*[row]; for(int i = 0; i < row; i++) {arr[i] = new int[column];};
    }

    int getElement(int r, int c, bool &success)
    {
        success = true;
        if ((r < row)&&(c < column))
            return arr[r][c];
        success = false;
        return 0;
    }

    bool setElement(int r, int c, int value)
    {
        if ((r >= row)||(c >= column))
        {
            if (showChanges) cout << "Element [" << r << "," << c << "] didn't set" << endl;
            return false;
        }
        arr[r][c] = value;
        return true;
    }

public:
    bool showChanges = false;

    Array()
    {
        cout << "Call constructor without parameters (create array[1x1])" << endl;
        create(1, 1);
    }

    Array(Array &source)
    {
        cout << "Call copy constructor" << endl;
        row = source.getRow();
        column = source.getColumn();
        showChanges = source.showChanges;
        create(row, column);
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < column; j++)
            {
                bool sucss;
                arr[i][j] = source.getElement(i,j, sucss);
            }
        }
    }

    Array(int row, int column)
    {
        cout << "Call constructor with parameters (row, column)" << endl;
        create(row, column);
    }

    Array(int row, int column, bool showChange)
    {
        this->showChanges = showChange;
        cout << "Call constructor with parameters (row, column, showChange)" << endl;
        create(row, column);
    }

    ~Array() { for(int i = 0; i < row; i++) delete arr[i]; delete[]arr; }

    int getRow()
    {
        return row;
    }

    int getColumn()
    {
        return column;
    }

    void Show()
    {
        cout << "Demension: " << row << "x" << column << endl;
        for(int i = 0; i < row; i++)
        {
            cout << "[";
            for(int j = 0; j < column; j++)
            {
                cout << arr[i][j];
                if ((j+1) < column) cout << ", ";
            }
            cout << "]" << endl;
        }
    }

    void fillData()
    {
        for(int i = 0; i < row; i++)
            for(int j = 0; j < column; j++)
                arr[i][j] = rand() % 100;
        if (showChanges) Show();
    }

    bool equal(Array b)
    {
        if ((row!= b.getRow())||(column!= b.getColumn()))
        {
            return false;
        }
        for(int i = 0; i < row; i++)
            for(int j = 0; j < column; j++)
            {
                bool bol;
                arr[i][j] = b.getElement(i,j,bol);
            }
    }

    bool add(Array b)
    {
        if ((row!= b.getRow())||(column!= b.getColumn()))
        {
            if (showChanges) cout << "Array not updated." << endl;
            return false;
        }
        for(int i = 0; i < row; i++)
            for(int j = 0; j < column; j++)
            {
                bool bol;
                arr[i][j] += b.getElement(i,j,bol);
            }
        if (showChanges) Show();
    }

    bool subtract(Array b)
    {
        if ((row!= b.getRow())||(column!= b.getColumn()))
        {
            if (showChanges) cout << "Array not updated." << endl;
            return false;
        }
        for(int i = 0; i < row; i++)
            for(int j = 0; j < column; j++)
            {
                bool bol;
                arr[i][j] += b.getElement(i,j,bol);
            }
        if (showChanges) Show();
    }

    void transpose()
    {
        Array c(*this);

        for(int i = 0; i < row; i++) delete arr[i]; delete[]arr;
        create(column, row);

        for(int i = 0; i < row; i++)
            for(int j = 0; j < column; j++)
            {
                bool succs;
                setElement(i, j, c.getElement(j,i, succs));
            }
        if (showChanges) Show();
    }

};


int main()
{
    cout << "Class Array presentation" << endl;
    cout << "Create array  a" << endl;
    Array a;
    a.Show();
    cout << "Create array  b[5,5]" << endl;
    Array b(5, 5);
    b.Show();
    b.fillData();
    b.Show();

    cout << "Create array c = b" << endl;
    Array c(b);
    c.Show();

    cout << "Create array D1[5,6]" << endl;
    Array D1(5, 6, true);
    D1.fillData();

    cout << "Create array D2[5,6]" << endl;
    Array D2(5, 6, true);
    D2.fillData();

    cout << "Create array D3[5,6]" << endl;
    Array D3(5, 6, true);
    D3.fillData();

    cout << "Create array F [6,5]" << endl;
    Array F(6, 5, true);
    F.fillData();

    cout << "Check if arrays are equal (c == b?): " << (c.equal(b)? "true":"false") << endl;
    cout << "Check if arrays are equal (c == D1?): " << (c.equal(D1)? "true":"false") << endl;
    cout << "Check if arrays are equal (D1 == D2?): " << (c.equal(D2)? "true":"false") << endl;

    cout << "Add D2 to D1: " << endl;
    D1.add(D2);

    cout << "Add F to D1: " << endl;
    D1.add(F);

    cout << "Substract D3 from D1: " << endl;
    D1.subtract(D3);

    cout << "Substract D3 from D1: " << endl;
    D1.subtract(D3);

    cout << "Substract F from D1" << endl;
    D1.subtract(F);


    cout << "Transpose D1" << endl;
    D1.transpose();
    Array g(D1);

    return 0;
}
