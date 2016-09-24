#ifndef MATRIX_H
#define MATRIX_H

#include "QVector"

template<typename T>
class Matrix
{
public:

    Matrix()
    {
        Matrix(0, 0);
    }

    Matrix(const unsigned int countOfRows,
           const unsigned int countOfColumns)
    {
        this->countOfRows = countOfRows;
        this->countOfColumns = countOfColumns;
        data = QVector<T>(countOfRows * countOfColumns);
    }

    T getAt(const unsigned int row,
            const unsigned int column) const
    {
        return data[row * countOfColumns + column];
    }

    void setAt(const unsigned int row,
               const unsigned int column,
               const T value)
    {
        data[row * countOfColumns + column] = value;
    }

    unsigned int getCountOfRows() const
    {
        return countOfRows;
    }

    unsigned int getCountOfColumns() const
    {
        return countOfColumns;
    }

    QVector<T> getRow(const unsigned int row) const
    {
        auto ret = QVector<T>(countOfColumns);
        for(unsigned int column = 0; column < countOfColumns; column++)
        {
            ret[column] = data[row * countOfColumns + column];
        }
        return ret;
    }

private:
    unsigned int countOfRows;
    unsigned int countOfColumns;
    QVector<T> data;
};

#endif // MATRIX_H
