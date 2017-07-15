import glob

env = Environment(
    CPPFLAGS='-O2 -g -std=c++11',
    CPPPATH=['./', 'third_party/include/'],
    LIBPATH=['third_party/lib'],
    LIBS=['glog', 'gtest'])
source = glob.glob('*.cc')
env.Program('test', source)
