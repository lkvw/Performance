# GSP 相似接口性能比较

```
/*
 * 0.0018 msecs per iteration (total: 60, iterations: 32768)
 * 表示测试共进行了 32768 次，共耗时 60 毫秒，每次测试的平均时间为0.0018毫秒
*/
```

-  查找表操作
```
testModel.findTable("BusinessDB","FBFX:NormItem"); // 0.0028 msecs per iteration (total: 93, iterations: 32768)
testModel[0].findTable("FBFX:NormItem");           // 0.0018 msecs per iteration (total: 61, iterations: 32768)
```

- 查找外键记录操作
```
FBFXNormItemTable[0].masterRecord("~PID");             // 0.28 msecs per iteration (total: 74, iterations: 256)
FBFXNormItemTable[0].findField("PID").masterRecord();  // 0.0028 msecs per iteration (total: 93, iterations: 32768)
```

- 查找主键记录操作
```
srcFBFXNormItemTable.locate("NormItemID", 24128);  // 0.0021 msecs per iteration (total: 71, iterations: 32768)
srcFBFXNormItemTable.findByID(24128);              // 0.000085 msecs per iteration (total: 90, iterations: 1048576)
```
- 表达式有效性检查
```
// 求值异常捕获的方式检查有效性
srcFBFXNormItemTable[0].evalExpr("1.231*3"); // 0.029 msecs per iteration (total: 61, iterations: 2048)
srcFBFXNormItemTable[0].evalExpr("1.231");   // 0.31 msecs per iteration (total: 80, iterations: 256)

srcFBFXNormItemTable.tableSchema().checkExpr("1.231*3", dtDouble); // 0.026 msecs per iteration (total: 55, iterations: 2048)
srcFBFXNormItemTable.tableSchema().checkExpr("1.231", dtDouble);  //  0.012 msecs per iteration (total: 53, iterations: 4096)
```

- 检索是否存在符合某个条件的记录
```
// 返回符合条件记录列表的方式
GSPRecordList oRecList = oResourceDetail.createRecordList("Quantity <> 0");
bGBCCompare = oRecList.count() > 0;

// locateEx 方式
GSPRecord oRecord = oResourceDetail.locateEx(GString("Quantity <> 0"));
if (NULL != oRecord)
{
    bGBCCompare = true;
}
```
