# SConstruct
import os

env = Environment(CXX='g++')
env.Append(CXXFLAGS=['-std=c++17', '-Wall', '-Wextra', '-pedantic'])

# Homebrewのパスを確認
homebrew_path = '/opt/homebrew'
if os.path.exists(homebrew_path):
    print(f"Homebrew detected at {homebrew_path}")
    env.Append(CPPPATH=[f'{homebrew_path}/include'])
    env.Append(LIBPATH=[f'{homebrew_path}/lib'])
    
    # Homebrewのpkg-configパスを環境変数に追加
    if 'PKG_CONFIG_PATH' in os.environ:
        env['ENV']['PKG_CONFIG_PATH'] = f"{homebrew_path}/lib/pkgconfig:{os.environ.get('PKG_CONFIG_PATH', '')}"
else:
    print("Homebrew not detected, using default paths")
    env.Append(CPPPATH=['/usr/local/include'])
    env.Append(LIBPATH=['/usr/local/lib'])

env.Append(LIBS=['libzmq'])

env.Append(CXXFLAGS=[f'-I{inc}' for inc in env['CPPPATH']])

# pkg-configを使用してZeroMQの設定を取得（エラーハンドリングを追加）
try:
    # if os.system('pkg-config --exists libzmq') == 0:
        # print("Using pkg-config for ZeroMQ")
        env.ParseConfig('pkg-config --cflags --libs libzmq')
        # env.ParseConfig('pkg-config --cflags --libs zmqpp')
    # else:
        # print("pkg-config for libzmq not found. Using specified paths.")
except:
    print("Error occurred while using pkg-config. Using specified paths.")

# ビルドターゲットの定義
targets = [
    'publisher', 'subscriber', 'requester', 'responder',
    'pusher', 'puller'
]
for target in targets:
    env.Program(target, f'{target}.cpp')