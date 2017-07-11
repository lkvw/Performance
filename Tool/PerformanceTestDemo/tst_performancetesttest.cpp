#include <QString>
#include <QtTest>
#include <QLibrary>
#include "GSPCore.h"
#include "GSPEngineUtils.h"

int loadGspDll()
{
    QString cusFuncDllPath = QCoreApplication::applicationDirPath() + "/GBQ.CustomFunctionsd.dll";

    QLibrary cusFuncLib(cusFuncDllPath);

    typedef void (*GBQInitEngineFunc)(const QString &engineDLLName);
    GBQInitEngineFunc pInitEngineFunc = (GBQInitEngineFunc)cusFuncLib.resolve("initEngine");

    typedef void (*GBQRegisterCustomFunctionFunc)(IGEPEngine *gepEngine);
    GBQRegisterCustomFunctionFunc pRegCusFunctionFunc = (GBQRegisterCustomFunctionFunc)cusFuncLib.resolve("Register");

    if (NULL == pInitEngineFunc || NULL == pRegCusFunctionFunc)
    {
        cusFuncLib.unload();
        return -1;
    }

    QString gspEngineDllPath =  QCoreApplication::applicationDirPath() + "/GSPEngined.dll";

    pInitEngineFunc(gspEngineDllPath);

    GEPEngine engine = gspEngine().defaultGEPEngine();
    pRegCusFunctionFunc(engine.p);

    return 0;
}

/*
 * 0.0018 msecs per iteration (total: 60, iterations: 32768)
 * 表示测试共进行了 32768 次，共耗时 60 毫秒，每次测试的平均时间为0.0018毫秒
*/

class PerformanceTestTest : public QObject
{
    Q_OBJECT

public:

    PerformanceTestTest();

private Q_SLOTS:

    void initTestCase();

    void test_findTable_1();
    void test_findTable_2();

    void test_masterRecord_1();
    void test_masterRecord_2();

private:
    GSPModel testModel;
};

PerformanceTestTest::PerformanceTestTest()
{

}

void PerformanceTestTest::initTestCase()
{
    if (!loadGspDll())
    {
        testModel = gspEngine().createModel();
        GSPModelPersistent(testModel).loadFromFile(QCoreApplication::applicationDirPath() + "/GBQ_39.gsp");
    }
}

void PerformanceTestTest::test_findTable_1()
{
    QBENCHMARK
    {
        testModel.findTable("BusinessDB","FBFX:NormItem");
    }
}

void PerformanceTestTest::test_findTable_2()
{
    QBENCHMARK
    {
        testModel[0].findTable("FBFX:NormItem");
    }
}

void PerformanceTestTest::test_masterRecord_1()
{
    GSPTable FBFXNormItemTable  = testModel[0].findTable("FBFX:NormItem");

    QBENCHMARK
    {
        FBFXNormItemTable[0].masterRecord("~PID");
    }
}

void PerformanceTestTest::test_masterRecord_2()
{
    GSPTable FBFXNormItemTable  = testModel[0].findTable("FBFX:NormItem");

    QBENCHMARK
    {
        FBFXNormItemTable[0].findField("PID").masterRecord();
    }
}

QTEST_MAIN(PerformanceTestTest)

#include "tst_performancetesttest.moc"
