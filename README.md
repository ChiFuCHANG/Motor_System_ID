微控制器：STM32F446RE 

軟體：STM32CubeMX, STM32CubeIDE, Matlab, WCHSerialPort 

其他硬體：L298N馬達驅動版、祥儀12V直流馬達（內建編碼器） 

控制目標：完成system identification，並利用ode45模擬其pid定點控制。 

實現： 
1. 使用一週期為PI/2、振幅為12的正弦波，當作開迴路系統的輸入，並蒐集馬達的輸出，取樣頻率為1000(Hz)。
2. 位置與速度的訊號，皆使用一階低通濾波器過濾雜訊。
3. 透過uart dma將時間、位置、速度與控制輸入的資訊傳入電腦，使用的serial tool為WCHSerialProt。
4. 利用matlab解析filtered.txt檔案，將頭5001筆輸入與輸出的資料，建立成arx模型。
5. arx模型的discrete-time型式為：y(k) + a1 * y(k - 1) + a2 * y(k - 2) = b1 * u(k - 1) , k = 2 ~ 5001
6. 利用最小平方法計算arx模型的係數(a1, a2, b0)，將其轉換為continuous-time型式。
7. 使用ode45模擬此系統的定點控制，控制演算法為pid控制。
