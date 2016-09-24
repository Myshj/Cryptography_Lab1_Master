#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "matrix.h"

void fillRandomProbabilityVector(QVector<double>& vector)
{
    const unsigned int count = vector.size();
    auto randomInts = QVector<unsigned int>(count);
    double sum = 0.0;

    for(unsigned int i = 0; i < count; i++)
    {
        randomInts[i] = qrand() % 1000;
        sum += randomInts[i];
    }

    for(unsigned int i = 0; i < count; i++)
    {
        vector[i] = (double)randomInts[i] / sum;
    }
}

void fillEqualProbabilityVector(QVector<double>& vector)
{
    const unsigned int count = vector.size();
    double value = (double)1 / count;

    for(unsigned int i = 0; i < count; i++)
    {
        vector[i] = value;
    }
    qDebug() << value;
}


void MainWindow::writeVectorToTable(const QVector<double>& vector, const QTableWidget* table)
{
    const unsigned int count = vector.size();
    for(unsigned int i = 0; i < count; i++)
    {
        table->item(0, i)->setText(QString::number(vector[i], 'g', 2));
    }
}

template<typename T>
void MainWindow::writeMatrixToTable(const Matrix<T> &matrix, const QTableWidget *table)
{
    unsigned int countOfRows = matrix.getCountOfRows();
    unsigned int countOfColumns = matrix.getCountOfColumns();

    for(unsigned int row = 0; row < countOfRows; row++)
    {
        for(unsigned int column = 0; column < countOfColumns; column++)
        {
            table->item(row, column)->setText(QString::number(matrix.getAt(row, column), 'g', 4));
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    switchToSquare();
}

void MainWindow::switchToSquare()
{
    tableOfFunction = Matrix<unsigned int>(ui->tableOfFunction_Square->rowCount(),
                                           ui->tableOfFunction_Square->columnCount());

    aprioriMessageProbabilities = QVector<double>(ui->tableOfAprioriMessageProbability_Square->columnCount());
    aprioriKeyProbabilities = QVector<double>(ui->tableOfAprioriKeyProbability_Square->columnCount());

    aposterioriMessageProbabilities = Matrix<double>(ui->tableOfAposterioriMessageProbability_Square->rowCount(),
                                                     ui->tableOfAposterioriMessageProbability_Square->columnCount());
    differenceBetweenAprAndApostMessageProbabilities = Matrix<double>(ui->tableOfAposterioriMessageProbability_Square->rowCount(),
                                                     ui->tableOfAposterioriMessageProbability_Square->columnCount());
    ratiosBetweenApostKeyProbAndAprMesrob = Matrix<double>(ui->tableOfAprioriKeyProbability_Square->columnCount(),
                                                           ui->tableOfAposterioriMessageProbability_Square->rowCount());
}

void MainWindow::switchToRectangle()
{
    tableOfFunction = Matrix<unsigned int>(ui->tableOfFunction_Rect->rowCount(),
                                           ui->tableOfFunction_Rect->columnCount());

    aprioriMessageProbabilities = QVector<double>(ui->tableOfAprioriMessageProbability_Rect->columnCount());
    aprioriKeyProbabilities = QVector<double>(ui->tableOfAprioriKeyProbability_Rect->columnCount());

    aposterioriMessageProbabilities = Matrix<double>(ui->tableOfAposterioriMessageProbability_Rect->rowCount(),
                                                     ui->tableOfAposterioriMessageProbability_Rect->columnCount());
    differenceBetweenAprAndApostMessageProbabilities = Matrix<double>(ui->tableOfAposterioriMessageProbability_Rect->rowCount(),
                                                     ui->tableOfAposterioriMessageProbability_Rect->columnCount());
    ratiosBetweenApostKeyProbAndAprMesrob = Matrix<double>(ui->tableOfAprioriKeyProbability_Rect->columnCount(),
                                                           ui->tableOfAposterioriMessageProbability_Rect->rowCount());
}

void MainWindow::switchToRectangle_2()
{
    tableOfFunction = Matrix<unsigned int>(ui->tableOfFunction_Rect_2->rowCount(),
                                           ui->tableOfFunction_Rect_2->columnCount());

    aprioriMessageProbabilities = QVector<double>(ui->tableOfAprioriMessageProbability_Rect_2->columnCount());
    aprioriKeyProbabilities = QVector<double>(ui->tableOfAprioriKeyProbability_Rect_2->columnCount());

    aposterioriMessageProbabilities = Matrix<double>(ui->tableOfAposterioriMessageProbability_Rect_2->rowCount(),
                                                     ui->tableOfAposterioriMessageProbability_Rect_2->columnCount());
    differenceBetweenAprAndApostMessageProbabilities = Matrix<double>(ui->tableOfAposterioriMessageProbability_Rect_2->rowCount(),
                                                     ui->tableOfAposterioriMessageProbability_Rect_2->columnCount());
    ratiosBetweenApostKeyProbAndAprMesrob = Matrix<double>(ui->tableOfAprioriKeyProbability_Rect_2->columnCount(),
                                                           ui->tableOfAposterioriMessageProbability_Rect_2->rowCount());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateTableOfFunction(
        const unsigned int constRow1,
        const unsigned int constColumn1,
        const unsigned int constValue1,
        const unsigned int constRow2,
        const unsigned int constColumn2,
        const unsigned int constValue2
        )
{
//    unsigned int constRow1 = ui->numberOfRowToBeConstant1_Square->value() - 1;
//    unsigned int constColumn1 = ui->numberOfColumnToBeConstant1_Square->value() - 1;

//    unsigned int constRow2 = ui->numberOfRowToBeConstant2_Square->value() - 1;
//    unsigned int constColumn2 = ui->numberOfColumnToBeConstant2_Square->value() - 1;

    unsigned int countOfRows = tableOfFunction.getCountOfRows();
    unsigned int countOfColumns = tableOfFunction.getCountOfColumns();

    unsigned int countOfEncryptedMessages = aposterioriMessageProbabilities.getCountOfRows();

    for(unsigned int i = 0; i < countOfRows; i++)
    {
        for(unsigned int j = 0; j < countOfColumns; j++)
        {
            tableOfFunction.setAt(i, j, 0);
        }
    }
    Matrix<bool> tableOfFunctionFillingMap(countOfRows, countOfColumns);

    tableOfFunction.setAt(constRow1, constColumn1, constValue1);
    tableOfFunction.setAt(constRow2, constColumn2, constValue2);

    tableOfFunctionFillingMap.setAt(constRow1, constColumn1, true);
    tableOfFunctionFillingMap.setAt(constRow2, constColumn2, true);

    for(unsigned int row = 0; row < countOfRows; row++)
    {
        for(unsigned int column = 0; column < countOfColumns; column++)
        {
            if(tableOfFunctionFillingMap.getAt(row, column))
            {
                continue;
            }
            unsigned int encryptedMessage = qrand() % countOfEncryptedMessages + 1;
            auto currentRow = tableOfFunction.getRow(row);
            while(currentRow.contains(encryptedMessage))
            {
                encryptedMessage = qrand() % countOfEncryptedMessages + 1;
            }
            tableOfFunction.setAt(row, column, encryptedMessage);
            tableOfFunctionFillingMap.setAt(row, column, true);
        }
    }
}


void MainWindow::on_generateTableOfFunctionButton_Square_clicked()
{
    generateTableOfFunction(
                ui->numberOfRowToBeConstant1_Square->value() - 1,
                ui->numberOfColumnToBeConstant1_Square->value() - 1,
                ui->valueToBeConstant1_Square->value(),
                ui->numberOfRowToBeConstant2_Square->value() - 1,
                ui->numberOfColumnToBeConstant2_Square->value() - 1,
                ui->valueToBeConstant2_Square->value()
                );
    writeMatrixToTable(tableOfFunction, ui->tableOfFunction_Square);
}

void MainWindow::on_generateTableOfFunctionButton_Rect_clicked()
{
    generateTableOfFunction(
                ui->numberOfRowToBeConstant1_Rect->value() - 1,
                ui->numberOfColumnToBeConstant1_Rect->value() - 1,
                ui->valueToBeConstant1_Rect->value(),
                ui->numberOfRowToBeConstant2_Rect->value() - 1,
                ui->numberOfColumnToBeConstant2_Rect->value() - 1,
                ui->valueToBeConstant2_Rect->value()
                );
    writeMatrixToTable(tableOfFunction, ui->tableOfFunction_Rect);
}

void MainWindow::on_generateTableOfFunctionButton_Rect_2_clicked()
{
    generateTableOfFunction(
                ui->numberOfRowToBeConstant1_Rect_2->value() - 1,
                ui->numberOfColumnToBeConstant1_Rect_2->value() - 1,
                ui->valueToBeConstant1_Rect_2->value(),
                ui->numberOfRowToBeConstant2_Rect_2->value() - 1,
                ui->numberOfColumnToBeConstant2_Rect_2->value() - 1,
                ui->valueToBeConstant2_Rect_2->value()
                );
    writeMatrixToTable(tableOfFunction, ui->tableOfFunction_Rect_2);
}

void MainWindow::on_generateAprioriMessageProbabilities_Square_clicked()
{
    if(ui->generateEqualProbabilities_Square->isChecked())
    {
        fillEqualProbabilityVector(aprioriMessageProbabilities);
    }
    else if(ui->generateRandomProbabilities_Square->isChecked())
    {
        fillRandomProbabilityVector(aprioriMessageProbabilities);
    }
    writeVectorToTable(aprioriMessageProbabilities, ui->tableOfAprioriMessageProbability_Square);
}

void MainWindow::on_generateAprioriMessageProbabilities_Rect_clicked()
{
    if(ui->generateEqualProbabilities_Rect->isChecked())
    {
        fillEqualProbabilityVector(aprioriMessageProbabilities);
    }
    else if(ui->generateRandomProbabilities_Rect->isChecked())
    {
        fillRandomProbabilityVector(aprioriMessageProbabilities);
    }
    writeVectorToTable(aprioriMessageProbabilities, ui->tableOfAprioriMessageProbability_Rect);
}

void MainWindow::on_generateAprioriMessageProbabilities_Rect_2_clicked()
{
    if(ui->generateEqualProbabilities_Rect_2->isChecked())
    {
        fillEqualProbabilityVector(aprioriMessageProbabilities);
    }
    else if(ui->generateRandomProbabilities_Rect_2->isChecked())
    {
        fillRandomProbabilityVector(aprioriMessageProbabilities);
    }
    writeVectorToTable(aprioriMessageProbabilities, ui->tableOfAprioriMessageProbability_Rect_2);
}

void MainWindow::on_generateAprioriKeyProbabilities_Square_clicked()
{
    if(ui->generateEqualKeyProbabilities_Square->isChecked())
    {
        fillEqualProbabilityVector(aprioriKeyProbabilities);
    }
    else if(ui->generateRandomKeyProbabilities_Square->isChecked())
    {
        fillRandomProbabilityVector(aprioriKeyProbabilities);
    }
    writeVectorToTable(aprioriKeyProbabilities, ui->tableOfAprioriKeyProbability_Square);
}

void MainWindow::on_generateAprioriKeyProbabilities_Rect_clicked()
{
    if(ui->generateEqualKeyProbabilities_Rect->isChecked())
    {
        fillEqualProbabilityVector(aprioriKeyProbabilities);
    }
    else if(ui->generateRandomKeyProbabilities_Rect->isChecked())
    {
        fillRandomProbabilityVector(aprioriKeyProbabilities);
    }
    writeVectorToTable(aprioriKeyProbabilities, ui->tableOfAprioriKeyProbability_Rect);
}

void MainWindow::on_generateAprioriKeyProbabilities_Rect_2_clicked()
{
    if(ui->generateEqualKeyProbabilities_Rect_2->isChecked())
    {
        fillEqualProbabilityVector(aprioriKeyProbabilities);
    }
    else if(ui->generateRandomKeyProbabilities_Rect_2->isChecked())
    {
        fillRandomProbabilityVector(aprioriKeyProbabilities);
    }
    writeVectorToTable(aprioriKeyProbabilities, ui->tableOfAprioriKeyProbability_Rect_2);
}

void MainWindow::generateAposterioriMessageProbabilities()
{
    unsigned int cryptogramCount = aposterioriMessageProbabilities.getCountOfRows();
    unsigned int messageCount = aposterioriMessageProbabilities.getCountOfColumns();

    for(unsigned int cryptogramRow = 0; cryptogramRow < cryptogramCount; cryptogramRow++)
    {
        for(unsigned int messageColumn = 0; messageColumn < messageCount; messageColumn++)
        {
            // Calculate P(Mi) +
            double PMi = aprioriMessageProbabilities[messageColumn];

            // Calculate PMi(Es) +
            double PMiEs = 0;
            const unsigned int keyCount = tableOfFunction.getCountOfRows();
            for(unsigned int keyRow = 0; keyRow < keyCount; keyRow++)
            {
                if(tableOfFunction.getAt(keyRow, messageColumn) == cryptogramRow+1)
                {
                    PMiEs += aprioriKeyProbabilities[keyRow];

                }
            }

            // Calculate P(Es)
            double PEs = 0;
            for(unsigned int keyRow = 0; keyRow < keyCount; keyRow++)
            {
                for(unsigned int innerMessageColumn = 0; innerMessageColumn < messageCount; innerMessageColumn++)
                {
                    if(tableOfFunction.getAt(keyRow, innerMessageColumn) == cryptogramRow+1)
                    {
                        PEs += aprioriKeyProbabilities[keyRow] * aprioriMessageProbabilities[innerMessageColumn];
                    }
                }
            }

            aposterioriMessageProbabilities.setAt(cryptogramRow,
                                                  messageColumn,
                                                  PMi * PMiEs / PEs);
        }
    }
}

void MainWindow::on_generateTableOfAposterioriMessageProbabilityButton_Square_clicked()
{
    generateAposterioriMessageProbabilities();
    writeMatrixToTable(aposterioriMessageProbabilities, ui->tableOfAposterioriMessageProbability_Square);
}

void MainWindow::on_generateTableOfAposterioriMessageProbabilityButton_Rect_clicked()
{
    qDebug() << ui->tableOfAposterioriMessageProbability_Rect->rowCount();
    generateAposterioriMessageProbabilities();
    writeMatrixToTable(aposterioriMessageProbabilities, ui->tableOfAposterioriMessageProbability_Rect);
}

void MainWindow::on_generateTableOfAposterioriMessageProbabilityButton_Rect_2_clicked()
{
    qDebug() << ui->tableOfAposterioriMessageProbability_Rect_2->rowCount();
    generateAposterioriMessageProbabilities();
    writeMatrixToTable(aposterioriMessageProbabilities, ui->tableOfAposterioriMessageProbability_Rect_2);
}


void MainWindow::on_tableOfFunction_Square_cellChanged(int row, int column)
{
    tableOfFunction.setAt(row, column, ui->tableOfFunction_Square->item(row, column)->text().toUInt());
}

void MainWindow::on_tableOfFunction_Rect_cellChanged(int row, int column)
{
    tableOfFunction.setAt(row, column, ui->tableOfFunction_Rect->item(row, column)->text().toUInt());
}

void MainWindow::on_tableOfFunction_Rect_2_cellChanged(int row, int column)
{
    tableOfFunction.setAt(row, column, ui->tableOfFunction_Rect_2->item(row, column)->text().toUInt());
}




void MainWindow::on_tableOfAprioriMessageProbability_Square_cellChanged(int row, int column)
{
    aprioriMessageProbabilities[column] = ui->tableOfAprioriMessageProbability_Square->item(row, column)->text().toFloat();
}

void MainWindow::on_tableOfAprioriMessageProbability_Rect_cellChanged(int row, int column)
{
    aprioriMessageProbabilities[column] = ui->tableOfAprioriMessageProbability_Rect->item(row, column)->text().toFloat();
}

void MainWindow::on_tableOfAprioriMessageProbability_Rect_2_cellChanged(int row, int column)
{
    aprioriMessageProbabilities[column] = ui->tableOfAprioriMessageProbability_Rect_2->item(row, column)->text().toFloat();
}




void MainWindow::on_tableOfAprioriKeyProbability_Square_cellChanged(int row, int column)
{
    aprioriKeyProbabilities[column] = ui->tableOfAprioriKeyProbability_Square->item(row, column)->text().toFloat();
}

void MainWindow::on_tableOfAprioriKeyProbability_Rect_cellChanged(int row, int column)
{
    aprioriKeyProbabilities[column] = ui->tableOfAprioriKeyProbability_Rect->item(row, column)->text().toFloat();
}

void MainWindow::on_tableOfAprioriKeyProbability_Rect_2_cellChanged(int row, int column)
{
    aprioriKeyProbabilities[column] = ui->tableOfAprioriKeyProbability_Rect_2->item(row, column)->text().toFloat();
}






void MainWindow::generateDifferenceBetweenAprAndApostMessageProbabilities()
{
    const unsigned int countOfCryptograms = differenceBetweenAprAndApostMessageProbabilities.getCountOfRows();
    const unsigned int countOfMessages = differenceBetweenAprAndApostMessageProbabilities.getCountOfColumns();

    for(unsigned int cryptogramRow = 0; cryptogramRow < countOfCryptograms; cryptogramRow++)
    {
        for(unsigned int messageColumn = 0; messageColumn < countOfMessages; messageColumn++)
        {
            differenceBetweenAprAndApostMessageProbabilities.setAt(
                        cryptogramRow,
                        messageColumn,
                        aposterioriMessageProbabilities.getAt(cryptogramRow, messageColumn) - aprioriMessageProbabilities[messageColumn]);
        }
    }
}

void MainWindow::on_generateTableOfDifferenceBetweenAprAndApostMessageProbabilitiesButton_Square_clicked()
{
    generateDifferenceBetweenAprAndApostMessageProbabilities();
    writeMatrixToTable(differenceBetweenAprAndApostMessageProbabilities, ui->tableOfDifferenceBetweenAprAndApostMessageProbabilities_Square);
}

void MainWindow::on_generateTableOfDifferenceBetweenAprAndApostMessageProbabilitiesButton_Rect_clicked()
{
    generateDifferenceBetweenAprAndApostMessageProbabilities();
    writeMatrixToTable(differenceBetweenAprAndApostMessageProbabilities, ui->tableOfDifferenceBetweenAprAndApostMessageProbabilities_Rect);
}

void MainWindow::on_generateTableOfDifferenceBetweenAprAndApostMessageProbabilitiesButton_Rect_2_clicked()
{
    generateDifferenceBetweenAprAndApostMessageProbabilities();
    writeMatrixToTable(differenceBetweenAprAndApostMessageProbabilities, ui->tableOfDifferenceBetweenAprAndApostMessageProbabilities_Rect_2);
}






void MainWindow::generateRatiosBetweenApostKeyProbAndAprMesProb()
{
    const unsigned int countOfKeys = ratiosBetweenApostKeyProbAndAprMesrob.getCountOfRows();
    const unsigned int countOfCryptograms = ratiosBetweenApostKeyProbAndAprMesrob.getCountOfColumns();

    for(unsigned int keyRow = 0; keyRow < countOfKeys; keyRow++)
    {
        for(unsigned int cryptogramColumn = 0; cryptogramColumn < countOfCryptograms; cryptogramColumn++)
        {
            // Calculate P(Kj)
            double PKj = aprioriKeyProbabilities[keyRow];

            // Calculate PKj(Es)
            double PKjEs = 0.0;
            const unsigned int countOfMessages = aprioriMessageProbabilities.size();
            for(unsigned int message = 0; message < countOfMessages; message++)
            {
                if(tableOfFunction.getAt(keyRow, message) == cryptogramColumn+1)
                {
                    PKjEs += aprioriMessageProbabilities[message];
                }
            }
            //qDebug() << PKjEs;

            // Calculate P(Es)
            double PEs = 0;
            for(unsigned int innerKeyRow = 0; innerKeyRow < countOfKeys; innerKeyRow++)
            {
                for(unsigned int innerMessageColumn = 0; innerMessageColumn < countOfMessages; innerMessageColumn++)
                {
                    if(tableOfFunction.getAt(innerKeyRow, innerMessageColumn) == cryptogramColumn+1)
                    {
                        PEs += aprioriKeyProbabilities[innerKeyRow] * aprioriMessageProbabilities[innerMessageColumn];
                    }
                }
            }

            // Calculate PEs(Kj)
            double PEsKj = PKj * PKjEs / PEs;

            // Find message
            //unsigned int message = 0;
            for(unsigned int innerMessageColumn = 0; innerMessageColumn < countOfMessages; innerMessageColumn++)
            {
                if(tableOfFunction.getAt(keyRow, innerMessageColumn) == cryptogramColumn+1)
                {
                    ratiosBetweenApostKeyProbAndAprMesrob.setAt(keyRow,
                                                                cryptogramColumn,
                                                                PEsKj / aprioriMessageProbabilities[innerMessageColumn]);
                    break;
                }
            }
        }
    }


}

void MainWindow::on_generateTableOfRatiosBetweenApostKeyProbAndAprMesProbButton_Square_clicked()
{
    generateRatiosBetweenApostKeyProbAndAprMesProb();
    writeMatrixToTable(ratiosBetweenApostKeyProbAndAprMesrob, ui->tableOfRatiosBetweenApostKeyProbAndAprMesProb_Square);
}

void MainWindow::on_generateTableOfRatiosBetweenApostKeyProbAndAprMesProbButton_Rect_clicked()
{
    generateRatiosBetweenApostKeyProbAndAprMesProb();
    writeMatrixToTable(ratiosBetweenApostKeyProbAndAprMesrob, ui->tableOfRatiosBetweenApostKeyProbAndAprMesProb_Rect);
}

void MainWindow::on_generateTableOfRatiosBetweenApostKeyProbAndAprMesProbButton_Rect_2_clicked()
{
    generateRatiosBetweenApostKeyProbAndAprMesProb();
    writeMatrixToTable(ratiosBetweenApostKeyProbAndAprMesrob, ui->tableOfRatiosBetweenApostKeyProbAndAprMesProb_Rect_2);
}






void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
    case 0:
        switchToSquare();
        break;
    case 1:
        switchToRectangle();
        break;
    case 2:
        switchToRectangle_2();
        break;
    default:
        break;
    }
}
