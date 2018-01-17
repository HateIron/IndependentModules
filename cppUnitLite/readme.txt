用法：
1、make 生成测试框架 frame.a，不带 main 函数.
	这种场景下，要使用外部的 main 函数
2、make main=1 会同时生成带 main 函数的 frame.a 和 ut.exe
    而且同时会运行 ./ut.exe,效果很拉风
3、CHECK_AND_SAVE 宏要依赖外部模块，外部模块自己实现
	AddFailStr(#CaseName)和AddSuccStr(#CaseName) 函数，
	这应该不是一件难事，而是一件很有意思的事情。
	如果没有外部实现也没有关系，只要不用这两个宏就可以了。
