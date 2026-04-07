# 1. 設定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 定義專案名稱
project("oop-project")

# 3. 設定 C++ 標準 (建議使用 C++17，這對之後的隨機數或現代語法比較友善)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 尋找專案中的原始碼檔案
# 這裡手動列出所有需要編譯的檔案，確保編譯器知道要找誰
set(SOURCE_FILES 
    main.cpp 
    Player.cpp 
    Player.h
    Dice.cpp
    Dice.h
    Cell.cpp
    Cell.h
)

# 5. 建立執行檔 (Executable)
# 第一個參數是你想生成的程式名稱，後面是剛才定義的檔案清單
add_executable(MonopolyGame ${SOURCE_FILES}  "Map.cpp" "Map.h" "UI.cpp" "UI.h")

# 6. (選用) 如果你的 .h 檔在不同資料夾，可以加入這行
# target_include_directories(MonopolyGame PUBLIC ${CMAKE_CURRENT_SOURCE_SET})

# 7. 印出訊息（除錯用，會在 VS 下方的輸出視窗看到）
message(STATUS "大富翁專案配置完成！準備編譯輸出：MonopolyGame")