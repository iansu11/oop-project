# 物件導向程式設計專題-大富翁遊戲
## 第15組
## 資工系 1B
## 組長:蘇詠翔   組員:呂宇恩、鍾奕萱

## 程式介紹
這是一個使用 C++ 開發的終端機版本的大富翁遊戲。遊戲設計使用了多個物件導向的概念（如封裝、繼承、多型等），並將地圖、玩家、機會命運卡片、骰子、規則等各自獨立為類別進行管理，提高了程式的擴展性與可讀性。玩家可以在遊戲中透過擲骰子移動，購買土地、收過路費、抽取機會命運、使用免坐牢卡，並運用策略成為最終的贏家。

## 遊戲規則
1. **遊戲人數**：支援 2 到 4 名玩家同時遊玩。
2. **遊戲模式**：提供三種不同的遊玩模式供玩家選擇：
   - **1.回合制**：玩家設定總回合數，回合結束時總資產最高的玩家獲勝。
   - **2.目標制**：玩家設定一個目標金額，最先達到該總資產的玩家獲勝。
   - **3.破產制**：遊戲持續進行，直到剩下最後一名未破產的玩家獲勝。超過20回合後玩家也可選擇提前結束遊戲並結算資產。
3. **地圖機制**：
   - 每次經過起點可獲得新一圈的獎金 2000 元。
   - 走到空地可選擇購買，若走到他人土地則需支付過路費。
   - 走到監獄，將暫停遊玩3回合，除非擁有並使用「免坐牢卡」。
   - 有各10種不同的機會、命運可以抽取，將依據所抽到的內容自動執行相對應的結果。
4. **破產機制**：當玩家現金不足以支付過路費或罰款，將先啟動變賣自己所擁有的土地機制，若仍無力償還時將宣告破產並退出遊戲。

## 玩法
1. 啟動程式後，首先輸入遊玩人數（2-4人）。
2. 依序輸入每位玩家的名稱。
3. 選擇想要的遊戲模式（1. 回合制 | 2. 目標制 | 3. 破產制）並根據提示設定相關參數。
4. 遊戲開始後，輪到你的回合時，按下 `[D]` 鍵擲骰子。
5. 根據角色踩到的格子，程式會自動觸發對應的事件，並適時需要玩家進行操作（如詢問是否購買土地、支付過路費、興建房屋、抽取機會命運等）。
6. 遊戲會自動進行資產計算與回合推進，當觸發遊戲模式的勝利條件時，遊戲結束並公佈最終贏家及總資產排名。

## 程式如何安裝執行

1. 進入github點選右上角綠色的code，列表出來後點選下方的DownLoad ZIP
 
   <img width="575" alt="安裝1" src="https://github.com/user-attachments/assets/8af5669d-7d36-4412-bbe6-5102e317029e" />
   
2. 下載完壓縮檔案，按右鍵選取解壓縮全部

   <img width="400" height="174" alt="安裝2" src="https://github.com/user-attachments/assets/29e24489-1089-44a0-998a-17b187f7cfae" />
   
3. 開啟 Visual Studio，點選右側開啟資料夾

   <img width="223" height="155" alt="安裝3" src="https://github.com/user-attachments/assets/27b1dd81-2d04-4579-8573-1dd3a4905fa4" />

4. 選擇檔案的資料夾

   <img width="700" alt="安裝4" src="https://github.com/user-attachments/assets/00bd0e7e-d093-4a58-ac24-4b3f37b9203b" />

5. 選取CMakeList.txt檔

   <img width="750" alt="安裝5" src="https://github.com/user-attachments/assets/de0c39c4-170f-4df8-af28-0367de04bf13" />

6. 按下 Visual Studio的執行按鍵
   
    <img width="431" height="100" alt="安裝6" src="https://github.com/user-attachments/assets/b9c7822c-9697-44fb-b0d0-0d43625e8a47" />

7. 可以開始執行

   <img width="733" height="266" alt="安裝7" src="https://github.com/user-attachments/assets/cd18ec24-3ce0-4329-b066-1bcb557b0550" />

## UML圖
   <img width="785" height="465" alt="UML大綱架構" src="https://github.com/user-attachments/assets/c23ebd42-2e48-4020-b8e5-cb0ac0e42ef8" />

   <img width="286" height="181" alt="螢幕擷取畫面 2026-06-06 104104" src="https://github.com/user-attachments/assets/cedb6ecf-aa70-4829-89b2-e0b3ba324531" />
   <img width="204" height="299" alt="螢幕擷取畫面 2026-06-06 104024" src="https://github.com/user-attachments/assets/cf5d550c-9764-4285-b375-36629a6b7ecd" />
   <img width="677" height="151" alt="螢幕擷取畫面 2026-06-06 103003" src="https://github.com/user-attachments/assets/f9ad2299-6152-438e-baaf-f54d209d6ed3" />
   <img width="681" height="142" alt="螢幕擷取畫面 2026-06-06 104149" src="https://github.com/user-attachments/assets/e00944da-a801-4bc0-8bc2-c65e750df238" />
   <img width="682" height="213" alt="螢幕擷取畫面 2026-06-06 104445" src="https://github.com/user-attachments/assets/101b3ddb-f959-4698-b1cf-955d1334e12a" />
   <img width="587" height="333" alt="螢幕擷取畫面 2026-06-06 104527" src="https://github.com/user-attachments/assets/532cf28c-f955-4979-afb2-eff09735dc93" />
   <img width="366" height="640" alt="螢幕擷取畫面 2026-06-06 104643" src="https://github.com/user-attachments/assets/050f3b5a-622c-4504-bd7a-b0fbed043f6e" />
   <img width="682" height="400" alt="螢幕擷取畫面 2026-06-06 104857" src="https://github.com/user-attachments/assets/fe7a3b2b-802d-4312-833b-3dd509ec21b5" />
   <img width="783" height="124" alt="螢幕擷取畫面 2026-06-06 104956" src="https://github.com/user-attachments/assets/c2f21002-e034-4769-a490-899ae813338f" />
   <img width="782" height="114" alt="螢幕擷取畫面 2026-06-06 105241" src="https://github.com/user-attachments/assets/961c60be-238b-4f66-b474-1f41047fdec7" />
   <img width="773" height="112" alt="螢幕擷取畫面 2026-06-06 105045" src="https://github.com/user-attachments/assets/b4780bdb-b983-4a06-9520-91e62cf70beb" />
   <img width="781" height="112" alt="螢幕擷取畫面 2026-06-06 105107" src="https://github.com/user-attachments/assets/04f0eef9-ff8c-4c6e-a729-900bbacffa96" />
   <img width="775" height="110" alt="螢幕擷取畫面 2026-06-06 105128" src="https://github.com/user-attachments/assets/0ec582aa-843f-4c29-9aa9-dae37484cd4b" />
   <img width="773" height="109" alt="螢幕擷取畫面 2026-06-06 105149" src="https://github.com/user-attachments/assets/0add3c79-1d7b-43e0-ba58-fb166e5349ae" />

## 運行畫面截圖
## ● 開始畫面
  <img width="1195" height="373" alt="開始畫面-2" src="https://github.com/user-attachments/assets/e5ca2566-c40e-4673-995f-c8a4c23f7777" />

## ● 購買土地
   <img width="635" height="134" alt="購買土地-2" src="https://github.com/user-attachments/assets/f8fd85f0-6cff-4690-9303-a213698c24f9" />

## ● 收過路費/破產機制
   <img width="783" height="353" alt="過路費破產-2" src="https://github.com/user-attachments/assets/d86e223a-2c4d-43f7-aca1-3779418f3dad" />

## ● 興建房屋
   <img width="935" height="121" alt="興建房屋內容-2" src="https://github.com/user-attachments/assets/219eb13c-71fa-48e4-9ada-b0ebf1623e89" />
   
## ● 抽取機會/命運
   <img width="410" height="151" alt="機會-2" src="https://github.com/user-attachments/assets/8fcd7046-ca25-45ca-9d69-5faa5bb02bc4" />
   <img width="365" height="150" alt="命運-2" src="https://github.com/user-attachments/assets/01de75b3-79f2-4ff9-940f-a008d88b228a" />

## ● 遊戲結束畫面
   <img width="599" height="712" alt="結束畫面-2" src="https://github.com/user-attachments/assets/a687a463-03e4-4b02-ac74-e44949c76dbd" />
## 操作影片連結
   https://drive.google.com/drive/u/1/home

## 分工資訊
   - **蘇詠翔:** 主要程式碼、簡報製作。
   - **呂宇恩:** html javascript 介面製作、簡報協作、程式碼協助測試除錯。
   - **鍾奕萱:** 簡報協作、程式碼協助測試除錯。
