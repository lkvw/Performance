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
