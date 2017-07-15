# leetcode的一些代码，包含google单元测试
# clone本工程
  git clone https://github.com/yangguangxu/leetcode.git
# 编译环境安装
  采样sconstruct作为编译工具，比make file好用很多
## ubuntu安装
  sudo apt-get install scons
## mac安装
  sudo brew install scons
# 编译项目代码
  到工程目录运行命令：scons
# 运行程序
  scons会生成一个leetcode的二进制文件，直接./leetcode即可运行所有完成过的leetcode题目
## 查看目前完成的题目
   ./leetcode --gtest_list_tests
## 只运行运行某个题目的测试：
   ./leetcode --gtest_filter=LeetCode.Add_Two_Numbers
  （运行Add Tow Numbers的测试）
