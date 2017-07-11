# GSP 相似接口性能比较

-  查找表操作
```
testModel.findTable("BusinessDB","FBFX:NormItem"); // 0.0028 msecs per iteration (total: 93, iterations: 32768)
testModel[0].findTable("FBFX:NormItem");           // 0.0018 msecs per iteration (total: 61, iterations: 32768)
```

- 查找外键操作
```
FBFXNormItemTable[0].masterRecord("~PID");             // 0.28 msecs per iteration (total: 74, iterations: 256)
FBFXNormItemTable[0].findField("PID").masterRecord();  // 0.0028 msecs per iteration (total: 93, iterations: 32768)
```
