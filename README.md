#动物群体行为快照


* [题目介绍](#题目介绍)
* [解题思路](#解题思路)
* [文件说明](#文件说明)
* [接口说明](#接口说明)
 * [AnimalGroupInfo](#AnimalGroupInfo)
 * [Util](#Util)
* [使用说明](#使用说明)
* [源码下载](#源码下载)
* [其他](#其他)


<a name="题目介绍"></a>
## 题目介绍

动物学家研究动物群体行为的一种方式是将信号发射器安转到动物身上，然后追踪动物在一定区域内的活动路线。科学家不但希望了解动物的活动路线，而且希望了解任意一个指定时间点上所有动物的分布。

假设现在又多个动物在指定区域活动。为了节省存储，科学家并未存储每一时刻动物的分布快照，而是存储当前时刻与上一时刻的变化。假设每一个动物位置由 x, y两个整数坐标，则规定以下存储格式：

* 第一行代表当前时刻的全局唯一Id(非空字符串，不包含空格，假设全局唯一)
* 第二行是当前时刻，格式为YYYY/mm/dd hh:MM:ss（2016/12/01 23:02:05）
* 第三行开始是各种动物的坐标变化，一个动物占用一行。变化形式有两种：

 * 第一种形式：{ 动物Id } { x坐标 } { y坐标 }。这种形式说明动物第一次出现在这个区域。
 * 第二种形式：{ 动物Id } { 上一时刻x坐标 } { 上一时刻y坐标 } { x坐标变化量 } { y坐标变化量 }。这种形式说明该动物在之前已经位于这个区域了，其上一时刻的坐标用于校验，二坐标变化量为正/负整数形式。

* 所有的数据全部在存储在一个字符串historyData中。

<b>例如</b>

e4e87cb2-8e9a-4749-abb6-26c59344dfee<br/>
2016/09/02 22:30:46<br/>
cat1 10 9

351055db-33e6-4f9b-bfe1-16f1ac446ac1<br/>
2016/09/02 22:30:52<br/>
cat1 10 9 2 -1<br/>
cat2 2 3

dcfa0c7a-5855-4ed2-bc8c-4accae8bd155<br/>
2016/09/02 22:31:02<br/>
cat1 12 8 3 4

<b>要求</b>

请编写一个函数，输入是上述字符串，和当前时刻的Id,输出为字符串。例如：
* Javascript: getSnapshot(historyData, id)
* Java: Srting getSnapshot(String historyData, String id)
* C#: string GetSnapshot(string historyData, string id)

输出该Id代表的时刻的定位的坐标快照
生成某一个时刻的所有动物的坐标快照。并将坐标按照 {动物Id} {x} {y} 的格式输出。输出时按照动物Id排升序。

例如，针对范例历史数据，当 id 为 dcfa0c7a-5855-4ed2-bc8c-4accae8bd155 时，输出内容如下： 

cat1 15 12<br/>
cat2 2 3

<b>验证输入信息</b>

程序应当验证输入有效性。

当 historyData 的格式不符合要求时输出
Invalid format.

若 historyData 数据存在问题，如下
e4e87cb2-8e9a-4749-abb6-26c59344dfee<br/>
2016/09/02 22:30:46<br/>
cat1 10 9

351055db-33e6-4f9b-bfe1-16f1ac446ac1<br/>
2016/09/02 22:30:52<br/>
cat1 10 9 2 -1<br/>
cat2 2 3

dcfa0c7a-5855-4ed2-bc8c-4accae8bd155<br/>
2016/09/02 22:31:02<br/>
cat1 11 8 3 4

则输出为
Conflict found at dcfa0c7a-5855-4ed2-bc8c-4accae8bd155

若有多个错误，则只需输出第一个即可。

<a name="解题思路"></a>
## 解题思路
### 输入
对 historyData 做简单处理，每一行末尾添加 \\n 换行，每一块数据区域后添加 \\n 作为结束标志，如：<br/>
```
string data = "e4e87cb2-8e9a-4749-abb6-26c59344dfee\n" +
                "2016/09/02 22:30:46\n" +
                "cat1 10 9\n\n" +
                "351055db-33e6-4f9b-bfe1-16f1ac446ac1\n" +
                "2016/09/02 22:30:52\n" +
                "cat1 10 9 2 -1\n" +
                "cat2 2 3\n";
```

### 输入验证
对于全局唯一的 Id，使用正则表达式匹配：<br />
```
string guidRegex = @"^[A-Za-z0-9]{8}-[A-Za-z0-9]{4}-[A-Za-z0-9]{4}-[A-Za-z0-9]{4}-[A-Za-z0-9]{12}$";
```
对于时间，首先使用正则表达式匹配格式，然后使用内建方法验证合法性：<br/>
```
string datetimeRegex = @"^\d{4}/\d{2}/\d{2} \d{2}:\d{2}:\d{2}$";
```
对于动物坐标信息，则先以空格分割，判断其长度为 3 或 5，然后进行相应的验证。

### 对象设计
* 动物及其坐标信息类：
按 { 动物Id } { 上一时刻x坐标 } { 上一时刻y坐标 } { x坐标变化量 } { y坐标变化量 } 形式统一设计，
无 x/y 变化量时用 0 代替。
* 某一时刻动物群体状态类：按  { 全局Id } { 时间 } { List<动物及其坐标信息> } 方式设计。

### 算法设计
* 首先，读入一条 { 某一时刻动物群体状态 } 信息，同时计算并保存该时刻的 { 动物群体快照 }；
* 循环读入 { 某一时刻动物群体状态 } 信息，并更新  { 动物群体快照 }；
* 当 { 全局Id } 与 输入 id 相匹配时，保存该时刻的动物群体快照，作为返回值；
* 继续读入信息，并更新动物群体快照，直至数据全部处理完成；
* 若无错误，则返回保存的返回值快照；否则，返回错误。


<a name="文件说明"></a>
## 文件说明
* AnimalGroupBehavior　　　　　　 项目工程文件
 * AnimalCoordinate.cs　　　　　　动物坐标及坐标变化状态类
 * AnimalStatus.cs　　　　　　　　某一时刻动物群体坐标变化的相关信息类
 * AnimalGroupInfo.cs　　　　　　 动物群体信息处理类
 * Util.cs　　　　　　　　　　　　工具类
 * Program.cs　　　　　　　　　　 项目运行入口

* AnimalGroupBehaviorTest　　　　 测试工程文件
 * UtilTest.cs　　　　　　　　　　工具测试类
 * AnimalGroupTest.cs　　　　　　 动物群体信息处理测试类

<a name="接口说明"></a>
## 接口说明
<a name="AnimalGroupInfo"></a>
### AnimalGroupInfo
* AnimalStatusList：动物群体状态数据，即全部数据。
```
private List<AnimalStatus> AnimalStatusList;
```

* AnimalSnapshoot：动物群体最新时刻快照。
```
private AnimalStatus AnimalSnapshoot;
```

* GetSnapShot：题目要求实现方法，功能略。
```
public string GetSnapShot(string historyData, string id)
```

* GetSnapShotByGUID：根据输入全局ID，获取该时刻的动物群体快照。该方法仅在上一方法执行后有效，即必须先输入 historyData 信息。
```
public string GetSnapShotByGUID(string guid)
```

* UpdateSnapshoot：更新某一时刻动物群体快照。每次读入数据时均执行方法，可以避免在获取快照信息时对全部数据进行扫描。
```
private bool UpdateSnapshoot(AnimalStatus status, out string errorInfo)
```

* PrintSnapshoot：打印动物群体快照信息，并返回题目要求格式的字符串。
```
private string PrintSnapshoot(AnimalStatus snapshoot)
```

<a name="Util"></a>
### Util
* TryVerifyGUID：验证 GUID 是否有效。
```
public static bool TryVerifyGUID(string guid)
```

* TryVerifyDateTime：验证日期格式字符串是否正确。
```
public static bool TryVerifyDateTime(string dtstr, out DateTime datatime )
```

* TryVerifyCoordinate：验证动物坐标数据是否正确。
```
public static bool TryVerifyCoordinate(string costr, ref AnimalCoordinate coordinate)
```

<a name="使用说明"></a>
## 使用说明
### 运行环境
* Visual Studio 2013 及其以上版本
* 安装 Unit Test Generator 单元测试插件

### 运行方法
* 原项目
```
1. 打开工程文件 -> 调试 -> 启动调试，即可查看题目要求输出结果。
2. 更改 historyData 或 id 数据，然后运行，可查看相应输出结果。
```

* 测试项目
```
1. 打开 UtilTest.cs 或 AnimalGroupTest.cs 文件，在任意方法上右击 -> 运行测试，即可观察该方法的测试结果。
2. 测试 -> 运行 -> 所有测试，即可查看全部测试结果。
```

<a name="源码下载"></a>
## 源码下载

<a name="其他"></a>
## 其他
咨询邮箱：<twofly0313@gmail.com>



